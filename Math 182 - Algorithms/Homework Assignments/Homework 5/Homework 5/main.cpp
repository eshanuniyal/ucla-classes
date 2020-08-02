#include <iostream>
#include <string>
#include <vector>
using namespace std;

// exercise 2
string findPalindrome(string str);
// exercise 9
int oddPeriodSquareRoots(int bound);
// exercise 10
int diophantineEquation(int bound);
// exercise 11
int previousReducedFraction(int num, int den, int bound);
// exercise 13
int minPathSumFourWays(string fileName, int dim);


int main() {

	// exercise 2
	for (string test : vector<string>{ "t", "racecar", "charaacter", "aibohphobia", "crococdile" })
		cout << findPalindrome(test) << endl;
	// exercise 9
	cout << "Exercise 9: " << oddPeriodSquareRoots(10000) << endl;
		// answer: 1322
	// exercise 10
	cout << "Exercise 10: " << diophantineEquation(1000) << endl;
		// answer: 661
	// exercise 11
	cout << "Exercise 11: " << previousReducedFraction(3, 7, 1000000) << endl;
		// answer: 428570
	// exercise 13
	cout << "Exercise 13: " << minPathSumFourWays("exercise13.txt", 80) << endl;
		// answer: 425185
	
}