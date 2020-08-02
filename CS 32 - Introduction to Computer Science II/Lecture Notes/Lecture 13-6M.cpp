// CLASS TEMPLATES

// these two minimum functions have similar code bodies but return different things
int minimum(int a, int b) {
	if (a < b)
		return a;
	else 
		return b;
}

double minimum(double a, double b) {
	if (a < b)
		return a;
	else
		return b;
}

// -----------------------------------------------------------------------------------------------------
// they can be made more concise with the following code:

template<typename T>	// announces what's coming is a typename template

T minimum(T a, T b) {
	if (a < b)
		return a;
	else
		return b;
}
// -----------------------------------------------------------------------------------------------------

int main() {
	int k;
	cin >> k;
	cout << minimum(k, 10) / 2;
		// here, the compiler goes through a process called "template argument deduction" by looking at the arguments of the function only
		// compiler sees k is of type int, and 10 can be an object of type int
		// compiler than manufactures a function (called an "instantiated template")
			// int minimum(int a, int b)
		// and compiles it so it can be called here
	double x;
	...;
	double y = 3 * minimum(x * x, x + 10);
		// here, similarly, the compiler decides it needs a function
			// double minimum(double a, double b)
	...;
	int z = minimum(0, 3 * k - k + 4);
	...;

	/* A few requirements must be met for this to work properly:
	1. The call must match some template
	2. The instantiated template must compile
	3. The instantiated template must do what you want
	*/

	int k;
	...;
	...minimum(k, 3.5);
		// k is of type int (suggesting T be of type int), but 3.5 is of type double (suggesting T be of type double)
		// template argument deducation therefore doesn't give a consistent value for T, resulting in a compile-time error
}

// #########################################################################################################
template<typename T1, typename T2>
bool isEqualTo(const T1 a, const T2 b) {
	return a == b;
}

void f() {
	int k;
	...isEqualTo(k, 10); // works fine, T1 and T2 are both deduced to be ints
	isEqualTo(k, 3.5); // works fine, T1 is int, T2 is double
	isEqualTo(3.5, k); // works fine, T1 is double, T2 is int
}

// #########################################################################################################
// example of when call doesn't match the template
template<typename T1, typename T2>

? ? ? minimum(const T1 a, const T2 b) {
	// since we don't know what type we'll return (could be double, int), there's really no way to code a function like this
	if (a < b)
		return a;
	else
		return b;
}

// #########################################################################################################
// example of when the instantiated template doesn't compile
class Chicken;
template<typename T>

T minimum(T a, T b) {
	if (a < b)
		return a;
	else
		return b;
}

int main() {
	Chicken c1; Chicken c2;
	...;
	Chicken c3 = minimum(c1, c2);
	/* What does this do?
	If we are going to overload the operator, we have two choices:
		1. Implementing a non-member function (preferred if we can implement without access to private data members)
			e.g.	bool operator==(const string& lhs, const string& rhs)
		2. Implementing a member function
			e.g.	class String{
						bool operator==(const string& rhs) const;
					}
	We must use one and only one of these choices. In the case of assignment operators, we must implement the overloaded == operator as a member function.
	Chances are, the Chicken class doesn't have a defined < operator, since it isn't obvious what any such operator should return.
	This will therefore invariable give us an error
	*/
}

// #########################################################################################################
// example of when the instantiated template doesn't do what we want
template<typename T>

T minimum(T a, T b) {
	if (a < b)
		return a;
	else
		return b;
}

char* minimum(char* a, char* b) {
		// defined to resolve issue in main below
	if (strcmp(a, b) < 0)
		return a;
	else
		return b;
}

int main() {
	char ca1[100]; // C string
	car ca2[100];
	cin.getline(ca1, 100);
	cin.getline(ca2, 100);
	char* ca3 = minimum(ca1, ca2);
		// this will compile, but it'll give us undefined behaviour because we'll really just be comparing the memory addresses
		// a way to fix this is to create another overload of the minimum function that doesn't use template typenames
			// such an overload might be the minimum function defined above
}

// NOTE: Everything about templates, unlike virtual functions in base classes, is decided in compile time

// #########################################################################################################
template<typename T>

T minimum(T a, T b) {
	if (a < b)
		return a;
	else
		return b;
}

T minimum(const T& a, const T& b) {
	// better template function for efficiency reasons
	if (a < b)
		return a;
	else
		return b;
}

int main() {
	ExpensiveToCopyThing x, y;
	...;
	...minimum(x, y);	// here, we don't want to create a function minimum that copies by reference, since what we're copying may be expensive to copy
		// therefore, when we write a template function that doesn't modify the original object in any way, it's better to pass by constant reference
}

// #########################################################################################################
template<typename T>

T sum(const T a[], int n) {
	T total = 0; // this doesn't work
	T total = T(); // this uses the default constructor for type T
		// this works for us, since the default constructor (when called explicitly with ()) is 0
		// total would be 0 for an int or double, false for a boolean, nullptr for a null pointer, empty string for a string, et cetera
	for (int k = 0; k != n; k++)
		total += a[k];
	return total;
}

int main() {
	double da[100];
	...;
	cout << sum(da, 10);
		// works just fine

	string sa[10] = { "This ", "is ", "a ", "test " };
	string s = sum(sa, 4);
		// this won't compile, since in line 178, we can't initialise an object of type string to 0
}

// #########################################################################################################

template<typename T>
class Stack {
public:
	Stack();
	void push(const T& x);
	...;
private:
	T m_data[MAXITEMS];
	int m_top;
};

// note: implemented this way, we can only have a stack of builtin types or a stack of a class type with a default constructor
	// this is required because when the constructor of the stack is called, m_data is going to be populated with default-constructed T objects;
		// T must therefore have a default constructor (or be a builtin type)

template<typename T>
void Stack<T>::Stack() {
	// two things to notice here:
		// we need to write template<typename T> before every single member function we implement
		// we write Stack<T> in the heading defining member functions
}

// #########################################################################################################
// C++ STANDARD TEMPLATE LIBRARY (STL)
/* The library provides various types and functions:
	- Stacks and queues
	- Vectors (dynamically resizeable array)
*/

#include <vector>
using namespace std;

int main() {
	vector<int> vi; // initialised with size 0
	vi.push_back(10);
	vi.push_back(20);
	vi.push_back(30);
	cout << vi.size(); // writes 3
	cout << vi.front(); // writes 10
	cout << vi.back(); // writes 30
	vi[1] = 40;
	// vi[3] = 50; would be undefined behavior
	for (size_t k = 0; k < vi.size(); k++)
		cout << vi[k] << endl;
	// writes 10 40 30, one per line
	vi.pop_back(); // removes item at back
	for (size_t k = 0; k < vi.size(); k++)
		cout << vi[k] << endl;
	// writes 10 40, one per line
	vi.at(1) = 60; // equivalent to v[1] = 60;
	vi.at(3) = 70; // throws exception
	vector<double> vd(10);
	// vd.size() is 10, each element is 0.0
	vector<string> vs(10, "Hello");
	// vs.size() is 10, each element is "Hello"
	int a[5] = { 10, 20, 30, 40, 50 };
	vector<int> vx(a, a + 5);
	// vx.size() is 5, vx[0] is 10, vx[1] is
	// 20, ..., vx[4] is 50
}