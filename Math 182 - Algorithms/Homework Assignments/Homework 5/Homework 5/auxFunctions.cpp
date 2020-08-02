#include <vector>
#include <fstream>	// defines ifstream
#include <string>
#include <iostream>
using namespace std;

// used for exercise 13
vector<vector<int>> loadMatrix(string fileName, int dim);
// used for exercise 9, 10
bool checkPerfectSquare(int N);
vector<int> findContinuedFraction(int N);

vector<vector<int>> loadMatrix(string fileName, int dim) {
	// loads matrix defined in input file with address "fileName" (rows separated by '\n', ints separated by ", ")
		// into square, 2D vector matrix

	vector<vector<int>> matrix;

	// loading file into inputFile
	ifstream inputFile(fileName);

	// file could not be found
	if (!inputFile) {
		cerr << "File could not be found." << endl;
		exit(1);
	}

	// iterate over rows; with each iteration, we generate a row vector
	for (int rowNum = 0; rowNum < dim; rowNum++) {
		vector<int> row;
		// iterating over each element in row (except last)
		for (int colNum = 0; colNum < dim; colNum++) {
			int rowElem;
			inputFile >> rowElem;	// extracting row element
			if (colNum < dim - 1)
				inputFile.ignore(10000, ',');	// skip comma before next element 
					// (only exists if not last element)
			row.push_back(rowElem);	// inserting row element into row
		}
		matrix.push_back(row);	// inserting row
	}

	return matrix;
}

bool checkPerfectSquare(int N) {
	// checks whether a number is a perfect square
	if (pow(int(sqrt(N)), 2) == N)
		return true;
	else return false;
}

vector<int> findContinuedFraction(int N) {
	// returns the period of the continued fraction for root n

	const int aStart = int(floor(sqrt(N)));	// termination check: when our next expression is root(n) - aStart, we can terminate
	
	// checking if N is a perfect square
	if (aStart * aStart == N)
		return vector<int> {};	// no continued fraction

	// sequence of a's (until sequence starts repeating
	vector<int> fractionConstants = { };

	int nK = 1;
	int dK = -aStart;	// in reality, denominator is root(n) - denominatorTerm

	do {
		// rationalising numerator / (root(n) - denominatorTerm)
		int dKp1 = -dK;	// (tentative) next denominator
		int nKp1 = (N - int(pow(dK, 2))) / nK;	// next numerator

		int aKp1 = 0;

		// transforming dKp1 to appropriate form
		while (N - int(pow(dKp1 - nKp1, 2)) > 0) {
			dKp1 -= nKp1;
			aKp1++;
		}

		// updating nK, dK, fractionConstants
		nK = nKp1; dK = dKp1;
		fractionConstants.push_back(aKp1);

	} while (nK != 1 || dK != -aStart);
	// if while condition is met, we're back to the first iteration and constants will repeat

	// returning continued fraction constants
	return fractionConstants;
}