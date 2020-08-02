#include <vector>
#include <set>
#include <algorithm>	// sort
using namespace std;

void generateAndSortTriplet(int m, int n, int& a, int& b, int& c);
bool checkCoprimality(int m, int n);
int euclid(int m, int n);

int findOptimalPerimeter(int bound) {
	// finds perimeter p <= bound with such that maximum number of triplets give perimeter p

	vector<vector<vector<int>>> pSolutions(bound + 1, vector<vector<int>> { });
		// pSolutions[p] is a vector of all triplets that sum to p

	// iterating m up to maximal value m can take given bound
	for (int m = 2; 2 * m * (m + 1) <= bound; m++) {
		// iterating n upto maximal value n can take given bound
		for (int n = 1; n < m && 2 * m * (m + n) <= bound; n++) {
			
			// checking whether m and p are coprime
			if (!checkCoprimality(m, n))
				continue;

			// generating and sorting triplet
			int a, b, c;
			generateAndSortTriplet(m, n, a, b, c);

			// generating perimeter
			int primitivePerimeter = a + b + c;

			// iterating over all triplets associated with primitive triplet
			for (int multiplier = 1; multiplier <= bound / primitivePerimeter; multiplier++) {
				
				// perimeter of regular triplet
				int perimeter = multiplier * primitivePerimeter;
				// finding current ordered triplet
				vector<int> currentTriplet = { a * multiplier, b * multiplier, c * multiplier };

				bool newSolution = true;	// we assume solution is novel by default

				// checking triplets already found
				for (vector<int> triplet : pSolutions[perimeter]) {
					// comparing triplets
					if (currentTriplet == triplet) {
						newSolution = false;
						break;
					}
				}
				// if current triplet is novel, insert it into pSolutions[perimeter]
				if (newSolution)
					pSolutions[perimeter].push_back(currentTriplet);				
			}
		}
	}

	// finding optimal p
	int pOptimal = 0;	// optimal p
	int pOptimalSolution = 0;	// number of solutions for optimal p

	// iterating p over 1 through bound to find optimal p
	for (int p = 1; p <= bound; p++)
		if (pSolutions[p].size() > pOptimalSolution) {
			// better p found -> update pOptimal, pOptimalSolution
			pOptimal = p;
			pOptimalSolution = pSolutions[p].size();
		}

	return pOptimal;
}

bool checkCoprimality(int m, int n) {
	// checks whether m and n are co-prime (assumes m > n)
	if (euclid(m, n) == 1)
		return true;
	else return false;
}

void generateAndSortTriplet(int m, int n, int& a, int& b, int& c) {
	// generates triplets from m and n using Euclid's formula, sorts and stores into a, b, and c

	// generating and sorting current triplet
	vector<int> currentPrimitiveTriplet = {
		int(pow(m, 2) - pow(n, 2)),
		2 * m * n,
		int(pow(m, 2) + pow(n, 2))
	};
	sort(currentPrimitiveTriplet.begin(), currentPrimitiveTriplet.end());

	// extracting a, b, and c (ordered)
	a = currentPrimitiveTriplet[0];
	b = currentPrimitiveTriplet[1];
	c = currentPrimitiveTriplet[2];
}

int euclid(int a, int b) {
	// returns 1 iff a and b are coprime
	if (b == 0)
		return a;
	else return euclid(b, a % b);
}