#include <string>
#include <iostream>
using namespace std;

// ALTERNATE IMPLEMENTATIONS OF STACK ------------------------------------------------------------------------------------------------------------------------------

// a stack implemented using arrays
/*	data members:
		top: tracks the first empty index of the array (equals 3 if stack has, say, 10, 20, 30)						initialised 0
			top is also, incidentally, always equal to the size of the stack
		capacity: keeps track of the capacity of the array															initialised, say, 100
			array is resized if we reach capacity		

	we can design the program such that with only these data members, we have a proper implementation of a stack
	all our member functions are pretty cheap

	advantages:
		array implementation takes less memory, since we don't need to also store pointers 
	disadvantages:
		array implementation has an expensive copying procedure when we run out of memory; however, this cost is averaged out

*/

// a stack implemented using a linked list
/* here, we can use the head as the active end of the stack, and not have a tail data member altogether (since we don't need to access the front of the stack)
	data members:
		top					initialised as null
			when we push our first entry, top points to that entry
		size				initialised as 0

	advantages:
		may be easier to implemente, don't have to worry about running out of space in an array
	disadvantages:
		every push or pop call is allocating or deallocating storage, both of which are relatively expensive operations
*/


// ALTERNATE IMPLEMENTATIONS OF QUEUE ------------------------------------------------------------------------------------------------------------------------------

// a queue implemented using a linked list
/* here, we need both the head and the tail, since we're inserting elements on one end and deleting from the other
	data members:
		head (for front of queue)
		tail (for back of queue)
	with this implementation, we need to deal with the special cases where we only have 1 element or even 0 elements
	even if we take the special cases into account, it's still a relatively simple implementation
*/

// a queue implemented using an array
/* the most challenging implementation of queue
	data members:
		tail: represents the index just after the last item added to the queue
		head: represents the index of the first item in the queue
			instead of moving all the elements left when we pop the queue, we can just increment head so we ignore the interesting item that was previously the first added
		capacity: to remember the capacity of the array
		size: to tell the size of the array (head - tail won't work; see below)

	what happens when we reach the end of the array?
		since we're incrementing head when we want to pop items, there's actually available space at the beginning of the array, so we shouldn't just go ahead and resize it
		copying all the elements one place left could be expensive
		here, the best thing to do is to continue the array as if it were circular: this is called a "circular array" or "ring buffer"
			when tail reaches 100, we set it to 0 instead, and start pushing new elements in the beginning of the array
			if after writing some such items, tail equals head, then we've truly filled the array
			also note: head == tail was a valid test for whether the array was empty earlier, but head == tail might also just mean the array is full with a circular array implementation
				head - tail also no longer always gives us the size of the array
				we therefore also need one other variable, to keep track of how many items are there in the queue
			when we resize, we'll copy elements into the larger array in the correct order, not just from index 0 of the old array
				we'll also reset head to 0 and update tail and capacity
*/

// -------------------------------------------------------------------------------------------------------------------------------------------
// Drawing a picture of circles and rectangles

class Circle {
	void move(double xnew, double ynew);
	void draw() const;

	double m_x;
	double m_y;
	double m_r;
};

void Circle::move(double xnew, double ynew) {
	m_x = xnew;
	m_y = ynew;
}

class Rectangle {
	void move(double xnew, double ynew);
	void draw() const;
	
	double m_x;
	double m_y; // coordinates of top-left corner
	double m_dx; // horizontal length
	double m_dy; // vertical length
};

void Rectangle::move(double xnew, double ynew) {
	m_x = xnew;
	m_y = ynew;
}

class Ellipse {
	void move(double xnew, double ynew);
	void draw() const;

	double m_x;
	double m_y;
	double a;
	double b;
};

void Ellipse::move(double xnew, double ynew) {
	m_x = xnew;
	m_y = ynew;
}

int main() {
	???? pic[100]; // we want this to be an array of 100 Rectangle and Circle objects, but we can only declare an array
	// we therefore need a collection that has items of different types
		// i.e. a heterogeneous collection
	
	// alternate solution
	Circle ca[100];
	Rectangle ra[100];
	Ellipse ea[100];

	// drawing the picture
	for (int i = 0; i != ...; i++)
		ca[i].draw()
	for (int i = 0; i != ...; i++)
		ra[i].draw()
	for (int i = 0; i != ...; i++)
		ea[i].draw()
}

void f(Circle& x) {
	x.move(10, 20);
	x.draw();
}

void f(Rectangle& x) {
	x.move(10, 20);
	x.draw()
}

void f(Ellipse& x) {
	x.move(10, 20);
	x.draw()
}

// now, however, we have a lot of identical implementations: implementations for Circle, Rectangle, and Ellipse's draw(), f(), 
	// and we also need to iterate over three loops to print the picture
	// if we need to add more objects of different types, our program will grow more and more redundant, and also be harder to code or manage

// ----------------------------------------------------------------------------------------------------------------------------------------------
// alternate code

// Shape is a generalisation, or a "superclass", of Circle and Rectangle
// Circle and Rectangle are specialisations, or "subclasses", of Shape

// the C++ terminology is that Shape is a "base" class, and Circle, Rectangle, and Ellipse are "derived" classes

class Shape {
	// announces that Shapes are moveable and drawable (as required by f)
	void move(double xnew, double ynew);
		// if all the Shapes move the same way, we can have just one implementation of move
	void draw() const;

	double m_x;
	double m_y;

};

class Circle : public Shape {
	// public Shape says a Circle is a kind of Shape
	// Circle "inherits" the move function from Shape, and the m_x and m_y data members
	void draw() const;

	double m_r;
};

void Shape::move(double xnew, double ynew) {
	m_x = xnew;
	m_y = ynew;
}

class Rectangle : public Shape{
	// public Shape says a Rectangle is a kind of Shape
	// Rectangle "inherits" the move function from Shape, and the m_x and m_y data members
	void draw() const;

	double m_dx; // horizontal length
	double m_dy; // vertical length
};

int main() {
	Shape* pic[100]; // we need a heterogeneous collection
	// such a collection must be an array of pointers, since the objects themselves have different sizes (e.g. Rectangle has four doubles, but Circle only has three)

	// language rules
		// a pointer to a derived object is automatically converted to a pointer to a base object when necessary
		// the address of a derived object is automatically converted to an address to a base object when necessary

	pic[0] = new Circle; // a pointer to a Circle is converted to a pointer to a Shape type and stored in pic[0]
	pic[1] = new Rectangle; // ...

	Circle c;
	f(c); // f takes an address to a Shape; the address of the Circle can automatically be converted to a Shape (per language rules)
	c.move(30, 40); // compiler first checks whether there is a move() function in Circle c; no, there is not
		// compiler sees that c is a derived class of Shape, and calls the move function in Shape accordingly
		// effectively, each Circle object can be thought of as containing a Shape object
			// when we're in the move function declared in Shape, "this" points to the Shape part of the Circle
	
}

void f(Shape& x) {
	// in order for the compiler to compile f, it needs to know .move and .draw can be called on all derived classes of Shape
	// check Shape class declaration to see how this is implemented
	x.move(10, 20); // will call the move function declared in Shape
	x.draw();
}