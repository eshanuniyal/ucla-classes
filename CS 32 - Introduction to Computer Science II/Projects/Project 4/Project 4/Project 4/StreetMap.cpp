#include "provided.h"
#include "ExpandableHashMap.h"
#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>

using namespace std;

unsigned int hasher(const GeoCoord& g) {
    return std::hash<string>()(g.latitudeText + g.longitudeText);
}

unsigned int hasher(const string& key) {
    hash<string> strHash;			// creates a string hasher
    return strHash(key);				// hashes key and returns
}

class StreetMapImpl {
    public:
        StreetMapImpl();
        ~StreetMapImpl();
        bool load(string mapFile);
        bool getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const;
    private:
        GeoCoord readGeoCoord(ifstream& inputFile) const;
        void insertAssociation(const GeoCoord& s, const GeoCoord& e, string& name);
        ExpandableHashMap<GeoCoord, vector<StreetSegment>> m_map;           // contains mappings of GeoCoords to vectors of StreetSegments
};

StreetMapImpl::StreetMapImpl() {
}

StreetMapImpl::~StreetMapImpl() {
}

bool StreetMapImpl::load(string mapFile) {

    // determining input file
    ifstream infile(mapFile);

    // file could not be found
    if (!infile)
        return false;

    // file found -> load data
    while (true) {

        // determining street name
        string streetName;
        getline(infile, streetName);

        // could not read street name -> ran out of streets / end of file -> break out of loop
        if (!infile)
            break;

        // determining number of street segments
        int nStreetSegments;
        infile >> nStreetSegments;
        infile.ignore(10000, '\n');

        // finding coordinates for each street segment
        for (int i = 0; i != nStreetSegments; i++) {

            // creating starting coordiante
            GeoCoord startingCoord = readGeoCoord(infile);
            // getting ending latitude
            GeoCoord endingCoord = readGeoCoord(infile);

            infile.ignore(10000, '\n');

            // inserting associations
            insertAssociation(startingCoord, endingCoord, streetName);      // direct association
            insertAssociation(endingCoord, startingCoord, streetName);      // reverse association
        }
    }

    return true;
}

bool StreetMapImpl::getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const {
    
    // checking whether starting coord gc is already a key in the map
    const vector<StreetSegment>* segsPtr = m_map.find(gc);
        // streetSegmentVectorPtr is declared const because getSegmentsThatStartWith is a const function
    
    // no such street segments -> leave segs unmodified and return false
    if (segsPtr == nullptr)
        return false;

    // street segments exist -> clear segs and insert streetsegments into segs
    segs.clear();
    for (int i = 0; i != segsPtr->size(); i++) {
        StreetSegment currentSeg = (*segsPtr)[i];
        segs.push_back(currentSeg);
    }

    return true;
}

// ##################################################################################################################
// AUXILIARY FUNCTIONS
// ##################################################################################################################

GeoCoord StreetMapImpl::readGeoCoord(ifstream& inputFile) const {

    // getting coordinates
    string startingLat, startingLong;
    inputFile >> startingLat;
    inputFile >> startingLong;

    // constructing and returning GeoCoord
    return GeoCoord(startingLat, startingLong);
}

void StreetMapImpl::insertAssociation(const GeoCoord& s, const GeoCoord& e, string& name) {
    // insert association into m_map; takes parameters starting coordinate (s), ending coordinate (e), and street name (name)

    // checking whether starting coord already has key in m_map
    vector<StreetSegment>* streetSegmentVectorPtr = m_map.find(s);
    StreetSegment streetSegment(s, e, name);

    // key found -> insert new street segment in list
    if (streetSegmentVectorPtr != nullptr) {
        streetSegmentVectorPtr->push_back(streetSegment);
        return;
    }

    // key not found -> create new association
    // new street segment vector
    vector<StreetSegment> newStreetSegmentVector(1, streetSegment);
    // associating creates vector in map
    m_map.associate(s, newStreetSegmentVector);
}

// ##################################################################################################################
// StreetMap Functions
// ##################################################################################################################
// These functions simply delegate to StreetMapImpl's functions.
// You probably don't want to change any of this code.

StreetMap::StreetMap() {
    m_impl = new StreetMapImpl;
}

StreetMap::~StreetMap() {
    delete m_impl;
}

bool StreetMap::load(string mapFile) {
    return m_impl->load(mapFile);
}

bool StreetMap::getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const {
   return m_impl->getSegmentsThatStartWith(gc, segs);
}