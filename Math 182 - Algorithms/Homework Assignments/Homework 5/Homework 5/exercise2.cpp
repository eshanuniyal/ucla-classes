#include <string>
#include <vector>
using namespace std;

string findPalindromeOfSubstring(string str, int s, int e, vector<vector<string*>>& palindromes);

string findPalindrome(string str) {
	vector<vector<string*>> palindromes(str.length(), vector<string*>(str.length(), nullptr));
		// palindromes[s][e - 1] stores the longest palindrome in str[s : e - 1] (inclusive); stores nullptr if palindrome not yet found
	
	// generating answer
	string longestSubsequentPalindrome = findPalindromeOfSubstring(str, 0, str.length(), palindromes);
	
	// freeing memory
	for (vector<string*> row : palindromes)
		for (string* p : row)
			if (p != nullptr)
				delete p;

	return longestSubsequentPalindrome;
}

string findPalindromeOfSubstring(string str, int s, int e, vector<vector<string*>>& palindromes) {
	// base case: empty string
	if (e - s == 0)
		return "";
	// base case: string of length
	else if (e - s == 1)
		return string(1, str[s]);
	// base case: longest palindrome already found
	else if (palindromes[s][e - 1] != nullptr)
		return *palindromes[s][e - 1];

	// variable to store answer
	string p;

	// comparing first and last character
	// first and last character match
	if (str[s] == str[e - 1]) {
		p = str[s] + findPalindromeOfSubstring(str, s + 1, e - 1, palindromes) + str[e - 1];
	}
	// first and last characters don't match
	else {
		// solving subproblems
		string p1 = findPalindromeOfSubstring(str, s + 1, e, palindromes);
		string p2 = findPalindromeOfSubstring(str, s, e - 1, palindromes);
		// finding optimal solution among subproblems
		if (p1.length() >= p2.length())
			p = p1;
		else p = p2;
	}

	// storing found palindrome for future reference
	palindromes[s][e - 1] = new string(p);
	// returning answer
	return p;
}