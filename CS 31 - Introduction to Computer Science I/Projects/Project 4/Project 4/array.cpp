#include <iostream>
#include <string>
#include <cassert>

using namespace std;

// declaring functions
int countMatches(const string a[], int n, string target);
int detectMatch(const string a[], int n, string target);
bool detectSequence(const string a[], int n, string target, int& begin, int& end);
int detectMin(const string a[], int n);
int moveToBack(string a[], int n, int pos);
int moveToFront(string a[], int n, int pos);
int detectDifference(const string a1[], int n1, const string a2[], int n2);
int deleteDups(string a[], int n);
bool contains(const string a1[], int n1, const string a2[], int n2);
int meld(const string a1[], int n1, const string a2[], int n2, string result[], int max);
int split(string a[], int n, string splitter);

int main()
{
	// countMatches tests
	string test_countMatches[7] = { "romanoff", "thor", "rogers", "banner", "", "danvers", "rogers" };
	assert(countMatches(test_countMatches, -4, "stark") == -1); // negative n, returns -1
	assert(countMatches(test_countMatches, 0, "romanoff") == 0); // zero n, returns 0
	assert(countMatches(test_countMatches, 7, "rogers") == 2); // two occurrences of "rogers" in first two elements
	assert(countMatches(test_countMatches, 7, "") == 1); // one occurrence of "" in first seven elements
	assert(countMatches(test_countMatches, 7, "rhodes") == 0); // no occurrences of "rhodes" in first seven elements
	cerr << "countMatches tests succeeded." << endl;

	// detectMatch tests
	string test_detectMatches[7] = { "romanoff", "thor", "rogers", "banner", "", "danvers", "rogers" };
	assert(detectMatch(test_detectMatches, -2, "romanoff") == -1); // negative n
	assert(detectMatch(test_detectMatches, 0, "romanoff") == -1); // zero n, no "romanoff" found
	assert(detectMatch(test_detectMatches, 7, "rogers") == 2); // "rogers" in index 2 in first seven elements
	assert(detectMatch(test_detectMatches, 2, "rogers") == -1); // no occurrences of "roger" in first two elements
	cerr << "detectMatch tests succeeded." << endl;

	// detectSequence tests
	string test_detectSequence[9] = { "thor", "romanoff", "danvers", "danvers", "stark", "stark", "stark", "banner", "banner" };
	int begin = 0;
	int end = 0;
	assert(detectSequence(test_detectSequence, -2, "danvers", begin, end) == false && begin == 0 && end == 0);
	// negative n; returns false and leaves begin and end unchanged
	assert(detectSequence(test_detectSequence, 0, "danvers", begin, end) == false && begin == 0 && end == 0);
	// zero n; returns false and leaves begin and end unchanged
	assert(detectSequence(test_detectSequence, 9, "romanoff", begin, end) == true && begin == 1 && end == 1);
	// sequence of length 1: returns true and sets begin to 1 and end to 1
	assert(detectSequence(test_detectSequence, 9, "rogers", begin, end) == false && begin == 1 && end == 1);
	// sequence not found: returns false and leaves begin and end unchanged
	assert(detectSequence(test_detectSequence, 9, "banner", begin, end) == true && begin == 7 && end == 8);
	// sequence of length 2: returns true and sets begin to 7 and end to 8
	assert(detectSequence(test_detectSequence, 9, "thor", begin, end) == true && begin == 0 && end == 0);
	// sequence of length 1, first element in array: returns true and sets begin to 0 and end to 0
	assert(detectSequence(test_detectSequence, 6, "stark", begin, end) == true && begin == 4 && end == 5);
	// sequence of length 2 (with more occurrances after interesting part of array ends): 
		// returns true and sets begin to 4 and end to 5
	cerr << "detectSequence tests succeeded." << endl;

	// detectMin tests
		string test_detectMin[5] = { "danvers", "banner", "stark", "banner", "" };
		assert(detectMin(test_detectMin, -2) == -1); // negative n, returns -1
		assert(detectMin(test_detectMin, 0) == -1); // n equals zero, returns -1
		assert(detectMin(test_detectMin, 1) == 0); // "danvers" at index 0 minimum in first element
		assert(detectMin(test_detectMin, 3) == 1); // "banner" at index 1 minimum in first three elements
		assert(detectMin(test_detectMin, 4) == 1);
		// "banner" at index 1 minimum (there is another at index 3, but the first one takes precedence)
		assert(detectMin(test_detectMin, 5) == 4); // "" at index 4 minimum in all five elements

	// moveToBack tests
	string test_moveToBack[5] = { "danvers", "banner", "stark", "banner", "" };
	assert(moveToBack(test_moveToBack, -1, -2) == -1); // negative n, returns -1
	assert(moveToBack(test_moveToBack, -1, -2) == -1); // zero n, returns -1
	assert(moveToBack(test_moveToBack, 1, -2) == -1); // negative pos, returns -1
	assert(moveToBack(test_moveToBack, 0, 0) == -1); // position index not in interesting indices, returns -1
	assert(moveToBack(test_moveToBack, 1, 1) == -1); // position index not in interesting indices, returns -1
	assert(moveToBack(test_moveToBack, 5, 0) == 0 && test_moveToBack[0] == "banner"
		&& test_moveToBack[1] == "stark" && test_moveToBack[2] == "banner"
		&& test_moveToBack[3] == "" && test_moveToBack[4] == "danvers");
	// "danvers"  at index 0 moved to end, returns 0
	assert(moveToBack(test_moveToBack, 5, 1) == 1 && test_moveToBack[0] == "banner"
		&& test_moveToBack[1] == "banner" && test_moveToBack[2] == ""
		&& test_moveToBack[3] == "danvers" && test_moveToBack[4] == "stark");
	// "stark" at index 1 moved to end, returns 1
	assert(moveToBack(test_moveToBack, 5, 2) == 2 && test_moveToBack[0] == "banner"
		&& test_moveToBack[1] == "banner" && test_moveToBack[2] == "danvers"
		&& test_moveToBack[3] == "stark" && test_moveToBack[4] == "");
	// "" at index 2 moved to end, returns 2
	assert(moveToBack(test_moveToBack, 5, 3) == 3 && test_moveToBack[0] == "banner"
		&& test_moveToBack[1] == "banner" && test_moveToBack[2] == "danvers"
		&& test_moveToBack[3] == "" && test_moveToBack[4] == "stark");
	// "stark" at index 3 moved to end, returns 3
	assert(moveToBack(test_moveToBack, 5, 4) == 4 && test_moveToBack[0] == "banner"
		&& test_moveToBack[1] == "banner" && test_moveToBack[2] == "danvers"
		&& test_moveToBack[3] == "" && test_moveToBack[4] == "stark");
	// "stark" at index 4 already at end, returns 4
	cerr << "moveToBack tests succeeded." << endl;

	// moveToFront tests
	string test_moveToFront[4] = { "danvers", "banner", "thor", "rogers" };
	assert(moveToFront(test_moveToFront, -1, -2) == -1); // negative n, returns -1
	assert(moveToFront(test_moveToFront, 1, -2) == -1); // negative pos, returns -1
	assert(moveToFront(test_moveToFront, 0, 0) == -1); // zero n, position index not in interesting indices; returns -1
	assert(moveToFront(test_moveToFront, 1, 1) == -1); // position index not in interesting indices, returns -1
	assert(moveToFront(test_moveToFront, 3, 0) == 0 && test_moveToFront[0] == "danvers"
		&& test_moveToFront[1] == "banner" && test_moveToFront[2] == "thor");
	// "danvers" at index 0 already at front, returns 0
	assert(moveToFront(test_moveToFront, 3, 1) == 1 && test_moveToFront[0] == "banner"
		&& test_moveToFront[1] == "danvers" && test_moveToFront[2] == "thor");
	// "banner" at index 1 moved to front, returns 1
	assert(moveToFront(test_moveToFront, 3, 2) == 2 && test_moveToFront[0] == "thor"
		&& test_moveToFront[1] == "banner" && test_moveToFront[2] == "danvers");
	// "thor" at index 2 moved to front, returns 2
	cerr << "moveToFront tests succeeded." << endl;

	// detectDifference tests
	string test_dD1[5] = { "danvers", "banner", "stark", "banner", "" };
	string test_dD2[4] = { "danvers", "banner", "thor", "rogers" };
	string test_dD3[6] = { "romanoff", "banner", "thor", "rogers", "", "danvers" };
	assert(detectDifference(test_dD1, -1, test_dD2, 0) == -1); // negative n1, returns -1
	assert(detectDifference(test_dD1, 0, test_dD2, -1) == -1); // negative n2, returns -1
	assert(detectDifference(test_dD1, 0, test_dD2, 3) == -1);
	// cannot compare any elements, as n1 equals zero; returns -1
	assert(detectDifference(test_dD1, 3, test_dD2, 0) == -1);
	// cannot compare any elements, as n2 equals zero; returns -1
	assert(detectDifference(test_dD1, 1, test_dD2, 3) == 1); // equal up to index 1, returns 1 as indices ran out
	assert(detectDifference(test_dD1, 5, test_dD2, 4) == 2); // index 2 is unequal, returns 2
	assert(detectDifference(test_dD1, 5, test_dD3, 5) == 0); // index 0 is unequal, returns 0
	cerr << "detectDifference tests succeeded." << endl;

	// deleteDups tests
	string test_deleteDups[6] = { "thor", "romanoff", "romanoff", "danvers", "stark", "stark" };
	
	assert(deleteDups(test_deleteDups, -2) == -1); // negative n, returns -1
	assert(deleteDups(test_deleteDups, 3) == 2 && test_deleteDups[0] == "thor"
		&& test_deleteDups[1] == "romanoff");
	// deleted "romanoff" at index 3, only two elements remaining from first three elements; returns 2
	assert(deleteDups(test_deleteDups, 6) == 4
		&& test_deleteDups[0] == "thor" && test_deleteDups[1] == "romanoff"
		&& test_deleteDups[2] == "danvers" && test_deleteDups[3] == "stark");
	// moved romanoff at index 3 and stark at index 5 to end, only four elements remaining from first six elements; returns 4
	assert(deleteDups(test_deleteDups, 6) == 6
		&& test_deleteDups[0] == "thor" && test_deleteDups[1] == "romanoff"
		&& test_deleteDups[2] == "danvers" && test_deleteDups[3] == "stark"
		&& test_deleteDups[4] == "romanoff" && test_deleteDups[5] == "stark");
	// all six elements remain ("romanoff" and "stark" were pushed to back in previous assert call); returns 6
	string test_deleteDups_2[5] = { "danvers", "danvers", "danvers", "thor", "thor" };
	assert(deleteDups(test_deleteDups_2, 5) == 2 && test_deleteDups_2[1] == "thor");
	// two elements ("danvers" and "thor") remain; "danvers", "danvers" and thor pushed to back
	cerr << "deleteDups tests succeeded." << endl;

	// contains tests
	string contains_test[10] = { "danvers", "thor", "stark", "banner", "romanoff", "stark" };
	// main array against which the other arrays will be tested
	string contains_test_2[10] = { "thor", "banner", "romanoff" };
	string contains_test_3[10] = { "stark", "thor" };
	string contains_test_4[10] = { "thor", "stark", "stark" };
	string contains_test_5[10] = { "thor", "thor", "stark" };
	assert(contains(contains_test, -1, contains_test_2, 3) == false); // negative n1, returns false
	assert(contains(contains_test, 6, contains_test_2, -1) == false); // negative n2, returns false
	assert(contains(contains_test, 0, contains_test_2, 0) == true);
	// empty array contains empty array; returns true
	assert(contains(contains_test, 6, contains_test_5, 0) == true);
	// empty array contained in contains_test; returns true
	assert(contains(contains_test, 0, contains_test_2, 3) == false); // n2 > n1, returns false
	assert(contains(contains_test, 6, contains_test_2, 3) == true);
	// "thor", "banner", "romanoff" appear in contains_test in order; returns true
	assert(contains(contains_test, 6, contains_test_3, 2) == false);
	// "stark" does not appear before "thor" in contains_test; returns false
	assert(contains(contains_test, 6, contains_test_4, 3) == true);
	// "thor", "stark", "stark" appear in contains_test in order; returns true
	assert(contains(contains_test, 6, contains_test_5, 3) == false);
	// No "thor" appears after "thor" in contains_test; returns false
	cerr << "All contains tests succeeded." << endl;

	// meld tests
	string meld_result[20];
	string meld_test_1[5] = { "banner", "rhodes", "rogers", "stark", "tchalla" };
	string meld_test_2[4] = { "danvers", "rogers", "rogers", "thor" };
	string meld_test_3[3] = { "rogers", "danvers", "thor" };
	assert(meld(meld_test_1, -1, meld_test_2, 3, meld_result, 9) == -1); // negative n1, returns -1
	assert(meld(meld_test_1, 1, meld_test_2, -3, meld_result, 9) == -1); // negative n2, returns -1
	assert(meld(meld_test_1, 2, meld_test_3, 3, meld_result, 9) == -1); // meld_test_3 is not nondecreasing
	assert(meld(meld_test_1, 2, meld_test_2, 3, meld_result, 4) == -1); // n1 + n2 exceeds max, returns -1
	assert(meld(meld_test_1, 0, meld_test_2, 4, meld_result, 5) == 4
		&& detectDifference(meld_result, 4, meld_test_2, 4) == 4);
	// n1 equals zero, first four elements of meld_result mirror meld_test_2; returns 4
	assert(meld(meld_test_1, 5, meld_test_2, 0, meld_result, 5) == 5
		&& detectDifference(meld_result, 5, meld_test_1, 5) == 5);
	// n2 equals zero, first five elements of meld_result mirror meld_test_1; returns 5
	assert(meld(meld_test_1, 5, meld_test_2, 4, meld_result, 20) == 9 // usual case
		&& meld_result[0] == "banner" && meld_result[1] == "danvers" && meld_result[2] == "rhodes"
		&& meld_result[3] == "rogers" && meld_result[4] == "rogers" && meld_result[5] == "rogers"
		&& meld_result[6] == "stark" && meld_result[7] == "tchalla");
	// both arrays fully merged in meld_test; returns 9
	cerr << "All meld tests succeeded." << endl;

	// split tests
	string split_test_1[6] = { "rhodes", "banner", "stark", "danvers", "thor", "rogers" };
	assert(split(split_test_1, -1, "romanoff") == -1); // negative n, returns -1
	assert(split(split_test_1, 0, "romanoff") == 0);
	// returns n = 0 since no interesting elements >= splitter
	assert(split(split_test_1, 6, "winter soldier") == 6);
	// returns n = 6 since no elements >= splitter
	assert(split(split_test_1, 6, "romanoff") == 4
		&& split_test_1[0] == "rhodes" && split_test_1[1] == "banner"
		&& split_test_1[2] == "rogers" && split_test_1[3] == "danvers"
		&& split_test_1[4] == "thor" && split_test_1[5] == "stark");
	// returns 4 (index of "thor" >= "romanoff"), 
	// array rearranged as { "rhodes", "banner", "rogers", "danvers", "thor", "stark" }
	string split_test_2[4] = { "romanoff", "rogers", "thor", "banner" };
	assert(split(split_test_2, 4, "thor") == 3 && split_test_2[0] == "romanoff" && split_test_2[1] == "rogers"
		&& split_test_2[2] == "banner" && split_test_2[3] == "thor");
	// returns 3 (index of "thor" >= "thor")
	// array rearranged as { "romanoff", ""rogers", "banner", "thor" }
	cerr << "All split tests succeeded." << endl;

	cerr << endl << "All tests succeeded." << endl;
}

