#include <vector>
using namespace std;

void reduceToProper(int& n, int& d);
int euclid(int m, int n);

int previousReducedFraction(int num, int den, int bound) {
	// returns the numerator n of the reduced proper fraction n / d immediately to the left of num / den for n < d <= bound

	double upperBound = double(num) / den;	// upper bound for desired n / d

	// tracking the best reduced fraction and the corresponding numerator found so far
	double bestRatio = 0;
	int nOptimal = 0;

	// iterating over denominators d
	for (int d = 2; d <= bound; d++) {
		
		int nStart = int(floor(d * upperBound));
		
		// decrementing nStart will we reach a viable candidate for n / d
		while (double(nStart) / d >= upperBound)
			nStart--;
			
		for (int n = nStart; n > 0; n--) {
			double ndRatio = double(n) / d;
			// terminating condition; if ndRatio < bestRatio, n/d is not a candidate
			if (ndRatio < bestRatio)
				break;

			// testing to see if we have a better candidate than our current best
			if (ndRatio > bestRatio) {
				// better candidate found -> find proper fraction
				int nReduced = n;
				int dReduced = d;
				reduceToProper(nReduced, dReduced);
				
				// update variables
				bestRatio = ndRatio;
				nOptimal = nReduced;
				// break, since any since any smaller n will give ndRatio < bestRatio
				break;
			}
		}
	}

	return nOptimal;
}

void reduceToProper(int& n, int& d) {
	// reduces n / d to a proper fraction

	int gcd = euclid(n, d);
	// iterate until n and d are co-prime
	while (gcd != 1) {
		// n and d are not co-prime; divide each by largest common factor
		n /= gcd; d /= gcd;
		gcd = euclid(n, d);
	}
}

int euclid(int a, int b) {
	// returns gcd(a, b)
	if (b == 0)
		return a;
	else return euclid(b, a % b);
}