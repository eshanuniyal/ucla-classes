package hw4;

import java.util.Random;

public class RandomAI implements CFPlayer {

    // creating random number generator
    private final Random rand = new Random();

    @Override
    public String getName() {
        return "Random Player";
    }

    @Override
    public int nextMove(CFGame g) {
        // returns, but does not itself play, a random legal column.

        int[][] s = g.getState();
        // iterating till a random column is found
        while (true) {
            // generating random column number
            int randColumn = rand.nextInt(7);
            // checking whether chosen column can be legally played
            if (g.getState()[randColumn][0] == 0) {
                //System.out.print(randColumn + '\n');
                return randColumn + 1;  // return column with 1-based indexing
            }
        }
    }
}
