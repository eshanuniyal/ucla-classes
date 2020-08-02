// Lecture 9 | Friday, Week 3

import java.util.Date;

// using an initialiser block
// we can use an initialiser block to avoid repeating code in constructors

public class Monster {
	private String dateOfBirth;
	private String name;
	// format of an initialiser block (typically placed before the constructors)
		// there is no function name or anything of the sort, just a pair of curly braces and some code inside it
		// the initialiser block is also called an "instance" initialiser block, in contrast with the "static" initialiser block
		// the initialiser block is run every time the class is instantiated, and it is run right before the constructor is run 
			// (which is why it is stylistically good to place it before a constructor)
	{
		dateOfBirth = (new Date()).toString();
	}
	// initialiser blocks aren't strictly necessary; you can achieve the same effect with a private method
	public Monster() {
		this("Unnamed");
	}
	public Monster(String name) {
		this.name = name;
	}
}


// static initialiser blocks
public class Card {
	private static final String[] suits;
	private static final char[] nums;
	// the static initialiser block is run once when the class is loaded
	static {
		suits = new String[] {"Clubs", "Diamonds", "Hearts", "Spades"};	// explicit array initialisation syntax; we don't need to specify the array has size 4
		
		nums = new char[13];	// array of size 13 for Aces through King
		nums[0] = 'A'; nums[10] = 'J'; nums[11] = 'Q'; nums[12] = 'K';	// inserting A, J, Q, K at appropriate indices
		for (int i = 0; i != 9; i++)	// inserting number elements
			nums[i] = ( (char) ('0') + i);	// uses ASCII conversion
	}
	// static initialiser blocks are mostly used to initialise static fields
}

// initialising fields: we can use shorthand to initialise fields that are easily set up
public class Complex {
	public double real = 0; imag = 0;	// equivalent to using an initialiser block to say { real = 0; imag = 0; }
}
public class Monster {
	private final String dateOfBirth = (new Date()).toString();	// equivalent to using the initialiser block in the above class
}

// there are 2 ways to initialise a final static field:
	// in its declaration, or
	// in a static initialisation block
// there are 3 ways to initialise a final non-static field:
	// in its declaration,
	// in an initialisation block, or
	// in a constructor

public class Test {
	public static void main(String[] args) {
		
	}
}