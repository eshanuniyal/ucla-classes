// Lecture 23 | Friday, Week 8

// Wildcards with generics (continued)

// Motivating example: should this be allowed?
ArrayList<Integer> l1 = new ArrayList<Integer>();
ArrayList<Object> l2 = l1;
// in other words, should ArrayList<Object> be a superclass of ArrayList<Integer>?

// no, and it isn't; otherwise we could do
ArrayList<Integer> l1 = new ArrayList<Integer>();
ArrayList<Object> l2 = l1;
l2.add("hello");	// l2 is just a reference identical to l1, it isn't actually a copy of the list
	// this would (as it should) result in an error

// Object is a superclass of Integer, but ArrayList<Object> is not a superclass of ArrayList<Integer>
// instead, we can use ?, the wildcard

ArrayList<Integer> l1 = new ArrayList<Integer>();
ArrayList<String> l2 = new ArrayList<String>();
ArrayList<?> l3;	// if we use a wildcard, we can get away with doing certain operations
l3 = l1;	// assignment of a reference to another ArrayList to l3 is now okay
l3.add("hello");	// this would still crash though
l3 = l2;
// ArrayList<?> is a superclass of ArrayList<Integer> and ArrayList<String>

// methods with wildcards
	// you can use wildcards to define methods
public static void printList(List<?> list) {
	for (Object elem : list) 
		System.out.print(elem + " ");
}

// you can achieve the exact same effect with an explicit type parameter
public static <T> void printList (List<T> list) {
	for (Object elem : list)
		System.out.print(elem + " ");
}

// you can upper-bound a wildcard to require it to be a subclass or implementation; this is the same idea as bounding explicit type parameters
static void sum(List<? extends Number> list) {
	double sum = 0;
	for (Number n : list)
		sum += n.doubleValue();
	System.out.println(sum);
}

// the upper-bound doesn't allow us to add Objects to the list
static void fn(List<? extends Number> list) {
	Double d = new Double(3.3);
	Number n = d;
	list.add(d);	// error; the list that's passed in may be a list of, say, integers
	list.add(n);	// you don't know whether the list is a list of Numbers, or what kind of Numbers the list takes
		// the compiler doesn't know
}

// you can lower-bound a wildcard to require it to be a superclass
static void addNum(List<? super Integer> list) {
		// this code says "the list variable is of type List, and the List contains objects of some superclass of the Integer class (e.g. Integer, Number, Object, et cetera)"
	for (int i = 0; i != 10; i++)
		list.add(new Integer(i));
			// here, we can add an Integer to the list because we know the list is either a list of Integers or some superclass of Integers,
				// so you can have implicit type conversion

	// the lower-bound doesn't, however, allow us to "get" from the List gracefully
	Integer i = list.get(0);	// error; list could be a List of Objects, or Numbers; you can't convert either to Integers
	Number n = list.get(0);		// error for the same reason
		// maybe list is a List<Object> that contains Strings; the compiler doesn't know
}

// if we have a method that's reading stuff from the list, upper-bounding is a good idea
// if we have a method that's writing stuff into the list, lower-bounding is a good idea

// Wildcards vs. type parameter
// You can use generics with a type parameter and/or with a wildcard
	// You can use wildcards for method inputs and return values
	// You cannot use wildcards to define generic classes; you must use explicit type parameters
	// You can upper and lower bound wildcards
	// You can only upper bound type parameters
	// Wildcards are arguably more confusing, but can be useful sometimes
		// Usually, upper-bounded wildcards are useful when you mostly read from the Object
		// Usually, lower-bounded wildcards are useful when you mostly write to the Object
		// Usually, unbounded wildcards are useful when you can accomplish everything by treating the Objects as just Objects
			// (say, by iterating over a list and just printing each item using the enhanced for loop)
		// Mostly, type parameters can do what wildcards can do, but not the other way around
			// there are a few things (like lower-bounding) that only wildcards can do
		// A function signature is more concise when written with a wildcard

// wildcard example
// Collection<E> has the method removeAll; here's how you might implement it
boolean removeAll(Collection<?> c) {
	// we use the fact that Collection contains Objects
	// we know ? inherits Object, and that's all we need
	for (Object o : c)
		remove(o);
	// return something
	...;
}

// Collection<E> also has the method addAll; here's how you might implement it
boolean addAll(Collection<? extends E> c) {
	// what we add to a Collection<E> must be an E; the upper bound guarantees ? is an E or extends E
	for (E e : c)
		add(e);
	// return something
}

// ------------------------------------------------------------------------------------------------------------------------
// class Collections and polymorphic algorithms

// the utility class Collections (not to be confused with Collection<E>) contains polymorphic algorithms for Collection<E>s
// the algorithms only use methods specified by the interfaces (i.e. they are polymorphic) and they therefore work with a wide range of Collection<E>s

// e.g. Collections has the method frequency; here's how you might implement it
public static int frequency(Collection<?> c, Object o) {
	int count = 0;
	// again, we use the fact that Collection contains Objects
	for (Object o2 : c)
		if (o2.equals(o))
			count++;
	return count;
}

// Collections has the method shuffle; here's how you might implement it
public static void shuffle(List<?> list) {
		// here, we use parameter of type List rather than Collection, since Sets do not have any ordering
	Random r = new Random();
	for (int i = 0; i != list.size(); i++) {
		j = r.nextInt(i);
		Collections.swap(list, i, j);
			// Collections' swap method swaps the entries at index i and j in the List list
	}
}

// Collections has the method copy; here's how you might implement it
public static <T> void copy(List<? super T> dest, List<? extends T> src) {
	// the upper-bound guarantees src contains T
	for (T t : src)
		// the lower-bound guarantees you can add T to dest
		dest.add(t);	
}

// ---------------------------------------------------------------------------------------------------------
// Comparators and Comparables

// Imagine you have
public class Complex {
	public final double real, imag;
	...
}

// and you try to sort a List of them
public static void main(String[] args) {
	List<Complex> list = new ArrayList<>();
	...
	Collections.sort(list);
		// Collections.sort sorts from "smallest" to "biggest", but what is "small" and "big"?
		// Complex class doesn't have a built-in notion for comparison, so we get a compiler error ("Complex is not comparable")
}

// the interface Comparator<T> compares a T against a T
// Comparator<T> demands
	public int compare(T t1, T t2)
// be implemented

// for class Complex, we could use the lexicographical ordering
public class Lex implements Comparator<Complex> {
		// we need to create a separate class that implements Comparator<Complex>; 
		// this is because we may want to define multiple different Comparators for a class, but could've only defined one compare function in Complex
	public int compare(Complex c1, Complex c2) {
		if (c1.real < c2.real) return -1;
		else if (c1.real > c2.real) return 1;
		else if (c1.imag < c2.imag) return -1;
		else if (c1.imag > c2.imag) return 1;
		else return 0;
	}
}

// Collections has the method max(Collection<? extends T>, Comparator<? super T>)
// if the first input is a List, here's how you might implement it
public static <T> T max(List<? extends T> list, Comparator<? super T> comp) {
		// you could use a Comparator of a superclass of Complex, which is why we have Comparator<? super T> to make the function more generic
	T currMax = list.get(0);
	for (int i = 1; i != list.size(); i++)
		if (comp.compare(currMax, list.get(i)) < 0)
			currMax = list.get(i);
	return currMax;
	// if the input is a general Collection, you must use its Iterator (since it could be a set)
}