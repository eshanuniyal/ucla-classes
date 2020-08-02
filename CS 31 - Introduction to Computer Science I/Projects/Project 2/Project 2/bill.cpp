#include <iostream>
#include <string>

using namespace std;

int main(){
	// collecting initial and final meter readings
	cout << "Initial meter reading: ";
	double initial_reading;
	cin >> initial_reading;

	cout << "Final meter reading: ";
	double final_reading; 
	cin >> final_reading;

	cin.ignore(10000, '\n'); // necessary to use getline() satisfactorily after cin

	// collecting customer name
	cout << "Customer name: ";
	string customer_name;
	getline(cin, customer_name);

	// collecting month number
	cout << "Month number (1=Jan, 2=Feb, etc.): ";
	int month;
	cin >> month;
	
	// --------------------------------------------------------------------------
	// calculations

	// deciding season --> second tier rates and cutoff for first tier
	double second_tier; double tier_cutoff;
	
	if (month >= 4 && month <= 10){ // if month lies between April and October
		second_tier = 3.39;
		tier_cutoff = 43;
	}else{ // if not between April and October, month has to lie between March and December
		second_tier = 2.87;
		tier_cutoff = 29;
	}

	// calculating meter usage
	double meter = final_reading - initial_reading;
	
	// declaring first tier cost and total cost variables
	double first_tier = 2.71;
	double amount = 0;

	if (meter <= tier_cutoff)
		amount = meter * first_tier;
	else
		amount = tier_cutoff * first_tier + (meter - tier_cutoff) * second_tier;

	// note: meter and tier_cutoff have been cast as doubles to avoid an overflow warning (C26451) 
		// in Visual Studio in the (meter - tier_cutoff) bracket in line 52

	// --------------------------------------------------------------------------
	// printing output
	cout << "---" << endl;

	// negative initial reading
	if (initial_reading < 0)
		cout << "The initial meter reading must be nonnegative.";
	// final reading exceeds initial reading

	else if (final_reading < initial_reading)
		cout << "The final meter reading must be at least as large as the initial reading.";

	// empty string provided for consumer name
	else if (customer_name == "")
		cout << "You must enter a customer name.";

	// month number is not an integer between 1 and 12
	else if (month < 1 || month > 12)
		cout << "The month number must be in the range 1 through 12.";

	// all checks are passed
	else {
		// setting precision of output bill to two decimal points
		cout.setf(ios::fixed);
		cout.precision(2);

		cout << "The bill for " << customer_name << " is $" << amount << endl;
	}
}