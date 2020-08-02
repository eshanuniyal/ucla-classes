// Lecture 10 | Monday, Week 4

// Inheritance, Interface, and Polymorphism

// Maps application
// Imagine writing a program that finds directions from one point to another, and you want to write a class for this
public class Direction {
	public GeoLocation getStartingPoint() {...; }
	public GeoLocation getDestination() {...; }
	public double getDistance() {...; }
	public double getTime() {...; }
}

// If you think about it, directions are best described as smaller paths put together
	// e.g. the directions from UCLA to UC Berkeley can be broken down into walking, taking a bus, walking, taking a flight, walking, taking another two buses, and then walking
// So perhaps Direction should have a "Path" array as its field

public class Direction {
	private Path[] subPaths;
	...;
	public double getTime() {
		double totalTime = 0;
		for (Path p : subPaths)
			totalTime += p.getTime();
		return totalTime;
	}
}

public class Path {
	public static final double walking_speed = 3;
	public final double distance;
	private final GeoLocation start, dest;
	...;
	public double getTime() {
		return distance / walking_speed; 
	}
	public string toString() {
		return "A pedestrian path from " + start + " to " + dest + ".";
	}
}

// however, a Path could be any kind of path, not just a pedestrian path
	// a bus route is quite different from a pedestrian path
	// non-pedestrian paths can have toll fees or fairs
	// bus or metro paths should contain information on the number of stops, et cetera

public class Path {
	public static final double walking_speed = 3;
	public final double distance;
	private final GeoLocation start, dest;
	public final boolean isPedestrian, isBus, isPlane;
	public final int fairCost, tollCost;
	public final int numStops;
	...;
	public double getTime() {
		if (isPedestrian)
			return distance / walking_speed; 
		else if (isPlane){
			if (isHeadWind)
				return distance / head_wind_airplane_speed;
			else
				return distance / tail_wind_airplane_speed
		}
		...;
	}
	public string toString() {
		return "A pedestrian path from " + start + " to " + dest + ".";
	}
}

// a Path class designed this way will therefore get fairly messy
// Pedestrian paths, bus routes, flights, and other paths should be separate classes, but then using them in class Direction becomes a pain
// If we note the hierarchical structure (pedPath, busPath, and flightPath are all different kinds of Paths), we realise inheritance is what we need


// Rules of inheritance: the basics
/* Say class B "inherits" or "extends" class A
	- A is called a superclass, base class, or parent class
	- B is called a subclass, derived class, extended class, or child class
	- B inherits A's public and protected fields and methods (except constructors)
	- B can have additional fields and methods, in addition to what it inherited from A
	- B can call A's public and protected constructors
	- B can override methods inherited from A
	- A reference variable of type A can refer to an object of type A or B
*/

// Say you want to write a class Part that represents mechanical parts
public class Part {
	public final double cost, weight;
	public Part(double cost, double weight) {
		this.cost = cost; this.weight = weight;
	}
	public String toString() {
		return "This is a part with cost " + cost + " and weight " + weight + ".";
	}
}

// say a Screw is a mechanical part
	// syntax for declaring Screw as a base class of Part
public class Screw extends Part {
	public final double size;
	public Screw(double cost, double weight, double size) {
		super(cost, weight);	// calls the super class (i.e. base class) constructor to initialise the cost and weight fields
			// it acts as a reference to the "this" keyword for the parent class
			// we can also do, say, super.cost() to call the cost method in super
		this.size = size;
	}
	// this toString() method overrides the toString() method of the parent class
	public String toString() {
			// we can also access fields inherited from Part, such as cost
		return "A screw of size " + size + " and cost " + cost + ".";
	}
}

// you can use Screw like any class, and you can access the inherited public fields cost and weight
public class Test {
	public static void main(String[] args) {
		Screw s1 = new Screw(5, 2, 17);
		System.out.println(s1);
		System.out.println(cost);
		System.out.println(s1.weight);
		System.out.println(s1.size);
	}
}

// a reference variable of type part can refer to a Part or a Screw
public class Test {
	public static void main(String[] args) {
		
		Part[] part_arr = new Part[3];	// create a Part array of size three
		
		part_arr[0] = new Part(1, 10);
		part_arr[1] = new Screw(5, 2, 17);
		part_arr[2] = new Bolt(12, 13, 14);	// Bolt is another child class of Part

		for (int i = 0; i != 3; i++)
			System.out.println(part_arr[i]);	// calls the toString() method of the derived classes if there is one and the Part class if not
	}
}

