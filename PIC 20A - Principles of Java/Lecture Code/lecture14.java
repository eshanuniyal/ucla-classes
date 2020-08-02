// Lecture 14 | Wednesday, Week 5

// Graphical User Interfaces and swing

import javax.swing.*;	// necessary to define JFrame and such
import java.awt.*;	// necessary for code after line 44

public class Test {
	public static void main(String[] args) {
		
		// JFrame is javax.swing.JFrame
		JFrame frame = new JFrame("Hello Swing");
			// input "Hello swing" is the frame's title

		// since JFrame is an object, we change its state with a member function
		frame.setVisible(true);	// we now see a window (but it's tiny and up in the corner, because it has size 0 by default)

		// the face of the window is called the "content pane"
		java.awt.Container contPain = frame.getContentPane();
			// the content pane is an object of type java.awt.Container (awt = abstract window toolkit, a library that preceded javax on which swing is built)

		// let's add a JLabel (a small graphical display of text) to the content pane
		JLabel label = new JLabel("Hello World");
		contPane.add(label);	// the add method, inherited from java.awt.Container, takes in java.aqt.Component (which JLabel inherits) as its input

		// it's good practice to not display a GUI until you're done building it; frame.setVisible(true) should be called after all the components have been defined and loaded
			// if the time it takes to build the GUI is perceivable, the user can see the GUI components popping into existence

		frame.setSize(300, 200);	// JFrame inherits setSize() from its parent class Component
			// width followed by height
		frame.setVisible(true);

		// even if we close the window, the program is still going to keep running; the window still exists, it's just not open/visible
		frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
			// when the window is closed, the program will end
			// this line is typically placed right after the definition of a JFrame

		// Instead of adding a JLabel, we can add a JButton:
		frame.getContentPane().add(new JButton("Do Nothing"));
			// by default, the button takes up the entire window, and it'll cover / hide the previously-created JLabel
			// JButton also inherits componnet

		// We should place Components in different locations
		contPane.add(new JLabel("Label name"), BorderLayout.CENTER);	// the label should be positioned in the center(-left) of the window
		contPane.add(new JButton("Do nothing"), BorderLayout.SOUTH);	// the button should be positioned at the bottom of the window

		// let's make the JButton do something
		button.addActionListener(new ActionClass());	// a method from java.awt.event.* (imported automatically in java.awt.*)
			// this is effectively a function that will do something when an action is taken
	}
}

class ActionClass implements ActionListener {
	public void actionPerformed(ActionEvent event) {
		System.out.println("Button clicked");
	}
}