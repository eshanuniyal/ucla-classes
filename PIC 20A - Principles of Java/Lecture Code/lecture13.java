// Lecture 13 | Monday, Week 4

// Interfaces

// Imagine that some objects can be resold
import java.util.Date;

public interface Resellable {
	// price of the object when sold at date d
	double sellAt(Date d);	// no implementation, but not declared abstract -> the method is in an "interface"
	// functionally, very similar to a base class in Java; all methods have to be abstract i.e. with no implementation
	// interfaces, just like classes, also go i ntheir own file
}

// a screw would likely sell at the same price at which it was bought
public class Screw extends Part implements Resellable {
	...;
	@Override 
	public double sellAt(Date d) {
		return cost;
	}
}

// perhaps leather degrades over time, so its resell value depreciates
public class SeatLeather extends Part implements Resellable {
	...;
	@Override 
	public double sellAt(Date d) {
		double price;
		// compute price while factoring depreciation
		...;
		return price;
	}
}

public class Car {
	private Part[] p_arr;	// array of parts, some of which may be resellable
	...;
	public double sellValue() {
		Date date;
		...;
		double price = 0;
		for (Part p : p_arr)
			if (p instanceof Resellable)	// checking whether a part is resellable (i.e. checking whether the object we're looking at is the instance of a class that implements Resellable)
				price += ((Resellable) p).sellAt(date);	// we convert p to a Resellable object (so Java doesn't give any errors) and call sellAt(), a Resellable method
	}
}


// An interface is like an abstract class; it must be implemented (instead of inherited) to be instantiated
// You "implement" an interface, and you "inherit" a class
// View an interface as a contract; an interface specifies methods that an implementation must provide

// Rules of interfaces
	// All fields must be public, static, and final (by default, they are, but you can redundantly specify these modifiers). In other words, interfaces can only have constants as fields
	// Interfaces are abstract (by default, they are, but you can redundantly specify abstract)
	// Interfaces do not have constructors
// There are exactly 3 types of methods for interfaces: abstract, default, and static
	// abstract is the default option (you can redundantly specify abstract)
	// We'll talk about default methods for interfaces later
	// Static methods for interfaces are rarely used
	// Methods must be public (by default, they are, but you can redundantly specify public)

// Abstract classes vs interfaces
	// Interfaces mostly specify abstract methods, while abstract classes can have non-constant fields
	// You can only inherit one class, but you can implement multiple interfaces

// Interfaces as function pointers
	// C++ and many other languages have function pointers
	// for instance, in C++:

int sum(int a, int b) {
	return a + b;
}

int max(int a, int b) {
	if (a > b) return a;
	else return b;
}

int reduce(int* arr, int n, int (*binOp)(int a, int b)) {
	int ret = binOp(arr[0], arr[1]);
	for (int i = 2; i != n; i++)
		ret = binOp(ret, arr[i]);
	return ret;
}

int main() {
	int n;
	int* arr;
	...;
	cout << reduce(arr, n, sum) << endl;	// we can pass in references to functions as paramaters
	cout << reduce(arr, n, max) << endl;
}


// in Java, we can use interfaces instead of punction pointers:

public interface BinOper {
	int op(int a, int b);
}

public class Adder implements BinOper {
	@Override 
	public int op(int a, int b) {
		return a + b;
	}
}

public class Maxer implements BinOper {
	@Override 
	public int op(int a, int b) {
		if (a > b) return a;
		else return b;
	}
}

public static int reduce(int[] arr, BinOper b) {
		// function takes an instance of interface BinOper i.e. an instance of a class that implements BinOper
	int ret = b.op(arr[0], arr[1]);
	for (int i = 2; i != arr.length; i++)
		ret = b.op(ret, arr[i])
	return ret;
}

public static void main(String[] args) {
	int[] arr;
	...;
	int sum = reduce(arr, new Adder());
	int max = reduce(arr, new Maxer());
	// Adder and Maxer Objects don't have any fields, but rather provide access to method op
	// Since Adder and Maxer implement interface BinOper, they must have the method op
}

// Inheriting/implementing from multiple classes and interfaces is often useful
// Java prohibits multiple inheritance from classes, as multiple inheritance is very error prone
// This is very rarely a limitation; usually, you can do exactly what you want by implementing multiple interfaces without compromising on convenience or readability

// example
// since countChar uses interface CharSequence and methods specified in CharSequence, it works with the classes charBuffer, Segment, String, StringBuffer, and StringBuilder
public int countChar(CharSequence str, char c) {
	int count = 0;
	for (int i = 0; i != str.length(); i++)
		if (str.charAt(i) == c)
			count++;
	return count;
}


// What is Object-Oriented Programming?
// Object-oriented programming (OOP) is a programming style centered around using objects
// A down-to-earth definition of bjects: an object is an association of data and functions
// The four coure tenets of OOP are:
	// abstraction
	// encapsulation
	// inheritance, and
	// polymorphism

// Abstraction
	// Abstraction allows us to model a complex system with many small components using fewer larger but abstract components
	// Sometimes abstract is easier
		// When using the class String in a program, it's helpful to simply use methods like charAt(int index), length(), or toUpperCase() without worrying about how they work
		// Even if you had to write these methods yourself, it's easier to worry about that issue separately
	// Abstraction is universal across all programming styles, but OOP is a particularly elegant way to provide abstraction

// Encapsulation
	// An encapuslated class hides its fields from the user, and instead provides methods that provide indirect access to the fields
	// Encapsulation can make your codebase safer and more readable
	// Perfect encapsulation is often impossible; however, a limited degree of encapsulation is still useful

// Inheritance
	// One reason to use inheritance is to re-use code written for the parent class
	// Another reason to use inheritance is for polymorphism

// Polymorphism
	// Polymorphism is the ability to present the same interface for differing underlying data types
	// When you refer to an object with a superclass reference and use overriden methods, you are using polymorphism
	// Polymorphism is a very powerful tool and is one of the key strengths of inheritance
	// Polymorphism is not exclusive to OOP, but OOP makes polymorphism is clean

// Side note for Homework 3: immutability
// To make a class immutable, make all fields final (so they cannot be changed) and private (so child classes cannot attempt to change them)