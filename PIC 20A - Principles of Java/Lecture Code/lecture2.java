// Lecture 2 | Wednesday, Week 1

/* 
Compiling C++ code
	- C++ code compiles into an executable
	- all cpp files are compiled into obj files by the compiler, and then linked by the linker to create an executable

Running C++ code
	- to run, the executable is loaded into memory and executed
*/

/* 
Compiling Java code
	- Java doesn't compile into an executable
	- The Java compiler (e.g. javac.exe for Windows 10) takes all .java files and compiles them into respective .class files; there is no "linking" in Java

Running Java
	- A Java program compiled into .class files is run by loading the .class files into memory and having the Java Virtual Machine (JVM, also loaded into memory) run them
		- This is what happens when we enter, say "java a1.class" or "java a1" into the terminal / command prompt
	- Anyone who wants to run a Java program therefore needs to have Java installed

/* 
Advantages: 
	- Write once, run anywhere (WORA)
		- Different systems need their own JVM to run Java. They are written to behave the same across all platforms.
		- The JVM therefore acts as a buffer between the diverse platforms and the Java programmer.
		- A programmer can develop Java on a PC and can expect it to run on Java-enabled cell phones. 
		- This saves programmers the effort of writing a different version of their software for each platform or operating system.
	- The JVM can analytically load and unload different classes from memory depending on what we're doing; 
		we can therefore manage memory more efficiently than with C++, where the entire executable needs to be loaded no matter what
*/

/* History of Java
Java was developed by Sun Microsystems (now acquired by Oracle) with the following design goals:
	- It must be "simple, object-oriented, and familiar"
	- It must be "robust and secure"
	- It must be "architecture-neutral and portable"
	- It must execute with "high performance"

Versions of Java
	- 1996: JDK 1.0
	- 1998: J2SE 1.2: javax.swing added
	- 2004: J2SE 5.0: Generics, for each loop, autoboxing/unboxing, varargs, and static imports added
	- 2014: Java SE 8: Lambda expressions added
	- 2020: Java SE 14
*/

// Note: Java and JavaScript are entirely unrelated; JavaScript was named similarly only as a marketing ploy.

// ------------------------------------------------------------------------------------------------------------------
// Variables

// In Java, there are primitive and reference variables

public class Test {
	// there is only going to be one unique instance of anything (function, variable, et cetera) declared static
	// we declare the main function public so the JVM can access it
	public static void main(String[] args) {
		double d1 = 0.2;	// declaring variables is similar to C++
		double d2 = 0.5;
		// syntax for printing
		System.out.println(d1 * d2);

		// Variable names are case-sensitive (as in C++) and must not conflict with reserved keywords
		// Reserved keywords include: abstract, class, continue, else, for, int, new, static, et cetera

		/* Primitive Data Types
			- byte: 	1 byte integer
			- short: 	2 byte integer
			- int: 		4 byte integer
			- long: 	8 byte integer
			- float:	single-precision floating-point number
			- double: 	double-precision floating-point number
			- boolean: 	a Boolean (it's not spelled bool)
			- char: 	16-bit unicode character
		Regardless of which types we use, the runtime is not affected much; we therefore choose which type to use entirely on the basis of memory efficiency.
		*/

		// Literals represent a fixed value in our source code
		// integer literals
		int i1 = 100; 			// decimal
		int i2 = 0x1bc; 		// hex
		int i3 = 0b11011; 		// binary
		long i4 = 1000000L; 	// L means long; if we don't write L, Java thinks it's an int and converts it into the largest int possible before storing it into i4
		// boolean literals
		boolean b1 = true;
		boolean b2 = false;
		// floating-point literals
		double d1 = 123.4f;		// Java converts automatically sees numbers with a decimal point as doubles, but it's still good practice to put the f
		double d2 = 1.234e2;	// in scientific notation
		float f1 = 123.4f;		// without the f, Java sees 123.4 as a double; we therefore need to add the f
		// character literals
		char c1 = 'a';
		char c2 = '\'';		// apostrophe character
	}
}

