#include <vector>
using namespace std;

vector<int> maxSubArray(const vector<int>& A) {
	// returns a vector { startingIndex, endingIndex, sum } to represent maximal subarray
	// finding maximal subarray starting at index 1
	
	int i2j_startIndex = 0;		// starting index of maximum subarray ending at j
	int i2j_sum = A[0];			// sum of maximum subarray ending at j
	int one2j_startIndex = 0;	// starting index of maximum subarray of A[1 .. j]
	int one2j_endIndex = 0;		// ending index of maximum subarray of A[1 .. j]
	int one2j_sum = A[0];		// sum of maximum subarray of A[1 .. j]

	// iterating from j + 1 to n (= A.length)
	for (unsigned int j = 0; j < A.size() - 1; j++) {

		// updating i2j_sum, startIndex for j+1
		// (finding max subarray ending at j + 1)
		if (i2j_sum > 0) {
			// max subarray ending at j + 1 is max subarray ending at j, plus A[j+1]
			i2j_sum += A[j + 1];
		}
		else {
			// max subarray ending at j+1 is simply A[j+1]
			i2j_startIndex = j + 1;
			i2j_sum = A[j + 1];
		}

		// updating one2j_startIndex, endIndex and sum
		// (finding max subarray of A[1 .. j + 1])
		if (i2j_sum > one2j_sum) {
			// max subarray of A[1 .. j + 1] is max subarray ending at j + 1
			one2j_startIndex = i2j_startIndex;
			one2j_endIndex = j + 1;
			one2j_sum = i2j_sum;
		}
		// else, max subarray of A[1 .. j + 1] is max subarray of A[1 .. j]
			// no need to update anything
	}

	// at end of loop, j = A.length
	return vector<int> {one2j_startIndex + 1, one2j_endIndex + 1, one2j_sum};
		// returning 1-based indices
}