int countMatches(const string a[], int n, string target) {
	if (n < 0) // negative n
		return -1;

	int matches = 0; // initialising a variable to store the number of matches

	// running through array
	for (int i = 0; i < n; i++)
		if (a[i] == target)
			matches++; // incrementing matches

	return matches; // returning matches
}

int detectMatch(const string a[], int n, string target) {
	if (n < 0) // negative n
		return -1;

	// running through array
	for (int i = 0; i < n; i++)
		if (a[i] == target)
			return i; // returning smallest position where string is found

	return -1; // no string found
}

bool detectSequence(const string a[], int n, string target, int& begin, int& end) {
	if (n < 0 || countMatches(a, n, target) == 0)
		return false; // negative n, or no occurrences in array

	// setting begin and end to the first index at which target occurs
	begin = detectMatch(a, n, target);
	end = detectMatch(a, n, target);

	// testing whether further consecutive indices equal target
	for (int i = begin + 1; i < n; i++) {
		// string at position i does not equal target
		if (a[i] != target) {
			end = i - 1; // updating end to equal the previous index
			break;
		}
		// loop not broken; the last string also equals target
		if (i == n - 1)
			end = i; // updating end to equal the last index
	}

	return true; // returning true
}

int detectMin(const string a[], int n) {
	// negative or zero n
	if (n <= 0)
		return -1;

	// initialising min_value to store the minimal string, and min_index to store the respective index
	string min_value = a[0];
	int min_index = 0;

	// running through loop (starting from index 1)
	for (int i = 1; i < n; i++)
		// string is less than min_value
		if (a[i] < min_value) {
			min_value = a[i]; // updating min_value
			min_index = i; // updating min_index with position i
		}

	return min_index; // returning the minimum index
}

