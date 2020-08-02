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
      while(g1.flip(reader.nextInt())) {}
      
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

              g.flip(i);
              g.flip(j);
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
      g.flip(firstFlipIndex);
      char firstFlip = g.previousFlipIdentity();
      
      boolean secondCardFound = false;

      // searching for an identical known face-down card
      for (int i = 0; i != g.n; i++)
        // identical known face-down card found
        if (knownArray[i] == firstFlip) {
          g.flip(i);  // flipping second identical card; this will certainly result in a match
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

      g.flip(secondFlipIndex);
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
      totalFlips += playGood(g);
    }
    
    // computing and returning average number of flips
    return (double)(totalFlips) / N;
  }

}