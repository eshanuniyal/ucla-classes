#include <iostream>
using namespace std;

// exercise 12
int findAmicableSum(int bound);
// exercise 13
int findNonAbundantSum();
// exercise 14
int findTruncatablePrimeSum();
// exercise 15
int findOptimalPerimeter(int bound);
// exercise 16
int expansionsWithLargeNumerators(int nIterations);

int main() {
	// exercise 12
	cout << "Exercise 12: " << findAmicableSum(10000) << endl;
		// answer 31626

	// exercise 13
	cout << "Exercise 13: " << findNonAbundantSum() << endl;
		// answer 4179871

	// exercise 14
	cout << "Exercise 14: " << findTruncatablePrimeSum() << endl;
		// answer 748317

	// exercise 15
	cout << "Exercise 15: " << findOptimalPerimeter(1000) << endl;
		// answer 840

	// exercise 16
	cout << "Exercise 16: " << expansionsWithLargeNumerators(1000) << endl;
		// answer 153
}