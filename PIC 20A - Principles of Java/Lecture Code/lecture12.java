// Lecture 12 | Friday, Week 4


// Widening primitive conversion
// A type conversion is either widening or narrowing
// Widening primitive conversions include:
int i = 100; 	// short to int
long li = i;	// int to long
double d = i;	// long to double
double d = (double) i;	// explicit widening conversion
float f = 12.3f;
double d2 = f;
// Widening conversion has (almost) no loss of precision or information
// Because widening is safe, it can happen implicitly


// Narrowing primitive conversion 
long li = 123123123123123123L;	// this works
// int i = li;	// error
int i = (int) li;	// works, since we cast explicitly
double d = 0.3;
float f = (float) d;
int i2 = (int) d;
// Information can be lost in narrowing conversion, if a big number doesn't fit into a smaller variable
// Narrowing conversion doesn't happen implicitly


// Widening reference conversion
// Converting a child class reference to a parent class reference is a widening conversion
Screw s = new Screw(1, 2, 1);
Part p = s;
Part p = (Part) s;
// Again, widening conversions can happen implicitly

// Narrowing reference conversion
// Converting a parent class reference to a child class reference is a narrowing conversion
Part p1 = new Part(1,2);
Part p2 = new Screw(1, 2, 1);
Screw s;
// s = p2;	// compile-time error, since the Part p2 refers to may not be a Screw
s = (Screw) p2;	// runs fine, since p2 refers to a Part that is a Screw
s = (Screw) p1;	// runtime error, since p1 does not refer to a Part that is a Screw
// Again, narrowing conversion doesn't happen implicitly. Whether p1 or p2 does indeed refer to an object of class Screw is checked at runtime (i.e. it's checked dynamically)
	// If not, an error is issued
// A reference to a child class cannot refer to an object of a parent class

// instanceof
// The relational operator instanceof checks the type of an object
public static void main(String[] args) {
	A a1 = new A();
	A a2 = new B();
	System.out.println(a1 instanceof Object);	// true, since all classes are derived from Object
	System.out.println(a1 instanceof A);		// true
	System.out.println(a1 instanceof B);		// false
	System.out.println(a2 instanceof Object);	// true
	System.out.println(a2 instanceof A);		// true
	System.out.println(a2 instanceof B);		// true
}

// equals
// All classes inherit the equals function from Object. By default it returns true if the two references refer to the same single object.
public class A {
	...;
	@Override // override equals so that it returns true if the two references refer to objects of the same type with the same meaning/properties
	public boolean equals(Object obj) {
		if (obj instanceof A) {
			// cast obj into type A
			A a = (A) obj;	// explicit narrowing conversion: will always run, since we checked obj is an instance of A
			// check if this and are equal (by comparing fields or other relevant properties)
			...;
		} else
			return false;
	}
}

// Constructor chaining
// A constructor is written as
/* 	accessModifier className(arguments) {
		explicitConstructorInvocation
		constructorBody
  	}
*/
// The explicit constructor invocation is something like this(arguments) or super(arguments). It must be the first line of the constructor
// If a constructor does not explicitly invoke another constructor, it by default calls super(), the no-argument constructor of the superclass
	// (Object has one constructor, which is a no-argument constructor)

// So all constructors call another constructor until the no-argument constructor of Object is reached
// As the sole exception, Object's no-argument constructor doesn't call another constructor
// This process is called constructor chaining

public class Complex {
	private final double real, imag;
	public Complex() {
		this(0., 0.);	// this is the only constructor called by this constructor
	}
	public Complex(double real, double imag) {
		// super(); is executed by Java
		this.real = real; this.imag = imag;
	}
}

// When you run new Complex():
	// 1. Complex() is called
	// 2. Complex(double real, double imag) is called
	// 3. Object() is called


// Abstract Classes
// An abstract method is declared without an implementation (analogous to "virtual" in C++)
public abstract class Path {
	public abstract double getTime();
}
// we want subclasses of Path to implement getTime, but there is no reasonable way to implement getTime for the superclass Path

// An abstract class may or may not include abstract methods
// An abstract class cannot be instantiated, but it can be inherited
// A non-abstract class (also called a "concrete" class) cannot have an abstract method
// In our example, the class Path must be an abstract class

// An abstract class lays out what its subclasses should do while only partially providing its implementation
// Say class B inherits an abstract class A
	// If B is non-abstract, it must implement the parent's abstract methods
	// If B is also abstract, the inherited abstract methods can be left abstract

// Final methods
	// A final method cannot be overriden or hidden
	// In a way, fianl is the opposite of abstract, since a final method cannot be overriden while an abstract method must be overridden
	// Methods called from constructors should generally be declared final
		// If a constructor calls a non-final method, a subclass may override that method and bad things can happen
// Final classes
	// A final class cannot be inherited
	// As a general advice, you should design and document for inheritence or else prohibit it with final
	// As with final methods, a final class cannot be inherited while an abstract class must be inherited

// Suppose we're writing a music player application
// No music file is just a generic MusicFile, but all MusicFiles can play
	// This is why we make MusicFile abstract and add a play() method in the base class
public abstract class MusicFile {
	...;
	public abstract void play();
	public abstract String songName();
}

// to play a music file, you decode the file and convert it into audio signals
public class WAVFile extends MusicFile {
	...;
	@Override 
	public void play() {
		// decode and play WAV file
		...;
	}
}


// When you write the musc player program, the abstract MusicFile class is useful; it allows you to not worry about the specific kinds of music files you have
public class Player {
	MusicFile[] songArr;
	...;
	public void playList() {
		for (MusicFile song : songArr)
			song.play();	// different versions of play are called "polymorphically"
	}
}