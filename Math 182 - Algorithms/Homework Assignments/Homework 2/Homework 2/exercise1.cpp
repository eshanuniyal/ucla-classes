#include<vector>
using namespace std;

vector<vector<int>> exercise1fast(vector<int> A) {
	vector<vector<int>> B(A.size(), vector<int>(A.size(), 0)); // create matrix
	// iterating over rows
	for (unsigned int i = 0; i < A.size(); i++) {
		B[i][i] = A[i]; // setting diagonal element (for correctness)
			// iterating over columns
		for (unsigned int j = i + 1; j < A.size(); j++)
			B[i][j] += B[i][j - 1] + A[j];  // setting value
	}
	return B;
}