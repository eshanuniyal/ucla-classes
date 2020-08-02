#include <queue> // defines queue object
#include <string> // defines string object
#include <iostream> // defines cout
#include <cassert> // for testing with the assert function

using namespace std;

class Coord {
    // cannot change
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    // Return true if there is a path from (sr,sc) to (er,ec)
    // through the maze; return false otherwise

    queue<Coord> coordQueue; // declare a stack of Coords
    coordQueue.push(Coord(sr, sc)); // push starting coordinate onto coordStack
    maze[sr][sc] = 'P'; // updating current location to 'P' for path

    // iterating while stack is not empty
    while (coordQueue.size() != 0) {
        Coord c_loc = coordQueue.front(); // (r, c) location we're currently examining
        coordQueue.pop(); // remove current coordinate from stack
        cerr << "(" << c_loc.r() << ", " << c_loc.c() << ")" << endl;
        // current row and column coordinates
        int cr = c_loc.r();
        int cc = c_loc.c();

        // we've reached the end coordinate
        if (cr == er && cc == ec)
            return true;

        // we can move east and haven't encountered the cell yet
        if (cr + 1 < nCols && maze[cr][cc + 1] == '.') {
            coordQueue.push(Coord(cr, cc + 1));
            maze[cr][cc + 1] = 'P';
        }
        // we can move south and haven't encountered the cell yet
        if (cr + 1 < nRows && maze[cr + 1][cc] == '.') {
            coordQueue.push(Coord(cr + 1, cc));
            maze[cr + 1][cc] = 'P';
        }
        // we can move west and haven't encountered the cell yet
        if (cc - 1 >= 0 && maze[cr][cc - 1] == '.') {
            coordQueue.push(Coord(cr, cc - 1));
            maze[cr][cc - 1] = 'P';
        }
        // we can move north and haven't encountered the cell yet
        if (cr - 1 >= 0 && maze[cr - 1][cc] == '.') {
            coordQueue.push(Coord(cr - 1, cc));
            maze[cr - 1][cc] = 'P';
        }
    }

    // no solution, return false
    return false;
}

int main() {

    string maze[10] = {
                "XXXXXXXXXX",
                "X...X..X.X",
                "X.XXX....X",
                "X.X.XXXX.X",
                "XXX......X",
                "X...X.XX.X",
                "X.X.X..X.X",
                "X.XXXX.X.X",
                "X..X...X.X",
                "XXXXXXXXXX"
    };

    if (pathExists(maze, 10, 10, 4, 3, 1, 8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;

    // testing whether all paths in a basic empty grid are detected
    for (int sr = 1; sr < 6; sr++)
        for (int sc = 1; sc < 6; sc++)
            for (int er = 1; er < 6; er++)
                for (int ec = 1; ec < 6; ec++) {
                    string test[7] = {
                        "XXXXXXX",
                        "X.....X",
                        "X.....X",
                        "X.....X",
                        "X.....X",
                        "X.....X",
                        "XXXXXXX",
                    };
                    assert(pathExists(test, 7, 7, sr, sc, er, ec));
                }
    cout << "All tests passed!" << endl;
}