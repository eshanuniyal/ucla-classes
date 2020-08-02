#define _CRT_SECURE_NO_WARNINGS 
	// this line needs to be put before any other #include to turn off Microsoft's warnings about using <cstring>'s functions
#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <cstring> // defines strlen, strcpy, strcat, strcmp
using namespace std;

void makeUpperCase(char s[])

int main() {
	// directional comparison between strings: 
		// the encoding for each character is compared with the encoding for the character at the same index in the other strnig
	string s1 = "hello";
	string s2 = "help";
	string s3 = "helping";
	string s4 = "hElp";

	if (s1 < s2) // true, because 'l' (in index 3) is less than 'p'
		cout << s1 << " is less than " << s2 << endl;
	if (s2 < s3) // true, because s3 contains s2 and has a few more characters
		cout << s2 << " is less than " << s3 << endl;
	if (s2 < s4) // no guarantee here; encoding for upper case characters may be before or after lower case characters, 
			// depends on encoding scheme
			// false in ASCII ('e' > 'E'), true for EBCDIC ('e' < 'E')
		...;

	// -------------------------------------------------------------------
	// C++ Strings
	string s; // empty string
	s = "Hello";
	s_length = s.size(); // .size() method gets the length of the string
	s_4 = s[4]; // can use indexing to refer to characters in a string
	s += '!'; // can append characters or strings to strings

	// -------------------------------------------------------------------
	// C Strings
	// in C, strings are represented by arrays of characters
	char hello[10] = { 'h', 'e', 'l', 'l', 'o', '\0' };
		// the marker of the end of a c-string is the character whose encoding is zero 
			// i.e. the null or NULL character '\0' (a.k.a. the zero byte)
			// whatever is there in the array after the zero byte is irrelevant
	// we may also initialise it as:
	char hello[10] = "hello";
	char s[100]; // initialises an array of 100 unknown characters; not equivalent to "string s;", which creates an empty string
	char t[100] = ""; // initialises an empty string (array with the zero byte at index 0)

	for (int i = 0; ...; i++)
		cout << t[i] << endl;

	int n = strlen(t); // returns the length of string t
		// length of time is proportional to length of string

	cout << s;
	cin.getline(s, 100); // indicates that the input array can have 100 characters
		// getline() as used with regular strings in C++ will not work

	s = t; // won't compile; cannot assign to an array
	
	strcpy(s, t); // strcpy(destination, source);
		// characters are copied index-by-index from source to destination
		// pretty large scope for problems here
		// need to make sure the source string is a valid c-string that ends with a zero byte, 
			// and that the destination array is big enough to store the copied string

	strcat(s, "!!!"); // concatenates "!!!" to s
	s += t; // won't compile, no += operator for arrays

	if (t < s) // will compile, but won't do what you want	
		...;

	if (strcmp(t, s) < 0) 
		// if negative, then t comes before s
		...;
	else if (strcmp(t, s) == 0)
		// if zero, then the strings are equal
		...;
	else if (strcmp(t, s) > 0)
		// if positive, then t comes after s
		...;

	// C++	a OP b
	// C	strcmp(a, b) OP 0
}

// example of a function where we need to deal with a C string
void makeUpperCase(char s[]) {
	// char s[] is a C string
	for (int i = 0; s[i] != '\0'; i++)
		s[i] = toupper(s[i]);
}