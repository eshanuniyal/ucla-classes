// Lecture 26 | Monday, Week 10

// Anonymous Classes, Lambda Expressions, and Functional Programming

// introductory example
// when you write an ActionListener for a GUI, you write a class and only use it once
class MyGUI {
	private JTextArea text;
	private final JButton button1, button2;

	private class B1L implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			System.out.println("button1 clicked");
		}
	}

	private class B2L implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			System.out.println(text.getText());
		}
	}

	{
		button1.addActionListener(new B1L());
		button2.addActionListener(new B2L());
		// this is wasteful; why do you need to name something you only use once?
			// this is poor style; the code above doesn't tell you what B1L and B2L do
			// you need to find their implementations somewhere else to figure that out
	}
}

// Anonymous classes
// when you use a class only once, don't name it; make it anonymous
// writing an anonymous class is like writing the class definition and then immediately calling the contructor (only once)

// this code uses an inner class
button1.addActionListener(new B1L());

// this code still uses an inner class
ActionListener AL1 = new B1L();
button1.addActionListener(AL1);

// instead use an anonymous class as below:
ActionListener AL1 = new ActionListener() {
	@Override 
	public void actionPerformed(ActionEvent e) {
		System.out.println("button1 clicked");
	}
};	// semicolon needed, since the entire definition is one statement
// the anonymous class has one instance, which is referred to by the reference AL1


// we can also get rid of the reference
button1.addActionListener(new ActionListener() {
	@Override 
	public void actionPerformed(ActionEvent e) {
		System.out.println("button1 clicked");
	}
});

// anonymous classes can have multiple methods
text.addMouseListener(new MouseListener() {
	public void mouseEntered(MouseEvent e) {
		System.out.println("Mouse entered");
	}
	public void mouseClicked(MouseEvent e) {}
	public void mouseExited(MouseEvent e) {}
	public void mousePressed(MouseEvent e) {}
	public void mouseReleased(MouseEvent e) {}
});

// -------------------------------------------------------------------------------------------
// Lambda Expressions

// Anonymous classes are useful, but the syntax of anonymous classes can be unwieldy and unclear
// In Java 8, lambda expressions were introduced. A lambda expression lets you concisely write an anonymous class that implements a functional interface.

// Functional interface
	// Legally speaking, an interface is a functional interface if it has exactly one abstract method
	// Conceptually speaking, an interface is a functional interface if its purpose is to provide a function
	// e.g. Comparator<E> is a functional interface, legally and conceptually
	// Comparable<E>, Iterable<E>, and Iterator<E> are not functional interfaces, conceptually
	// Functional interfaces often have the annotation @FunctionalInterface
	// java.util.function has many useful functional interfaces

// Java uses functional interfaces instead of function pointers
@FunctionalInterface
public interface BinOper {
	int op(int a, int b);
}

public static int reduce(int[] arr, BinOper b) {
	int ret = b.op(arr[0], arr[1]);
	for (int i = 2; i != arr.length; i++)
		ret = b.op(ret, arr[i]);
	return ret;
}

// we can implement a functional interface with an anonmyous class
int[] i_arr = ...;
int max = reduce(i_arr, new BinOper() {
	int op(int a, int b) {
		if (a > b) return a;
		else return b;
	}
});	// it's nice that all of the logic is here, and not somewhere else in a separate BinOper class definition
	// however, even this is a bit verbose and hard to read

// instead, we use a lambda expression
int[i] i_arr = ...;

int max = reduce(i_arr,
	(a,b) -> {
		if (a > b) return a;
		else return b;
	}
);
// a lambda expression is an anonymous class
// (a, b) is the method inputs; what comes after -> is the method body
// we can get away without specifying what type of functional interface we're implementing since Java can look at the definition of reduce and see that it takes a BinOper

// we can simplify the method with the conditional operator
int[] i_arr = ...;
int max = reduce(i_arr,
	(a,b) -> { return (a > b) ? a : b; }
		// return a if the predicate (a > b) is true; b otherwise
);

// when a lambda expression's method body consists of a single return statement, we can omit the curly braces and return
int[] i_arr = ...;
int max = reduce(i_arr, (a,b) -> (a > b) ? a : b);
int sum = reduce(i_arr, (a,b) -> a + b);

// we can write a named class that implements Predicate<T>
class Pred implements Predicate<Number> {
	@Override
	public boolean test(Number n) {
		return n.doubleValue() >= 0;
	}
}

Set<Integer> s1 = new HashSet<>();
...
List<Integer> pos_entries = ListUtil.select(s1, new Pred());

