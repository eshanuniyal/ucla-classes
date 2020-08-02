// Lecture 8 | Wednesday, Week 3

// Fisher-Yates shuffle (a.k.a. Knuth shuffle)
/* The Fisher-Yates shuffle randomly permutes an array

Algorithm:
	a = some array of length n
	for i = n - 1, ..., 1
	j = randInt 0 <= j <= i
	swap(a[j], a[i])

The Fisher-Yates shuffle makes all n! permutations occur with the equal probability 1/n!.
	(assuming pure random generation, which we don't really get - for practical purposes though, it's close enough)
The Fisher-Yates shuffle is equivalent to putting all n objects in a box, shaking and mixing, and pulling out one object at a time.
*/

// Pseudo-random numbers

// Random number generation
/* The "random number" Math.random() returns are not truly random. They are pseudo-random numbers, which are deterministic numbers that look random.
You can't generate truly random numbers on a computer.

There are several ways to generate pseudo-random numbers and they are programmed into "pseudo-random number generators" (PRNGs; a.k.a. random number engines)
	e.g. linear congruential generator or Mersenne Twister
Some PRNGs are bad and some are better than others.
	e.g. rand() from cmath is a bad PRNG; random numbers generate by rand() repeat after a certain point
None are perfect, and all have tradeoffs.
You need a "seed" for a PRNG. Given the same seed, the PRNG will produce the same output.
*/

import java.util.Random;

public class Test {
	public static void main(String[] args) {
		long seed = System.currentTimeMillis();	// common choice of seed
		Random rand1, rand2;

		rand1 = new Random(seed);
		for (int i = 0; i != 10; i++)
			System.out.print(rand1.nextInt(10) + " ");

		System.out.print("\n");

		rand2 = new Random(seed); 
		for (int i = 0; i != 10; i++)
			System.out.print(rand2.nextInt(10) + " ");

		// a PRNG always needs a seed
		// if you don't provide one, the algorithm will create its own seed (usually based on the current time)
		rand = new Random();
		// usually, it's okay to use the automatic seed and not worry about it
		// sometimes, however, you want the same pseudo-random numbers, say for debugging purposes; for that, set the seed explicitly
	}
}

// Monte Carlo method
// The Monte Carlo method is a fancy name for a simple idea: simulate a bunch of random events and take their average to understand the "average behaviour"

// Using Monte Carlo to compute Pi (by checking how many random points fall in a quarter-circle of radius 1 in a 1 by 1 box)
import java.util.Random
public class Test {
	public static void main(String[] args) {
		
		Random rand = new Random(0);
		int n = 1000000;	// 1 million
		int count = 0;

		for (int i = 0; i != n; i++) {
			double x = rand.nextDouble();	// equivalent to math.Random()
			double y = rand.nextDouble();

			if (x*x + y*y <= 1)
				count++;
		}

		System.out.println((4.0 * count) / n);	// proportion of points in the circle should be pi/4, since it's a quarter-circle
	}
}

// Don't copy immutable Objects
public class Test {
	public static void main(String[] args) {
		String s1 = "Hello"
		String s2 = s1;	// just a reference to the same String object; don't do this
		String s3 = new String(s1);	// creates a reference to a new, identical String object

	}
}


// a factory method is a static method that returns an instance of the class
	// i.e. any function declared static that returns an instance of the class

public class Complex {
	public double real, imag;
	// /static/ constructor from polar coordinates
	public static Complex fromPolar(double r, double th) {
		double re = r*Math.cos(th);
		double im = r*Math.sin(th);
		return new Complex(re, im);
	}
	// there are two main advantages of factory methods:
		// you can have multiple factory methods with the same number and types of inputs
		// the factory method's name can be descriptive
	public static Complex fromXY(double x, double y) {
		re = x;
		im = y;
	}

	// we can also create a copy factory method instead of a copy constructor
	public static Complex copy(Complex c) {
		return new Complex(c.real, c.imag);
	}

	// we can force people to use factory methods by making constructors private
	private Complex(double r, double i) {
		real = r; imag = i;
	}

	// within a non-static method or a constructor, "this" is a reference to the current object
	public Complex(double real, double imag) {
		this.real = real; this.imag = imag;
	}	// this is the most common use of "this", to access a field the name of which is shadowed by a method or constructor parameter

	// another use for "this" is for "explicit constructor invocation" (a.k.a. "constructor chaining")
	public Complex() {
		this(0, 0);	// calls the constructor with the appropriate arguments (i.e. the constructor below)
			// saves us from writing this.real = 0; this.imag = 0;
	}
	public Complex(double real, double imag) {
		this.real = real; this.imag = imag;
	}
	// when you use "this" to call another constructor, you must do so in the first line of the constructor
}

public class Test {
	public static void main(String[] args) {
		Complex c1, c2;

		// we can use factory methods with identical argument types
		c1 = Complex.fromXY(0.1, 0.3);
		c2 = Complex.fromPolar(5.1, Math.PI/2)
	}
}