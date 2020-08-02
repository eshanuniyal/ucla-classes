#include <string>
#include <iostream>
using namespace std;

class Circle {
	public:
		Circle(double x, double y, double r);
		...;
	private:
		double m_x;
		double m_y;
		double m_r;
};

Circle::Circle(double x, double y, double r) 
	: m_x(x), m_y(y), m_r(r){
	if (r <= 0) {
		cout << "Cannot create a circle with radius " << r << endl;
		exit(); 
	}
}

class StickFigure {
	public:
		StickFigure(double bl, double headDiamter, string nm, double hx, double hy);
		...;
	private:
		string m_name;
		Circle m_head;
		double m_bodyLength;
};

// Steps of construction
	// 1. ........
	// 2. Construct the data members, using the member initialisation list; if a member is not listed:
		// * If a data member is of a builtin type, it's left initialised
		// * If a data member is of a class type, the default constructor is called for it; error if there is none
	// 3. Execute the body of the constructor

StickFigure::StickFigure(double bl, double headDiameter, string nm, double hx, double hy)
	: m_name(nm), m_head(hx, hy, headDiameter / 2), m_bodylength(bl) {
	// we construct m_head in the member initalization list; if we put it in the body instead, the compiler will first try to construct it with a default constructor (zero-argument constructor)
		// and throw an error when it sees that there isn't one
		// this is a case where we use the member initialisation list because we have to
	// with some other builtin types (e.g. m_name, a string), we /can/ put them in the body, but it's wasteful - they will be constructed with default values and then be overwritten
		// this is a case where we put the variable in the member initialisation list because it's more efficient
	// always try to initialise as many members with the member initialisation list as possible
	if (bl <= 0) {
		cerr << "......." << endl;
		exit(1);
	}
}

// -------------------------------------------------------------------------------------------
class A {
	A(int i);

	// string m_s;
	// int m_num;

	int m_num;
	string m_s;
};

A::A(int i)
	: m_num(2 * i), m_s(m_num, '*') {}
		// note: m_s is a string type, and we can create strings with two parameters; the first determines how many times the second is to be repeated e.g. sample(3, '*') creates "***"
	// this will not work, since the data members are initialised in the order in which they are declared in the class - not the order they are listed in the member initialisation list
	// for this to work, we would therefore need to declare m_num before m_s in the class declaration
		// it's therefore good practice to always list items in the member initialisation list in the order they are declared, or change the order they are declared so the
			// initialisation list works as expected

int main() {
	A a(3);
}

// -------------------------------------------------------------------------------------------
/* RESOURCE MANAGEMENT
 - We need to manage resources involved in running a program (e.g. memory), since there's a limited amount of them
*/

// e.g. creating a String class

class String {
	public:
		String(const char* value);
		String(); // default constructor
		~String();
	private:
		char m_text[10]; // 10 would mean nine interesting characters plus a zero byte
		char m_text[100000]; // should be able to hold most strings, but most such strings would take up much more memory than needed
		// a better way to go about it is to create a pointer that dynamically allocates as much memory as we need

			// Class invariant:
			// m_text points to a dynamically allocated array of m_len + 1 characters
			// m_len >= 0
			// m_text[m_len] == '\0'

		char* m_text;
		int m_len; // if we specify the length of the string, then functions won't have to expensively compute its length when they need that (and we no longer need a zero byte character)
			// however, we still want a zero byte character so we can use the C-libraries functions for strings/C-strings, which requires there be a zero byte to know a string ends
};

String::String(const char* value = "") 
	// default parameter value is ""
		// for reasoning, read String::String()
{
	// what we get is a pointer to the first character; we don't yet know the length of the string
	m_len = strlen(value); // we can use the C-library to find strlen (it returns the number of characters before the zero byte starting at the given pointer)
	
	// m_text = value; // pointer m_text set to pointer to the first character
		// not a good idea - see example in void() for explanation

	m_text = new char[m_len + 1]; // creates a dynamically allocated array to store m_text
		// note: for a dynamically allocated array, we don't need to know its size until compile time
	strcpy(m_text, value); // copies value into m_text
}

// entirely useless - read through and then refer to String constructor declaration
String::String() {
	// default constructor creates the empty string
	m_len = 0;
	m_text = new char[1];
		// we create an array of length 1 instead of just creating a character, since we only have one destructor and it expects an array
	m_text[0] = '\0';

	// rewriting default constructor so it's similar to the main constructor
	m_len = strlen(""); // equivalent to m_len = 0;
	m_text = new char[m_len + 1]; // equivalent to new char[1];
	strcpy(m_text, ""); // equivalent to m_text[0] = '\0';
		// this implementation of the default constructor is identical to the main constructor, with value swapped out for ""
		// when we declare a function, we can provide for optional parameters - we might as well get rid of our default constructor,
			// and make value an optional parameter in the main constructor with default value ""
}

String::~String() {
	delete [] m_text; // deletes the object m_text points to
		// in C++, we can either dynamically allocate a single object or an array of objects
		// if it's an array of objects we're looking at that start at a certain address, we use the [] operator to indicate we want to delete the entire array
		// if we use the wrong kind of delete, it's undefined behaviour
}

void{
	String s("Hello");
		// constructing a String object using the C-string "Hello" (equivalent to {'H', 'e', 'l', 'l', 'o', '\0'}
	char buffer[1000];
		// create a 1000 byte array
	cin.getline(buffer, 1000);
		// take input and store into buffer; say, "Hello" -> {'H', 'e', 'l', 'l', 'o', '\0', ...}
	String s2(buffer);
		// creates a string s2 with m_len = 5 and m_text pointing to position of 'H' (first character address of buffer)
	cin.getline(buffer, 1000);
		// takes input and stores into buffer; say, "wow"
		// ISSUE: s2 now points to a different string and has the incorrect length
		// this issue arises because of a problem with our implementation: 
			// m_text = value does not satisfy the class invariant of m_text pointing to a /dynamically allocated/ array, since value might not be dynamically allocated
}

int main() {
	String t;
		// do we want a default constructor? Is there a value everyone would expect t to have as default?
			// in this case, yes, because most people would consider the empty string "" a natural default

	for (...) {
		h(); // some function that does something with String objects
			// when we exit h(), the dynamically allocated array is not deleted automatically (even though the String object pointing to it is deleted)
				// this is a memory leak - after some large number of runs, we'll run out of memory and the program crashes
			// therefore, we need to make sure that before our String objects are deleted, the dynamically allocated arrays are deleted
			// we do this via the destructor function in String
	}
}