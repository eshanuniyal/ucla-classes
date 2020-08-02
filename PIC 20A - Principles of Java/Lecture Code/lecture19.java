// Lecture 19 | Wednesday, Week 7

// a single catch block can catch multiple types of exceptions using |
try {
	...
}
catch (IOException | SQLException e) {
	System.out.println(e);
}

// throw an exception with throw
public class Test {
	public static void fn(int i) {
		if (i == 0) {
			throw new IllegalArgumentException();	
				// we create and throw a new IllegalArgumentException()
				// java.lang.IllegalArgumentException is a runtime exception
			System.out.println("We never reach this line");
		}
	}

	public static void main(String[] args) {
		fn(0);
	}
}

// to throw a checked exception, specify it with throws
import java.io.*;

public class Test {
	public static void fn() throws IOException {
			// adding "throws IOException" to the function definition lets the compiler know that the function fn potentially throws an IOException
		...;
		throw new IOException();
	}

	public static void main(String[] args) {

		// we now have to wrap any calls of fn() in a try-catch block
		try {
			fn();
		} catch (IOException e) {
			...
		}
	}
}

// instead of catching an exception, you can "duck" or "specify" it
import java.io.*;

public class Test {
	public static void main(String[] args) throws FileNotFoundException {
			// by adding "throws FileNotFoundException" to the function declaration, 
				// we pass the responsibility of catching any FileNotFoundExceptions to whichever function called this
		// now compiles
		FileInputStream in = new FileInputStream("file.txt");
	}
	// you "duck" the responsibility of catching the exception and pass it on to whoever calls your exception
	// (in this case, you're passing on the responsibility to JVM, and JVM doesn't catch anything)

	public static void fn() throws Exception {
		...
		// if there's any exception in fn(), the function that called it (say, main) has to catch it
	}
}

// so you must "catch or specify" checked exceptions
// some view catch or specify as a flaw of Java that forces cumbersome code
// you can bypass the catch or specify mechanism by ducking and only throwing runtime exceptions, but this is not recommended

// Should you catch exceptions?
	// in a sense Errors are most severe, and checked exceptions are least severe
	// as discussed, you shouldn't catch Errors and runtime exceptions
	// you must catch or specify checked exceptions, but you may not want to rely on the catch
	// it's usually better to prevent exceptions from happening at all
		// e.g. check if a file exists before opening it
	// this way, exceptions are truly exceptional, and you use catch to exit the program gracefully instead of catching an exception and keep going

// the "finally" block /always/ executed after the try-catch block
try {
	...
} catch (SomeException e) {
	...
} catch (AnotherException e) {
	...
} finally {
	// resource cleanup
	// this code always runs no matter what
}

public static void fn() {
	try {
		throw new Exception();
	}
	catch (Exception e) {
		System.out.println("We'll excit fn()");
		return;
	}
	finally {
		// this code is still executed before we call "return" in the catch code
		System.out.println("finally ran");
	}

	System.out.println("We never reach here");
}

// The "finally" block is always executed if you reach a try-catch statement, no matter what

// why do you need finally?
	// in Java, you usually don't free resources manually; the garbage collector handles memory management automatically
	// however, some resources are very expensive, and you do want to free them manually (using provided methods)
	// put such resource cleanups in the finally block to ensure they always happen
	// we'll see a concrete example of this when we talk about streams

// demo
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;	// not needed, but for clarity's sake

public class Main {

	static JTextArea fileInput;
	static FileLoader fileLoader = new FileLoader();
	static JTextArea fileContents = new JTextArea;

	// the FileLoader class needs to be an inner class of main so it can use fileInput 
	private class FileLoader implements ActionListener {
	public void actionPerformed(ActionEvent event) {
		try {
			File myObj = new File(fileInput.getText());
			Scanner myReader = new Scanner(myObj);
				// scanner can also be used to read from files
			while (myReader.hasNextLine()) {
				String data = myReader.nextLine();
				fileContents.append(data);
				fileContents.append('\n');
			}
			myReader.close();
		} catch (FileNotFoundException e) {
			System.out.println("An error occurred.");
			e.printStackTrace();
				// prints function calls that led up to the exception
		}
	}
}

	public static void main(String[] args) {
		Jframe frame = new JFrame("Hello Swing");
		frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

		Container pane = frame.getContentPane();
		
		fileInput = new JTextArea();
		fileInput.setBackground(Color.BLUE);
		pane.add(fileInput, BorderLayout.NORTH);

		JButton loadFileButton = new JButton("Load the file");
		loadFileButton.addActionListener(fileLoader);
		pane.add(loadFileButton, BorderLayout.SOUTH);

		fileContents.setBackground(Color.YELLOW);
		pane.add(fileContents, BorderLayout.CENTER);

		frame.setSize(640, 480);
		frame.setVisible(true);
	}

	// if we now run the code and enter a garbage name in the fileInput JTextArea, the catch block in the FileLoader class is run
} 