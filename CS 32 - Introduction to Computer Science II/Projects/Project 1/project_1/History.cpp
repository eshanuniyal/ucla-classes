#include "History.h"
#include "Arena.h"
#include "globals.h"

#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////
//  History implementation
///////////////////////////////////////////////////////////////////////////

History::History(int nRows, int nCols) {
    // may assume 1 <= nRows <= MAXROWS, and 1 <= nCols <= MAXCOLS

    m_rows = nRows;
    m_cols = nCols;

    // initialising each position in history grid (m_grid) to be 0 (zero poisoned vampires at beginning of game)
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            m_grid[r - 1][c - 1] = 0;
}

bool History::record(int r, int c) {
    // to be called to notify the History object that a vampire has started its turn poisoned but alive at a grid point
    //  function returns false if row r, column c is not within bounds; otherwise, it returns true after recording what it needs to
    if (r < 1 || r >= MAXROWS || c < 1 || c >= MAXCOLS)
        // out-of-bounds parameters
        return false;
    
    m_grid[r - 1][c - 1]++;
        // incrementing count of vampires at that grid position that have been poisoned
    return true;
}

void History::display() const {
    // clears the screen and displays the history grid as the posted programs do
    // function does clear the screen, display the history grid, and write an empty line after the history grid; 
        // it does not print the "Press enter to continue." after the display. 
    
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;

    // Fill displayGrid with dots (empty) and stars (poisoned blood vials)
    for (r = 1; r <= m_rows; r++)
        for (c = 1; c <= m_cols; c++) {
            int n_vampires = m_grid[r - 1][c - 1];
                // number of poisoned vampires at position
            char gridChar;
                // contains the character to be placed in grid position
            int A_ascii = int('A');
                // ascii value of A character
            
            // determining grid character value based on number of poisoned vampires at that grid position
            if (n_vampires == 0)
                gridChar = '.';
            else if (n_vampires > 0 && n_vampires <= 25)
                gridChar = A_ascii + n_vampires - 1;
            else if (n_vampires > 25)
                gridChar = 'Z';

            displayGrid[r - 1][c - 1] = gridChar;
        }
   
    // Draw the grid
    clearScreen();
    for (r = 1; r <= m_rows; r++)
    {
        for (c = 1; c <= m_cols; c++)
            cout << displayGrid[r - 1][c - 1];
        cout << endl;
    }
    cout << endl;
}