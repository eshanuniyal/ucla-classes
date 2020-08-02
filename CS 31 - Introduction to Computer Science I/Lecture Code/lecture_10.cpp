#include <iostream>
#include <string>
#include <cctype>

using namespace std;

void exchange(int& x, int& y);
bool is_valid_date(int y, int m, int d);

int main() {
	
	// Ending a specific iteration of a loop - continue
	for (...; ...; ...) {
		...;
		...;
		if (...; ...; ...) {
			...;
			...;
			continue; // ends the current iteration, moves on to next iteration
		}
		// code after this line will not be run if first if condition was satisfied, because of continue;
		...;
		...;
		if (...; ...; ...)
			...;
	}

	// break:		abandon this and all ramining iterations
	// continue:	abandon this iteration of the loop

	int a;
	int b;
	cin >> a >> b;
	if (a < b)
		exchange(a, b);
	else
		cout << a << " is at least as big as " << b << endl;

	// -----------------------------------------------------------------------------------
	// Character Comparison and Encoding

	char ch = 76; // legal in C++; whichever character has encoding 76 will be assigned to ch
		// 'L' in ASCII, "<' in EBCDIC
	int k = 'L'; // 76 if ASCII, 211 if EBCDIC

	/*
	The following few relationships are guaranteed in C++:
	' ' < 'A' < 'B' ... 'Y' < 'Z'
	' ' < 'a' < 'b' ... 'y' < 'z'
	' ' < '0' < '1' ... '8' < '9'
	Relative ordering of upper and lower case letters depends on the encoding
	*/

	ch++; // increments the encoding of the character
		// in ASCII, 76 ('L') becomes 77 ('M')

	double d = 3.68;
	cout.setf(ios:fixed);
	cout.precision(1);

	cout << d; // calls the function for double: writes '3' '.' '7'
		// if ASCII, this is 51 46 55
		// in EBCDIC, this is 243 75 247

	int k = 77;
	cout << k; // calls the function for int; writes '7' '7'
		// if ASCII, this is 55 55
		// if EBCDIC, this is 247 247
	cout << ch; // calls the function for character; 
		// writes 'M' if ASCII, '(' if EBCDIC
		// in both, encoding is 77

	// therefore, cout << k writes 77 since k is declared as an int; 
		// cout << ch writes a character ['M' or '('] depending on the encoding scheme

	ch = 1089; // too big for the one-byte character type, which can only take values from 1 to 127/255 
			// (depends on whether it's interpreted as a signed or unsigned quantity)
		// the actual value that ch gets assigned to depends on the compiler
		// probably going to store 1089 % 256 = 65, which is 'A' in ASCII

	char ch = 'a';
	cout << toupper(ch) << endl; // writes '65', since 65 is the ASCII code for 'A' and 
		// toupper() returns the integer representing the ASCII code for the character, not the character itself
	ch = toupper(ch);
	cout << ch << endl; // writes 'A', since toupper(ch) was assigned to a variable with type character in the above line

	if (isupper(ch) == true) // do not do this; this may not work
		...;
		// isupper() returns an integer, not a boolean
		// if isupper() wants to say "false", it returns 0
		// if isupper() wants to say "true", it returns a non-zero integer
			// here lies the issue: we are comparing a non-zero integer with "true", which is defined as "1"
			// therefore, if isupper() returns 7 when true, comparing it with true (or 1) yields false
		// this applies to all cctype functions

}

// function to exchange values of x and y; x and y are passed-by-reference
void exchange(int& x, int& y) {
	int t = y;
	y = x;
	x = t;
}

bool is_valid_date(int y, int m, int d) {
	if (m < 1 || m > 12 || d < 1)
		return false;
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
		return (d <= 31); // returns true if the statement inside the brackets is true
	if (m == 4 || m == 6 || m == 9 || m == 11)
		return (d <= 30);
	// at this point, m must be 2
		// deal with leap/non-leap year...

	// a rather tedious way to do it: use arrays?

	// --------------------------------------------------------------------------
	// Arrays

	const int n_months = 12;

	const int days_in_month[n_months] = {
		31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31
	}; // creates an array of 12 integers
	// const makes the array unmodificable

	if (m != 2)
		return (d <= days_in_month[m - 1]);

	// printing months
	// Could use a switch statement to look at the month number and print the month name
	// Better way: use an array

	const string month_names[n_months] = {
		"January", "February", "March",
		"April", "May", "June",
		"July", "August", "September"
		"October", "November", "December"
	}; // declares an immutable array of twelve strings

	for (int i = 1; i <= n_months; i++)
		cout << month_name[m - 1] << endl;

	// printing all months with a specific number of days
	cout << "These months have 31 days:" << endl;
	for (int i = 0; i < n_months; i++)
		if (days_in_month[i] == 31)
			cout << month_name[i] << endl;

	// finding length of an array
	// days_in_month.size() does not tell you how big it is
	// days_in_month.length does not tell you how big it is




}