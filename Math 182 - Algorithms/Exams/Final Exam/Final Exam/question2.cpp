#include <vector>
#include <iostream>
#include <string>
using namespace std;

void PrintOptimalParens(const vector<vector<int>>& s, int i, int j);

void MatrixChainOrder(vector<int> p) {
	// finds optimal matrix chain parenthesisation

	const int n = p.size() - 1;
	vector<vector<int>> m(n + 1, vector<int>(n + 1, 0));
	vector<vector<int>> s(n, vector<int>(n + 1, 0));	
		// we create larger matrices than is really needed for 1-based indexing

	for (int i = 0; i <= n; i++)
		m[i][i] = 0;

	for (int l = 2; l <= n; l++) {
		for (int i = 1; i <= n - l + 1; i++) {
			int j = i + l - 1;
			m[i][j] = INT_MAX;	// sentinel
			for (int k = i; k <= j - 1; k++) {
				int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
	
	// returns s (with 1-based indexing)
	PrintOptimalParens(s, 1, n);
}

void PrintOptimalParens(const vector<vector<int>>& s, int i, int j) {
	if (i == j)
		cout << "A" << i;
	else {
		cout << "(";
		PrintOptimalParens(s, i, s[i][j]);
		PrintOptimalParens(s, s[i][j] + 1, j);
		cout << ")";
	}
}