#include "provided.h"
#include <map>
using namespace std;

// ##################################################################################################################
// AUXILIARY FUNCTION DECLARATIONS
// ##################################################################################################################

void printCoordinates(const GeoCoord& coord, double g = 0, double h = 0) {
    cout << coord.latitudeText << " " << coord.longitudeText << " " << g << " " << h << " " << g + h << endl;
}

// ##################################################################################################################
// PointToPointRouter Declaration
// ##################################################################################################################


class PointToPointRouterImpl {
    public:
        PointToPointRouterImpl(const StreetMap* sm);
        ~PointToPointRouterImpl();
        DeliveryResult generatePointToPointRoute(
            const GeoCoord& start,
            const GeoCoord& end,
            list<StreetSegment>& route,
            double& totalDistanceTravelled) const;
    private:
        const StreetMap* m_streetMap;

        // auxiliary functions for A* search algorithm
        bool checkCoords(const GeoCoord& start, const GeoCoord& end) const;
        GeoCoord findCurrentCoord(const map<GeoCoord, double>& openList, const GeoCoord& end) const;
};

PointToPointRouterImpl::PointToPointRouterImpl(const StreetMap* sm) 
    : m_streetMap(sm) {}

PointToPointRouterImpl::~PointToPointRouterImpl() {

}

DeliveryResult PointToPointRouterImpl::generatePointToPointRoute(
    const GeoCoord& start, const GeoCoord& end,
    list<StreetSegment>& route, double& totalDistanceTravelled) const {
    // finds an optimal route using the A* search algorithm
    // we use Euclidean distance as a heuristic

    // trivial case: starting coordinate is ending coordinate
    if (start == end) {
        route.clear();
        totalDistanceTravelled = 0;
        return DELIVERY_SUCCESS;
    }

    // checking for bad coordinates
    if (!checkCoords(start, end))
        return BAD_COORD;

    map<GeoCoord, GeoCoord> parents;
    map<GeoCoord, double> openList;        // initialising open list (maps GeoCoords to doubles representing g)
    map<GeoCoord, double> closedList;      // initialising closed list (maps GeoCoords to doubles representing g)

    // pushing starting coordinate onto open list
    openList[start] = 0;    // starting coordinate has zero g
    
    // variable to track current coordinate
    GeoCoord currentCoord = start;

    // while open list isn't empty
    while (!openList.empty()) {
        
        // finding current coord (i.e. coord with smallest f)
        currentCoord = findCurrentCoord(openList, end);
        double currentCoordG = openList[currentCoord];
        
        // removing current coord from open list
        openList.erase(currentCoord);

        // found the solution -> break
        if (currentCoord == end)
            break;

        // finding segments that start with current coordinate
        vector<StreetSegment> nextSegs;
        m_streetMap->getSegmentsThatStartWith(currentCoord, nextSegs);

        // updating parents and open list with next coordinates
        for (int i = 0; i != nextSegs.size(); i++) {
            
            // generating data about next coordinate
            const GeoCoord nextCoord = nextSegs[i].end;                                     // pointer to next geocoordinate
            const double newG = currentCoordG + distanceEarthMiles(currentCoord, nextCoord);         // change in g in this coordinate
                
            // bool to check whether parent of coord needs to be added/updated
            bool addCoordParent = true;

            map<GeoCoord, double>::iterator openListItr, closedListItr;
            openListItr = openList.find(nextCoord);
            closedListItr = closedList.find(nextCoord);

            // nextCoord is in open list
            if (openListItr != openList.end()) {
                // if newG is lesser, no need to update parent
                if (openListItr->second <= newG)
                    addCoordParent = false;
            }
            // nextCoord is in closed list
            else if (closedListItr != closedList.end()) {
                // if newG is lesser, no need to update parent
                if (closedListItr->second <= newG)
                    addCoordParent = false;
                // newG is greater -> move coordinate from closed list to open list
                else {
                    openList[nextCoord] = closedListItr->second;    // newG is greater, so no update
                    closedList.erase(closedListItr);
                }
            }
            // nextCoord not in open list or closed list -> put nextCoord in open list
            else 
                openList[nextCoord] = newG;

            // adding/updating parent
            if (addCoordParent)
                parents[nextCoord] = currentCoord;
        }

        // pushing current coordinate into closed list
        closedList[currentCoord] = currentCoordG;
    }

    // no route found
    if (currentCoord != end)
        return NO_ROUTE;

    // route found 
    totalDistanceTravelled = 0;
    route.clear();

    // calculate route by backtracking from end node via parents
    GeoCoord e = end;

    while (true) {

        // finding starting geocoordinate of current segment
        GeoCoord s = parents[e];

        // finding desired street segment (from s to e)
        vector<StreetSegment> segs;
        m_streetMap->getSegmentsThatStartWith(s, segs);
        // iterating over segs to find desired street segment
        for (int i = 0; i != segs.size(); i++) {

            if (segs[i].end == e) {
                route.push_front(segs[i]);
                totalDistanceTravelled += distanceEarthMiles(s, e);
                e = s;
                break;
            }
        }

        // base case: s = starting coordinate
        if (s == start)
            break;
    }
    return DELIVERY_SUCCESS;
}

// ##################################################################################################################
// AUXILIARY FUNCTION DEFINITIONS
// ##################################################################################################################

bool PointToPointRouterImpl::checkCoords(const GeoCoord& start, const GeoCoord& end) const {
    // checks whether coordinates are in the map data
    
    vector<StreetSegment> startSegs, endSegs;
    // if getSegmentsThatStartWith returns true, then that means there are segments associated with the coordinates
    if (m_streetMap->getSegmentsThatStartWith(start, startSegs) && m_streetMap->getSegmentsThatStartWith(end, endSegs))
        return true;

    // coordinates not in map
    return false;
}

GeoCoord PointToPointRouterImpl::findCurrentCoord(const map<GeoCoord, double>& openList, const GeoCoord& end) const {
    // retrieving geocoordinate in open list with smallest f (= h+g)

    // creating a map of GeoCoords to their f values
    map<GeoCoord, double> fValues;
    for (map<GeoCoord, double>::const_iterator itr = openList.cbegin(); itr != openList.cend(); itr++)
        fValues[itr->first] = itr->second + distanceEarthMiles(itr->first, end);

    // finding best coordinate (i.e. coordinate with smallest f value)
    GeoCoord bestCoord = fValues.cbegin()->first;
    double smallestF = fValues.cbegin()->second;
    for (map<GeoCoord, double>::const_iterator itr = fValues.cbegin(); itr != fValues.cend(); itr++)
        if (itr->second < smallestF) {
            bestCoord = itr->first;
            smallestF = itr->second;
        }

    // returning best coordinate
    return bestCoord; 
}
// ##################################################################################################################
// PointToPointRouter Functions
// ##################################################################################################################
// These functions simply delegate to PointToPointRouterImpl's functions.
// You probably don't want to change any of this code.

PointToPointRouter::PointToPointRouter(const StreetMap* sm)
{
    m_impl = new PointToPointRouterImpl(sm);
}

PointToPointRouter::~PointToPointRouter()
{
    delete m_impl;
}

DeliveryResult PointToPointRouter::generatePointToPointRoute(
        const GeoCoord& start,
        const GeoCoord& end,
        list<StreetSegment>& route,
        double& totalDistanceTravelled) const
{
    return m_impl->generatePointToPointRoute(start, end, route, totalDistanceTravelled);
}