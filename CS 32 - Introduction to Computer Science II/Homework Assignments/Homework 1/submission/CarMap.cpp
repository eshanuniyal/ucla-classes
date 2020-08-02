#include "CarMap.h"
#include "Map.h"

#include <string>
#include <iostream>
using namespace std;

CarMap::CarMap() {
}

bool CarMap::addCar(string license) {
	// If a car with the given license plate is not currently in the map, and there is room in the map, 
		// add an entry for that car recording that it has been driven 0 miles, and return true.  
	// Otherwise, make no change to the map and return false.

	// checking that license isn't already in map and that map has more space
	if (!m_cars.contains(license) && fleetSize() != DEFAULT_MAX_ITEMS) {
		m_cars.insert(license, 0);
		return true;
	}

	// car either already in map or can't be added
	return false;
}

double CarMap::miles(string license) const {
	// If a car with the given license plate is in the map, return how many miles it has been driven; otherwise, return -1.
	
	// integer to store miles driven for given license key
	double miles_driven;

	// checking whether license is in map, and changing miles_driven if it is
	if (m_cars.get(license, miles_driven))
		return miles_driven;

	// car not in map
	return -1;
}

bool CarMap::drive(string license, double distance) {
	// If no car with the given license plate is in the map or if distance is negative, make no change to the map and return false.
	// Otherwise, increase by the distance parameter the number of miles the indicated car has been driven and return true.

	// checking if distance is less than zero
	if (distance < 0)
		return false;

	double miles_driven = miles(license); // -1 if car not in map
	
	if (miles_driven != -1) { // checking if car in map
		m_cars.insertOrUpdate(license, miles_driven + distance); // updating miles driven for given car
		return true;
	}
	else return false; // car not in map
}

int CarMap::fleetSize() const {
	// Return the number of cars in the CarMap.
	return m_cars.size();
}

void CarMap::print() const {
	// Write to cout one line for every car in the map.  
	// Each line consists of the car's license plate, followed by one space, followed by the number of miles that car has been driven.  
	// Write no other text. The lines need not be in any particular order.

	for (int i = 0; i != fleetSize(); i++) {
		string license;
		double miles_driven;
		m_cars.get(i, license, miles_driven);
		cout << license << " " << miles_driven << endl;
	}
}