#include <iostream>
#include <string>

using namespace std;

struct Target {

	// if you don't declare public/private member functions or data members, they'll default to public
	// if you instead used "class Target {}", member functions and data members default to private
		// structs and classes are identical in every other way in C++
		// in practice, C++ programmers use "class" for any new type that has any sort of interesting behaviour 
			// such as moving targets
		// any type that simply represents, say, an (x, y) coordinate on a string, would be declared as struct
	public:
		Target() // constructor, called automatically whenever a Target variable is declared
		bool move(char dir);
		void replayHistory() const;
		int position() const; // could also use this member function if you decide you don't want a pos member variable
			// const after function name implies the function doesn't change any values
			// these are called const member functions --> an objects passed into them are treated as constant
		// in C++, these are called member functions
	// other languages may call them methods, operations, et cetera
	

	private: // these values cannot be edited directly 
		// Invariant: 
			// history consists of only Ls and Rs
			// pos = number of Rs - number of Ls in history
		// you can also have private member functions
			// e.g. if you have a bunch of public functions that do the same sorta thing, you can write a helper function for those 
			// and declare it private so the user can't directly call it
		string history;
		int pos;
		// Invariant
		// history consists of only Rs and Ls (right and left movements)
		// the number of Rs minus the number of Ls tells you the position pos
};

// target's initialisation function, equivalent to 
	// void Target::init() {}
Target::Target() {
	pos = 0; // equivalent to this->pos = 0;
	history = ""; // equivalent to this->history = 0;
		// this-> may be left out if and only if there aren't any other variables (say, in main) that use the same name (say, pos or history)
}

bool Target::move(char dir) {

	switch (dir) {
	case 'R': 
	case: 'r' :
		pos++;
		break;
	case 'L':
	case 'l':
		pos--;
		break;
	default:
		return false; // returns false if invalid dir
	}

	history += toupper(dir);
	return true;
}

void Target::replayHistory() const {
	// here, even though we're declaring an integer i, we don't need to declare it as a data member since we don't need to remember it
	for (int i = 0; i != history.size(); i++)
		cout << history[i] << endl;
}

int Target::position() const {
	int current_pos = 0;
	for (int i = 0; i != history.size(); i++)
		if (history[i] == 'R')
			current_pos++;
		else
			current_pos--;
	return current_pos;
}

// a function that is not a member function of Target, but acts as one
// useful if you have a type you can't modify directly but want to set up functions for
// cannot access private member functions or edit private data members
void repeatMove(Target& x, int n_times, char dir) {
	for (int i = 0; i != n_times; i++)
		x.move(dir); // public member function, so we can access it
}

// we pass x by constant reference, so we don't create a copy of the Target member (which may have an expensive, long history variable)
void report(const Target& x) { // WON'T COMPILE, since the compiler doesn't know that x.position() won't modify x
	// to make sure this compiles, we need to let the compiler know that position is a member function that doesn't modify anything
	// check struct Target to see how this is done (int position() const)
	cout << "There's a target at position " << x.position() << endl;
}

int main() 
	// -------------------------------------------------------------------------------------------------------
	// Using struct Target

	Target t;
	Target t2;
	
	t.move('R');
	t.move('R');
	t.move('L');
	t.replayHistory();
	t2.move('L');

	char ch;
	... get a value for ch...
	if (!t.move(ch))
		...error...;

	// declaring an array of Targets
	Target ta[3]; // creates an array of three Targets, with each calling the constructor Target (pos = 0, history = "")
	ta[0].move('R');
	repeatMove(ta[2], 5, 'L');
}

void add_targets(Target* tpa[], int& nt, int n_new) {
	for (int i = 0; i != n_new; i++) {
		tpa[nt] = new Target; // "new" is a keyword of the language that creates a new Target object and returns a pointer to it
			// this target object can be at any available memory location, since it's created dynamically
		nt++;
	}
}

