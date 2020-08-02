package hw2;

import java.util.Random;

public class MatchCardGame {

  private class Card {

    private char cardChar;      // character representing the card
    private boolean isRevealed; // boolean representing whether or not the card has been revealed

    // initialiser block
    {
      isRevealed = false;
    }

    // constructor
    private Card(char cardChar) {
      this.cardChar = cardChar;
    }
  }
  
  // public fields
  public final int n; // size of game
  // private fields
  private Card[] cardArray; // array to store all cards in game
  private int[] flippedIndices; // array to store indices of cards flipped in current turn (max 2); the second (and last) index will always represent the previously flipped card 
  private int nFlips; // number of times player has flipped in game (proxy for score)

  // initialiser block
  {
    // initialising flippedIndices
    flippedIndices = new int[] {-1, -1};

    // initialising nFlips
    nFlips = 0;
  }
  
  // constructor; we may assume n is a multiple of 4, and that 4 <= n <= 4 * 26
  public MatchCardGame(int n) {
    // without shuffling, cards 0, 1, 2, and 3 should be 'a', cards 4, 5 , 6, and 7 should be 'b', and so on

    // storing number of cards in game
    this.n = n;

    // initialising cardArray
    cardArray = new Card[n];
    
      // outer loop runs as many times as there are letters in game
    for (int i = 0; i != n / 4; i++)
        // inner loop runs four times for each letter
      for (int j = 0; j != 4; j++) {  
        char cardChar = (char) ((int)'a' + i);
        cardArray[4*i + j] = new Card(cardChar);
      }
  }

  public void shuffleCards() {
    // scrambles the card array with the Fisher-Yates shuffle

    // creating a PRNG with current time as a seed
    long seed = System.currentTimeMillis();
    Random generator = new Random(seed);

    // iterating to perform Fisher-Yates shuffle
    for (int i = n - 1; i != 0; i--) {
      
      // card at current index
      Card currentCard = cardArray[i];
      
      // random index 0 <= j <= i
      int j = generator.nextInt(i + 1);
      
      // swapping cards
      cardArray[i] = cardArray[j];
      cardArray[j] = currentCard;
    }

  }

  public String boardToString() {
    // converts the state of the board to an appropriate String representation

    // string to store board state
    String boardString = "";

    // iterating over cards to generate boardString
    for (int i = 0; i != n / 4; i++) {
      for (int j = 0; j != 4; j++){

        // index of the card we're currently looking at
        int cardIndex = 4*i + j;

        // if card has been revealed already, push the card to boardString
        if (cardArray[cardIndex].isRevealed)
          boardString += cardArray[cardIndex].cardChar + " ";
        // if card hasn't been revealed, push * to boardString
        else
          boardString += "* ";
      }
      if (i != (n / 4) - 1)
        boardString += '\n';
    }
    
    return boardString;
  }

  public boolean flip(int i) {
    // plays card number i. 
    // If card i cannot be played because it’s face-up, or if i is an invalid card number, then return false. 
    if (i < 0 || i >= n || cardArray[i].isRevealed || flippedIndices[1] == i)
      return false;

    // i can be played -> play card i and return true
    
    // revealing card  
    cardArray[i].isRevealed = true;
    nFlips++;

    // storing card index to revert flip in case of mismatch
    flippedIndices[0] = flippedIndices[1];  // moving previously flipped card index to first position
    flippedIndices[1] = i;  // inserting currently flipped card index in second position
    return true;
  }

  public boolean wasMatch() {
    // returns true if the previous pair was a match and returns false otherwise. 
    // This method should be called only after flip() has been successfully called an even number of times and before flipMismatch() is called.
    if (cardArray[flippedIndices[1]].cardChar == cardArray[flippedIndices[0]].cardChar)
      return true;
    else
      return false;
  }

  public char previousFlipIdentity() {
    // returns the face of the previously flipped card as a char.
    // This method should only be called after a card has been flipped
    return cardArray[flippedIndices[1]].cardChar;
  }

  public void flipMismatch() {
    // reverts the a mismatched pair to face-down position. 
    // This method should only be called after a 2 calls of flip results in a mismatch.

    // reverting flipped cards (indices in flippedIndices) to face-down position
    cardArray[flippedIndices[0]].isRevealed = false;
    cardArray[flippedIndices[1]].isRevealed = false;

    // resetting flippedIndices
    flippedIndices[0] = -1;
    flippedIndices[1] = -1;
  }

  public boolean gameOver() {
    // returns true if all cards have been matched and the game is over and returns false otherwise

    // boolean to represent whether all cards have been flipped
    boolean allCardsFlipped = true;

    // searching for face-down cards
    for (int i = 0; i != n; i++)
      if (cardArray[i].isRevealed == false)
        allCardsFlipped = false;

    return allCardsFlipped;
    }

  public int getFlips() {
    // returns the total number of card flips that have been performed so far
    return nFlips;
  }
  
}