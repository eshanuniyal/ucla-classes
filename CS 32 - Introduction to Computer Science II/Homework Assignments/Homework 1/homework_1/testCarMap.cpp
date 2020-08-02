#include "CarMap.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
    // testing constructor function
    CarMap constructor_test;
    assert(constructor_test.fleetSize() == 0); // when first constructed, fleet size is 0

    // testing addCar
    CarMap addCar_test;
    for (int i = 0; i != DEFAULT_MAX_ITEMS - 1; i++) {
        string new_license = "California-" + to_string(i);
        assert(addCar_test.addCar(new_license));
        assert(addCar_test.miles(new_license) == 0);
    } // fills almost the entire map with cars California-0 ... California 238; 
        // each addition should return true, and miles driven for each new car should be 0
    assert(!addCar_test.addCar("California-0")); // "California-0" already in map, can't be added
    assert(addCar_test.addCar("California-239")); // car not in map, added successfully
    assert(!addCar_test.addCar("California-240")); // car not in map, but map full -> can't be added

    // testing miles function
    // If a car with the given license plate is in the map, return how many miles it has been driven; otherwise, return -1.
    CarMap miles_test;
    miles_test.addCar("a");
    miles_test.drive("a", 21); // preliminary test of drive
    assert(miles_test.miles("a") == 21); // testing whether miles for "a" were updated
    assert(miles_test.miles("b") == -1); // "b" not in map

    // testing drive function
    CarMap drive_test;
    drive_test.addCar("a");
    assert(!drive_test.drive("a", -1) && !drive_test.drive("b", 1)); // can't drive negative distance or drive a car not inamp
    assert(drive_test.drive("a", 2) && drive_test.miles("a") == 2); // drive "a" for two miles

    // testing fleetSize function
    CarMap fleetSize_test;
    assert(fleetSize_test.fleetSize() == 0); // empty fleet has size zero
    for (int i = 0; i != DEFAULT_MAX_ITEMS; i++) 
        fleetSize_test.addCar("California-" + to_string(i));
    assert(fleetSize_test.fleetSize() == 240); // full fleet
    fleetSize_test.addCar("a"); // 
    assert(fleetSize_test.fleetSize() == 240); // full fleet - car could not be added, so size shouldn't be incremented

    // testing print function
    CarMap print_test;
    for (int i = 0; i != 10; i++)
        print_test.addCar("California-" + to_string(i));
    print_test.drive("California-0", 10);
    print_test.print();

    cerr << "All tests passed successfully." << endl;
}