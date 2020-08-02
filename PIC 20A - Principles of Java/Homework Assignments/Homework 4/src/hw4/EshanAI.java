package hw4;

import java.util.ArrayList;

public class EshanAI implements CFPlayer {

    @Override
    public String getName() {
        return "Eshan's AI";
    }

    @Override
    public int nextMove(CFGame g) {
        // returns, but does not itself play, a legal column that your AI wants to play.
        // Your AI must be good enough to beat RandomAI 80% of the time

        // determining the number that represents our player
        int playerInt;
        if (g.isRedTurn())
            playerInt = 1;
        else
            playerInt = -1;

        // storing state for future reference
        int[][] state = g.getState();

        int winningMove = -1;  // winning move to make (-1 indicates there isn't one)
        int winBlockingMove = -1;   // win-blocking move to make (-1 indicates there isn't one)
        // searching for winning move (or win-blocking move)
        // checking columns for winning move (or win-blocking move)
        for (int i = 0; i != 7; i++) {
            // creating ArrayList to represent column
            ArrayList<Integer> column = new ArrayList<>();
            for (int j = 0; j != 6; j++)
                column.add(state[i][j]);

            // column full -> continue
            if (column.get(0) != 0)
                continue;
            // column not full
            int start = 0;
            while (column.get(start + 4) != 0)
                start++;
            // CONTINUE WRITING CODE HERE
        }


        return 0;
    }
}
