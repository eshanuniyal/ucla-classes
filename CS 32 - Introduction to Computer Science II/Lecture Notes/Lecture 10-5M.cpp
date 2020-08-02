#include <string>
#include <iostream>
using namespace std;

// Shape is a generalisation, or a "superclass", of Circle and Rectangle
// Circle and Rectangle are specialisations, or "subclasses", of Shape

// the C++ terminology is that Shape is a "base" class, and Circle, Rectangle, and Ellipse are "derived" classes

class Shape {
	// announces that Shapes are moveable and drawable (as required by f)
	void move(double xnew, double ynew);
		// if all the Shapes move the same way, we can have just one implementation of move
		// we could add the virtual keyword to move(), but if we don't need different implementations of move depending on which object it's called on, 
			// it's best to leave it out for optimisation reasons
		// added virtual keyword for WarningSymbol implementation further down
	virtual void draw() const;
		// adding the virtual keyword lets the compiler know that draw() in class is a virtual function, and that it's superseded by the draw()
			// function of whichever object type the Shape is contained in; we are still guaranteed that all Shapes are drawable
		// we do still need to implement a draw() function for Shape
		// when we declare draw() in the derived classes, we don't need to use the virtual keyword, but it's still a good idea to do so

	// note: not every kind of member function can be virtual
		// constructors cannot be virtual

	double m_x;
	double m_y;

};

class Circle : public Shape {
	void draw() const;
		// overrides the draw() implementation of Shape when draw() is called on a Shape object inside a Rec object
		// we don't need to use the virtual keyword (since it's been used in Shape), but it's good practice to do so

	double m_r;
};

void Shape::move(double xnew, double ynew) {
	m_x = xnew;
	m_y = ynew;
}

class Rectangle : public Shape{
	virtual void draw() const;
		// overrides the draw() implementation of Shape when draw() is called on a Shape object inside a Circle object
		// we don't need to use the virtual keyword (since it's been used in Shape), but it's good practice to do so
	virtual void move(double xnew, double ynew);
		// virtual added for Warning Symbol implementation further down
	double m_dx; // horizontal length
	double m_dy; // vertical length
};

int main() {
	Shape* pic[100];
		// this stores pointers to Shape objects, and all the Shape objects it points to are contained in objects of derived classes

	pic[0] = new Circle; // a pointer to a Circle is converted to a pointer to a Shape type and stored in pic[0]
		// the Shape pointer points to the Shape automatically contained in the Circle object, but not the Circle object itself
	pic[1] = new Rectangle; // ...

	Circle c;
	c.draw();
	// works just fine, since compiler knows c is a Circle
	f(c);
	c.move(30, 40); // compiler first checks whether there is a move() function in Circle c; no, there is not
		// compiler sees that c is a derived class of Shape, and calls the move function in Shape accordingly


	for (int i = 0; i != ...; i++)
		pic[i]->draw();
	// the problem with draw is that the compiler doesn't know which draw() function to call: the one in Shape or the one in Circle/Rectangle?
	// there are two ways to "bind" function calls to the the appropriate function declarations:
			// static-binding - determined at compile time
			// dynamic-binding - determined during runtime
		// in every language other than C++, if you don't say anything, you get dynamic binding
			// we specify that we want dynamic binding by adding a "virtual" keyword to the appropriate class declaration
}

void f(Shape& x) {
	x.move(10, 20); // will call the move function declared in Shape
	x.draw();
		// which draw function do we call? In f, the compiler doesn't know whether x is contained in a Circle or a Rectangle or what 
		// it only knows the address of the Shape object x
		// it therefore calls the Shape draw() function -> this is fixed by adding the virtual keyword to Circle and Rectangle's draw() functions, 
			// that would override it
}

// ------------------------------------------------------------------------------------------------------------------------------------------
// say, we now want to add a class WarningSymbol derived from Shape for which the move function also makes the WarningSymbol flash three times

class WarningSymbol : Shape {
	void move(double xnew, double ynew);
};

void WarningSymbol::move(double xnew, double ynew) {
	Shape::move(xnew, ynew);
		// calls the move function on the Shape contained in WarningSymbol
	...flash three times...;
}

int main() {
	WarningSymbol x;
	x.move(10, 20);
		// here, x flashes three times, because the compiler knows x is a WarningSymbol and calls the appropriate move function
	g(x);
		// here, x doesn't flash three times, because its address is converted to the address of the Shape object inside WarningSymbol x
		// in g(), then, we'll call the move() function of the Shape class, not the WarningSymbol class
		// we therefore need to make sure the move() function in Shape is also virtual
}

void g(Shape& s) {
	s.move(10, 20);
		// here, WarningSymbol 
}

// ------------------------------------------------------------------------------------------------------------
class Shape {
	// if a class contains at least one pure virtual function, it becomes an "abstract (base) class"
	// this means in this case, we cannot create a Shape object that's just that; we'll get a compile time error
		// we can still have Shape objects contained in derived objects, or pointers to shapes or reference to shapes; 
		// you just can't have an actual Shape object

	// if we had a derived class of Shape without a declared draw() function (such as a Closed Figure class, 
	// which itself is a base class for Circles and Rectangles) that class would inherit the pure virtual draw function and itself be an abstract class
	
	void move(double xnew, double ynew);
	virtual void draw() const = 0;
		// the = 0 means the draw() function in Shape is a "pure virtual function" -> it has no implementation that's going to be automatically inherited
	double m_x;
	double m_y;

};

void Shape::move(double xnew, double ynew) {
	m_x = xnew;
	m_y = ynew;
}

class Rectangle : public Shape {
	virtual void draw() const;
	virtual double diag() const;
		// we make diag() virtual because Squares have a more efficient implementation for computing the diagonal, 
		// and we'd want to use that implementation for Squares

	double m_dx; // horizontal length
	double m_dy; // vertical length
};

double Rectangle::diag() {
	return sqrt(m_dx * m_dx + m_dy * m_dy);
}