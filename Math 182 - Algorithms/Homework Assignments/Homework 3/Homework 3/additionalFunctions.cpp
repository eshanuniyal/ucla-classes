// functions that were designed to help solve some of the exercises, but weren't used after all
#include <vector>
using namespace std;

vector<vector<int>> generatePrimeFactors(const vector<int>& primes, int bound) {
	// return a vector of prime factorisations for each index

	// vector of prime factors
	vector<vector<int>> factors;
	factors.push_back(vector<int> {});	// for 1-based indexing later
	factors.push_back(vector<int> {});	// for 1-based indexing later

	// iterating up to bound to find prime factorisations for each
	for (int n = 2; n <= bound; n++) {

		// iterating until k == 1 (i.e. all primes found)
		for (int prime : primes) {
			// checking if k is divisible by prime factor
			if (n % prime == 0) {
				// inserting prime in factors[k]
				int k = n;
				while (k % prime == 0)
					k /= prime;
				factors.push_back(factors[k]);
				factors[n].push_back(prime);
				break;

			}
		}
	}
	return factors;
}