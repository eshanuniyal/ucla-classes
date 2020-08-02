#include <iostream> 
using namespace std; 

// lines 6 to 21 imported from lecture_3.cpp
int main() {
	double payRate;

	cout << "How many hours did you work this week? ";
	cin >> hoursWorked;
	cout << "What is your hourly rate of pay? ";
	cin >> payRate;


	// Calculating and printing results
	double totalPay = hoursWorked * payRate;

	cout.setf(ios::fixed);
	cout.precision(2); 

	cout << endl;
	cout << "You earned $" << totalPay << "." << endl;
	
	/* if-else statement format

	if (condition){
		statementIfTrue
	}else{
		statementIfFalse
	}

	*/
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

	cout << "$" << (totalPay * withholdingRate) << " will be withheld." << endl;

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
	/*
	int m = 2;
	int n = 3;
	n = 4 * m; // n is now 8
	n = 2 * n; // n is now 16
	...
	int a = 3;
	int b = a + 5; // b is now 8
	a = 4 // b is still 8
	*/

	// -------------------------------------------------------

	/* nested if statements
	--- code
	if (citizenship == "US)
		if (age >= 18)
			cout << "You are eligible to vote in U.S. elections." << endl;
	else
		cout << "You are not a U.S. citizen." << endl;

	--- note
	here, each else matches up with the nearest preceding if that doesn't have an else part
	therefore, the "else" on line 123 is not paired with the "if" on line 120 -- it's paired up with the "if" on line 121

	--- fix: adding curly braces to the main "if"
	if (citizenship == "US){
		if (age >= 18)
			cout << "You are eligible to vote in U.S. elections." << endl;
	}
	else
		cout << "You are not a U.S. citizen." << endl;
	*/

	/* "or" operator: ||
	if (citizenship == "US" || citizenship == "Canada")
		cout << "The country code is 1" << endl;
	--- note
	(citizenship == "US" || "Canada") 
	// will compile, but will always give you a True result (because "Canada" is not 0, and is therefore not False, and is therefore True)
	(citizenship == "US" || == "Canada") // might compile, but will not work as expected
	(rating >= 1 && <= 10) // error
	*/

	/* "and" operator: &&
	if (citizenship == "US" && age >= 18)
		cout << "You are eligible to vote in U.S. elections." << endl;
	--- note
	&& operator has higher precedence than ||
	--- example
	if (citizenship == "US" || citizenship == "Canada" && age >= 18) // will not work; and has higher precedence than or
	--- fix
	if ((citizenship == "US" || citizenship == "Canada") && age >= 18)

	*/
}
