// Lecture 20 | Friday, Week 7

// As we have templates in C++, we have Generics in Java

// introductory example: ArrayList
// java.util.ArrayList<E> is a generic class that represents a resizable array containing objects of type E (analogous to std::vector<T>)

public class Test {
	public static void main(String[] args) {
		ArrayList<String> s_arr = new ArrayList<String>();
		s_arr.add("Hello");
		s_arr.add("World");
		s_arr.add("Java");

		// the methods of ArrayList<E> are parameterised as well
			// the method "add" has signature:
		public boolean add(E e);
		// this provides safety
		s_arr.add(Boolean.FALSE);	// error
	}
}

// classes can have paramaterised types
public class Pair<A, B> {
	private A first;
	private B second;

	public Pair(A first, B second) {
		this.first = first;
		this.second = second;
	}

	public void setFirst(A f) { first = f; }
	public void setSecond(B s) { second = s; }
	public A getFirst() { return first; }
	public B getSecond() { return second; }
}

// generic interfaces
public interface Comparable<T> {
	int compareTo(T o);
}	// this is in fact the java.lang.Comparable interface

// methods can have parameterised types
public class Util {
	public static<A, B>
	boolean samePair(Pair<A, B> p1, Pair<A,B> p2) {
		return (p1.getFirst().equals(p2.getFirst()) && p1.getSecond().equals(p2.getSecond()));
	}
}

// bounded type parameters
// you can "bound" i.e. set a requirement for the type parameter
public class Util {
	public static<T extends Comparable<T>> 
	T getMax (T a, T b) {
		if (a.CompareTo(b) > 0)
			return a;
		else
			return b;
	}
}	// when bounding, use "extends" for classes and interfaces

// enhanced for loop and interface Iterable
// we can use the enhanced for loop with Iterable objects
ArrayList<String> s_list;
s_list = new ArrayList<String>();
...;
for (String s : s_list)
	System.out.prinlnt(s);
	// we can do this since ArrayList<String> implements the interface java.lang.Iterable<String>

// under the hood, this is how the enhanced for loop works
for (java.util.Iterator<String> iter = s_list.iterator(); iter.hasNext(); ) {
	String s = iter.next();
	System.out.println(s);
}

// when you omit the angled brackets, you get the raw type
public static void main(String[] args) {
	ArrayList s_arr1 = new ArrayList();
	ArrayList<Object> s_arr2 = new ArrayList<Object>();
	// a raw type is similar to what you get when the type parameter is Object
		// so s_arr1 and s_arr2 are almost the same, but the raw type is less safe
	// raw types should be avoided; they are only provided for backwards compatibility
}

// type inference: often, you can omit the type parameter and let it be inferred
public static void main(String[] args) {
	ArrayList<String> s_arr = new ArrayList<>();
		// type inference has nothing to do with raw types
		// you must use <> (the "diamond") to have the compiler infer the unspecified type parameter
}

// you can't use primitive types with generics
// primitive types are not objects; you can't do
public static void main(String[] args) {
	ArrayList<int> int_arr;	// error
}s