// Last time - looking at c strings - represented as arrays of characters
// Necessary to interface with libraries or operating systems written in
// Any advantage for using c-strings? - for programs in c++ - high performance applications, using c-strings improves performance. Cost benefit analysis between convenience of c++ strings and speed of c-strings.

//POINTERS

//Typical uses

	// another way of implementing of passing by reference
	// Also helps you want to interface with libraries and applications written in C
	// Another way to go through an array and visit all the elements in an array
	// Manipulate dynamic storage
	// represents relationships in data structures

//Using Pointers to pass by reference

	//Example of converting polar coordinates to Cartesian coordinates from previous lecture

	//instead of using references we use pointers
	/*
	 r [5]		[5] rho
	 angle [0]	[0] theta
	 x [???]<---[pointer to the position of the double 'x'] xx
	 y [???]<---[pointer to the position of the double 'y'] yy
	 */

 #include <math>
 using namespace std;
 
 int main ()
{
	double r;
	double angle;
	//... get values for r and angle ...
	double x;
	double y;
	polarToCartesian(r, angle, &x, &y);
}

void polarToCartesian(double rho, double theta, double* xx, double * yy)
{
	*xx = rho * cos(theta);
	*yy = rho * sin(theta);
}
 
 // double& means reference-to-double or another-name-for-some-double 
	// this is how we normally pass by reference
 	// created in the c++ language, so that you don't have to use pointers
 // double* means pointer-to-double or address of-some-double //spacing is irrelevant2
 
 &x means "generate a pointer to x" or "address of x"
 *p means "the object that p points to " or "follow the pointer p"
 
 C programmer would use pointers instead of passing by reference
 
 Draw pictures when using pointers in order to follow along with what's happening - makes things easier


// **NEW EXAMPLE**

/*

double a = 3.1;
double b = 5.1;
double* p = &a; //p only holds a pointer to the double a
double* q = 7.6; // cannot store a double in a pointer to a double
double c = a;
double d = p; //Doesn't work because the d holds a double and not a pointer
double d = *p; // holds the double the p points to. Works since the object that p points to is a double and d is a double
				//p* is the object that p points to
p = b; <- Does not compile because a pointer cannot equal to a double

*p = b; //object that p points to is b, and we declared that p would point to a, hence it changes a to 5.1
p = &b; //redefines p to point to b

*p += 4; *p = *p + 4  = (5.1 + 4) = b IS NOW 9.1

int k = 7;
p = &k; <- error because p is a pointer to a double, not a pointer to an int which is what k is


int* z = &k;

cout << (k * b); //writes 63.7
cout << (k * p); does not work
cout << (k * *p); //writes 63.7 same as before
cout << (*z**p); // cout << (*z)*(*p); writes 63.7

 double* q;
 
 // *q = 4.3; //runtime problem because q has not been defined yet
 // from before we know that p now points to b
 q = p
 double* r = &a;
 *r = b; //writes a value as 9.1
 
 
 if (p == r) //false
 			//comparing pointers, p points to b, r points to a. value of a and b may be the same but p and r are not the same as they point to different things
 if ( *p == *r) // true since value of a and value of b are equal.
 
if (p == q) // true since comparing pointers
 */

/*NEW EXAMPLE*/

/*
 
 const int MAXSIZE = 5;
 double da[MAXSIZE];
 int k;
 double* dp;
 
 double* k = &da[k]
 
 for (int k = 0; k < MAXSIZE; k++)
 {
 	da[k] = 3.6;
 }
 
 */


