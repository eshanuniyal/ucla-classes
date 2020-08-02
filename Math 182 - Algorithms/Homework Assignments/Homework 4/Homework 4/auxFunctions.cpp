#include <unordered_map>
using namespace std;


// auxiliary function for exercises 12,13
int findDivisorSum(int n, unordered_map<int, int>& divisorSums) {
	// returns the sum of divisors of n (less than n)

	// checking if divisor sum already found (unordered_map search is constant time)
	if (divisorSums.find(n) != divisorSums.end())
		return divisorSums[n];

	// divisor sum not already found -> find sum of all divisors

	int nDivisorSum = 0;
	int rootN = ceil(sqrt(n));

	// we iterate up to root n to find all divisors pairs
	for (int d = 1; d < rootN; d++)
		// if d divides n, add both divisors to divisorSums[n]
		if (n % d == 0)
			nDivisorSum += d + n / d;

	// checking for case where n is a perfect square
	if (pow(rootN, 2) == n)
		nDivisorSum += rootN;

	// subtracting n, since we only want sum of divisors less than n (and n was added as part of (1, n) pair)
	nDivisorSum -= n;

	// inserting divisor sum in map (unordered_map insertion is constant time)
	divisorSums[n] = nDivisorSum;

	return nDivisorSum;
}