// however, it's much cleaner to use a lambda expression:
List<Integer> pos_entries = ListUtil.select(s1, (n) -> n.doubleValue() >= 0);
// when a lambda expression's parameter list has one parameter, we can omit the parentheses
List<Integer> pos_entries = ListUtil.select(s1, n -> n.doubleValue() >= 0);

// you can use lambda expressions when the return type is void
button2.addActionListener(
	(e) -> { System.out.println(text.getText()); }
);
// when the method returns void and the method body only has one statement, you can omit the curly braces
button2.addActionListener(
	e -> System.out.println(text.getText()))

// references can refer to an instance of an anonymous class written with a lambda expression
ActionListener AL2 = e -> System.out.println(text.getText());
button2.addActionListener(AL2);
BinOper sum_op = (a,b) -> a + b;
int sum = reduce(i_arr, sum_op);

// Lambda expressions only work with functional interfaces
	// the single method you write is the implementation of the single abstract method
	// the method inputs are the method inputs of the single abstract method, which types are known
		// so the types of the inputs are inferred from the method's signature
	// the method's return type are the abstract method's return type, which are known
		// so the return type is inferred from the method's signature

// Method reference
// imagine you write class Person and you have
public class PersonComp {
	public static int cmpByName(Person a, Person b) {
		 return a.getName().compareTo(b.getName());
	}
	public static int cmpByAge(Person a, Person b) {
		return a.getBirthday().compareTo(b.getBirthday());
	}
}

// you can use other methods to write a lambda expression
Person[] p_arr = ...;
// use static method
Arrays.sort(p_arr, (a,b) -> PersonComp.cmpByAge(a, b));
String[] s_arr = ...;
Arrays.sort(s_arr, (a,b) -> a.compareToIgnoreCase(b));
// however, even this is more complicated than necessary, because the lambda expression simply calls another method

// to simplify these lambda expressions, you can use method references
Person[] p_arr = ...;
Arrays.sort(p_arr, PersonComp::cmpByName);
String[] s_arr = ...;
Arrays.sort(s_arr, String::compareToIgnoreCase);
// when a lambda expression simply calls another method, you can simplify it to a method reference

// ------------------------------------------------------------------------------------------------------------------------
// Procedural programming vs. OOP
	// Procedural and object-oriented programming are two contrasting programming styles
	// Procedural programming revolves around using procedures (functions that are called not for their return value, perhaps because they return void) 
		// to operate on chunks of data (e.g. structs of C)
	// OOP revolves around objects, collections of data members accompanied by useful member functions

// C is called a procedural programming language because it provides the tools for procedural programming
// Java and C++ are called object-oriented languages because they also provide the tools for object-oriented programming

// Imperative programming vs. functional programming
	// Imperative and functional programming are two contrasting styles
	// Imperative programming describes /how/ a program should operate (to accomplish what you want) via variables and loops
	// Functional or declarative programming describes /what/ a program should accomplish via functions that do not cause side effects
		// Functions in functional programming can be understood via inputs and outputs, as they have no side effects

// Haskell and Lisp are called functional programming languages because they provide the tools for functional programming
// Java and C++ were called imperative languages because they provided the tools for imperative programming
// However, Java 8 and C++11 introduced major functional programming features; now functional programming on these languages is much more effective

// e.g. summing even numbers between 1 and 100
// the imperative way of summing all integers between 1 and 1000 is
int sum = 0;
for (int i = 0; i <= 1000; i++)
	if (i % 2 == 0)
		sum += i;
// you tell (as if you're speaking in "imperative mood") how the program should operate to achieve what you want

// the functional way is
int sum = IntStream.rangeClosed(1, 1000).filter(a -> a % 2 == 0).sum();
	// you're saying "create a stream of integers from 1 to 1000, filter to keep only even numbers, and sum them"

// here's how to do the Monte Carlo example functionally:
Random rand = new Random(seed);
double apx_pi = IntStream.generate( () -> {
		double x = rand.nextDouble();
		double y = rand.nextDouble();
		return (x * x + y*y <= 1) ? 1 : 0;} )
	.limit(1_000_1000)
	.average()
	.getasDouble()
	* 4;

List<Person> peopleList;
...;
double averageMaleAge = peopleList.stream()
	.filter(p -> p.getGender() == Person.MALE)
	.mapToInt(Person::getAge)
	.average()
	.getAsDouble();
	// this code is very readable; the step-by-step logic of computing the average male age is easy to follow

// 