// Lecture 16 | Monday, Week 6

import javax.swing.*
import java.awt.event.*

// Events
	// Various GUI components fire "events". By default, these events are ignored, but you can choose to listen to them.
	// When you attach an EventListener to an event, the EventListener is run when the event is fired.
	// There are several types of events (it is possible to create and fire custom events, but we won't)
	// When a Component has the method
		public void addXListener(XListener l);
	// you can tell that it fires an XEvent

// ActionEvent and ActionListener
	// Buttons and clickable components can fire java.awt.event.ActionEvents
	//  java.awt.event.ActionListner listens to an ActionEvent
	// The interface ActionListener has one method
		public void actionPerformed(ActionEvent e)
	// which is called when the ActionEvent the ActionListener is listening to is fired

// A Jbutton (and any AbstractButton) can fire an ActionEvent. Use
	addActionListener(ActionListener l)
// to attach an ActionListener to the JButton's ActionEvent

// Let's separate the main function from the GUI:

public class Test {
	public static void main(String[] args) {
		MyGUI gui = new MyGUI();
			// good practice to have a separate GUI class that loads up the GUI properly, and has all the logic of the GUI
			// part of the reason is just readability
			// the other part is that if all the logic is in the same class, methods of that class can access its fields (i.e. GUI components) more easily
	}
}

class MyGUI implements ActionListener {

	private JTextArea text;

	public MyGUI() {
		...;
		JButton button = new JButton("Click me");
		button.addActionListener(this);	// we can pass in "this" because MyGUI implements ActionListener
			// whenever an ActionEvent is fired (e.g. when the button is clicked), the button will call the ActionListener's actionPerformed method
		...;
	}

	@Override 
	public void actionPerformed(ActionEvent e) {
		// must be defined, since MyGUI implements ActionListener
		System.out.println(text.getText());
			// since ActionPerformed is a method of MyGUI, it can access other components of the GUI
	}
}

// if you think about it, it's weird that the class MyGUI is an ActionListener
// what listens to the JButton's ActionEvent should /belong/ to the GUI, it should not be the GUI itself

// Inner Classes as EventListeners
	// Using a GUI as an A
	// If you have 2 JComponents that fire ActionEvents, what do you do?
		// if the GUI itself is the ActionListener, it can only have one actionPerformed method; we might need two
		// a potential ad-hoc solution:
	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getSources() == button1)
			System.out.println("Button1 clicked");
		else if (e.getSource() == button2)
			System.out.println("Button2 clicked");
	}
	// using ActionEvent is fine; that actionPerformed gets more and more complicated with the more JComponents firing ActionEvents is the issue
	// it's better to use inner classes as EventListeners

class MyGUI implements ActionListener {

	private JTextArea text;
	private final JButton button1, button2;

	{
		// a java.awt.Component can fire a java.awt.event.MouseEvent
		// a java.awt.event.MouseListener listens to a MouseEvent
		JPanel panel = new JPanel();
		panel.addMouseListener(new ML());

		JFrame frame = new JFrame();
		// setDefaultCloseOperation
			// when you close a JFrame, a WindowEvent is fired, and by default, the JFrame is hidden
			// when a java.awt.Window (a superclass of JFrame) exists, Java does not exist, even if the end of main() is reached
			// you can add a WindowListener to the JFrame and have it dispose the JFrame when it's closed. You can do the same with:
		frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		// once all JFrames are disposed, Java can exit the program

		// you can also forcefull exit the program upon closing the JFrame
		frame.setDefaultCLoseOperation(JFrame.EXIT_ON_CLOSE);
			// even if you have other frames open, the program will exit if you close this particular frame (and those other windows will also then be closed)
	}

	public MyGUI() {
		JButton button1 = new JButton();
		JButton button2 = new JButton();
		button1.addActionListener(new B1L());	// a new instance of B1L is used as the ActionListener for button1
		button2.addActionListener(new B2L());
	}

	// button1 listener class
	private class B1L implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			System.out.println("Button1 clicked");
		}
	}

	// button2 listener class
	private class B2L implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			System.out.println(text.getText());
		}
	}

	private class ML implements MouseListener {
		// there are many different MouseListener methods, each of which must be implemented (even if they should do nothing for our purposes)
			// this is because MouseListener is an interface that declares each of these (implicitly abstract) methods
		public void mouseClicked(MouseEvent e) {
			System.out.println("clicked");
			String xy = "(" + e.getX() + "," + e.getY() + ")";
			System.out.println(xy);	// print where the mouse clicked inside the panel
		}
		// moved mouse over some component
		public void mouseEntered(MouseEvent e) {
			System.out.println("entered");
		}
		// mouse exited the area of some component
		public void mouseExited(MouseEvent e) {
			System.out.println("exited");
		}
		public void mousePressed(MouseEvent e) {
			System.out.println("pressed");
		}
		public void mouseReleased(MouseEvent e) {
			System.out.println("released");
		}
	}

	// note: if we have too many listeners, it might be cleaner to declare all the listener classes as package-private classes (put them in another file) 
		// or private class (put them in the same file, but not in the GUI class)
	// however, only inner classes can access elements of the GUI (as B2L does with field text)

}