#include <string>
#include <iostream>
using namespace std;
// -------------------------------------------------------------------------------------------
/* RESOURCE MANAGEMENT
 - We need to manage resources involved in running a program (e.g. memory), since there's a limited amount of them
*/

// e.g. creating a String class

class String {
	public:
		String(const char* value = "");
		String(const String& other); // copy constructor
		String& operator=(const String& rhs); // assignment operator
		~String();
	private:
		char m_text[10];
		char m_text[100000]; 
			// Class invariant:
			// m_text points to a dynamically allocated array of m_len + 1 characters
			// m_len >= 0
			// m_text[m_len] == '\0'
		char* m_text;
		int m_len; 
};

String::String(const char* value)
{
	m_len = strlen(value); 
	m_text = new char[m_len + 1]; // creates a dynamically allocated array to store m_text
	strcpy(m_text, value); // copies value into m_text
}

String::String(const String& other) {
		// copy constructor takes input String address (see h() below)
		// we pass by reference because if we were to pass by value, that passing by value would call the copy constructor, 
			// which would pass by value and call the copy constructor, and it would create an infinite recursion
	m_len = other.m_len;
		// assigns "other"'s m_len to this->m_len
	m_text = new char[m_len + 1];
		// critically important - we don't copy the pointer, we create a pointer to a new address
	strcpy(m_text, other.m_text);
		// this implementation leaves other.m_text intact and ensures passing by value works as expected
		// note: since we are in a member function of the class String, we can talk about private data members of /any/ String objects, including "other"
}

String& operator=(const String& rhs) {
	if (this != &rhs) {
		delete[] m_text; // gets rid of the object m_text points to; necessary because we're about to overwrite the m_text pointer
			// here on, it's similar to the copy constructor
			// ISSUE: if the rhs object is somehow equal to the lhs object (e.g. String t; t = t;), then we won't be able to call strcpy
			// we fix this by checking (this != &rhs)
		m_len = rhs.m_len;
		m_text = new char[m_len + 1];
		strcpy(m_text, rhs.m_text);

		/* NOTE: for builtin types, the assignment operator actually returns the new value
			- if you're writing your own assignment operators, the preferred style is that your assignment operator return a reference to the left hand side object
		*/
	}
	return *this;
		// returns the String that the "this" pointer points to -> an address
}

String::~String() {
	delete[] m_text; // deletes the object m_text points to
}


void f(String t){
	...;
	String u("Wow");
	u = t;
		/* now, we look at how assignment works
		- assignment does not use the copying constructor, since the copying constructor constructs a new object - u, however, has already been constructed
		- the compiler writes an assignment operator for us when we don't specify one - this assignment operator has a similar issue to the default copy constructor, plus one more:
			- the old value of m_text in u, "Wow", never got deleted
		- how do write an assignment operator for the class?
			- maybe we want something that takes u = t, treats it as u.operator=(t) -> a member function called assign that takes a reference object as a parameter
			- refer to assignment operator implementation
			*/
}

void h(){
	String s("Hello");
	f(s);
		/* when we pass the String object s into f by value,
			passing by value implies copying -> we therefore need a copying constructor for each class
			language rule: If we do not declare a copy constructor for a class, the compiler writes one for you
				this default copy constructor creates a new object and copies each data member to the copy
		with the Circle class (lecture 4), we didn't have to worry about creating a copy constructor
			with this class, however, the new object (say, t) will have a data member m_text with the value of s's m_text copied into it
			therefore, the t's m_text will be the same pointer as s's m_text
			this means changes to the object t's m_text points to will also change the object s's m_text point sto since they're identical
		an additional issue
			when f returns, t is gonna go away
			when a String object goes away, its destructor is called, which deletes the object m_text points to
			this means that after we call f on String object s, we'll lose the object m_text points to even though we passed in by value, effectively making s unusable 
				(m_text is now a dangling pointer)
		an additional (related) issue
			when h returns, s goes away
			the destructor will try to delete the object m_text points to, and crash because m_text will be a dangling pointer
	*/

	/* There are two exceptions to when we need to do this:
		1. When the pointer data members of an object don't own the object 
			e.g. if a class object has a pointer but doesn't own the object that pointer points to, we don't need to create the copy constructor
		2. 
	*/
}

int main() {
	String t;

	for (...) {
		h();
	}


}

// ----------------------------------------------------------------------------------
void f(int a, int b = 42, int c = 87);
void f(int a, int b, int c) {}
	// note: C++ language rules do not allow us to specify default values in both the prototype and the constructor
		// usually, we put default values in the prototype, and not the constructor, as is done here

int main() {
	f(10, 20, 30); // equivalent to f(10, 20, 30);
	f(10, 20); // equivalent to f(10, 20, 87);
	f(10); // equivalent to f(10, 42, 87);
	f(10, , 30); // DOES NOT WORK - default values can only be passed in at the end of the list of arguments
}

// ----------------------------------------------------------------------------------