void playGame() {
	Target* targets[100]; // an array of a hundred pointers to a hundred targets (target objects have not yet been created)
	int nTarget = 0;

	// adding targets
	if (...)
		add_targets(targets, n_targets, 3);

	// deleting a target at index n
	// assume there's only three interesting target elements in targets right now

	delete target[n]; // deletes whichever object target[n] points to
		// falling target[n] at any point now is undefined behaviour; target[n] is now a "dangling pointer"
	for (int i = n; i != nTargets - 1; i++) {
		targets[n] = targets[n + 1]; // moves all pointers one index to the left
	} // issue with this code: by overwriting the pointer at targets[n], we no longer have a pointer to point whichever Target object it pointed to
		// we therefore now have a piece of memory we have no way of getting to --> a.k.a. garbage
		// not necessarily an issue, unless we keep doing this; we'll have more and more memory that's garbage, inaccessible, and unavailable for reallocation
		// this is called a memory leak
		// we therefore need to delete the object from memory, so we can give the memory back to the operating system

	targets[nTargets - 1] = nullptr; // resetting last pointer to null pointer; not really necessary if our code is disciplined and we never access it
	nTargets--; // number of interesting targets decreases


	// Variables in memory
		// named local variables ("automatic variables") live on the stack
			// these are automatically deleted whenever the local environment is exited
		// variables declared outside any function live on the "global storage area" (the "static storage area"); aren't deleted during the program
		// dynamic variables live on the "heap"
			// we can use the keyword "delete" to delete them (see line 140)
			// otherwise, these won't be deleted even when the program ends


	int i = 7; // random value
	targets[i]->move('R'); // since targets[i] is a pointer, we use the -> operator instead of the . operator to call a member function
}
// -----------------------------------------------------------------------------------------------------
// Pet and Toy class examples

class Toy {
	...;
};


class Pet {
	public:
		Pet(string nm, int initialHealth); // constructor with two parameters
		Pet(); // constructor with no parameters
		~Pet(); // destructor
		string name() const;
		void addToy();
		void removeToy();
	private:
		string m_name;
		string m_health;
		Toy m_favouriteToy; // if we do this, the pet /must/ have a favourite toy; not a good idea
		Toy* m_favouriteToy; // if no favourite toy, pointer is a null pointer
};

Pet::Pet(string nm, int initialHealth) { // constructor with two parameters
	m_name = nm;
	m_health = initialHealth;
	m_favouriteToy = nullptr;
}

Pet::Pet() { // constructor with no parameters
	m_name = "Hey, you!";
	m_health = 10;
	m_favouriteToy = nullptr;
}

Pet::~Pet() { // special function that executes automatically for any object --> destructor	 
	delete m_favouriteToy; // releases memory allocated dynamically to favourite Toy object
		// this works even if m_favouriteToy is nullptr and addToy was never asked
		// when "delete" is used with a nullptr, nothing happens
}

string Pet::name() const {
	return m_name;
}

void Pet::addToy() {
	delete m_favouriteToy; // deletes previous dynamically allocated favourite toy, if any
	m_favouriteToy = new Toy; // creates a dynamically allocated Toy object
}

void Pet::removeToy() {
	delte m_favouriteToy; // deletes previous dynamically allocated favourite toy, if any
	m_favouriteToy = nullptr; // resets m_favouriteToy to nullptr
}

int main() {
	Pet p1("Fido", 20);
	cout << "I have a pet named " << p1.name() << endl;
	Pet p2; // error, won't compile; missing constructor parameters of type string and int
		// adding a constructor with no parameters fixes this
}

// -----------------------------------------------------------------------------
// Company and Employee examples

class Employee {
	public:
		Employee(string nm, double sal, int ag);
		void receiveBonus() const;
	private:
		string m_name;
		double m_salary;
		int m_age;
		Company* m_company;
};

Employee::Employee(Company* cp, string nm, double sal, int ag,) {
	m_name = nm;
	m_salary = sal;
	m_age = ag;
	m_company = cp;
}

void receiveBonus() const {
	cout << "Pay to the order of " << m_name << "$" << (m_salary * m_company->bonusRate)  << endl;
}

class Company {
	public:
		Company();
		void hire(string nm, double sal, int ag);
		void setBonusRate(double rate);
		void giveBonuses() const;
	private:
		Employee* m_employees[100];
		int m_nEmployees;
		double m_bonusRate;
}

Company::Company() {
	m_nEmployees = 0;
}

void Company::hire(string nm, double sal, int ag) {
	if (m_nEmployees == 100)
		return; // employee array full

	m_employees[m_nEmployees] = new Employee(this, nm, sal, ag); // creates new employee dynamically
		// "this" is a pointer to the company
	m_nEmployees++;
}

void Company::setBonusRate(double rate) {
	m_bonusRate = rate;
}

void Company::giveBonuses() const {
	for (int i = 0; i != m_nEmployees; i++)
		m_employees[k]->receiveBonus();
}

int main() {
	Company myCompany;
	myCompany.hire("Ricky", 80000, 34);
	myCompany.hire("Lucy", 40000, 32);

	Company yourCompany;
	yourCompany.hire("Fred", 50000, 51);

	myCompany.setBonusRate(.02);
	myCompany.giveBonuses();
}