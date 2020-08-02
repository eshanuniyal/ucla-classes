#include <iostream>
#include <string>
#include <cctype>
#include <cmath> // gives access to math functions like sine and cosine

using namespace std;

bool is_valid(string input); // bool = boolean = type that returns true (or 1) or false (or 0)
string digits_of(string input);
void greet(int n_times, string message);
void polar_to_cartesian(double rho, double theta, double x, double y);

int main() {

	cout << "Enter a phone number: ";
	string phone;
	getline(cin, phone);
	
	while (!is_valid(phone)) {
		cout << "A phone number must have 10 digits; try again." << endl;
		cout << "Enter a phone number: " << endl;
		getline(cin, phone)
	}
	// asking for the phone number in line 15 and then again in 21 is a bit redundant; not the best way to go about it

	// Better implementation - no repetitive code, easy to read
	// This struction is often called a "n-and-a-half-times loop"
		// you don't go through the full loop; you usually get out halfway at some point

	string phone;

	// while (true) { // loop runs until it is manually broken out of due to the break in line 35
	for (;;) // equivalent to "while (true)" - syntax catches your eye to make it clearer that you're using an n-and-a-half-times loop
		// in this for condition, you don't initialise anything, you leave the condition empty (equivalent to true, and you don't need to increment i because there isn't an i
		cout << "Enter a phone number: " << endl;
		getline(cin, phone);
		
		if (is_valid(phone))
			break; 
		// the break statement allows you to leave the loop; the code within the loop after break is not executed either
		
		cout << "A phone number must have 10 digits; try again." << endl;
	}

	cout << "The digits in the number are " << digits_of(phone) << endl;

	// Booleans in C++: true = 1; false = 0
	
	//Common mistake: consider the following expression

	// if (1 <= x <= 10)
		/* here, it's going to evaluate (1 <= x) first, since comparison operators move left to right
		this will return either true (1) or false (0), depending on the value of x
		it will then compare the value 1 or 0 with 10, and since 1 <= 10 and 0 <= 10, it will return true
		therefore, this would return true no matter what the value of x is, and it won't give any compile errors since such code is legal in C++
		*/

	// --------------------------------------------------------------------------------------
	// Using the polar_to_cartesian function (written below)
	double r;
	double angle;
	...; // get values r and angle
	double x;
	double y;
	polar_to_cartesian(r, angle, x, y);
	...;
	double x2;
	polar_to_cartesian(2 * r, angle, x2, y);
		
}

// ---------------------------------------------------------------------------------------
// Functions

bool is_valid	(string input) {
	// function to test whether input string is a valid phone number (has 10 digits)
	int n_digits = 0;

	for (int i = 0; i != input.size(); i++)
		if (isdigit(input[i]))
			n_digits++;

	if (n_digits == 10)
		return true;
	else // whenever writing a function to return a boolean, be sure to write both true and false return statements
		return false;
}

string digits_of(string input) {
	// function to return the actual phone number
	string digits = "";

	for (int i = 0; i != input.size(); i++)
		if (isdigit(input[i]))
			digits += input[i]; // way to append a character onto the end of a string
			// digits.append(input[i]) // alternate method: works with both characters (such as input[i]) and strings (such as input itself)

	return digits;
}

/* Testing whether a program worked
Every program, when it finishes, has an "exit status".
The exit status is a small integer, generally limited to the range 0 to 127. It represents whether the program worked or not.

If the program believes it worked (no compile errors and such) --> exit status = 0 (success)
If the program believes it failed (some sort of error) --> exit status = non-zero *(failure; likely 1; other numbers would give some information about how it failed)
	be careful: 0 as a boolean is False, but as an exit status, it means the program worked fine (counterintuitive)
*/

void greet(int n_times, string message) { // prints message n_times
	if (n_times < 0) {
		cout << "I can't greet you a negative number of times!" << endl;
		return 1; // indicates problematic input
	}
	for (int i = 0; i < n_times; i++)
		cout << message << endl;
}

/*
void polar_to_cartesian(double rho, double theta, double xx, double yy) { // does not work!
	// rho = distance from origin, theta = angle
	xx = rho * cos(theta); 
	yy = rho * sin(theta);
	// these new values of xx and yy are contained to polar_to_cartesian; the value of input parameters (x and y) in main() are not changed
	// xx and yy are local variables, not global variables
}
*/

void polar_to_cartesian(double rho, double theta, double& xx, double& yy) { // correct version: note the ampersands in parameter declaration
	// "double&" makes xx and yy "references" to the original objects x and y, without creating a new local copy
	// a reference is just another name for an already existing object; allows the function to change things in the original environment
	xx = rho * cos(theta); // stores new value in original x in main()
	yy = rho * sin(theta); // stores new value in original y in main()

	// rho and theta will still be initialised as copies, while xx is just another name for x and yy is just another name for y
}