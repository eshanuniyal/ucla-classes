// Lecture 4 | Monday, Week 2

package edu.ucla.math
	// all the code in this file now belongs to a package name edu.ucla.math


// classes can be public or package-private (no explicit modifier)
	// package-private files can be accessed within the same file and the same package
	// if you a know a class should not be used elsewhere, make it package private
// moreover, any file must only have one public class, and its name must match the filename
// the class with the main function must be public

class Complex {	// a class for a complex number; if our main routine were in a different file, we would want to make this public
	
	// fields and methods of a package-private class can be package-private
	// a public class can but probably shouldn't have package-private methods

	// constructors: no return type, may or may not have arguments/parameters
	// default constructor: Java creates an empty default constructor if you don't define any constructor
	public Complex() {
		real = 0; imag = 0;
	}
	// constructor with arguments
	public Complex(double r, double i) {
		real = r; imag = i;
	}

	// methods: in Java, member functions are called methods
	public void printNum() {
		System.out.println(real + "+" + imag + "i");
	}

	public Complex add(Complex c) {
		// adds complex number c with the current complex number and returns the total
		return new Complex(real + c.real, imag + c.imag);
	}

	// public fields
	public double real;
	public double imag;

	// private fields
	private int sad;
}

public class lecture4 {
	// you can write the main function anywhere, so long as it's only defined once
		// "String[] args" means an array of strings called args, that refers to command-line arguments you can pass in
    public static void main(String[] args) {

    	// reference variables: using a class in another class
        Complex c1;	// anything that's not a primitive variable is a "reference variable" e.g. class objects
        	// if we just write "Complex c1", it's just an uninitialised reference variable - unlike as in C++, the default constructor is not automatically called
        c1 = new Complex();	// you must use the "new" keyword to instantiate an Object (i.e. reference variable)
        Complex c2 = new Complex(0.1, 1.2);

        // reference variables are like pointers: c1 is not the Object, it only refers to the Object (which is why they're called "reference" variables)
        Complex c2 = c1;	// copies the reference, not the object itself
        	// c2 and c2 now refer to the same Complex Object
        c2.real = 10;	// c1.real is also now 10

        c1 = new Complex(3, 3);	// the first Complex Object that c1 was a reference to remains, since c2 is still a reference to it
        	// c2 remains unchanged
        c1 = null;	// the second (previous) Complex Object that c1 was a reference to is now gone
        // the garbage collector will automatically destroy Objects with no reference variables referring to it
        	// you do not, however, have a guarantee on how quickly / when Java will do that

    	// calling a method in Java
        c1.printNum();	// throws an exception, since c1 is null
        c2.printNum();

        // two main memory issues in Java:
        	// running out of memory if allocate too much of it
        	// null pointer exceptions thrown if you try to access reference variables that refer to Objects that have been garbage collected

        // adding complex numbers with add() method
        Complex c3 = new Complex(1, 2);
        Complex c4 = new Complex(3, 4);
        Complex c5 = c1.add(c2);
        // alternatively, we can write:
    	// Complex c5 = (new Complex(1,2)).add(new Complex(3, 4));
        	// in this case, the objects are discarded as soon as the resulting sum is assigned to c5 and the statement is complete
        c5.printNum();	// output 4.0+6.0i


    }
    // variables are destroyed at end of scope of the main method
}