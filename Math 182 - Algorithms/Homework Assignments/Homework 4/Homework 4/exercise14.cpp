#include <vector>
#include <unordered_set>
using namespace std;

bool checkTruncatability(int prime, unordered_set<int>& primesSet);

int findTruncatablePrimeSum() {
	// returns sum of all primes truncatable from left to right with preserved primality

	unordered_set<int> primesSet;	// set of primes up to primeBound (for constant search)
	vector<int> primesVec;	// vector of primes up to primeBound (for ordered iteration)
	
	// generating primes and populating primesSet and primesVec
	// generatePrimes(1000000, primesSet, primesVec);

	const int maxTruncatablePrimes = 11;	// known number of truncatable primes
	int truncatablePrimeCount = 0;	// number of trunctable primes found

	int truncatablePrimeSum = 0;	// sum of truncatable primes
	
	// continually generating and testing primes
	for (int n = 2; truncatablePrimeCount < maxTruncatablePrimes; n++) {

		// finding prime
		bool primeFound = true;		// we assume we have a prime until and unless we find a prime factor
		int maxPrimeFactor = ceil(sqrt(n));

		// searching for prime factor
		for (int prime : primesVec) {
			if (n % prime == 0)
				primeFound = false;
			if (prime > maxPrimeFactor || !primeFound)
				break;
		}
		
		// factor of i found -> i is a prime
		if (!primeFound)
			continue;

		// no factor of i found -> i is a prime
		else {
			int prime = n;

			// updating primesVec and primesSet
			primesVec.push_back(prime);
			primesSet.insert(prime);

			if (checkTruncatability(prime, primesSet)) {
				// updating truncatable prime sum and count
				truncatablePrimeSum += prime;
				truncatablePrimeCount++;
			}
		}
	}

	return truncatablePrimeSum;
}

bool checkTruncatability(int prime, unordered_set<int>& primesSet) {
	// returns whether a prime is truncatable

	// 2, 3, 5, and 7 don't count as truncatable primes
	if (prime < 10)
		return false;

	bool truncatablePrime = true;	// we assume prime is truncatable by default
	int primeLength = ceil(log10(prime));	// number of digits in prime

	// truncating prime from left to right and checking primality
	for (int p = primeLength - 1; p >= 1 && truncatablePrime; p--) {
		int truncatedPrime = prime % int(pow(10, p));	// truncated prime
		// checking primality
		if (primesSet.find(truncatedPrime) == primesSet.end())
			truncatablePrime = false;
	}

	// truncating primes from right to left and checking primality
	for (int p = 1; p < primeLength && truncatablePrime; p++) {
		int truncatedPrime = prime / int(pow(10, p));	// truncated prime
		// checking primality
		if (primesSet.find(truncatedPrime) == primesSet.end())
			truncatablePrime = false;
	}

	return truncatablePrime;
}