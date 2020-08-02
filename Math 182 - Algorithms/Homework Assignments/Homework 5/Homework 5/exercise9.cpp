#include<vector>
#include <math.h>	// floor, sqrt
using namespace std;

vector<int> findContinuedFraction(int N);
// defined in auxFunctions.cpp

int oddPeriodSquareRoots(int bound) {
	// returns the number of continued fractions of root(n) that have an odd period for n <= bound

	int oddCount = 0;

	// finding continued fractions with odd period
	for (int N = 2; N <= bound; N++)
		if (findContinuedFraction(N).size() % 2 == 1)
			oddCount++;

	return oddCount;
}