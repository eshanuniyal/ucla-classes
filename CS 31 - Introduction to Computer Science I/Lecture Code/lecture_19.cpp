#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Fan {
	public: void turnOn();
			...;
};

class Rock {
	public:
		double weigh() const;
		...;
};

class Robot {
	...;
	Fan m_cooler; // every robot has a fan, not optional
		// when the robot goes away, the fan should go away
	Rock* m_rock; // every robot may or may not have a rock
		// if m_rock is a null pointer, the robot is not carrying a rock
		// otherwise, the rock is the object pointed to by m_rock
};

void Robot::blah {
	if (m_rock == nullptr && m_rock->weight() > 50) // arrow -> used for m_rock, since m_rock is a pointer to a rock
		m_cooler.turnOn(); // period . used for m_cooler, since m_cooler is an object
}

// ------------------------------------------------------------------------------------------------------------------

class Complex {
	public:
		Complex(double re, double im);
		Complex();
		double real() const;
		double imag() const;
	private:
		// double m_real;
		// double m_imag;
		double m_rho;
		double m_theta;

};

Complex::Complex(double re, double im) {
	// m_real = re;
	// m_imag = im;

	// constructor using polar coordinates
		// more expensive to construct, but using polar coordinates makes multiplication of complex numbers cheap
	m_real = sqrt(re * re + im * im);
	m_theta = atan(im, re);
}

complex::Complex() {
	// m_real = 0;
	// m_image = 0;
	
	// polar coordinates
	m_rho = 0;
	m_theta = 0;
}

double Complex::real() {
	// return m_real;

	// conversion from polar coordinates
	return m_rho * cos(m_theta);
}

double Complex::imag() {
	// return m_imag;

	// conversion from polar coordinates
	return m_rho * sin(m_theta);
}


int main() {
	Complex c1(-4, 3); // -4 + 3i
	cout << cl.real(); // write -4

	Complex ca[100]; // won't compile, since the constructor requires two arguments for each Complex object
		// we need to add a default constructor with no arguments
		// the complex numbers will now be initialised to to 0 + 0i

}

// ---------------------------------------------------------------------------------------------------

// NOTE - You can overload a function name (i.e. give it multiple meanings) if the functions differ in the number or types of parameters
	// for example, the two Complex functions declared in the class Complex have the same name but differing number of parameters; this is therefore no issue

// without overloading, functions would look this
void drawCircle(Circle c);
void drawRectangle(Rectangle r);

// with overloading, we can create functions like this
void draw(Circle c);
void draw(Rectangle r); // these are functions with the same name, but different parameter types --> different functions

int main() {
	Rectangle r;
	Circle c;

	// without overloading
	drawCircle(c);
	drawRectangle(r);

	// with overloading
	draw(c); // calls the draw function that takes a Circle argument
	draw(r); // calls the draw function that takes a Rectangle argument
}


void f(int a; double b);
void f(double c; int d);

double g(int i);
int g(int i); // these two functions are not overloaded; will give an error
	// parameters need to be different in some way, the return value doesn't matter as far as overloading is concerned

int main() {
	f(3, 4); // gives compilation error; ambiguous call!
		// both overloaded functions are equally good, so the compiler can't decide which one to use
}