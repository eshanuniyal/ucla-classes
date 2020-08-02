package hw4;

import java.util.Random;
import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class GUICF extends CFGame {

    // fields
    private GameBoard this_board = new GameBoard();
    private CFPlayer redPlayer;
    private CFPlayer blackPlayer;

    // constructors
    public GUICF(CFPlayer ai) {
        // sets up and starts a human vs. AI game, where the red player (the player who goes first) is randomly decided

        // picking red player randomly (null indicates Human Player)
        Random rand = new Random();
        if (rand.nextInt(2) == 0) {
            redPlayer = ai;
            blackPlayer = null;
        }
        else {
            redPlayer = null;
            blackPlayer = ai;
        }

    }
    public GUICF(CFPlayer ai1, CFPlayer ai2) {
        // sets up and starts a AI vs. AI game, where the red player (the player who goes first) is randomly decided
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

    // methods
    private boolean playGUI(int c) {
        // plays the column c. So the internal game logic inherited from CFGame and the displayed board
        // represented in this_board must be updated. If c is a column that can be played, play the column
        // and return true. Otherwise return false and do not update the state of the game.

        // if column can be played, update the gameboard and return true
        if (play(c)) {
            int x = c;  // x coordinate of block to be painted
            // determining y-coordinate (row number)
        }
        return true;
    }

    private class GameBoard extends javax.swing.JPanel {

        ArrayList<JLabel> gridSquares = new ArrayList<>();
            // for JLabel at (i, j) on the board, it's stored at index (7*(j-1) + (i - 1)) in gridSquares

        private GameBoard() {
            // initialize empty board

            // setting layout for the board
            this.setLayout(new GridLayout(6, 7));
            // inserting labels (as squares)
            for (int i = 0; i != 6 * 7; i++) {
                JLabel newLabel = new JLabel();
                // setting border for each label
                newLabel.setBorder(BorderFactory.createLineBorder(Color.BLACK));
                // inserting label into the board
                this.add(newLabel);
                // inserting label into gridSquares
                gridSquares.add(newLabel);
            }
        }
        private void paint(int x, int y, int color) {
            // paints specified coordinate red or black
            // uses 1-based indexing, with the top-left coordinate being (1,1)
            // computing label index in gridSquares based on given coordinates
            int labelIndex = 7*(y-1) + (x - 1);
            // colouring label as appropriate
            if (color == 1)
                gridSquares.get(labelIndex).setBackground(Color.RED);
            else if (color == -1)
                gridSquares.get(labelIndex).setBackground(Color.BLACK);
        }
    }
}
