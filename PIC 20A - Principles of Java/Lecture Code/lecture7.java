// Lecture 7 | Monday, Week 3

// ---------------------------------------------------------------------------------------------------------------
// Creating packages (continued)
// you can create a package with the "package" declaration at the beginning of code

package packageName;

import java.util.Scanner;

public class SomeClass {
	...
}

// when no package name is specified, the class belongs to the unnamed "package"
// the unnamed package is for developing small or temporary applications
	// generally, you should put all classes in named packages

// with respect to a base directory, place the files for a package named packageName within the folder packageName. Place the files for the unnamed package in the base directory.
// e.g.:
package packageName;

public class someClass {
	...
}

// this file should be placed in baseDirectory\packageName\SomeClass.java
	// packages have a one-to-one mapping with folders and directories of a project

// Compiling a Java file within a package
	// to compile a .java file within a package, use
		// javac packageName\Test.java
	// from the base directory
// to run the main function of a class within a package, use
		// java packageName.Test
	// from the base directory

// ------------------------------------------------------------------------------------------------------------------
// Garbage Collection

// Java periodically deletes unreferenced Objects; this process is called "garbage collection" and is performed by the "garbage collector"
// When the garbage collector runs is unpredictable and none of your business; s
// Sometimes unreferenced Objects may never be garbage collected 
	// (and the memory is returned to the OS as the program exits)
// Your program should never rely on the garbage collector behaving in a certain way
// However, you may want to explicitly control garbage collection for debugging purposes

// finalize()
// The garbage collector will run the finalize() method before destroying the Object
// Because garbage collection is unpredictable, you shouldn't rely on finalize() to clean up your Object (exceptions are rare)
// So don't think of finalize() as the equivalent of destructors in C++; only use finalize() as a debugging tool

// debugging with garbage collection
public class Monster {
	private static int monsterCount = 0;
	private boolean isAlive;
	public Monster() {
		monsterCount++;
		isAlive = true;
	}
	public void kill() {
		monsterCount--;
		isAlive = false;
	}
	// we can use finalize() to debug by overloading the method
	protected void finalize() {
		if (isAlive)
			System.out.println("Live Monster is being garbage collected.");
	}
}

public class lecture7 {
	
	public static void main(String[] args) {
		
		// Sytem.gc()
			// the static method System.gc() suggests Java to run the garbage collector
			// this is only a suggestion, and it may be ignored
		
		Monster m1 = new Monster();
		Monster m2 = new Monster();
		m1.kill();
		m1 = null; m2 = null;	// the Monster Objects m1 and m2 pointed to are now waiting ot be garbage collected
		System.gc();	// should see a message from m2.finalize(), but maybe not

		// code should never rely on System.gc()		
	}
}

// Default Constructor
// When there are no constructors, the compiler provides a no-argument constructor called the default constructor
public class Complex {
	public double real, imag;
	// the no-argument constructor provided by the compiler is as follows:
	public Complex() {}
}
// the default constructor basically does nothing

// Private Constructor
// One may provide a single private constructor to prevent users from instantiating a class
// This is a useful feature for utility classes
public class MyMath {
	private MyMath() {}	// no MyMath objects can be instantiated
	...;
}

// Copy Constructor
// By convention, the constructor of class T with a single input of type T is called the copy constructor and is used to copy Objects
public class Complex {
	public double real, imag;
	...
	public Complex(Complex c) {
		real = c.real; imag = c.imag;
			// even if real and imag were private, this would still work since the copy constructor is a function of the same class (even if we're not in the same instance)
	}
}
// In Java, unlike in C++, there is no automatic default copy constructor

// = doesn't copy Objects
// You can copy primitive variables but not reference variables with =, since = only copies the reference
public class Test {
	public static void main(String[] args) {
		int i1 = 7;
		int i2 = i1;	// copy
		Complex c1 = new Complex(1, 4);
		Complex c2 = c1; // not a copy: rather, a reference to the same Complex object c1 points to
		Complex c3 = new Complex(c1);	// copy

		// if we were to call a function with c3, we'd be calling the function by reference and not value
		func(c1);	// pass by reference
		// to pass in an Object by value, use the syntax
		func(new Complex(c1));	// pass by value (copy constructor needs to be defined)
	}
}