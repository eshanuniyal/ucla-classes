#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// ----------------------------------------------------------------
// Functions (study after code in main())

// you can declare functions in the beginning of main, and then define them after main
void greet(int n_times, string message);
int square(int k);


int main() {
	// ----------------------------------------------------------------
	// Continuation of Character Type from Lecture 7
	// New type: Character
	char ch = s[1]; // ch is a character initialised to a lower case e from "Hello"
	// for certain characters that are hard to recognise (such as spaces and tabs), there are character sequences that may be used
	// e.g. '\t' represents the tab character; '\n' represents the new line characters

	char c = 'x'; // works fine
	char c = "x"; // doesn't work; won't compile
	string s = "x";; // works fine
	string s = 'x'; // doesn't work; won't compile

	// ----------------------------------------------------------------
	// Checking character types in a string
	cout << "Enter a phone number: ";
	string num;
	getline(cin, num);
	
	int n_digits = 0;
	for (int i = 9; i < num.size(); i++)
		if (isdigit(num[i])) // checks if num[i] is a digit; relies on library cctype
			n_digits++;
	if (n_digits != 10)
		cout << "A phone number must contain 10 digits." << endl;

	/* Other cctype functions
	isdigit(ch) '0' '1' '2' ... '9'
	islower(ch) 'a' 'b' 'c' ... 'z'
	isupper(ch) 'A' 'B' 'C' ... 'Z'
	is alpha(ch) 'a' 'b' 'c' ... 'z' and 'A' 'B' 'C' ... 'Z'
	*/

	// to use an if condition where you're checking whether something /isn't/ a certain kind of character, use
		// !isdigit(ch) or isdigit(ch) == false
	// note that only characters are accepted as input in these functions

	// ----------------------------------------------------------------
	// Checking whether a number is in a range
	cout << "Enter a number: ";
	int num;
	cin >> num;

	if (!(num >= 1 && num <= 10)) // adding exclamation mark at the beginning of a condition inverts the result
		cout << "x is not in the range 1 through 10" << endl;
	// better way
	if (num < 1 || num > 10)
		cout << "x is not in the range 1 through 10" << endl;
	
	// ----------------------------------------------------------------
	// Other cctype functions
	
	string s = "hello";
	if (s.size() > 0) // if s were an empty string (length 0), then calling s([0]) would cause an issue
		s[0] = toupper(s[0]); // converts the first letter of s ('h') to uppercase ("H")
	// if the character given as input is not a letter, toupper() just returns the same character

	if (s[0] == 'E' || s[0] == 'e')
		...;
	if (toupper(s[0]) == 'E') // equivalent to line 64
		...;

	// Common mistakes
	string s = "Hello";
	... toupper(s) ...; // won't compile; toupper() must take a character as input

	toupper(s[0]); // will compile, but won't do anything since it wasn't assigned to s[0]
	
	// converting a character to upper case and then back to lower case may not give you the original character
		// for example, e (with an accent) in French will be converted to 'E', and that will then be converted to 'e'
	// tolower(toupper(s[0])) not necessarily equal to s[0]

	// ----------------------------------------------------------------
	// Functions
		// code before main() function
	greet(2, "Hello"); // write out hello three times
	...;
	greet(1, "Hey"); // write out hello three times

}

// note: functions declared before main

void greet(int n_times, string message) { // prints message n_times
	for (int i = 0; i < n_times; i++)
		cout << message << endl;
}
// functions need to be written before the main() function, else they will not be recognised when called inside main()

// syntax of declaring a function
	// void --> function returns nothing
	// int --> function returns an integer (e.g. main() returns 0 or 1 depending on how it runs)

// note: variables declared within a function are only usable within said function


int square(int k) {
	return k * k;
}