int moveToBack(string a[], int n, int pos) {
	// negative n or negative pos or pos not in relevant part of a
	if (n < 0 || pos < 0 || pos > n - 1)
		return -1;

	// storing the string to be eliminated
	string eliminated = a[pos];

	// moving all items after pos to the left
	for (int i = pos + 1; i < n; i++)
		a[i - 1] = a[i];

	// adding eliminated string to the end
	a[n - 1] = eliminated;

	// returning pos
	return pos;
}

int moveToFront(string a[], int n, int pos) {
	// negative n or negative pos or pos not in relevant part of a
	if (n < 0 || pos < 0 || pos > n - 1)
		return -1;

	// storing the string to be eliminated
	string eliminated = a[pos];

	// moving all items before pos to the right
	for (int i = pos; i > 0; i--)
		a[i] = a[i - 1];

	// adding eliminated string to the beginning
	a[0] = eliminated;

	// returning pos
	return pos;
}

int detectDifference(const string a1[], int n1, const string a2[], int n2) {
	// negative n1 or n2
	if (n1 <= 0 || n2 <= 0)
		return -1;

	// initialising n to store the number of indices to run through
	int n;
	if (n1 < n2) // n1 is less than n2
		n = n1;
	else // n2 is less than or equal to n1 
		n = n2;

	// running through arrays
	for (int i = 0; i < n; i++)
		if (a1[i] != a2[i]) // comparing elements in each array
			return i;

	// all the elements up to n are equal
	return n;
}

