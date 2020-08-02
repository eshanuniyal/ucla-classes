#include <vector>
#include<iostream>
using namespace std;

#include <boost/multiprecision/cpp_int.hpp>	// for large ints, from the non-standard boost library
using namespace boost::multiprecision;

vector<vector<int>> generateMatrix(int sz);
vector<int> maxSubArray(const vector<int>& A);	
	// from exercise 2, for finding maximal subarray

void checkArrayAndUpdateMax(const vector<int>& arr, int& max) {
	// checks input array for sum of maximal subarray (arrMax) and updates max is arrMax > max
	
	// computing sum of maximal subarray
	int arrMax = maxSubArray(arr)[2];
	// updating max if necessary
	if (arrMax > max)
		max = arrMax;
}

int greatestAdjacentEntrySum(int sz) {
	// returns the greatest sum of any number of adjacent entries (horizontal, vertical, diagonal, or anti-diagonal)
	// in a matrix of size sz*sz (assumed sz <= 2000)
	
	vector<vector<int>> matrix = generateMatrix(sz);

	int max = matrix[0][0];	// tracks the greatest adjacent entry sum

	// checking rows
	for (int row = 0; row < sz; row++)
		checkArrayAndUpdateMax(matrix[row], max);	

	// checking columns
	for (int col = 0; col < sz; col++) {
		// creating column vector
		vector<int> column(sz, 0);

		// iterating over rows to insert elements
		for (int row = 0; row < sz; row++)
			column[row] = matrix[row][col];

		checkArrayAndUpdateMax(column, max);
	}

	// checking diagonals starting in top row
	for (int startCol = 0; startCol < sz; startCol++) {
		
		// creating diagonal vector
		vector<int> diagonal; diagonal.reserve(sz);

		// iterating over rows to insert elements
		for (int rowNum = 0; startCol + rowNum < sz; rowNum++)
			diagonal.push_back(matrix[rowNum][startCol + rowNum]);
		
		checkArrayAndUpdateMax(diagonal, max);
	}

	// checking diagonals starting in leftmost column
	for (int startRow = 1; startRow < sz; startRow++) {
			// starting row at 1 since diagonal starting at [0][0] already checked
		// creating diagonal vector
		vector<int> diagonal; diagonal.reserve(sz);

		// iterating over columns to insert elements
		for (int colNum = 0; startRow + colNum < sz; colNum++)
			diagonal.push_back(matrix[startRow + colNum][colNum]);
		
		checkArrayAndUpdateMax(diagonal, max);
	}


	// checking anti-diagonals starting in top row
	for (int startCol = sz - 1; startCol >= 0; startCol--) {

		// creating anti-diagonal vector
		vector<int> antiDiagonal; antiDiagonal.reserve(sz);

		// iterating over rows to insert elements
		for (int rowNum = 0; startCol - rowNum >= 0; rowNum++)
			antiDiagonal.push_back(matrix[rowNum][startCol - rowNum]);
		
		checkArrayAndUpdateMax(antiDiagonal, max);
	}

	// checking anti-diagonals starting in rightmost column
	for (int startRow = 1; startRow < sz; startRow++) {

		// creating anti-diagonal vector
		vector<int> antiDiagonal; antiDiagonal.reserve(sz);

		// iterating over columns to insert elements
		for (int colNum = 0; startRow + colNum < sz; colNum++)
			antiDiagonal.push_back(matrix[startRow + colNum][sz - 1 - colNum]);
		
		checkArrayAndUpdateMax(antiDiagonal, max);
	}

	return max;
}

vector<vector<int>> generateMatrix(int sz) {
	// generates a matrix of size sz*sz (assumed sz <= 2000) using lagged fibonacci numbers

	// creating a vector of generated numbers
	vector<int> generatedNums(sz*sz, 0);

	// itearting to sz^2 times to generate all numbers
	for (int k = 1; k <= sz * sz; k++) {
		cpp_int Sk;		// cpp_int is variable size
		// generating Sk
		if (k <= 55)
			Sk = (100003 - 200003 * k + 300007 * cpp_int(pow(k, 3))) % 1000000 - 500000;
		else
			Sk = (generatedNums[k - 25] + generatedNums[k - 56] + 1000000) % 1000000 - 500000;
		// inserting Sk into generatedNums
		generatedNums[k - 1] = int(Sk);
	}

	// creating a matrix from generatedNums
	vector<vector<int>> matrix(sz, vector<int>(sz, 0));
		// initialising to a matrix of zeros

	int k = 0;
	for (int rowNum = 0; rowNum < sz; rowNum++) {
		// iterating over columns
		for (int colNum = 0; colNum < sz; colNum++) {
			// inserting generatedNums[k]
			matrix[rowNum][colNum] = generatedNums[k];
			k++;	// incrementing k
		}
	}

	return matrix;
}