#include<vector>
#include<unordered_map>	// for exercise 16
#include<iostream>

using namespace std;

long long	exercise12(int bound, vector<int> factors);
int			exercise13(int bound, vector<int> factors);
long long 	exercise14(vector<int> desiredFactors);
int			exercise15(int bound);
int			exercise16(int bound);

int main() {
	// main function calls all the exercise functions
	
	// exercise 12
	cout << "Exercise 12: " << exercise12(1000000, vector<int>{ 3, 5 }) << endl;
		// answer: 233333166668

	// exercise 13
	cout << "Exercise 13: " << exercise13(10000000, vector<int> { 2 }) << endl;
		// answer: 4613732

	// exercise 14
	// creating and populating factors
	vector<int> desiredFactors;
	for (int i = 1; i <= 30; i++)
		desiredFactors.push_back(i);
	cout << "Exercise 14: " << exercise14(desiredFactors)<< endl;
		// answer: 2329089562800
	
	// exercise 15
	cout << "Exercise 15: " << exercise15(100000) << endl;
		// answer: 1299709

	// exercise 16
	cout << "Exercise 16: " << exercise16(3000) << endl;
}

long long exercise12(int bound, vector<int> factors) {
	// returns sum of all numbers under bound that are multiples of at least one factor in factors

	long long sum = 0;	// creating sum variable
	
	// iterating over numbers under bound
	for (int currentNum = 1; currentNum < bound; currentNum++)
		// iterating over factors
		for (int factor : factors)
			// checking whether factor divides currentNum
			if (currentNum % factor == 0) {
				sum += currentNum;	// updating sum
				break;	// breaking out of loop (don't need to check for other factors)
			}

	// returning sum
	return sum;
}

int exercise13(int bound, vector<int> factors) {
	// returns the sum of all fibonacci numbers under bound that are divisible by any factor in factors
	
	int sum = 0; // creating sum variable

	int F_nm2 = 0;	// F_(n-2)
	int F_nm1 = 1;	// F_(n-1)

	while (true) {
		// computing F_n
		int F_n = F_nm2 + F_nm1;

		// terminating condition
		if (F_n >= bound)
			return sum;


		// checking whether F_n is divisible by any factor in factors
		for (int factor : factors)
			if (F_n % factor == 0) {
				sum += F_n;	 // updating sum
				break;	// breaking out of loop (don't need to check for other factors)
			}
		// updating F_(n-2) and F_(n-1)
		F_nm2 = F_nm1; F_nm1 = F_n;
	}
}

long long exercise14(vector<int> desiredFactors) {
	// returns the smallest integer divisible by each nuber in desiredFactors
	// desiredFactors = list of all the numbers that should divide our desired number
	// algorithm: first compute a list of the primes that themselves factorise all the desiredFactor
	// then, iterating over desiredFactors, successively find the smallest number divisible by every factor encountered until that point

	// note: this function doesn't work for values of n larger than 42 (of course it's 42), because of overflow on long longs
		// this is not a limitation of the algorithm itself: the smallest number that is divisible by 1, 2, ..., 43
		// is larger than long long can support (i.e. larger than 2^63)

	// computing an upper-bound for the primes we need to consider
	int primeBound = 0;
	// iterating over factors to find largest factor
	for (int factor : desiredFactors)
		if (factor > primeBound)
			primeBound = factor;

	vector<int> primes;		// vector of all primes upto and including largest factor

	// searching for primes (primitive algorithm) by iterating over the range (2, primeBound) (inclusive)
	for (int i = 2; i <= primeBound; i++) {
		bool primeFound = true;		// we assume we have a prime until and unless we find a factor
		// iterating over the range(2, i - 1) (inclusive)
		for (int j = 2; j < i; j++) {
			// checking whether j divides i
			if (i % j == 0) {
				// j divides i -> i is not a prime
				primeFound = false;
				break;	// don't need to continue checking for primality
			}
		}
		// no factor of i found -> i is a prime
		if (primeFound)
			primes.push_back(i);
	}

	long long currentMin = 1;	// minimum number divisible by all numbers up to and including desiredFactors[i]
	for (int i = 0; i != desiredFactors.size(); i++) {
		
		int n = desiredFactors[i];

		// optimisation: if currentMin is already divisible by n, no need to multiply or consider it
		if (currentMin % n == 0)
			continue;
		
		long long nextMin = currentMin *= n;	// actual currentMin is now some factor of nextMin

		// iterating over primes to continually divide candidateMin till we have currentMin
		for (int prime : primes) {
			
			// dividing by current prime until dividing any further would violate the loop invariant
			while (true) {

				// checking whether candidateMin is divisible by prime
				if (nextMin % prime != 0)
					break;

				// computing next minCandidate
				long long minCandidate = nextMin / prime;	// computing next candidate for min
				bool trueCandidate = true;	// minCandidate is considered a true candidate by default

				// iterating over desiredFactors upto and including i'th index
				for (int j = 0; j <= i; j++)
					// if minCandidate is not divisible by a single desiredFactor, it's not a valid candidate
					if (minCandidate % desiredFactors[j] != 0) {
						trueCandidate = false;
						break;	// don't need to check further
					}

				// minCandidate is a true candidate -> update nextMin
				if (trueCandidate)
					nextMin = minCandidate;
				// minCandidate is not a true candidate -> cannot divide by current prime further, break out of loop
				else break;
			}
		}
		// updating current minimum
		currentMin = nextMin;
	}

	// return currentMin
	return currentMin;
}

