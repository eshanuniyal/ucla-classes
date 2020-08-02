#include <vector>
using namespace std;

#include <boost/multiprecision/cpp_int.hpp>	// for large ints, from the non-standard boost library
using namespace boost::multiprecision;

int largeCombinations(int minCombinations, int nBound) {
	// returns the number of values of (n r), with 0 <= r <= n <= nBound, that are greater than minCombinations

	// computing a vector of factorials
	vector<cpp_int> factorials = { 1 };		// initialised to 0!
	// iterating to build factorials
	for (int n = 1; n <= nBound; n++)
		factorials.push_back(factorials.back() * n);

	int count = 0;	// number of combinations found that are greater than min

	// iterating over all (n, r) for 0 <= n <= nBound
	for (int n = 1; n <= nBound; n++)
		for (int r = 0; r <= n; r++) {
			// computing nCr
			cpp_int nCr = factorials[n] / (factorials[r] * factorials[n - r]);
			// checking if nCr > min
			if (nCr > minCombinations)
				count++;
		}
	
	return count;
}