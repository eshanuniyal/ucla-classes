// Lecture 24 | Wednesday, Week 9

// ---------------------------------------------------------------------------------------------------------
// Iterables and Iterators

// we can use the enhanced for loop with a Collection<E> since it extends Iterable<E>
Collection<?> coll;
...
for (Object o : coll)
	System.out.println(o);


// interface Iterable<E> requires
public Iterator<E> iterator()
// each call of iterator() returns a new instance of Iterator<E>

// interface Iterator<E> requires
public boolean hasNext()	// tells the user whether or not there are more entries in the Iterable object
public E next()	// returns the next entry in the Iterable object


// using Iteraotr, we can write a while loop equivalent to the enhanced for loop
Collection<Number> coll;
...
Iterator<Number> itr = coll.iterator();
	// we create an iterator object called "itr" for coll
while (itr.hasNext()) {
		// while more elements left in coll
	Number n = itr.next();	// get next element, increment the iterator
	System.out.println(n);
}

// you can also use the normal for loop
Collection<Number> coll;
...
for (Iterator<Number> itr = coll.iterator(); itr.hasNext(); ) {
	Number n = itr.next();
	System.out.println(n);
}
// Note: always use the enhanced for loop if you can

// max with Iterator
// here's you might implement Collections.max
static <T> T max(Collection<? extends T> coll, Comparator<? super T> comp) {
	Iterator<T> iter = coll.iterator();
	T currMax = itr.next();
	while (itr.hasNext()) {
		T currT = itr.next();
		if (comp.compare(currMax, currT) < 0)
			currMax = currT;
	}
}

// writing an Iterable
public class ArrayList<E> extends AbstractList<E> implements List<E>, Iterable<E> {
	// to make ArrayList iterable, it must implement Iterable<E> and have a method iterator() that returns an object of type Iterator<E>
		// the object of type Iterator<E> must be defined in an inner class that implements Iterator<E>
	public Iterator <E> iterator() {
		return new Itr();
	}

	// Itr must be an inner class, and not a top-level or static nested class because we want to use the properties / fields of the specific ArrayList instance
	private class Itr implements Iterator<E> {
		private int currInd = 0;
		public boolean hasNext() {
			return currInd < size();
		}
		public E next() { return get(currInd++); }
			// get will be called with currInd, and only then will currInd be incremented (post-script ++)

		// the Iterator interface doesn't require a prev() method, but we could define one if we like
	}
}

// a new Iterators stats anew
	// each call of iterator() returns a new instance of Iterator<E> that starts anew
Collection<Integer> coll = new ArrayList<>();
coll.add(1); coll.add(2); coll.add(3);

// both loops print exactly the same thing: "1 2 3 "
for (Iterator<?> itr = coll.iterator(); itr.hasNext();)
	System.out.print(itr.next() + " ");

for (Iterator<?> itr = coll.iterator(); itr.hasNext(); )
	System.out.prin(itr.next() + " ");

// iterating through a Map
// a Map<K, V> is not an Iterable<E> (remember, a Map<K, V> is not a Collection<E>)
// you can iterate through the keys of Map<K, V> with a Set<K>
Map<String, Integer> m = new HashMap<>();
...
for (String key : m.keySet())
	System.out.println(key);

// you can iterate through the key-value pairs of Map<K,V> with a Set<Map.Entry<K,V>>
for (Map.Entry<String, Integer> entry : m.entrySet()) {
	String key = entry.getKey();
	String value = entry.getValue();
}	// Entry is a public static interface of class Map

// -------------------------------------------------------------------------------------------------------------------
// some features are optional
Set<Number> s = new HashSet<>();
...
Set<Number> const_s = Collections.unmodifiableSet(s);
const_s.add(7);	// UnsupportedOperationException
System.out.println(const_s.getClass());	// prints java.util.Collection$UnmodifiableSet
	// UnmodifiableSet is a private static nested class of Collections
	// you can't created references or instances of it from the outside, but Collections can return an instance of it to you

// optional features are anti-polymorphic
	// to keep the library size manageable, Java doesn't provide separate interfaces for each variant of each collection
	// instead, some operations are designated optional and throw an UnsupportedOperationException when called
	// this goes against the spirit of polymorphism, but the authors of the Java API had to make the trade-off

// -------------------------------------------------------------------------------------------------------------------
// hashCode and equals
// Collections or Maps named HashX use the method hashCode of class Object
	// general contract of hashCode: two equal Objects must have the same hashcode
	// so when
		o1.equals(o2);
	// is true, then
		o1.hashCode() == o2.hashCode()
	// must be true, where o1 and o2 are objects

// when you override equals, you should also override hashcode; otherwise, you take a significant performance hit when using HashX
// for optimal performance, you want a good hash code
// just remember: always override hashcode when you override equals

class Complex {
	public final int real, imag
	public Complex(int r, int i) { real = r; imag = i; }
	@Override
	public boolean equals(Object o) {
		if (o instanceof Complex)
			return (real == ((Complex) o).real) && (imag == ((Complex) o).imag);
		else
			return false;
	}
	// without overriding hashCode, code can take significantly longer to run
	@Override
	public int hashCode() {
		int result = 17;
		result = 31 * result + rea;
		result = 31 * result + imag;
		return result;
	}
} 