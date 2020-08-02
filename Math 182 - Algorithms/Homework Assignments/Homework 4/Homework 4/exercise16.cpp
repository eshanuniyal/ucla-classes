#include <vector>
using namespace std;

#include <boost/multiprecision/cpp_int.hpp>	// for large ints, from the non-standard boost library
using namespace boost::multiprecision;

int expansionsWithLargeNumerators(int nIterations) {
	// returns the number of continued fraction expansions (in lowest form) of sqrt(2) that have
		// more digits in the numerator than in the denominator

	cpp_int nk = 3;
	cpp_int dk = 2;

	int largeNumeratorCount = 0;	// we're starting at 

	for (int itr = 2; itr <= nIterations; itr++) {
		
		// generating t_{k+1}
		cpp_int nkp1 = nk + 2 * dk;
		cpp_int dkp1 = nk + dk;

		nk = nkp1; dk = dkp1;

		if (nk.str().size() > dk.str().size())
			largeNumeratorCount++;
	}
	return largeNumeratorCount;
}