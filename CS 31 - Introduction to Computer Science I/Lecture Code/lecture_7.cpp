#include <iostream>

using namespace std;

int main(){
	// ----------------------------------------------------------------
	// Continuation of While Loops from Lecture 6

	cout << "How many times do you want to be greeted? ";
	int n_times;
	cin >> n_times;

	int i = 0;
	while (i < n_times) { // loop runs while condition is True
		cout << "Hello" << endl;
		i++;
	}
	// here, if we don't do i++, the loop will run infinitely

	// do-while loops
	do
		statement;
	while (condition);

	// example
	cout << "How many times do you want to be greeted? ";
	int n_times;
	cin >> n_times;

	int i = 0;
	do {
		cout << "Hello" << endl;
		i++;
	} while (i <= n_times);

	// here, the code will run at least once; it will check for the condition only after executing the first "do"
	// also note that the "while (condition);" ends with a semicolon

	// ----------------------------------------------------------------
	// For Loops with Initialisation
	for (initialisation; condition; iteration)
		statement;

	// example
	for (int i = 0; i < length; i++)
		cout << "Hello" << endl;
	
	for (int k = 10; k >= 0; k--)
		cout << k << endl;
		// this is a off-by-one or "fencepost" error - the loop is going to print k 11 times, not 10

	// ----------------------------------------------------------------
	// Accessing individual characters of a string

	string s = "Hello";
	for (int k = 0; k < s.size(); k++) // <string name>.size() returns the number of characters in a string
		cout << s[k] << endl; // s[k] refers to the character at position k in string s

	// code to take an input and count the number of E's (both upper and lower case)
	cout << "Enter some text: ";
	string t;
	getline(cin, t);

	int count = 0;
	for (int i = 0; i < t.size(); i++)
		if (t[i] == 'e' || t[i] == 'E') // note: C++ distinguishes wetween a character and a string
			// t[i] is of type character; comparing it to "e" or "E" would not work, it needs to be comapred to 'e' and 'E'
			count++;

	// New type: Character
	char ch = s[1]; // ch is a character initialised to a lower case e from "Hello"
	// for certain characters that are hard to recognise (such as spaces and tabs), there are character sequences that may be used
	// e.g. '\t' represents the tab character; '\n' represents the new line characters
    }