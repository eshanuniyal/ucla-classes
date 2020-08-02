int chainLength(long long n);

int longestCollatzChain(int bound) {
	// returns the starting number under bound which generates the longest Collatz chain

	int maxChainLength = 0;		// maximum chain length currently found
	int nBest = 0;		// best starting number currently found

	// iterating up to bound
	for (int n = 1; n < bound; n++) {
		int nChainLength = chainLength(n);

		// checking if current chain is longest found so far
		if (nChainLength > maxChainLength) {
			// updating maxChainLength and nBest
			maxChainLength = nChainLength;
			nBest = n;
		}
	}

	// returning best starting number
	return nBest;
}

int chainLength(long long n) {
	// returns the length of the Collatz chain of n
	int length = 1;		// we include n in the chain

	// iterating until n is reduced to 1
	while (n != 1) {
		// divide by 2 if even
		if (n % 2 == 0)
			n = n / 2;
		// multiply by 3, add 1 if odd
		else n = 3 * n + 1;
		// increment chain length
		length++;
	}
	return length;
}