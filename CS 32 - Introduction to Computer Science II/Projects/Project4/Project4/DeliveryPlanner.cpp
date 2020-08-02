#include "provided.h"
#include <vector>
using namespace std;

// ##################################################################################################################
// DELIVERYPLANNERIMPL DECLARATION
// ##################################################################################################################

class DeliveryPlannerImpl
{
public:
    DeliveryPlannerImpl(const StreetMap* sm);
    ~DeliveryPlannerImpl();
    DeliveryResult generateDeliveryPlan(
        const GeoCoord& depot,
        const vector<DeliveryRequest>& deliveries,
        vector<DeliveryCommand>& commands,
        double& totalDistanceTravelled) const;
    private:
        double findAngle(const GeoCoord& start, const GeoCoord& end) const;             // finds direction of end coordinate from start coordinate
        string findDirection(double dir) const;                                   // finds string direction given angle
        DeliveryResult generateMovementPlan(                                            // generates delivery plan from start location to end location
            const GeoCoord& s, const GeoCoord& e, 
            vector<DeliveryCommand>& commands, 
            const PointToPointRouter& route, 
            double& totalDistanceTravelled) const;
        const StreetMap* m_streetMap;
};

// ##################################################################################################################
// DELIVERYPLANNERIMPL IMPLEMENTATIONS
// ##################################################################################################################

DeliveryPlannerImpl::DeliveryPlannerImpl(const StreetMap* sm)
    : m_streetMap(sm) {}

DeliveryPlannerImpl::~DeliveryPlannerImpl()
{
}

DeliveryResult DeliveryPlannerImpl::generateDeliveryPlan(
    const GeoCoord& depot,
    const vector<DeliveryRequest>& deliveries,
    vector<DeliveryCommand>& commands,
    double& totalDistanceTravelled) const {

    // trivial case; no deliveries requested
    if (deliveries.size() == 0)
        return DELIVERY_SUCCESS;

    // resetting totalDistanceTravelled and commands vector
    commands.clear();
    totalDistanceTravelled = 0;

    // optimizing delivery planner
    DeliveryOptimizer optimizer(m_streetMap);       // delivery optimizer class
    double oldCrowDistance;
    double newCrowDistance;
    vector<DeliveryRequest> optimalDeliveries = deliveries;
    optimizer.optimizeDeliveryOrder(depot, optimalDeliveries, oldCrowDistance, newCrowDistance);
        // modify optimalDeliveries to optimal deliveries plan

    // creating router
    PointToPointRouter router(m_streetMap);

    // default starting and ending coordinates
    GeoCoord s = depot;
    GeoCoord e = optimalDeliveries.front().location;
    
    // iterating over deliveries to attempt deliveries (all movement from depot to last delivery location is covered in this loop)
    for (int i = 0; i != optimalDeliveries.size(); i++) {

        // determining ending coordinate    
        e = optimalDeliveries[i].location;
        string item = optimalDeliveries[i].item;
        
        // generating movement result for current delivery (DELIVERY_SUCCESS if delivery worked; BAD_COORD or NO_ROUTE if it didn't)
        DeliveryResult movementResult = generateMovementPlan(s, e, commands, router, totalDistanceTravelled);

        // checking whether delivery worked
        switch (movementResult) {
            case BAD_COORD: return BAD_COORD;
            case NO_ROUTE: return NO_ROUTE;
            case DELIVERY_SUCCESS: break;       // not necessary, but avoids an unused enumeration value warning
        }

        // deliver successful -> generate delivery command
        DeliveryCommand delivery; 
        delivery.initAsDeliverCommand(item);
        commands.push_back(delivery);

        // updating s
        s = e;
    }

    // attempt movement from last delivery location to depot
        // we update commands and totalDistanceTravelled if all goes well, and return NO_ROUTE if no route found
    return generateMovementPlan(optimalDeliveries.back().location, depot, commands, router, totalDistanceTravelled);
}

// ##################################################################################################################
// AUXILIARY FUNCTIONS
// ##################################################################################################################

