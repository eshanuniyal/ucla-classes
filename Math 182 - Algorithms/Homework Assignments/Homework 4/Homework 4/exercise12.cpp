#include <unordered_map>
using namespace std;

// auxiliary functions
int checkAmicability(int a, unordered_map<int, int>& divisorSums);
int findDivisorSum(int n, unordered_map<int, int>& divisorSums);
	// defined in auxFunctions.cpp

int findAmicableSum(int bound) {
	// returns the sum of all amicable numbers under bound

	// vector to store sum of all divisors
	unordered_map<int, int> divisorSums;

	int amicableSum = 0;
	// finding sum of amicable numbers less than bound
	for (int n = 1; n < bound; n++)
		if (checkAmicability(n, divisorSums))
			amicableSum += n;
	
	return amicableSum;
}

int checkAmicability(int a, unordered_map<int, int>& divisorSums) {
	// checks whether input number a is amicable

	// finding divisor sum for a
	int b = findDivisorSum(a, divisorSums);	// divisorSums[a] = b
	if (b != a) {
		// finding d(b)
		int d_b = findDivisorSum(b, divisorSums);
		// we check if d(b) == a
		if (d_b == a)
			return true;	// a is amicable
	}
	// a is not amicable
	return false;
}
