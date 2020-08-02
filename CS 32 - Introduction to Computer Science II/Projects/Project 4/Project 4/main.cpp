#include "ExpandableHashMap.h"
#include <string>
#include <iostream>
using namespace std;


void testExpandableHashMap();

int main() {
	testExpandableHashMap();
}

void testExpandableHashMap() {
	// Define a hashmap that maps strings to doubles and has a maximum load factor of 0.2. It will initially have 8 buckets when empty.
	ExpandableHashMap<string, double> nameToGPA(0.2);  // Add new items to the hashmap. 
	nameToGPA.associate("Carey", 3.5);  // Carey has a 3.5 GPA 
	nameToGPA.associate("David", 3.99); // David beat Carey
	nameToGPA.associate("Abe", 3.2);	// Abe has a 3.2 GPA
	double* davidsGPA = nameToGPA.find("David");

	if (davidsGPA != nullptr)
		*davidsGPA = 1.5; // after a re-grade of David’s exam

	nameToGPA.associate("Carey", 4.0); // Carey deserves a 4.0 replaces old 3.5 GPA
	double* lindasGPA = nameToGPA.find("Linda");

	if (lindasGPA == nullptr)
		cout << "Lindais not in the roster!" << endl;
	else
		cout << "Linda’s GPA is: " << *lindasGPA << endl;
}