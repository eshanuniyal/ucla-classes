
long long binomial(int n, int k) {
	// base cases
	if (k == 0 || n == k)
		return 1;
	else return binomial(n - 1, k) + binomial(n - 1, k - 1);
}