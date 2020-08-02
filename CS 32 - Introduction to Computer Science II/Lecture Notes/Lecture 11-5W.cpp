#include <string>
#include <iostream>
using namespace std;

class Shape; class Circle; class Polygon;

int main() {
	Shape* sp;
	if (...)
		sp = new Circle;
	else
		sp = new Polygon;

	// we are either deleting a Circle or a Polygon, the latter of which needs a destructor to get rid of the linked list's nodes
		// Circle doesn't need a destructor, since Circle doesn't deal with any pointers
	delete sp;
	// when the compiler sees "delete sp," it calls Shape's destructor, since sp is a pointer to a Shape
}


struct Node {};

class Shape {
	
	...;
	virtual ~Shape();
		// we have to declare a destructor for Shape solely to say it is virtual, so the destructor for Polygon will be called when we're deleting a Polygon
		// because we declared the destructor, however, the compiler doesn't write it for us as it otherwise would; we therefore now need an implementation of the Shape destructor
	
	/* Note - Destruction happens in three steps:
		1. Execute the body of the destructor
		2. Destroy the data members (do nothing for builtin types, call destructor for class types)
		3. Destroy the base part
	Our destructors for derived classes (such as Polygon) will therefore call Shape's destructor in step 3 --> Shape must have an implemented destructor
		// this also holds true if we're trying to implement a pure virtual Shape destructor: */
	virtual ~Shape() = 0 {}; // e.g.
	// if a class is designed to be a base class, declare its destructor virtual and implement it

	

	double m_x;
	double m_y;

};

class Circle : public Shape {
	double m_r;
};

class Polygon : public Shape {

	// destroys the linked list
	virtual ~Polygon();

	// a linked list of coordinates of all the polygon's vertices relative to the starting vertex
	Node* head;
};


// ------------------------------------------------------------------------------------------------------------

int main() {
	Circle c(-2, 5, 10);
}


struct Node {};

class Shape {
	public:
		Shape(double x, double y) : m_x(y), m_y(y) {};
		...;
	private:
		double m_x;
		double m_y;

	/* Note - Construction happens in three steps:
		1. Construct the base part
		2. Construct the data members per the member initialization list
		3. Execute the body of the constructor 
	
	We must therefore either have a default constructor for Shape, or call Shape's user-defined constructor in the member initialization list of the constructor of a derived class	
		- In this case, it doesn't make sense to create a default constructor for Shape, since we don't really want 
		  to default-construct m_x and m_y to certain values; the user will specify those values when constructing a Circle	*/
};

class Circle : public Shape {
	public:
		Circle(double x, double y, double r) : m_x(x), m_y(y), m_r(r) {};
			// this is wrong, because m_x and m_y are private member variables of Shape; they cannot be used in the member initialization list of Circle
		Circle(double x, double y, double r) : Shape(x, y), m_r(r) {};
			// this is correct
	private:
		double m_r;
};


// #############################################################################################################

/* SORTING AN UNSORTED PILE INTO TWO PILES
	- Split the pile into two piles of N/2 items each
	- Sort the left pile
	- Sort the right pile
	- Merge the two sorted piles into one sorted pile

	If we apply the same algorithm to the two smaller piles to make things quicker, we have a *recursive solution*	

	if N > 1
		- Split the pile into two piles of N/2 items each
		- Sort the left pile
		- Sort the right pile
		- Merge the two sorted piles into one sorted pile
	else
		return pile

	With any recursive solution, we must be able to prove it terminates (which, in this case, we know is true because we terminate at N <= 1)
		and that it is does the correct thing (which, in this case, we can prove by induction)
*/

void sort(int a[], int b, int e) {
	// takes parameters array a, beginning index b, ending index e (which is just past the last index we actually look at)
	if (e - b > 1) { // if current size is strictly greater than one
		int mid = (b + e) / 2; // integer division gives midpoint
		sort(a, b, mid); // sorting left half
		sort(a, mid, e); // sorting right half
	}

}