// all objects (except java.lang.Object) that don't explicitly inherit another class inherits java.lang.Object
// this is where toString() comes from; it is inherited from Object
// equals() is another useful function inherited from Object. We will see how to override equals().

package hw2;

import java.util.Random;

public class PlayCard {
  public static void main(String[] args) {
    //set up reader to take inputs
    java.util.Scanner reader = new java.util.Scanner (System.in);
    
    int n = 16; //game size
    MatchCardGame g1 = new MatchCardGame(n);
    g1.shuffleCards();
    
    while(g1.gameOver()) {
      //print board status
      System.out.println(g1.boardToString());
      
      //ask for a card to flip until we get a valid one
      System.out.println("Which card to play?");
      while(!g1.flip(reader.nextInt())) {}
      
      //print board status
      System.out.println(g1.boardToString());
      
      //ask for a card to flip until we get a valid one
      while(!g1.flip(reader.nextInt())) {}
      
      //say whether the 2 cards were a match
      if(g1.wasMatch()) {
        System.out.println("Was a match!");
      } else {
        //print board to show mismatched cards
        System.out.println(g1.boardToString());		
        System.out.println("Was not a match.");
        //flip back the mismatched cards
        g1.flipMismatch();
      }
    }
    
    //Report the score
    System.out.println("The game took " + g1.getFlips() + " flips.");
    
    //Using the AIs
    int count;
    MatchCardGame g2 = new MatchCardGame(n);
    g2.shuffleCards();
    count = playRandom(g2);
    System.out.println("The bad AI took " + count + " flips.");
    MatchCardGame g3 = new MatchCardGame(n);
    g3.shuffleCards();
    count = playGood(g3);
    System.out.println("The good AI took " + count + " flips.");
    // Using MCs
    int N = 1000;
    System.out.println("The bad AI took " + randomMC(N) + " flips on average.");
    System.out.println("The good AI took " + goodMC(N) + " flips on average.");
  }

  // Artificial Players

  public static int playRandom(MatchCardGame g) {
    // plays the game by flipping a legal random card. i.e., at each turn, play one of face-down cards with equal probability independent of any past plays. 
    // The method plays until the game is over and returns the total number of flips.

    // creating random number generator with current time as seed
    long seed = System.currentTimeMillis();
    Random generator = new Random(seed);

    // creating array to keep track of revealed cards (true if card has been revealed, false otherwise)
    boolean[] revealArray = new boolean[g.n];
    for (int i = 0; i != g.n; i++)
      revealArray[i] = false;


    // playing until game over
    while(!g.gameOver()) {

      //print board status
      // System.out.println(g.boardToString());

      // generate random valid move
      int firstFlip, secondFlip;
      while (true) {
        // generates pair of random flips between 0 (inclusive) and n (exclusive)
        firstFlip = generator.nextInt(g.n);
        secondFlip = generator.nextInt(g.n); 
        // continue and generate again if card at either index has already been revealed or if both indices are equal
        if (revealArray[firstFlip] || revealArray[secondFlip] || firstFlip == secondFlip)
          continue;
        break;  // valid moves found
      }
          
      // flipping
      g.flip(firstFlip);
      g.flip(secondFlip);

      // updating revealArray if matching pair found
      if (g.wasMatch()){
        revealArray[firstFlip] = true;
        revealArray[secondFlip] = true;
      }
      // turning cards back to face down if matching pair not found
      else
        g.flipMismatch();
    }
    // returning number of flips taken
    return g.getFlips();
  }

