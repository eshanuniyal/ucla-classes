// Lecture 15 | Friday, Week 5

import javax.swing.*
import java.awt.event.*

public class Test {
	public static void main(String[] args) {
		
		JFrame frame = new JFrame("Hello Swing");
		java.awt.Container contPain = frame.getContentPane();

		JLabel label = new JLabel("Hello World");
		contPane.add(label);

		frame.setSize(300, 200);
		frame.setVisible(true);

		frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
	
		frame.getContentPane().add(new JButton("Click me"));
	
		contPane.add(new JLabel("Label name"), BorderLayout.CENTER);
		contPane.add(new JButton("Do nothing"), BorderLayout.SOUTH);

		button.addActionListener(new ActionClass());

		// swing inheritance hierarchy
			// the swing and awt libraries are organised around inheritance
		/* Hierarchy
						.lang.Object
							|
						.awt.Component
							|
						.awt.Container
					/		|
		.awt.Window		x.swing.JComponent
			|				|			   \
		.awt.Frame 		x.swing.JLabel		x.swing.AbstractButton
			|									|
		.x.swing.JFrame 					x.swing.JButton
		*/

		// To build a graphical user interface (GUI), you need to
			// create components
			// layout the components, and
			// make the components do useful things

		// Basic JComponents

		// JLabel
		// Use JLabel to display a text and/or an image; the text and image are unselectable
		JLabel ourLabel = new JLabel("UCLA logo");		// creating a new JLabel
		Icon ourIcon = new ImageIcon("ucla.jpg");		// creating a new Icon (for the JLabel)
		ourLabel.setIcon(ourIcon);	// setting the icon to our label; setIcon takes in Icon, which ImageIcon implements
		// the interface javax.swing.Icon represents a small fixed size picture, typically used to decorate components
			// ImageIcon is the most useful class that implements Icon within the Java API
			// ImageIcon's constructors support a few ways of loading an image
				// What is the "description"?
				// What does equals() do? It's inherited but not overriden
				// Can you add an ImageIcon directly to a content pane?
					// No, because ImageIcon doesn't inherit from Component, and therefore can't be loaded to a content pane
			// here's only one useful class that implements Icon, but that doesn't mean the interface Icon is useless; we can create our own custom Icons
				// to implement Icon we must implement hte (implicitly) abstract method
					// paintIcon(Component c, Graphics g, int x, int y)
				// we need to learn about java.awt.Component and java.awt.Graphics

		// setting position of the label
		ourLabel.setVerticalTextPosition(JLabel.BOTTOM);
		ourLabel.setHorizontalTextPosition(JLabel.CENTER);
			// JLabel inherits the static fields BOTTOM and CENTER from interface SwingConstants
		// inserting label in our content pane
		contPane.add(ourLabel, BorderLayout.CENTER);	// note: a JLabel can be purely a picture, it doesn't have to be text and an image

		// The constructors and "setter" methods tell us a lot about what we can do with the class
			// Use the "getter" methods to retrieve information

		// JPanel
			// javax.swing.JPanel is a general purpose lightweight container
			// it doesn't do anything, but it's a container of other components
			// it helps treat a group of components as one entity and position them accordingly

		JPanel panel1 = new JPanel();
		panel1.add(new JLabel("Label in panel1"));
		contPane.add(panel1, BorderLayout.CENTER);

		JPanel panel2 = new JPanel();
		panel2.add(new JLabel("Label in panel2"));
		contPane.add(panel2, BorderLayout.SOUTH);

		panel1.setBackground(Color.YELLOW);
		panel2.setBackground(70, 80, 75);	// RGB 

		// nested JPanels
		JPanel panel3 = new JPanel();
		panel1.add(panel3, BorderLayout.CENTER);



		// GUIs naturally have a nested and hierarchical structure; this makes inheritance and polymorphism perfect for the job
			// as with ImageIcon, we can also create custom JPanels (see below ActionCLass)
				// JPanel inherits paintComponent from JComponent
				protected void paintComponent(Graphics g);
				// it's protected and not final; it's meant to be overriden
				// Java calls paintComponent when it renders the GUI on the screen

		JLabel label = new JLabel("UCLA Logo");
		Icon icon = new MissingIcon();
		label.setIcon(icon);
			// instead of loading an icon from an ImageFile, we're just creating an instance of our MissingIcon class
		label.setVerticalTextPosition(JLabel.BOTTOM);
		label.setHorizontalTextPosition(JLabel.CENTER);
		contPane.add(label, BorderLayout.CENTER);
		frame.setSize(300, 200);
		frame.setVisible(true);		// icon shows up

		// use javax.swing.JTextArea to display multiple lines of text that the user can edit
		// JTextArea inherits javax.swing.text.JTextComponent and is one of the several components that can hold text
		JTextArea textArea = new JTextArea();
		textArea.setBackground(Color.YELLOW);
		contPane.add(textArea);
		frame.setSize(300, 200);
		frame.setVisible(true);
	}
}


class MyPanel extends JPanel {
	@Override
	public void paintComponent(Graphics g) {
		// use java.awt.Graphics to draw onto components
		// set the colour and the properites of the draw, and then draw
		// "Draw" draws the border; "Fill" fills the interior of the shape
		// the x-coordinate goes from left to right; the y-coordinate goes from top to bottom
			// think of g as a paintbrush for painting the components
		g.setColor(Color.ORANGE);
		g.fillRect(20, 50, 100, 100);
		g.setColor(Color.RED);
		g.drawOval(30, 30, 10, 10);
	}
}

// Custom Icon
public class MissingIcon implements Icon {
	private int w = 32, h = 32;

	// (since Icon is an interface, we need to implement each function)
	@Override
	public int getIconWidth() { return w; }

	@Override
	public int getIconHeight() { return h; }

	@Override
	public void paintIcon(Componenet c, Graphics g, int x, int y) {
		g.setColor(Color.BLACK);
		g.drawRect(x, y, w - 1, h - 1);
		g.setColor(Color.WHITE);
		g.fillRect(x + 1, y + 1, w - 2, h - 2);
		g.setColor(Color.RED);
		((Graphics2D) g).setStrok(new BasicStroke(4));	// sets the stroke width (4 pixels) for the lines we are about to draw,
			// using the java.awt.Graphcs2D class, a subclass of java.awt.Graphics with additional functionality
			// since Java 1.2, all Graphics objects provided by the Java API are actually Graphics2D objects
		g.drawLine(x + 10, y + 10, x + w - 10, y + h - 10);
		g.drawLine(x + 10, y + h - 10, x + w - 10, y + 10);
	}
}