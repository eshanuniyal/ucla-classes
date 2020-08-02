// Lecture 22 | Wednesday, Week 8

// Collections and Data Structures

// How do you write a phone book program?
// Some programmer may think "hash table" and write the pseudo code:
HashTable phoneBook = new HashTable();
for each (name, phoneNumber) {
	phoneBook.put(name, phoneNumber)
}
print("Sam's phone number is ");
print(phoneBook.get("Sam"));
// this is correct, but the reasoning skips an important step

// the hash table is good for this problem for 2 separate reasons:
	// the interface of the hash table (it's "put" and "get" functions) are convenient for this application i.e. the code is easy to write
	// the data structure that implements the interface is efficient i.e. the code is fast
// Java separates these considerations via interfaces and their implementations

// Interfaces to data structures
	// the interface specifies how to use the Collection and Map
	// if the interface is convenient to use for a problem, then its implementations are probably fast/efficient for the problem
	// so it is often, but not always, enough to understand only the interface and not the specific implementations

// Interface Collection
// the interface Collection<E> represents a group of Objects/elements of type E
// Collection<E> supports operations like "add", "contains", "remove", "size", and "toArray"
// Collection<E> is abstract (since it's an interface) and is inherited by more specific interfaces

// Collection interface hierarchy
/*			Collection 							Map
		 /		 |		 \						 |
	Set 		List		Queue			  HashMap
	 |			  |			  |	
	HashSet		ArrayList	LinkedList
*/

// using the Collection interface
static void main(String[] args) {
	Collection<String> c = new ArrayList<String>();
		// we could just as well declare c as an ArrayList<String>; however, this also works because the Collection interface requires implementation of add, remove, et cetera
		// one advantage to declaring c as a collection is if you don't want access to any additional functionality in ArrayList, and just want to use the basic collection functionality
	c.add("Alice");
	c.add("Bob");
	c.add("Carol");

	System.out.println(c.contains("Eric"));	// false

	c.remove("Carol");
	c.remove("Dave");	// does nothing

	System.out.println(c.size());	// 2

	String[] s_arr = c.toArray();
	for (string s : c)
		System.out.println(s);
}

// using the Set interface
public class CouponCollector {
	public static void main(String[] args) {
		Set<Integer> s = new HashSet<>();
			// the interface Set<E> is a Collection<E> that doesn't contain duplciate elements, much like the mathematical set
		Random random = new Random();
		int count = 0;
		while (s.size() < 100) {
			s.add(random.nextInt(100));	// autoboxing
			count++;
		}
		System.out.println("Bought " + count + " coupons to collect all 100");
	}
}

// interface List<E> is a Collection<E> that
	// allows duplicates
	// orders the elements
	// supports positional access via methods like get(int index) and set(int index, E)
	// supports resizing (as most all Collections do) via methods like add and remove
// ArrayList<E>, a variable-length array, is the most used List<E>

// interface Queue<E> is a Collection<E> that
	// allows duplicates and
	// typically (but not always) supports first-in, first-out (FIFO) access with methods like add(E e) and remove()
// FIFO means you retrieve elements in the order you add them

// a printer prints Documents in the order they arrive at
public class PrinterManager {
	// LinkedList supports FIFO access
	private Queue<Document> q = new LinkedList<>();
	public void addJob(Document d) {
		q.add(d);
	}
	public Document nextJob() {
		return q.remove();
	}
	public boolean jobDone() {
		return q.isEmpty();
	}
}

// Maps
// Map<K, V> maps Objects of type K (key) to Objects of type V (value)
	// Map<K, V> is not a Collection<E>
public class PhoneBook {
	private Map<String, Integer> m = new HashMap<>();
	public void addNum(String name, Integer num) {
		m.put(name, num);
	}
	public Integer getNum(String name) {
		return m.get(name);
	}
	public boolean haveNumber(String name) {
		return m.containsKey(name);
	}
}

// Why use Collections and Maps?
	// Whatever you do with Collections and Maps can be done with basic arrays
	// However, the interfaces provide a convenient interface, and their implementations are usually faster than using basic arrays
	// The Collection and Map interfaces are implemented with data structures, wich are often quite sophisticated and complicated
	// Different implementations use different data structures and provide related but different features

// Set implementations
// HashSet is most common and usually the fastest
// LinkedHashSet preserves insertion-order

public class SetExample() {
	Set<Integer> s1 = new HashSet<>();
	Set<Integer> s2 = new LinkedHashSet<>();
	for (int i = 10; i > 0; i--) {
		s1.add(i); s2.add(i);
	}

	for (Integer i : s1)
		System.out.println(i);	// order unpredictable
	for (Integer i : s2)
		System.out.println(i);	// ordered as added
}

// List implementations
// ArrayList is most common and usually the fastest; LinkedList can be faster depending on where you're inserting/accessing elements

public class ListExample() {

	List<Character> l1 = new ArrayList<>();
	List<Character> l2 = new LinkedList<>();

	long start, end;
	start = System.currentTimeMillis();

	for (int i = 0; i != 100000; i++)
		l1.add(0, 'a');
		// insert element 'a' at the front (index 0) of the list
	end = System.currentTimeMillis();
	System.out.println(end - start);

	start = Systme.currentTimeMillis();
	for (int i = 0; i != 100000; i++)
		l2.add(0, 'a');
	end = System.currentTimeMillis();
	System.out.println(end - start);
}

// LinkedList is actually both a Queue and a List; it's the most commonly used Queue implementation and supports FIFO access
	// PriorityQueue uses an ordering that is not FIFO

// Map implementations
	// HashMap is most common and usually the fastest
	// LinkedHashMap preserves insertion-order

// ----------------------------------------------------------------------------------------------------------------------
// Wildcards with generics

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
l3 = l1;
l3.add("hello");	// this would still crash, but you could do some other things
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