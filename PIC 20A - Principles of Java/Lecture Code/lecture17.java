// Lecture 18 | Monday, Week 7
// Note: Lecture 17 (Wednesday, Week 6) was review for midterm exam on Friday, Week 6

// Layout managers
// JPanels use layout managers to lay out its components
	// by default, JPanels use FlowLayout
	// by default, content panes use BorderLayout
// All layout managers implement the interface LayoutManager

// setting the layout manager
// set a JPanel's layout manager in its constructor:
Jpanel panel = new JPanel(new BorderLayout());
	// we can initialise a panel or content pane with an instance of the layout manager we wanna use
Container contentPane = frame.getContentPane();
contentPane.setLayout(new FlowLayout());
	// we can also call setLayout on a panel or content pane with an instance of the layout manager we wanna use

/* BorderLayout
--------NORTH-------
WEST	CENTER	EAST
--------SOUTH-------
*/
// CENTER gets as much of the available space as possible; other areas get the minimum space to fit their Components
// When no position is specified, .add places a Component in CENTER


/* GridLayout
Button 1	Button 2 |
Button 3	Button 4 |-> 3 by 2 grid layout
Button 5	(empty)  |
Button A Button B (empty)  |-> 2 by 3 grid layout
Button C Button D Button E |
*/

Container pane = frame.getContentPane();
JPanel panel1 = new JPanel();
JPanel panel2 = new JPanel();
pane.add(panel1, BorderLayout.NORTH);
pane.add(panel2, BorderLayout.SOUTH);

// we now organise the buttons inside the panels using Grid Layout
panel1.setLayout(new GridLayout(0,2));	// "0" means the number of rows is undetermined; Java dynamically decides how many rows to put in as you keep adding buttons
panel1.add(new JButton("Button 1"));
panel1.add(new JButton("Button 2"));
panel1.add(new JButton("Button 3"));
panel1.add(new JButton("Button 4"));
panel1.add(new JButton("Button 5"));
panel2.setLayout(new GridLayout(2,3));
panel2.add(new JButton("Button A"));
panel2.add(new JButton("Button B"));
panel2.add(new JLabel ("(empty JLabel)"));
panel2.add(new JButton("Button C"));
panel2.add(new JButton("Button D"));
panel2.add(new JButton("Button E"));
// we could reset our layout using setLayout if we want to add more components than we initially thought
panel2.setLayout(new GridLayout(2, 4));

// Putting space between Components
// Here are three simple ways to insert empty space in your GUI:
	// Layout manager, invisible components, and empty borders
	// Some layout managers give you some control over empty space
	// Empty JPanels or JLabels can take up space
	// You can add invisible borders around JPanels and JLabels

// Borders
// JPanels and JLabels can have Borders
JPanel panel1 = new JPanel();
	// use the factory class javax.swing.BorderFactory to create a javax.swing.border.Border object
panel1.setBorder(BorderFactory.createLineBorder(Color.BLACK));
JPanel panel2 = new JPanel();
panel2.setBorder(BorderFactory.createEmptyBorder(3,3,3,3));
	// dimension go top, left, bottom, right

// Absolute positioning
// You can manually specify the size and position of Components with absolute positioning
// This is usually a bad idea; using a GUI using absolute positioning does not adjust well to resizing and to differences between systems

// --------------------------------------------------------------------------------------------------------------------------------------
// Exceptions

// Introductory example
// Imagine trying to read from a file:
import java.io.*
public class Test {
	public static void main(String[] args) {
		
		FileInputStream in = new FileInputStream("file.txt");	// error!
			// this code does not compile because the exception for not having the file is unaccounted for

		// catching the exception
		try {
			FileInputStream in = new FileInputStream("file.txt");
		} catch (FileNotFoundException e) {
			System.out.println("File not found");
			return;
		}

		// do something with opened file
		// ...

		// the 3 types of exceptions
		// Exceptions are objects that inherit Throwable
			// Unchecked exceptions inherit RuntimeException
			// Checked exceptions inherit Exception but not RuntimeException
			// Errors inherit Error, which also inherits Throwable

		// Unchecked exceptions are not checked by the compiler, i.e. the code compiles without a try-catch block
		int[] i_arr = {1, 2, 3};
		System.out.println(i_arr[3]);
		// compiles fine but doesn't run fine
			// unlike C++, Java doesn't check for out-of-bounds access when compiling for performance reasons

		// you can catch unchecked exceptions though
		int[] i_arr = {1, 2, 3};
		try {
			System.out.println(i_arr[3]);
		} catch (ArrayIndexOutOfBoundsException e) {
				// this is a declaration of an exception variable
				// the variable e will be of type ArrayIndexOutOfBoundsException
			System.out.println("Exception happened");
			System.out.println(e);
			System.out.println(e.getMessage());	
				// exceptions usually have a getMessage() method which provides us with user-readable information about the exception
		}

		// unchecked exceptions are also called runtime exceptions
		// you don't have to explicitly handle a runtime exception, and you probably don't want to
		// since runtime exceptions are usually called by bugs or flaw of your code,
			// you should fix the problem instead of catching the runtime exception

		// Checked exceptions
			// you must explicitly handle checked exceptions, or your code won't compile
			// checked exceptions are part of the function specification as much as the input and outputs of the function are
			// functions specify, with the "throws" keyword, what kind of checked exceptions it throws

	}
}

// Errors
	// Error represents fatal problems the program probably can't and shouldn't recover from, such as java.lang.OutOfMemoryError
	// Errors are treated like unchecked exceptions in that you don't have to explicitly handle them
	// You really shouldnt' catch Errors. If you do, you shouldn't continue the program.

// this example causes a java.lang.StackOverflowError
public class Test {
	public static void fn() {
		fn();
	}
	public static void main(String[] args) {
		fn();
	}
}
// (this is recursion without a base case)


// to handle exceptions, the risky code must go in a "try block"
try {
	// risky code
} catch (ExceptionType name){
	// code
}

// exceptions are polymorphic; you can specify a superclass to catch exceptions of subclass types
try {
	...
} catch (Exception e) {
	System.out.println("Any exception");
}

// you can have multiple catch blocks
// an exception is checked against each catch block in the stated order (at most one catch block is run)
try {
	...
} catch(RuntimeException e) {
	System.out.println("Unchecked exception");	
		// any runtime exception is an unchecked exception
} catch (Exception e) {
	System.out.println("Checked exception");
		// if we have an exception that's not a runtime exception, it has to be a checked exception 
		// (checked exceptions inherit from Exception, but not from RuntimeException)
} catch (Throwable e) {
	System.out.println("Error");
		// we don't have an exception -> we must have an Error, which inherits from Throwable
}
// note: the order of the catch blocks do matter in this example