// Lecture 21 | Monday, Week 8

// Number, Autoboxing and Unboxing

// Consider a function that can take in any object
public static void printClassAndObj(Object obj) {
	System.out.println(obj.getClass());	// all Objects have a getClass() method
	System.out.println(obj);
}	// this method unfortunately doesn't work with primitives - or it shouldn't, based on what we understand so far

public stativ coid main(String... args) {
	Complex c1 = new Complex(3.3, 2.9);
	int i1 = 2;
	printClassAndObj(c1);
	printClassAndObj(i1);
} 
/* the output is:
class Complex
3.3 + 2.9i
class java.lang.Integer
2
*/

// in the printClassAndObj(i1) line, the int i1 was "autoboxed" into an object of type Integer
// the Java langauge provides their respective wrapper classes for the 8 primitives types:
	// boolean, byte, char, float, int, long, short, and double correspond to
	// Boolean, Byte, Character, Float, Integer, Long, Short, and Double
// when we pass a variable of a primitive data type into a function that takes an Object, Java creates the corresponding wrapper class object and passes that in instead
// the wrapper classes take more memory than the primitive data types

// many of these wrapper classes (and a few other classes, such as BigInteger) inherit from java.lang.Number

// the class Number is an abstract class designed to be inherited by classes representing numbers

// out of the 8 wrapper classes for primitive tpes, 6 inherit Number: Byte, Float, Integer, Long, Short, and Double
// (Boolean and Character do not inherit Number)

// the class Character only inherits from Object
// in addition to being the wrapper class of "char", Character provides other useful features:
System.out.println(Character.toUpperCase('c'));
	// (toUpperCase is a static method)

// the class Boolean only inherits from Object; it's not very useful aside from being the wrapper class for boolean

// the Java language provides special support to the 8 wrapper classes in the form of autoboxing and unboxing
// autoboxing allows you to convert a primitive type into its respective wrapper class type, implicitly or explicitly
boolean b1 = false;
Boolean b2 = b1;	// implicit boxing (autoboxing)
Boolean b3 = (Boolean) b1;	// explicit boxing

// unboxing allows you to convert a wrapper class type into its respective primitive type, implicitly or explicitly
Integer i1 = new Integer(3);	// constructor for Integer
int i2 = i1;	// implicit unboxing
int i3 = (int) i1;	// explicit unboxing

// autoboxing and unboxing are special features provided by the language; you cannot make classes you write support autoboxing and unboxing

// autoboxing and unboxing is slower than using primtive types but they can provide certain convenience
import java.util.*;
public class Test {
	public static void main(String[] args) {
		ArrayList<Character> l = new ArrayList<>();	// since ArrayList is a generic class and requires a class object, we can't use it to store primitive types
			// .add works because of autoboxing
		l.add('a'); l.add('b'); l.add('c');
		Collections.shuffle(l);
			// you can use Collections with Objects but not with primitive types
		for (int i = 0; i != 3; i++)
			System.out.println(l.get(i));
	}
}