DeliveryResult DeliveryPlannerImpl::generateMovementPlan(
    const GeoCoord& s, const GeoCoord& e,
    vector<DeliveryCommand>& commands,
    const PointToPointRouter& router,
    double& totalDistanceTravelled) const {
    // generates delivery plan from start location to end location
    
    list<StreetSegment> route;              // list of street segments that make up route from s to e
    double routeDistanceTravelled;          // distance travelled along route from s to e
    vector<DeliveryCommand> routeCommands;  // commands to follow to move from s to e

    // generating point to point route
    DeliveryResult result = router.generatePointToPointRoute(s, e, route, routeDistanceTravelled);

    // checking whether delivery worked
    switch (result) {
        case BAD_COORD: return BAD_COORD;
        case NO_ROUTE: return NO_ROUTE; 
        case DELIVERY_SUCCESS: break;       // not necessary, but avoids an unused enumeration value warning
    }

    // delivery worked -> generating movement commands
    for (list<StreetSegment>::const_iterator itr = route.cbegin(); itr != route.cend(); itr++) {

        // finding current segment, direction in and length of current segment
        double angle = findAngle(itr->start, itr->end);
        string dir = findDirection(angle);
        double segmentDist = distanceEarthMiles(itr->start, itr->end);
        
        // generating delivery command
        DeliveryCommand command;

        // base case -> if current route segment is the first, generate proceed command
        if (routeCommands.size() == 0)
            command.initAsProceedCommand(dir, itr->name, segmentDist);
            
        // not first movement -> checking whether we're moving along the same street as previous command
        else if (routeCommands.back().streetName() == itr->name) {
                // increase distance travelled along the street instead of generating a new proceed command
                routeCommands.back().increaseDistance(segmentDist);
                continue;   // continue onto next iteration, since we're not creating any new commands
        }

        // different streets -> check whether command should be to proceed or to turn
        else {
            
            // iterator to previous segment
            list<StreetSegment>::const_iterator prevItr = itr; prevItr--;

            // finding difference in angles between current and previous segment
            double prevAngle = findAngle(prevItr->start, prevItr->end);
            double angleDifference = prevAngle - angle;
            
            // no significant angle difference -> proceed onto new street
            if (abs(angleDifference) < 1 || abs(angleDifference) > 359)
                command.initAsProceedCommand(findDirection(angle), itr->name, segmentDist);

            // significant angle difference -> generate turn command
            else {
                // creating turn command
                DeliveryCommand turnCommand;

                if (angleDifference <= 0 || angleDifference >= 180)
                    turnCommand.initAsTurnCommand("left", itr->name);
                else // if (angleDifference <= 359)
                    turnCommand.initAsTurnCommand("right", itr->name);

                routeCommands.push_back(turnCommand);
                command.initAsProceedCommand(findDirection(angle), itr->name, segmentDist);
            }
        }

        // pushing movement command
        routeCommands.push_back(command);
    }

    // pushing delivery commands onto commands
    for (int i = 0; i != routeCommands.size(); i++)
        commands.push_back(routeCommands[i]);
    
    // updating distance travelled
    totalDistanceTravelled += routeDistanceTravelled;
    return DELIVERY_SUCCESS;
}

double DeliveryPlannerImpl::findAngle(const GeoCoord& start, const GeoCoord& end) const {
    double angle = atan2(end.latitude - start.latitude, end.longitude - start.longitude) * 180 / (4 * atan(1.0));
    if (angle < 0)
        angle += 360;
    return angle;
}

string DeliveryPlannerImpl::findDirection(double dir) const {
    if (dir < 0)
        return "INVALID DIRECTION";
    else if (dir < 22.5)    return "east";
    else if (dir < 67.5)    return "northeast";
    else if (dir < 112.5)   return "north";
    else if (dir < 157.5)   return "northwest";
    else if (dir < 202.5)   return "west";
    else if (dir < 247.5)   return "southwest";
    else if (dir < 292.5)   return "south";
    else if (dir < 337.5)   return "southeast";
    else                    return "east";
}

// ##################################################################################################################
// DELIVERYPLANNER FUNCTIONS
// ##################################################################################################################
//******************** DeliveryPlanner functions ******************************

// These functions simply delegate to DeliveryPlannerImpl's functions.
// You probably don't want to change any of this code.

DeliveryPlanner::DeliveryPlanner(const StreetMap* sm) {
    m_impl = new DeliveryPlannerImpl(sm);
}

DeliveryPlanner::~DeliveryPlanner() {
    delete m_impl;
}

DeliveryResult DeliveryPlanner::generateDeliveryPlan(
    const GeoCoord& depot,
    const vector<DeliveryRequest>& deliveries,
    vector<DeliveryCommand>& commands,
    double& totalDistanceTravelled) const {
    return m_impl->generateDeliveryPlan(depot, deliveries, commands, totalDistanceTravelled);
}
