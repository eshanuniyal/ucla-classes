#include<vector>
#include<string>
using namespace std;

int digitProduct(vector<int> digitIndices) {
	// returns the product of digits at each of digitIndices

	// finding max digit index
	unsigned int maxIndex = 0;
	for (int index : digitIndices)
		if (index > maxIndex)
			maxIndex = index;

	// creating string and reserving storage
	string fractionalPart;
	fractionalPart.reserve(maxIndex);
	
	// iterating until fractionalPart is complete
	for (int i = 1; true; i++) {
		
		// checking whether fractionalPart is complete
		if (fractionalPart.size() >= maxIndex)
			break;

		// inserting next integer
		fractionalPart += to_string(i);
	}
	
	// computing product by iterating over indices
	int prod = 1;
	for (int index : digitIndices)
		prod *= fractionalPart[index - 1] - '0';	
			// fractionalPart[index - 1] is implictly cast to the int representing its ASCII code
			// subtracting '0' (i.e. the ASCII code for 0) converts it to the desired digit

	return prod;
}