int deleteDups(string a[], int n) {
	// negative n
	if (n < 0)
		return -1;

	// initialising variable to store number of retained elements
	int n_retained = n;

	// running through array
	for (int i = 1; i < n_retained; i++) {

		// if current element equals last element
		if (a[i] == a[i - 1]) {
			moveToBack(a, n, i); // moving current element to the back of the array
			i--; // decrementing i
			n_retained--; // decrementing n_retained
		}
	}

	// returning the number of retained elements
	return n_retained;
}

bool contains(const string a1[], int n1, const string a2[], int n2) {
	// negative n1 or n2 or n2 exceeds n1
	if (n1 < 0 || n2 < 0 || n2 > n1)
		return false;

	// case where we're considering 0 elements from a2
	if (n2 == 0)
		return true;

	// initialising next_index to store the index to start searching from 
		// i.e. the index after that where the last element was found
	int next_index = 0;

	// running through elements of a2
	for (int i = 0; i < n2; i++) {

		// creating a boolean (false by default) to store whether the current element has been found
		bool found = false;

		// running through elements of a1, starting from next_index
		for (int j = next_index; j < n1; j++)

			// elements match
			if (a2[i] == a1[j]) {
				found = true; // element found
				next_index = j + 1; // updating last index
				break; // breaking out of inner loop
			}

		// element wasn't found
		if (found == false)
			return false;
	}

	// all elements were found in the same order
	return true;
}

