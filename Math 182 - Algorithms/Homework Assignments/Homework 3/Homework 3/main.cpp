#include <iostream>
#include <vector>
using namespace std;

#include <boost/multiprecision/cpp_int.hpp>	// for large ints, from the non-standard boost library
using namespace boost::multiprecision;

// exercise 13
int largeCombinations(int minCombinations, int nBound);
// exercise 14
int maxEulerTotientRatio(int bound);
// exercise 15
int nPartitions(int n);
// exercise 17
int greatestAdjacentEntrySum(int sz);
// exercise 16
int efficientExponentiationSum(int bound);

int main() {
	
	// exercise 13
	cout << "Exercise 13: " << largeCombinations(1000000, 100) << endl;
		// answer: 4075

	// exercise 14
	cout << "Exercise 14: " << maxEulerTotientRatio(1000000) << endl;
		// answer 510510, with totient ratio ~5.53939
	
	// exercise 15
	cout << "Exercise 15: " << nPartitions(100) << endl;
		// answer 190569291

	// exercise 16
	cout << "Exercise 16: " << efficientExponentiationSum(20) << endl;
	
	// exercise 17
	cout << "Exercise 17: " << greatestAdjacentEntrySum(2000) << endl;
		// answer 52852124
}