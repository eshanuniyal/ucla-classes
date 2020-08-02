// Lecture 5 | Wednesday, Week 2

// Compiling multiple files
/* When you compile "javac Test.java", and Test.java uses a class named Complex, there are three scenarios:
	- javac finds and uses a package-private class Complex defined in the file Test.java
	- javac finds and uses Complex.java or Complex.class in the current directory
	- javac can't figure out what Complex is and issues an error
(The command-line option "-classpath" changes where to look for Complex.java or Complex.class)

When javac finds the definition of Complex in another file, there are three scenarios:
	- There's Complex.class but not Complex.java; then, javac uses Complex.class
	- There's Complex.java but not Complex.class; then, javac compiles Complex.java and produces Complex.class
	- There's both Complex.java and Complex.class: 
		- if, according to the files' timestamps, Complex.class is newer than Complex.java, then Complex.class is used
		- if Complex.java is newer, it's recompiled and Complex.class is overwritten
		i.e. Complex.java is effectively recompiled if it has been updated since the last compilation

Summary:
Put all .java files in the same directory, and explicitly compile only the file with the main function. The rules are set up so that things will just work.
*/

// Final and Static Modifiers
// A final variable can be set only once; it's like "const" in C++.

public static void main(String[] args) {
	final int i;	// blank final variable
	int j = 2;
	System.out.println(j);
	i = 3;
	System.out.println(i + j);
	// i = 5; // error; final variables cannot be changed after first assignment

	Complex c1 = new Complex(0, 0);
	func(7, c1);
	c1.printNum();	// 5.0 + 0.0i
}

// you can make function parameters final to prevent certain bugs
static void func(final int i, final Complex c) {
	// if we specify final, we're passing by reference rather than value and the variables cannot be changed
	// i = 2;	// error
	// c = new Complex(1, 2);	// error
	c.real = 5; // not an error; properties of c are not necessarily final, even though c is final (i.e. the memory c is pointing to is final)
}

// final field smust be initialised by the end of the constructor in a class
class Complex {
	
	final public double real, imag;
	
	// if we make the fields final but don't have a default constructor, we could run into an error if the user creates a Complex object using 
		// the default constructor, which doesn't initialise the final variables
		// we therefore must either define a default constructor if we're using final fields, or somehow make sure the default constructor is never used 
	public Complex() {
		real = 0; imag = 0;
	}

	public Complex(double r, double i) {
		real = r; imag = i;
	}
}
// In addition to variables, methods and classes can be final; more on that when we talk about inheritance

// Static Fields
// A static field belongs to the class, not the instantiated Object. Only one copy of it is shared across Objects of the same class.
public class Monster {
	
	private static int count = 0;	// intialise count; shared across Monster objects

	// constructor
	public Monster() {
		count++;
		System.out.println("New Monster created.");
		System.out.println("There are ");
		System.out.println(count + " Monsters.\n");
	}
}

public class Test {
	public static void main(String[] args) {
		Monster m1 = new Monster();	// count = 1
		Monster m2 = new Monster();	// count = 2
		Monster m3 = new Monster(); // count = 3

		// we get the following print out:
		// New Monster created. There are 1 Monsters.
		// New Monster created. There are 2 Monsters.
		// New Monster created. There are 3 Monsters.
	}
}

// Constants with static fields: Use "static final" fields for constants

public class MyMath {
	public static final double PI = 3.14159265;
	public static final double E = 2.718281828;
	// static final effectively means the field is shared across Objects (static), and cannot be modified (final)
}

public class Test {
	public static void main(String[] args) {
		double r = 3;
		System.out.println(2 * MyMath.PI * r);	// this works, because PI is shared across MyMath objects
		MyMath m1 = new MyMath();
		System.out.println(2 * m1.PI * r);	// this also works, but it's bad style since the reader thinks that PI is something that depends on how it's defined in m1
	}
}

// Static Functions
// A static function belongs to the class, not the instantiated Object. A static function can only access static fields.

public class Monster {
	private static int count = 0;
	private final String name;
	// ...
	public static int countMonster() {
		// System.out.println(name); // error! can't access non-static field
		return count;	// works, since count is a static field
	}
}

// Some static functions have nothing to do with objects, and are packaged together into a class
public class MyMath {
	public static final double PI = 3.14159265;
	public static final double E = 2.718281828;
	public static double sqrt(double d) { ... }
	public static double  sin(double d) { ... }
	public static double  cos(double d) { ... }
	public static double  tan(double d) { ... }
	
	// this is done because users will never create an actual MyMath object; they only need access to the functions offered by the MyMath class
	// if these functions weren't static, then we'd need to create a MyMath object to call them
}

// Other uses of static: in addition to fields and methods, initialisation blocks can be static. More on that soon.
	// main functions are always static, because there can only ever be one definition of the main function


// Arrays
// An array is an Object of reference type which contains a fixed number of components of the same type
	// double[] dArr;	// dArr is a reference variable of type double[]
// Few things to note:
	// Length is fixed
	// The array length is not part of its type
	// Arrays use zero-based indexing

public class ArrayTest {
	public static void main(string[] args) {
		
		double[] d_arr; 	// without initialisation, we cannot use this array
			// it's equal to null by default

		// create an array with an "array creation expression"
		int[] i_rr = new int[5];
		
		for (int i = 0;i != 5; i++)
			i_arr[i] = 0;

		i_arr = new int[9];	// the old array is garbage collected and new memory is allocated for i_arr
		// (the length of i_arr is not part of its type)

		// Arrays of Objects have the same syntax
		Complex[] c_arr = new Complex[5];	// an array of (not yet created) complex numbers
		for (int i = 0; i != 5; i++)
			c_arr[i] = new Complex();
		c_arr = null;	// uninitialises the array; we can't use it anymore, and the memory it previously pointed to is garbage collected

		// we can also use the array initialiser
		int[] new_arr = {1, 2, 3};	// dynamically create an array; Java compiler figures out what the length of the array should be
		// new_arr = {2, 3, 4, 5, 6};	// error; cannot change length
		new_arr = new int[] {2, 3, 4, 5, 6};
		Complex[] c_arr = {new Complex(0, 1), new Complex(), null};
		c_arr[2] = new Complex(3, 8);

		// an array has a public final field named length
			// we can therefore access the length of the array using arrayName.length
		int[] i_a = new int[30];
		for (int i = 0; i != i_a.length; i++)
			i_a[i] = 0;
	}
}