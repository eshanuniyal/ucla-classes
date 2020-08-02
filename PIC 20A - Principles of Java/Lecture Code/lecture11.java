// Lecture 11 | Wednesday, Week 4

// Protected vs. private access modifiers
// A protected member is accessible by a derived class, but not from the outside world (classes within the same package can access protected members as well)
// A private member is only accessible within the class; however, a derived class can indirectly access a private member through an inherited method

public class A {
	private int field;
	protected int getField() { return field; }
}

public class B extends A {
	public void someMethod() {
		System.out.println(getField());	// works okay: since getField() is protected and B is derived from A, B can access getField()
		// System.out.println(field);	// error: even though B is derived from A, it can't access private members of A
	}
}

// Ordering Access Modifiers
// The four access modifiers, in order of least to most restrictive are:
	// public > protected > package-private > private

//	Modifier 		Class 	Package 	Subclass 	World
//  -----------------------------------------------------
//	public 			  Y		   Y			Y		  Y
//  protected 		  Y		   Y			Y		  N
//  package-private	  Y 	   Y 			N 		  N
//  private  	      Y		   N 			N 		  N

// Rules of inheritance: fields
	// public fields are inherited as public fields
	// protected fields are inherited as protected fields
	// private and package-private fields are not inherited
	// inherited fields cannot be overriden; they can only be hidden
// These rule apply to static and instance fields

// Rules of inheritance: methods
	// a public method is inherited as a public method
	// a protected method is inherited as a protected method
	// private and package-private methods are not inherited
// These rules apply to static and instance methods

// Rules of inheritance: instance methods
// Say class B inherits class A
	// When B defines a method with the same signature as an instance method of A, the inherited method is overriden
	// When B overrides an instance method of A, it can widen but not narrow the access modifier
		// If overriden, a public method must be overriden as a public method
		// If overriden, a protected method can be overriden as a public or a protected method
	// B doesn't inherit and thus cannot override private and package-private methods
		// If B defines a method with the same signature as a private or package-private method of A, the two methods bare no relationship to each other

// Rules of inheritance: static methods
// Say class B inherits class A
	// When B defines a method with the same signature as a static method of A, the inherited method is hidden
	// static and instance methods are separate and one cannot override or hide another
		// An instance method of B cannot override or hide a static method of A; this causes a compile-time error
		// A static method of B cannot override or hide an instance method of A; this causes a compile-time error

// Rules of inheritance: only members are inherited
// In java, a member of a class are its methods and fields; public and protected members are inherited
	// Constructors, static initialisers, and instance initialisers are not members and therefore are not inherited

// Hiding

public class A {
	public int field = 0;
	public statc int field_s = 0;
	public int fn() { return 0; }
	public static int fn_s() { return 0; }
}

public class B extends A {
	public int field = 1;			// hide (fields of a base class are not overriden)
	public statc int field_s = 1;	// hide (static fields are still fields, so they are not overriden )
	public int fn() { return 1; }	// override (non-static method)
	public static int fn_s() { return 1; }	// hide (static method)
}

public class Test {
	public static void main(String[] args) {
	
		// creating an A object
		A a1 = new A();
		System.out.println(a1.field);	// output 0
		System.out.println(a1.field_s);	// output 0
		System.out.println(a1.fn());	// output 0
		System.out.println(a1.fn_s());	// output 0
		// here, the fact that B inherits A is irrelevant


		// creating a B object
		B b1 = new B();
		System.out.println(b1.field);	// output 1
		System.out.println(b1.field_s);	// output 1
		System.out.println(b1.fn());	// output 1
		System.out.println(b1.fn_s());	// output 1

		// creating a B object but storing it in a reference to an A object
		A a2 = new B();
		// because a2 is a reference of type A, the hidden members of A are called
		System.out.println(a2.field);	// output 0
		System.out.println(a2.field_s);	// output 0
		System.out.println(a2.fn());	// output 1 (regardless of reference type, the overriding method of B is called )
		System.out.println(a2.fn_s());	// output 0

	}
}


// Avoid hiding: it usually only causes confusion and brings little benefit. It's generally best to avoid name conflicts.
	// there's almost always a better alternative than using hiding


// super
// Say class B inherits class A. Access overriden or hidden members of A within B with super.

public class B extends A {
	public int field = 1;	// hide
	public static int field_s = 1;	// hide
	public int fn() { return 1; } 	// override
	public static int fn_s() { return 1; }	// hide
	public void accessSuper() {
		System.out.println(super.field);	// output 0
		System.out.println(super.field_s);	// output 0
		System.out.println(super.fn());		// output 0
		System.out.println(super.fn_s());	// output 0
	} 
}

// Overriding vs hiding methods
// Say class B inherits class A. You override instance methods while you hide static methods.
// Within B you can access inherited methods of A whether they are overriden or hidden or not with super. From the outside, you can access hidden methods but not overriden methods.

public class Test {
	public static void main(String[] args) {
		
		B b1 = new B();	// reference to a B object
		A a1 = b1;	// reference to an A object (that's actually a B object)

		System.out.println(b1.fn());	// output 1 (calls B's fn() method, since b1 is a reference to a B object)
		System.out.println(a1.fn());	// output 1 (calls B's fn() method, since B overrides A's fn() method)
		System.out.println(a1.fn_s());	// output 0 (calls A's fn() method)
		System.out.println(b1.fn_s());	// output 1 (calls the B's fn_s() method, since A's is hidden)
		System.out.println(((A) b1).fn_s());	// output 0 (converts b1 to a reference to an A object and then calls A's fn_s() method)
	}
}

// Overriding vs. hiding methods (continued)
// Hidden methods are hidden but accessible; overriden methods are inaccessible from the outside
public class Direction {
	private Path[] subPaths;
	public double getTime() {
		double totalTime = 0;
		// you want p.getTime() to use the overriding method to compute the time based on what kind of path p refers to
		for (Path p : subPaths)
			totalTime += p.getTime();
		return totalTime;
	}
}

// Shadowing and Obscuring

// Shadowing and obscuring happen names conflict and ambiguity arises; they are similar to hiding

// Shadowing
public class A {
	private double field;
	public A(double field) {
		this.field = field;	// argument shadows field (this use of shadowing is okay)
	}
}

// Obscuring
import java.lang.Math;

public class Test {
	public static void main(String[] args) {
		String Math = "Hello";
		// variable name obscures class name
		// System.out.prinln(Math.PI);	// gives us an error, since Math is defined as a String in local scope and takes preference over the imported Math package
	}
}


// Annotations
// Annotations, a form of metadata, provide data about a program that is not part of the program itself
// Annotations don't change your code but will catch certain errors

public class A {
	...;
	@Override 	// indicates to the Java compiler that the method below it should override some method
	public String toSpring() {
		return "An object of type A";
	}	// we get an error, since toSpring() is misspelled and doesn't end up overriding toString()
	// if a method annotated with @Override
}

// Annotations are useful debugging tools
	// There are other annotations, and you can define custom annotations
// We will only use @Override in this course