  public static int playGood(MatchCardGame g) {
    // plays the game with perfect memory. 
    // After an even number of flips, if there is a known face-down pair, play the pair. 
    // Otherwise, randomly play, with equal probability, one of the unknown facedown cards. 
    // After an odd number of flips, if there is a known face-down match, play the match.
    // Otherwise, randomly play, with equal probability, one of the unkown face-down cards. 
    // The method plays until the game is over and returns the total number of flips
    
    // creating random number generator with current time as seed
    long seed = System.currentTimeMillis();
    Random generator = new Random(seed);

    // creating array to keep track of known, face-down cards (card character if card is known and face-down, * otherwise)
    char[] knownArray = new char[g.n];
    for (int i = 0; i != g.n; i++)
      knownArray[i] = '*';

    // creating array to keep track of face-up cards
    boolean[] revealArray = new boolean[g.n];
    for (int i = 0; i != g.n; i++)
      revealArray[i] = false;

    // playing until game over
    while(!g.gameOver()) {

      //print board status
      // System.out.println(g.boardToString());

      /*// for debugging
      for (char i : knownArray)
        System.out.print(i + " ");
      System.out.print('\n');
      for (boolean b : revealArray)
        if (b)
          System.out.print("t ");
        else
          System.out.print("f ");
      System.out.print('\n');
      */
      boolean knownPairFound = false;
      // checking if there is a known face-down pair
      // iterating over all cards (except the last) in knownArray to look for known, unrevealed pairs
      for (int i = 0; i != g.n - 1; i++) {
        // known face-down card found
        if (knownArray[i] != '*') {
          // searching for another identical known face-down card after known card
          for (int j = i + 1; j != g.n; j++) {
            // cards match
            if (knownArray[j] == knownArray[i]) {
              // playing both cards; this will certainly result in a match

              assert !revealArray[i] : "Card at index " + i + " has already been revealed";
              assert !revealArray[j] : "Card at index " + j + " has already been revealed";
              assert g.flip(i) : "Card at index " + i + " cannot be flipped";
              assert g.flip(j) : "Card at index " + i + " cannot be flipped";
              // updating knownPairFound
              knownPairFound = true;
              // resetting indices in knownArray; since both cards have been revealed, we don't care about them anymore
              knownArray[i] = '*';
              knownArray[j] = '*';
              // updating revealArray
              revealArray[i] = true;
              revealArray[j] = true;

              break;
            }  
          }
          if (knownPairFound)
            break;
        }
      }
      // known pair found and moved -> end of turn
      if (knownPairFound)
        continue;

      // known pair not found -> generate random valid move
      int firstFlipIndex;
      while (true) {
        // generates random flip between 0 (inclusive) and n (exclusive)
        firstFlipIndex = generator.nextInt(g.n);
        // break if card is face-down and unknown
        if (!revealArray[firstFlipIndex] && knownArray[firstFlipIndex] == '*')
          break;
      }

      // flipping and finding first card
      assert g.flip(firstFlipIndex) : "Card at index " + firstFlipIndex + " cannot be flipped";
      char firstFlip = g.previousFlipIdentity();
      
      boolean secondCardFound = false;

      // searching for an identical known face-down card
      for (int i = 0; i != g.n; i++)
        // identical known face-down card found
        if (knownArray[i] == firstFlip) {
          assert g.flip(i) : "Card at index " + i + " cannot be flipped";  // flipping second identical card; this will certainly result in a match
          // updating secondCardFound
          secondCardFound = true;
          // resetting index of second card in knownArray
          knownArray[i] = '*';
          // updating revealArray
          revealArray[firstFlipIndex] = true;
          revealArray[i] = true;
        }

      if (secondCardFound)
        continue;

      // second identical known card not found -> generate random valid move
      int secondFlipIndex;
      while (true) {
        // generates random flip between 0 (inclusive) and n (exclusive)
        secondFlipIndex = generator.nextInt(g.n);
        // break if card is face-down and unknown
        if (!revealArray[secondFlipIndex] && knownArray[secondFlipIndex] == '*' && secondFlipIndex != firstFlipIndex)
          break;
      }

      assert g.flip(secondFlipIndex) : "Flip at index " + secondFlipIndex + " failed.";
      char secondFlip = g.previousFlipIdentity();

      // updating revealArray if matching pair found
      if (g.wasMatch()){
        revealArray[firstFlipIndex] = true;
        revealArray[secondFlipIndex] = true;
      }
      // turning cards back to face down if matching pair not found, updating knownArray
      else{
        g.flipMismatch();
        knownArray[firstFlipIndex] = firstFlip;
        knownArray[secondFlipIndex] = secondFlip;
      }
    }
    // returning number of flips taken
    return g.getFlips();
  }

  // Monte Carlo simulations

  public static double randomMC(int N) {
    
    final int gameSize = 32;  // size of each game
    int totalFlips = 0; // total number of flips

    // running N games
    for (int i = 0; i != N; i++) {
      // creating game and shuffling cards
      MatchCardGame g = new MatchCardGame(gameSize);
      g.shuffleCards();
      // computing number of flips (returned by playRandom) and adding to totalFlips
      totalFlips += playRandom(g);
    }

    // computing and returning average number of flips
    return (double)(totalFlips) / N;
  }

  public static double goodMC(int N) {
    
    final int gameSize = 32;  // size of each game
    int totalFlips = 0; // total number of flips

    // running N games
    for (int i = 0; i != N; i++) {
      // creating game and shuffling cards
      MatchCardGame g = new MatchCardGame(gameSize);
      g.shuffleCards();
      // computing number of flips (returned by playGood) and adding to totalFlips
      totalFlips += playGood(g)
    }
    
    // computing and returning average number of flips
    return (double)(totalFlips) / N;
  }

}