int meld(const string a1[], int n1, const string a2[], int n2, string result[], int max) {
	// negative n1 or n2, or sum of n1 and n2 exceeds max
	if (n1 < 0 || n2 < 0 || n1 + n2 > max)
		return -1;	

	// checking for whether a1 is nondecreasing
	for (int i = 1; i < n1; i++)
		if (a1[i] < a1[i - 1])
			return -1;

	// checking for whether a2 is nondecreasing
	for (int i = 1; i < n2; i++)
		if (a2[i] < a2[i - 1])
			return -1;

	int next_index = 0; // the next available index in result
	int index_1 = 0; // the next index to be inserted in a1
	int index_2 = 0; // the next index to be inserted in a2

	// loop runs while result isn't populated by all elements of n1 and n2
	while (next_index != n1 + n2) {

		// (a1 hasn't runout) and (a2 has runout or next element from a1 <= next element from a2)
		if (index_1 < n1 && (index_2 == n2 || a1[index_1] <= a2[index_2])) {
			result[next_index] = a1[index_1]; // adding to result
			index_1++; // incrementing index_1
		}
		// adding elements from a2
		// (a2 hasn't runout) and (a1 has runout or next element from a2 <= next element from a1)
		else if (index_2 < n2 && (index_1 == n1 || a2[index_2] <= a1[index_1])) {
			result[next_index] = a2[index_2]; // adding to result
			index_2++; // incrementing index_2
		}
		next_index++; // incrementing next_index
	}

	// retuning total number of elements added to result
	return next_index;
}

