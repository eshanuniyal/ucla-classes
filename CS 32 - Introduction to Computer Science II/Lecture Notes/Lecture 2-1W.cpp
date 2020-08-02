#include <iostream>
#include <cstdlib>
	// defines exit()

const double PI = 3.1416;
	// for consistent use of pi

using namespace std;

class Circle{
	public:
		Circle(double x, double y, double r);
		void scale(double factor);
		void draw() const;
			// this public section of the class is the interface
		double radius() const; // necessary for area()
			// we specify const because if we don't, area(const Circle& x) won't allow us to call radius
	private:
		double m_x; // class invariant: m_x > 0
			// think about whether a circle with radius 0 should be considered a valid circle
		double m_y;
		double m_r;
			// data members, unless absolutely necessary, should be created privately
}; // don't forget a semicolon when declaring a class

// -----------------------------------------------------------------
double area(Circle x){
	// this is also part of the interface
	// however, it creates a new copy of the Circle object - in some cases, this approach may be expensive
	return PI * (x.radius() ** 2)
}

// alternative (more efficient) implementation of area():
double area(const Circle& x) {
	// passing by reference avoids the expensive copying
	// we could pass by pointer, but then risk someone passing in a nullpointer in the function (which it can't use .radius() on)
	// however, since we're passing by reference and don't want any implementation of this function to change the Circle object, we use the const keyword 
	return PI * (x.radius() * *2);
		// the compiler doesn't know whether .radius() modifies the circle object, and will therefore not compile
			// we need to put const after radius() in the class definition to account for this
}
// -----------------------------------------------------------------

Circle::Circle(double x, double y, double r){
	if (r <= 0){ // checking if negative r
		cout << "Cannot create a circle with radius " << r << endl;
		exit(); // defined by <cstdlib> - takes parameter exit status, which indicates
			// whether a program believes it succeeded or failed
			// 0 indicates a program believes it worked
			// non-zero value indicates failure, and might indicate why a program failed
	}
	m_x = x;
	m_y = y;
	m_r = r;
}

bool Circle::scale(double factor){
	// returning a boolean instead of void, to indicate whether we were able to scale the radius 
		// (i.e. to indicate whether the factor was positive)
	if (factor <= 0) // checking whether factor is positive
		return False;
	m_r *= factor;
	return True;
}

void Circle::draw() const{
	// draw the circle using m_x, m_y, m_r
}

double Circle::radius() const{
	return m_r;
}

int main(){
	Circle blah(8, -3, 3.7); // creates a circle centered at (8, -3) with radius 3.7
	Circle c(-2, 5, 10);
	c.scale(2); // scales the circle by a factor of 2 using scale method from Circle class
	c.draw(); // draws the circle using draw method from Circle class

	double ff;
	cin >> ff;
	if (!c.scale(ff))
		// error
}

// -----------------------------------------------------------------------------------------------------
/* There are two steps to compiling:
	1. Converting the source files to object files
	2. Combining the object files via a linker to create the executable file
		i.e. source files ---------(compiler)-----------> object files ---------(linker)------------> executable file
There are three conditions to a working linker:
	1. Every need must be satisfied (error message: undefined symbol, unresolved reference, or something)
	2. Nothing must be defined more than once (error message: multiply-defined symbol)
	3. There must be exactly one main() function.

*/// ------------------------------------------------------------------
// myapp.cpp
	// defines: main()
	// needs: f(double x), << (provided by iostream), cout (provided by namespace std)

#include <iostream>
using namespace std;

void f(double x);
	// necessary to avoid compiling error with myapp.cpp

int main() {
	double a = 3;
	f(a);
	cout << a;
}

// --------------------------------------------------------------------
// stuff.cpp
	// defines: f(double x)
	// needs: sin (provided by cmath)

#include <cmath>
using namespace std;

void f(double x) {
	// ...
	sin(x);
		// no prototype needed because the header #include <cmath> automatically gives stuff.cpp access to all cmath functions
	// ...;
}

// -----------------------------------------------------------------------------------------------------
// myapp.cpp
#include "Circle.h"

int main() {
	Circle c(-2, 5, 10);
	c.draw();
	// ...
}
// --------------------------------------------------------------------
// Circle.h
// we put the prototype of the class and and any related non-member functions in the "header file"

class Circle {
	public:
		Circle(double x, ...);
		void draw() const;
	private:
		// ...
};

// --------------------------------------------------------------------
// Circle.cpp
// we put the implementation of functions defined in the header file in the "implementation file"
#include "Circle.h"

Circle:Circle(double x, ...); {
// ...
}

void Circle::draw() const {
// ...
}

// -----------------------------------------------------------------------------------------------------
// alternative way to write a constructor: member initialization list
Circle::Circle(double x, double y, double r)
	: m_x(x), m_y(y),m_r(r) {
		// this initialises m_x as x, m_y as y, and so on
	if (r <= 0) { 
		cout << "Cannot create a circle with radius " << r << endl;
		exit(); 
	}
}
