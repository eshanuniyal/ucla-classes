#include <iostream>

using namespace std;

int main(){
    // continuation of if statements

    // if (a/b + c/d > 10)
        // underfined behaviour if b or d are 0
    // if (a/b + c/d > 10 && b != 0 && d != 0)
        // still undefined behaviour: with || and &&, C++ evaluates the first expression (a/b + c/d > 10) before looking at the other ones
    if (b != 0 && d != 0 && a/b + c/d > 10)
        // correct expression; (a/b + c/d > 10) will only be tested if a != 0 and b != 0
    
    int n = 17;
    cout << "n is " << n << endl;
    if (n = 0) // problem: == needs to be used, rather than =
        cout << "n is zero" << endl;
    else
        cout << "n is not zero; n is " << n << endl;

    /* Output
    n is 17
    n is not zero; n is 0
    --- problem
    here, not only is n reassigned to 0, but the assignment also returns something
    therefore, (n = 0) returns n, which is 0
    0 is treated as false
    */
    
    // stylistic recommendation: write if-else statements where the condition is such that the if part is shorter, and the else part longer
    // example of bad style
    if (citizenship != "US" || age < 18)
    {
        ...
        ...
    }
    else
        cout << "You can vote in U.S. elections" << endl;
    
    // example of good style - here, the if and else statements are closer to each other and therefore easier to read
    if (citizenship == "US" && age >= 18) 
        cout << "You can vote in U.S. elections" << endl;
    else
    {
        ...
        ...
    }
    
    // observe how the condition changed: != became == for checking citizenship, || became &&, and < became >=

    /* De Morgan's Laws
    not (A or B) --> (not A) and (not B)
    not (A and B) --> (not A) or (not B)
    */


	// Example of if-else nesting
	if (income < 30000)
		cout << "Low";
	else {
		// if (income >= 30000 && income < 100000) --> inefficient; do not need to test whether income is greater than 30000
		if (income < 100000)
			cout << "Middle";
		else {
			// if (income >= 100000 && income < 500000) --> inefficient; do not need to test whether income is greater than 100000
			if (income < 500000)
				cout << "High";
			else
				cout << "Very high";
		}
	}

	// Alternative, better way of writing this: "if ladder"
	if (income < 30000)
		cout << "Low";
	else if (income < 100000)
		cout << "Middle";
	else if (income < 500000)
		cout << "High";
	else
		cout << "Very High";

	// ----------------------------------------------------------------
	// Switch Statements
	switch (choice) { // choice can only be an integer expression 
		case 1:
			...
			break; // exits switch statement
		case 2:
		case 4: 
			... // if case 2 or case 4, do this
			break; 
		case 3:
		case 5:
			... // if case 3 or case 5, do this
			break;
		default:
			cout << "Choice must be 1 through 5." << endl;
	}

	// ----------------------------------------------------------------
	// While Loops

	cout << "How many times do you want to be greeted? ";
	int n_times;
	cin >> n_times;

	int i = 0;
	while (i < n_times) { // loop runs while condition is True
		cout << "Hello" << endl;
		i++;
	}
	
	// ----------------------------------------------------------------
	// Abbreviations of operators
	
	/*
	Division			i = i / 7	-->		i /= 7
	Multiplication		i = i * 7	-->		i *= 7
	Addition			i = i + 7	-->		i += 7
	Subtraction			i = i - 7	-->		i -= 7

	Adding one			i += 1		-->		i++
	Subtracting one		i -= 1		-->		i--
	*/

    }