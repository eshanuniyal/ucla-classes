// Lecture 3 | Friday, Week 1

import java.util.Scanner;	// importing Scanner class from Java API for I/O
		// in Java, we import by specifying the name of a class, a namespace, or a package

// in Java, data members are called "fields"; the first letter of the name of a class is capitalised by convention
// We don't make the Complex class public because in general, Java expects only one public class per .java file, and our main class must be public
	// Complex is assumed package-private in the absence of an explicit modifier
class Complex {	// a class for a complex number
	// public fields
	public double real;
	public double imag;
	// private fields
	private int sad;
}

public class lecture3 {
    public static void main(String[] args) {
        // String class
        // The class String is not a primitive data type. However it receives special support by the language, so people often think of it as such.

        // Variables should always be initialised before use, unlike in C++
        int i; 	// i is declared
        // System.out.println(i);	// won't compile
        i = 0;	// i is assigned / initialised
        System.out.println(i);	// compiles

        // Conversions
        // A variable of one time is converted to another with:
        	// Casting conversions (explicit)
        	// Other implicit conversions

        double d1 = 1 / 2;	// here, without casting, Java performs integer division (which gives 0) before storing the result into d, which isn't what we want        
        // Casting conversion converts from type T1 to T2 with (T2) T1
        double d2 = ((double) 1) / ((double) 2);
        // alternatively, we could use literals to achieve the same result
        double d3 = 1.0 / 2.0;
        // if we were mixing operations (say, with an integer and a double), the integer would implicitly be casted as a double
        double d4 = 1.0 / 2;	// same result

        // Implicit conversion converts from type T1 to T2 when a variable of type T1 is provided when T2 is expected
        double d = 5; 	// implicit conversion from int (5) to double (5.0)

        // Generally speaking, it's best to be conscious where any kind of type conversions are happening; always explicitly cast when unsure

        // Operators
        int j = 3;
        System.out.println(j++);	// print 2; modify j to 3
        System.out.println(++j);	// modify j to 4; print 4
        System.out.println(j > 0);	// true
        System.out.println((i > 0) || false);	// true
    
        // Basic Input/Output
        Scanner reader = new Scanner(System.in);
        int k = reader.nextInt();	// get whatever next integer the user types in
        	// if user enters a non-int (say, with letters or special characters) and hits enter, Java throws an exception
        	// even if the user enters a double, we'll get an exception because a double can't be implicitly casted as an int
        	// we can validate the input without parsing it by using reader.hasNextInt() to avoid exceptions
        System.out.println(k);	// print out the int

        double dl = reader.nextDouble();	// get whatever next double the user types in
        	// if user enters an int, it'll be implicitly casted to a double because double is a wider type than int
        System.out.println(dl);


        // ---------------------------------------------------------------------------------------------------------------------
        // Control Structures
        
        // if-else control statements

        i = 3;
        if (i > 0) {
        	System.out.println("i is positive");
        	i = 0;
        }
        else if (i < 0)	// if there is only one statement following a control structure, we can omit the curly brackets
        	System.out.println("i is negative");
        else
        	System.out.println("i is zero");

        // "for" control statements also work exactly as they do in C++
        for (int itr = 0; itr != 5; itr++)
        	System.out.println(itr);

        // ---------------------------------------------------------------------------------------------------------------------
		// Some basic concepts in classes: data members, member functions, constructors, and public and private members

        // Complex class defined before main
        Complex c = new Complex();
        c.real = 5; c.imag = 1;
        // c.sad = 3;	// we cannot access private fields; error

        // Access Modifiers
        // In Java, there are 4 access modifiers: public, private, protected, and package-private (no explicit modifier).
        
    }
}