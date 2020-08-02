#include <unordered_map>
using namespace std;

int findDivisorSum(int n, unordered_map<int, int>& divisorSums);

int checkAbundance(int n, unordered_map<int, int>& divisorSums) {
	// check if n is an abundant number
	if (findDivisorSum(n, divisorSums) > n)
		return true;
	else return false;
}

int findNonAbundantSum() {
	// returns the sum of all positive integers that can't be expressed as a sum of two abundant numbers

	const int upperBound = 28123;
	// known upper bound on positive integers that can't be expressed as sum of two abundant numbers

	unordered_map<int, int> divisorSums;	// map of numbers to the sum of their divisors
	vector<int> abundantNumbers;	// vector of abundant numbers (for ordered iteration)

	// generating abundant numbers up to upperBound
	for (int k = 1; k <= upperBound; k++) {
		if (checkAbundance(k, divisorSums))
			abundantNumbers.push_back(k);
	}

	vector<int> abundantSumExpressible(upperBound + 1, false);
		// creating a vector of upperBound + 1 candidates for the desired numbers
		// abundantSumExpressible[k] = true if k can be expressed as a sum of two abundant numbers, false otherwise

	// number of abundant numbers found
	const int abundantCount = abundantNumbers.size();

	// finding all sums of abundant numbers <= upperBound
	// iterating over abundant numbers
	for (int i = 0; i < abundantCount; i++) {
		int abundantOne = abundantNumbers[i];
		// iterating over abundant numbers >= abundantone (to avoid overlap)
		for (int j = i; j < abundantCount; j++) {

			int sum = abundantOne + abundantNumbers[j];	// sum of abundant numbers
			// updating abundantSumExpressible[sum]
			if (sum <= upperBound)
				abundantSumExpressible[sum] = true;
			// if sum > upperBound, future sums will also be greater -> break
			else break;
		}
	}

	// finding sum of numbers not expressible as sums of abundant numbers
	int nonAbundantSum = 0;
	// iterating over abundantSumExpressible
	for (int k = 1; k < abundantSumExpressible.size(); k++)
		// if k is not expressible as sum of two abundant numbers, add k to nonAbundantSum
		if (!abundantSumExpressible[k])
			nonAbundantSum += k;

	return nonAbundantSum;
}