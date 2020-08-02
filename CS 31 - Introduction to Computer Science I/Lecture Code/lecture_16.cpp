# include <iostream>
#include <string>

using namespace std;

struct Employee {
	// new structs declared before main() routine
	// naming convention: new types are declared with a capital letter
	string name;
	double salary;
	int age;
	// these are called fields/instance variables/attributes in some languages; in C++, they are called data members
}; // note: there must be a semicolon after the curly braces when declaring a struct

void printPaycheck(const Employee& e);
void celebrateBirthday(Employee e);
double totalPayroll(const Employee emps[], int nEmps);

struct Target {
	
	void init();
	void move(char dir);
	void replayHistory();
	// in C++, these are called member functions
	// other languages may call them methods, operations, et cetera

	int pos;
	int history[]; // won't work, we need to declare the size at compile time and don't know how many movements there will be
	string history; // C++ strings can be added to ad infinitum
		// Invariant
		// history consists of only Rs and Ls (right and left movements)
		// the number of Rs minus the number of Ls tells you the position pos

};

void Target::init() {
	pos = 0; // equivalent to this->pos = 0;
	history = ""; // equivalent to this->history = 0;
}

int main() 
	// -------------------------------------------------------------------------------------------------------
	// Classes

	// class Employee declared before main routine
	Employee e1;
	Employee e2;

	e1.name = "Fred";
	e.salary = 50000;
	e2.age = 49;

	e2.name = "Ethel";
	et2.salary = 60000;
	e2.age = 32;

	Employee company[100]; // creates an array with 100 Employee objects
	company[2].name = "Ricky";

	// runs through array and prints each object's name character by character
	for (int i = 0; i != company[2].name.size(); i++)
		cout << company[2].name[i] << endl;

	printPaycheck(company[1]);
	
	// -------------------------------------------------------------------------------------------------------
	// Using struct Target

	Target t;
	t.init();
	t.move('R');

	Target t2;
	t2.init();
	t2.move('L');
	t2.move('L');

	// right now, nothing stops anyone from changing t.pos or t2. history directly without calling the function move
	// in order for pos and history to be consistent with each other, we don't want to allow that
}

// pass by value version
void printPaycheck(Employee e) {
	// here, e is a copy of the original object company[1]
	cout << "Pay to the order of " << e.name << " the amount $" << e.salary / 12 << endl;
}

// pass by reference version is better, since we don't need to create a copy of the object here
void printPaycheck(const Employee& e) {
	// here, e a reference to the original object company[1]
	cout << "Pay to the order of " << e.name << " the amount $" << e.salary / 12 << endl;
	e.salary != 1.10; // tries to give the employee a 10% raise; won't work, we've declared Employee as a constant object
}

void celebrateBirthday(Employee e) {
	e.age++;
}

// pointer version of celebrateBirthday
void(celebrateBirthday(Employee* ep)) {
	(*ep).age++; // in C++, the . operator has higher precedence than the * operator, so we need to override that by adding brackets
	// an alternative, cleaner way to do exactly the same thing is
	ep->age++;
}

double totalPayroll(const Employee emps[], int nEmps) {
	// takes input array emps of Employee objects and returns the total of all the salaries
	double total = 0;
	for (int i = 0; i < nEmps; i++)
		total += emps[i].salary;
	return total;
}