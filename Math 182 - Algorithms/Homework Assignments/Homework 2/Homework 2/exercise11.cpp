#include<cmath>	// for sqrt(n)
using namespace std;

int nDivisors(int num);

int HighlyCompositeTriangular(int minDivisors) {
	// returns the smallest triangular number with more than minDivisors divisors
	
	// iterating till desired number is found
	for (int n = 1; true; n++) {
		int T_n = (n * (n + 1)) / 2;
		if (nDivisors(T_n) > minDivisors)
			return T_n;
	}
}

int nDivisors(int num) {
	// returns the number of divisors of integer num

	int divisorCount = 0;	// number of divisors found

	double numRoot = sqrt(num);	// floor of sqrt(n) 
		// (minor optimisation: don't want to compute sqrt(n) each iteration)

	// iterating up to numRoot (the smaller element of each divisor pair of n is <= nRoot)
	for (int d = 1; d < numRoot; d++)
		// checking if divisor pair found
		if (num % d == 0)
			divisorCount += 2;

	// if n is perfect square -> add one divisor
	if (numRoot - floor(numRoot) == 0)
		divisorCount++;

	return divisorCount;
}