int exercise15(int n) {
	// returns the nth prime (primitive, brute force algorithm)

	vector<int> primes = { 2 };		// initialising with 2 (so primes is non-empty)
	int primesFound = 1;

	// iterating from 3-onwards until we find nth prime
	for (int primeCandidate = 3; true; primeCandidate++) {

		bool primeTrue = true;	// we assume primeCandidate is a prime by default
		double primeCandidateRoot = sqrt(primeCandidate);
		// iterating over primes and checking divisibility to check whether primeCandidate is truly a prime
		for (int prime : primes) {
			
			// if prime > sqrt(primeCandidate), we don't need to check 
				// this is because the largest prime factor of any composite number is less than or equal to its square root
			if (prime > primeCandidateRoot)
				break;

			// prime divides prime candidate -> primeCandidate is not a prime
			if (primeCandidate % prime == 0) {
				primeTrue = false;
				break;	// don't need to check further
			}
		}

		// primeCandidate is a prime -> add to primes, and increment primesFound
		if (primeTrue) {
			primes.push_back(primeCandidate);
			primesFound++;
		}
		else continue;

		// found nth prime -> return last prime found
		if (primesFound == n)
			return primes.back();
	}
}

int exercise16(int bound) {
	// returns the number d in [2, bound) such that 1/d has the longest recurring cycle in its decimal fraction part

	int currentBestD = 2;		// the current best value of d
	int currentBestCycle = 0;	// the current longest recurring cycle (naturally, associated with currentBestD)

	// iterating over [2, bound)
		// optimisation: larger values of d give longer cycles, so we start from the bound and decrement from there
	for (int d = bound - 1; d >= 2; d--) {
	
		// optimisation: 1/d can have a recurring cycle of length at most d-1	
			// if the currentBestCycle is larger than d-1, we don't need to check for the current and all lower values of d
		if (currentBestCycle > d - 1)
			break;
		
		unordered_map<int, int> dividends;	// a map of the dividends obtained at each step of long division mapped with
			// key = dividend of some step, value = index of digit in fractional part associated with the step
			// unordered map gives O(1) search

		int currentDividend = 1;		// current dividend in the long division algorithm
		int currentStep = 0;	// current division step

		// iterating until we find a recurring cycle or the decimal expansion terminates
		while (true) {

			// inserting current dividend and step number
			dividends.insert(pair<int, int> { currentDividend, currentStep++ });

			// next dividend = remainder after current step of division
			int nextDividend = (currentDividend * 10) % d;

			// checking if division has terminated
			if (nextDividend == 0)
				break;

			// division has not terminated -> checking if we have a cycle
			bool recurringCycle = false;	// default assumption that there isn't a recurring cycle
			int cycleLength = -1;	// default cycle length (modified only if there is a cycle)
			
			// checking whether dividend has been previously find
			unordered_map<int, int>::const_iterator itr = dividends.find(nextDividend);
			if (itr != dividends.end()) {
				recurringCycle = true;
				// finding cycle length: currentStep - the step of the previous occurence of currentDividend
				cycleLength = currentStep - itr->second;
			}
	
			// cycle found -> update currentBestD and currentBestCycle as necessary, break out of loop
			if (recurringCycle) {
				if (cycleLength > currentBestCycle) {
					currentBestCycle = cycleLength;
					currentBestD = d;
				}
				break;
			}

			// decimal expansion not terminated and cycle not found -> set up next iteration
			currentDividend = nextDividend;			// updating currentDividend
		}
	}
	// return the best d found
	return currentBestD;
}