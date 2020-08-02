#include <iostream> // library for input and output (io)
using namespace std; // reference to library (std::cout, std::cin, et cetera)

int main(){
	// declarating variables:
		// type identifier;
	// double is a type that represents numbers that can have fractional values; range is about 10^-308 to 10^308, precise up to 15 significant digits
	// int is only from -2 billion to 2 billion
	double hoursWorked; // good naming scheme: hoursWorked or hours_worked
	double payRate;

	cout << "How many hours did you work this week? " ;
	cin >> hoursWorked;
	cout << "What is your hourly rate of pay? " ;
	cin >> payRate;


	// Calculating and printing results
	double totalPay = hoursWorked * payRate;

	cout.setf(ios::fixed); // necessary if you want to set precision
	cout.precision(2); // decides how many digits we want to the right of the decimal point

	// Arithmetic Expressions
		// * / + - % (modular operator)
		// multiplication and division take precedence over addition and subtraction
			// e.g. 3 + 2 * 4 = 3 + (2 * 4) --> multiplication takes precedence
			// e.g. 27 / 3 * 3 = (27 / 3) * 3 --> when there's equal precedence, operation proceeds left to right
			// e.g. 6 - 2 + 1 = (6 - 2) + 1 --> when there's equal precedence, operation proceeds left to right
		// float / float = float
		// float / int = float
		// int / float = float
		// int / int = int (rounded off to greatest integer below result e.g. 14 / 5 = 2, not 2.8 or 3)

		// examples of operations
			// Example 1
				// double x = 3.1 + 14 / 5 returns x = 5.1
			// Example 2
				// int a = 10;
				// int b = a * a; --> b = 100
				// int c = 25 / (b - 100) --> runtime error: division by 0
					// Some compilers may check to see whether you're going to be dividing by zero at any point in the program
					// Some compilers may just return the largest possible integer
					// Other compilers may just do nonsensical stuff
					// Reason why running on multiple compilers is quite useful
			// Example 3
				// double d;
				// double e = 2 * d; // undefined behaviour: d is uninitialised
				// cout << e;
					// on most machines, the compiler will just take a random value of d and multiply that by 2
			// Example 4
				// int f = 1000;
				// int g = f * f * f;
				// int h = f * g; // undefined behaviour: 1 trillion cannot be represented by an int, exceeds 2 billion limit of int
					// here, h is going to be given the base-10 value of the last few bits in the binary representation of 1 trillion
					// the program may run successfully, but the resultant value will not be accurate; it may even be negative
			// Example 5
				// double p = 42; // won't convert the double to an integer
				// int i = 42.8; // legal: i will become 42 rather than 42.8
					// may give a warning from the compiler

	cout << endl;
	cout << "You earned $" << totalPay << "." << endl;
	// alternative:  cout << "You earned" << (hoursWorked * payRate) << "." << endl;

	// -------------------------------------------------------------------------------
	// LECTURE 5

	// if-else statement format

	if (condition){
		statementIfTrue
	}
	else{
		statementIfFalse
	}
	
	
	// note: if there's only a single statement, {} not needed

	// typical conditions
		// a > b; a >= b; a < b; a <= b;
		// a != b; a == b; (can also perform these two comparisons with strings)

	// determining withholding rate
	double withholdingRate; // needs to be declared outside the if-else statement; 
		// if declared inside, then the scope will not allow us to use withholdingRate outside
	if (payRate >= 14.00)
		withholdingRate = 0.10; // this is an example of an assignment statement
	else
		withholdingRate = 0.05;

	/* 
	declaration with initialisation: 
		type variable = expression;
	declaration without initialisation, followed by assignment:
		type variable;
		variable = expression;
	*/

	// -----------------------------------------------------------

	// here, note that the "=" sign (or assignment operator) is not the same as the equal sign in mathematics
	// in mathematics, a = b implies that a equals b and that relationship is true; 
		// it's a statement of fact
	// in computer science, a = b wipes out the old value of a and replaces it with the value of b; 
		// it's an assignment action, not a statement of fact
		// after the assignment, the statement becomes a fact

	// a discussion on assignment
	
	int m = 2;
	int n = 3;
	n = 4 * m; // n is now 8
	n = 2 * n; // n is now 16
	...
	int a = 3;
	int b = a + 5; // b is now 8
	a = 4 // b is still 8
	

	// -------------------------------------------------------

	// nested if statements
	if (citizenship == "US)
		if (age >= 18)
			cout << "You are eligible to vote in U.S. elections." << endl;
	else
		cout << "You are not a U.S. citizen." << endl;
	/*
	--- note
	here, each "else" matches up with the nearest preceding "if" that doesn't have an "else" part
	therefore, the "else" on line 123 is not paired with the "if" on line 120 -- it's paired up with the "if" on line 121
	
	--- fix: adding curly braces to the main "if" */
	if (citizenship == "US"){
		if (age >= 18)
			cout << "You are eligible to vote in U.S. elections." << endl;
	}
	else
		cout << "You are not a U.S. citizen." << endl;
	*/
	cout << "$" << (totalPay * withholdingRate) << " will be withheld." << endl;
}