int split(string a[], int n, string splitter) {
	// negative n
	if (n < 0)
		return -1;

	// finding the number of elements to come before splitter
	int n_before = 0;
	for (int i = 0; i < n; i++)
		if (a[i] < splitter)
			n_before++;

	// running through first n_before elements of array
		// to exchange elements that come before and after splitter
	for (int i = 0; i < n_before; i++) {

		string temp; // stores an element to be moved after splitter

		// finding element that should come after splitter
		if (a[i] >= splitter) {
			temp = a[i]; // storing element in temp
			// finding element after splitter that should come before
			for (int j = n_before; j < n; j++)
				if (a[j] < splitter) {
					cerr << a[i] << " " << a[j] << endl;
					a[i] = a[j]; // moving element at index j to index i
					a[j] = temp; // moving element at index i (temp) to index j
					break;
				}
		}
	}

	// putting any strings that equal splitter in the right position

	int n_replaced = 0; // initialising n_replaced to store the number of elements replaced by splitter		

	// while loop runs till all splitter strings are in the right position
	while (n_replaced < countMatches(a, n, splitter)) {

		// if splitter not in correct position
		if (a[n_before + n_replaced] != splitter) {

			int replace_index = n_before + n_replaced; // index where splitter needs to be inserted
				
			int splitter_index; // current index of splitter
			// looping through array (after n_before + n_replaced elements) to find splitter
			for (int i = n_before + n_replaced; i < n; i++)
				if (a[i] == splitter)
					splitter_index = i; // updating index of splitter

			// swapping array elements
			a[splitter_index] = a[replace_index];
			a[replace_index] = splitter;
		}
		n_replaced++; // incrementing n_replaced
	}

	// returning position of first element >= splitter
	for (int i = 0; i < n; i++)
		if (a[i] >= splitter)
			return i;

	// no element >= splitter; returning n
	return n;
}