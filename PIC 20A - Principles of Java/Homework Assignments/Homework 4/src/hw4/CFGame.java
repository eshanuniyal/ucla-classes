package hw4;

// for winner() function
import java.util.Set;
import java.util.HashSet;

public class CFGame {
    //state[i][j]= 0 means the i,j slot is empty
    //state[i][j]= 1 means the i,j slot has red
    //state[i][j]=-1 means the i,j slot has black
    private final int[][] state;
    private boolean isRedTurn;

    {
        state = new int[7][6];  // columns by rows
        for (int i=0; i<7; i++)
            for (int j=0; j<6; j++)
                state[i][j] = 0;
        isRedTurn = true; // red goes first
    }

    public int[][] getState() {
        int[][] ret_arr = new int[7][6];
        for (int i=0; i<7; i++)
            for (int j=0; j<6; j++)
                ret_arr[i][j] = state[i][j];
        return ret_arr;
    }

    public boolean isRedTurn() {
        return isRedTurn;
    }

    public boolean play(int column) {
        // plays the column c. If column c cannot be played because it is full or because it is an invalid
        // column, return false. Otherwise, return true. The columns are counted with 1-based indexing,
        // i.e., the columns range from 1 to 7

        // column out of bounds -> return false
        if (column < 1 || column > 7)
            return false;

        // actual column index (0-based indexing)
        int colIndex = column - 1;

        // iterating over cells in column (starting from bottom row, which has index 5)
        for (int j = 5; j >= 0; j--) {
            // checking for whether j'th cell is available
            if (getState()[colIndex][j] == 0) {
                // red turn -> cell should have 1
                if (isRedTurn())
                    state[colIndex][j] = 1;
                // black turn -> cell should have -1
                else state[colIndex][j] = -1;
                // changing turn
                isRedTurn = !isRedTurn;
                return true;
            }
        }
        // no empty cells found -> column not empty
        return false;
    }

    public boolean isGameOver() {
        // returns true if the game is over because there is a winner or because there are no more possible
        // moves and returns false otherwise.

        // checking if there are no more possible moves
        boolean emptyCell = false;
        // iterating over columns
        for (int i = 0; i != 7; i++)
            // we only need to check the top row of each column to see whether the column is full
            // if column isn't full, set emptyCell to true and break
            if (getState()[i][0] == 0) {
                emptyCell = true;
                break;
            }

        // if board is full (i.e. no more possible moves) return false
        if (!emptyCell)
            return true;

        // checking for winner; if winner() returns -1 or 1 (indicating someone did win the game), return true
        if (winner() != 0)
            return true;

        // board is not full and there is no winner -> return false
        return false;
    }

    public int winner() {
        // returns 1 if red is the winner, -1 if black is the winner, and 0 if the game is a draw.
        // This method should be called when isGameOver returns true
        // In my implementation of CFGame, this function is also used as an auxiliary function for isGameOver()
        // (to avoid code redundancy), so this implementation of winner() doesn't rely on the game actually being over.

        int[][] constState = getState();

        // checking columns for winner
        for (int i = 0; i != 7; i++) {
            int win = checkListForWin(constState[i]);
            // if someone won in current column, return win
            if (win != 0)
                return win;
        }

        // checking rows for winner
        for (int j = 0; j != 6; j++){
            // creating row array from state
            int[] row = new int[7];
            for (int i = 0; i != 7; i++){
                row[i] = constState[i][j];
            }
            // checking for winner
            int win = checkListForWin(row);
            // if someone one in current row, return win
            if (win != 0)
                return win;
        }

        // checking diagonals for winner
        // generating and checking diagonals from top-left corner, top row
        for (int i = 0; i != 4; i++) {
            // creating diagonal array (can have maximum six elements)
            int[] diagonal = new int[] {0, 0, 0, 0, 0, 0};
            int n = 0;
            // in each iteration, we get element one column to the right, one row down
            while (i + n < 6) {
                diagonal[n] = constState[i+n][n];
                n++;
            }
            // checking diagonal array
            int win = checkListForWin(diagonal);
            if (win != 0)
                return win;
        }
        // generating and checking diagonals from top-left corner, first column
            // there are only two diagonals in this case, since we've already considered the diagonal
            // from the absolute top left corner
        for (int j = 1; j != 3; j++) {
            // creating diagonal array (can have maximum six elements)
            int[] diagonal = new int[] {0, 0, 0, 0, 0};
            int n = 0;
            // in each iteration, we get element one column to the right, one row down
            while (j + n < 6) {
                diagonal[n] = constState[n][j+n];
                n++;
            }
            // checking diagonal array
            int win = checkListForWin(diagonal);
            if (win != 0)
                return win;
        }
        // generating and checking diagonals from top-right corner, top row
        for (int i = 6; i != 2; i--) {
            // creating diagonal array (can have maximum six elements)
            int[] diagonal = new int[] {0, 0, 0, 0, 0, 0};
            int n = 0;
            // in each iteration, we get element one column to the left, one row down
            while (i - n > 0) {
                diagonal[n] = constState[i-n][n];
                n++;
            }
            // checking diagonal array
            int win = checkListForWin(diagonal);
            if (win != 0)
                return win;
        }
        // generating and checking diagonals from top-right corner, last column
        // there are only two diagonals in this case, since we've already considered the diagonal
        // from the absolute top right corner
        for (int j = 1; j != 3; j++) {
            // creating diagonal array (can have maximum six elements)
            int[] diagonal = new int[] {0, 0, 0, 0, 0};
            int n = 0;
            // in each iteration, we get element one column to the left, one row down
            while (j + n < 6) {
                diagonal[n] = constState[6-n][j+n];
                n++;
            }
            // checking diagonal array
            int win = checkListForWin(diagonal);
            if (win != 0)
                return win;
        }

        // could not find a winner -> return draw
        return 0;
    }

    private int checkListForWin(int[] list) {
        // given a list of integers, checks for whether there are four consecutive red/black disks (i.e. a win)
        // returns 0 if no one wins in given list, 1 if red wins, -1 if black wins

        // if list has k elements, iterating over first k - 3 elements
        for (int i = 0; i <= list.length - 4; i++) {
            // creating set of all states in the four cells starting from the current cell
            Set<Integer> vals = new HashSet<>();
            for (int n = 0; n != 4; n++)
                vals.add(list[i + n]);

            // checking whether we have a solution
            if (vals.size() != 1)
                continue;   // we have more than one kind of entry -> no solution
            // only one kind of entry -> check if cells are in fact empty
            if (vals.contains(0))
                continue;   // cells are empty
                // cells are non-empty and unique -> we have a winner
            else return vals.contains(1) ? 1 : -1;
            // return 1 if cells are all 1 (red); -1 (black) otherwise
        }
        // no one wins in given list
        return 0;
    }
}
