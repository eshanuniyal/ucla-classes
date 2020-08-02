// Lecture 6 | Friday, Week 2

import java.util.Scanner;
	// in C++, #include effectively copy-pastes a file into the program
	// in Java, you can choose to only import a particular class from a file
// alternatively, you can import an entire package
import java.util.*;
	// imports all classes from the package java.util
import static java.lang.Math.*;	// imports all static methods of the Math class

// import static fields and methods of a class with static import
import static java.lang.Math.PI;		// we can then use "PI" instead of "Math.PI" (java.lang is imported by default)
import static java.lang.Math.sqrt;		// we can then use "sqrt()" instead of "Math.sqrt()"

// Varargs
// A function can take a variable number or arguments (varargs)

static void fn(int i, double d, char... c_arr[]) {
		// the ... specifies that the function can take a variable number of characters; whatever number of characters are passed in are put into the array
	// i and d are not varargs, and are therefore required
	System.out.println(i)
	System.out.println(d)
	// c_arr is a vararg
	for (int j = 0; j != c_arr.length; j++)
		System.out.println(c_arr[i])

	// note: varargs can only be used in the final argument position
	// if we were only using an array input, we would always have to pass in an array; using varargs makes the syntax when calling a function a little nicer
}


public class lecture6 {
	// the main function must have either the following signature:
	public static void main(String[] args) {
		// or the signature "public static void main(String... args)"
		// the parameter args contain the inputs provided through the command line
			// e.g. java ClassName input1 input2 input3

		// fn can be called with 2, 3 or more arguments
		fn(1, 2.2);
		fn(5, 1.2, 'a', 'b', 'c', 'd');
		// this is equivalent to:
		fn(5, 1.2, new char[] {'a', 'b', 'c', 'd'})


		// in Java, there are two types of for loops: regular and enhanced for loops
		int[] i_arr = {1, 5, 0, 2, 9};

		// regular for loop
		for (int i = 0; i != i_arr.length; i++)
			System.out.println(i_arr[i])
		
		// enhanced for loop (a.k.a. for-each loop)
		for (int j : i_arr)	// may be read as "for each j in i_arr"
			System.out.println(j);

		/* Strings
			- String is an Object (not a primitive type) that represents a sequence of characters
			- Strings have a lot of special support by the Java language such as String literals and the + operator (that works with almost all primitive data types)
			- Strings behave like references and are immutable; to change a String, you have to create a new one with the desired changes and discard the old one
				- The class StringBuffer provides a mutable array of characters
		*/

		// use "" to write String literals
		String s1 = "Good morning.";

		// "Object" is a special class in Java that all classes inherit from; all Objects have a method with signature
			// public String toString()
		// whether you explicitly make one or not. The System.out.println method calls toString on its input

		Complex c1 = new Complex();
		System.out.println(c1);
		System.out.println(c1.toString());	
			// both give the same output: Complex@15db9742 (type name followed by memory location)
			// see Complex class below to see how to override toString()

		// The + operator
		// The + operator on "primitiveType + String" (or vice-versa) converts the primitive type to an appropriate String type and concatenates it to the other String
		// The + operator on "Object + String" (or vice-versa) calls the toString on the Object and concatenates the output to the other String


		// Math, a utility class
		// A "utility" class contains a set of common and reused members; a utility class is more of a package (a bundle of useful methods) rather than a blueprint for an Object
			// Utility classes use static members to provide their functionalities
		System.out.println(Math.sin(0.1));	// sin is a static method of Math
		// in fact, you are not allowed to instantiate a Math Object
		// Math m1 = new Math();	// error: Math() has private access in Math (this is achieved by marking the constructor of the Math class private)

		// packages and fully qualified names
		// Java code is organised through "packages" like java.lang or java.util
		// To use a class within a package, refer to its "fully qualified name"
		java.util.Scanner r;	// fully qualified name of the Scanner class is "java.util.Scanner"
		// we can use import declarations to make this cleaner (see top of file)
		Scanner r2;	// we can do this if we have written an import statement for java.util

		// The java.lang package is special; all classes in it are automatically imported
			// it provides us with the Math package, System.out.println, et cetera

		// Static imports
		// Import static fields and methods of a class with static imports
			// (see top of file for syntax)
			// static imports should be used very sparingly; they make code less readable
			// moreover, when you static import from an entire class, you import too many names (e.g. all the methods of Math) and that may cause naming conflicts

		// in order to use something, you either have to import it directly or import a package that contains it

		// Java API
		// The Java language comes with a library called the Java API (Application Program Interface)
		// The Java API is organised into packages like java.lang, java.util, java.net, java.io, or javax.swing
		// Becoming proficient with Java involves learning key parts of the Java API

	}
}


// you can override the toString method to get a more useful output
public class Complex {
	public String toString() {
		return real + "+" + imag + "i";
	}	
}

// ---------------------------------------------------------------------------------------------------------------
// Creating packages
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
// e.g.
package packageName;

public class someClass {
	...
}

// this file should be placed in baseDirectory\packageName\SomeClass.java