package hw4;

import java.util.Random;
import java.util.Scanner;

public class ConsoleCF extends CFGame {

    // private fields
    private CFPlayer redPlayer;
    private CFPlayer blackPlayer;

    public ConsoleCF(CFPlayer ai) {
        // sets up a human vs. AI game, where the red player (the player who goes first) is randomly decided
    }

    public ConsoleCF(CFPlayer ai1, CFPlayer ai2) {
        // sets up a AI vs. AI game, where the red player (the player who goes first) is randomly decided

        // assigning players randomly
        Random rand = new Random();
        if (rand.nextInt(2) == 0) {
            redPlayer = ai1;
            blackPlayer = ai2;
        }
        else {
            redPlayer = ai2;
            blackPlayer = ai1;
        }
    }

    public void playOut() {
        // plays the game until the game is over

        // iterate until game finishes
        while (!isGameOver()) {
            // variable to store the column to make a move in
            int moveCol;
            // current player picks a column to move
            if (isRedTurn())
                moveCol = redPlayer.nextMove(this);
            else
                moveCol = blackPlayer.nextMove(this);
            // make play in the chosen column
            play(moveCol);
        }
    }

    public String getWinner() {
        // return either "draw", "Human Player", or the AI’s name given by CFPlayer’s getName method
        int winner = winner();
        if (winner == 0)
            return "draw";
        else return (winner == 1) ? redPlayer.getName() : blackPlayer.getName();
    }

    private class HumanPlayer implements CFPlayer {

        @Override
        public String getName() {
            return "Human Player";
        }

        @Override
        public int nextMove(CFGame g) {
            // prints the state of the board to the command line and ask the user for the next move.
            // If the provided move is invalid, says so and ask again for a valid move

            // printing board state
            int[][] state = g.getState();
            // printing column names
            System.out.println("1 2 3 4 5 6 7 ");
            // iterating over columns to print game board
            for (int i = 0; i != 7; i++) {
                // iterating over rows
                for (int j = 0; j != 6; j++) {
                    // print R (for red) if 1 in current position
                    if (state[i][j] == 1)
                        System.out.print("R ");
                    // print B (for black) if -1 in current position
                    else if (state[i][j] == -1)
                        System.out.print("B ");
                    // print . for an empty space
                    else
                        System.out.print(". ");
                }
                // ending line
                System.out.println();
            }

            // taking user input
            // creating scanner
            Scanner reader = new Scanner(System.in);
            // iterating till we get valid user input
            System.out.print("Please enter a valid column number to play in: ");
            while (true) {
                // asking for input
                int n = reader.nextInt();
                // checking if input is in-bounds
                if (n < 1 || n > 7) {
                    System.out.println("Column number out of bounds; please try again.");
                    continue;
                }
                // checking if input gives a legal move
                if (state[n-1][0] != 0) {
                    System.out.println("Column is already full; please try again");
                    continue;
                }
                // input is in-bounds and gives a legal move -> return input
                return n;
            }

        }
    }
}
