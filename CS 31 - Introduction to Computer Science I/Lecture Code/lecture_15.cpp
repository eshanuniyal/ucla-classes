# include <iostream>
#include <string>

using namespace std;

const int MAX_NAME_LENGTH = 6; // used for string_length function and in main

double day_mean(const int a[][n_days], int n_rows, int day_number);
int strings_with_length(const char a[][MAX_NAME_LENGTH], int n; int target_length);

struct Employee {
	// new structs declared before main() routine
	// naming convention: new types are declared with a capital letter
	string name;
	double salary;
	int age;
	// these are called fields/instance variables/attributes in some languages; in C++, they are called data members
}; // note: there must be a semicolon after the curly braces when declaring a struct

int main() {
	
	const int n_weeks = 5;
	const int n_days = 7;
	
	// two dimensional arrays
	int attendance[n_weeks][n_days];
		// creates an array with five rows and seven columns
		// equivalent to an array of five objects, each of which have seven objects

	cout << attendance[2] << endl;
		// writes out a pointer to &attendance[2][0], not the array at index 2 (since you can't cout entire arrays)
	
	// printing the total attendance for each week
	for (int w = 0; w < n_weeks; w++) {
		int t = 0;
		for (int d = 0; d < n_days; d++)
			t += attendance[w][d];
		cout << "The total for week " << w << " is " << t << endl;
	}

	// finding mean for a day
	double meanWed = day_mean(attendance, n_weeks, 2 /* Wed*/);

	// three dimensional array
	int multiplex[16][5][7]; // screen, week, day

	// Arrays of C-Strings

	const int MAXPETS = 5;
	
	char pets[MAXPETS][MAX_NAME_LENGTH + 1] = { "cat", "mouse", "eel", "ferret", "horse" };
		// initialises an array of C-Strings (because of type "char" and absence of #include <string>)
		// the "+ 1" is to accou ntfor the zero byte character

	// -------------------------------------------------------------------------------------------------------
	// Classes

	// class Employee declared before main routine
	Employee e1;
	Employee e2;

	e1.name = "Fred";
	e.salary = 50000;
	e2.age = 49;

}

double day_mean(const int a[][n_days], int n_rows, int day_number) {
		// we must leave the first dimension empty, but must supply the number of elements in all the remaining dimensions
	if (n_rows <= 0)
		return 0;

	int total = 0; for (int r = 0; r < n_rows; r++)
		total += a[r][day_number];
	return static_cast<double>(total) / n_rows;
}


int strings_with_length(const char a[][MAX_NAME_LENGTH], int n; int target_length) {
	int total = 0;
	for (int i = 0; i < n; i++)
		if (strlen(a[i]) == target_length)
			total++;
	return total;
}