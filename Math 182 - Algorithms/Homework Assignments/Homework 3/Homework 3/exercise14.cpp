#include <vector>
using namespace std;

vector<int> generatePrimes(int primeBound);	// used by brute force algorithm

int maxEulerTotientRatio(int bound) {
	// returns that maximum value of n / totient(n) for n <= bound
	// "clever" algorithm

	double totientRatio = 1;	// to keep track of the optimal totient ratio
	int n = 1;	// to keep track of n that gives the optimal totient ratio

	vector<int> primes;

	// iterating over natural numbers to identify primes until n exceeds bound
	for (int p = 2; n*p <= bound; p++) {
		// checking if p is prime by iterating over primes
		bool primeFound = true;
		for (int prime : primes)
			if (p % prime == 0) {
				primeFound = false;
				break;
			}
		// prime found
		if (primeFound) {
			primes.push_back(p);	// update primes
			totientRatio *= p / double(p - 1);	// update totientRatio
			n *= p;	// update n
		}
	}
	return n;
}

int maxEulerTotientRatioBruteForce(int bound) {
	// returns that maximum value of n / totient(n) for n <= bound
	// brute force algorithm

	vector<int> primes = generatePrimes(bound);
	
	// vector of prime factors
	vector<double> totientRatios;	// totientRatios[k] is k/totient(k)
	totientRatios.push_back(0); totientRatios.push_back(0);	
		// setting base cases 0 and 1

	int bestNum = 0;
	double bestTotientRatio = 0;

	// iterating up to bound to find prime factorisations for each
	for (int n = 2; n <= bound; n++) {
		int k = n;
		// iterating until k == 1 (i.e. all primes found)
		for (int prime : primes) {
			// checking if k is divisible by prime factor
			if (n % prime == 0) {
				// reducing n (represented by k) to a number that doesn't have the same prime factor
				while (k % prime == 0)
					k /= prime;
				// finding nTotientRatio (using Euler's Product Formula)
				double nTotientRatio;
				if (k == 1)
					// n only has one prime factor
					nTotientRatio = double(prime) / (prime - 1);
				else
					// n has more than one prime factor -> nTotientRatio = kTotentRatio * p / (p-1)
					nTotientRatio = totientRatios[k] * (double(prime) / (prime - 1));
				// updating bestTotientRatio and bestNum, if necessary
				if (nTotientRatio > bestTotientRatio) {
					bestTotientRatio = nTotientRatio;
					bestNum = n;
				}
				// updating totientRatios
				totientRatios.push_back(nTotientRatio);
				// don't need to check further primes
				break;
			}
		}
	}
	
	return bestNum;
}

vector<int> generatePrimes(int primeBound) {
	vector<int> primes;		// vector of all primes upto and including largest factor

	// searching for primes (primitive algorithm) by iterating over the range (2, primeBound) (inclusive)
	for (int n = 2; n <= primeBound; n++) {
		bool primeFound = true;		// we assume we have a prime until and unless we find a prime factor
		int maxPrimeFactor = ceil(sqrt(n));
		
		// searching for prime factor
		for (int prime : primes) {
			if (n % prime == 0)
				primeFound = false;
			if (prime > maxPrimeFactor || !primeFound)
				break;
		}
		// no factor of i found -> i is a prime
		if (primeFound)
			primes.push_back(n);
	}
	return primes;
}
