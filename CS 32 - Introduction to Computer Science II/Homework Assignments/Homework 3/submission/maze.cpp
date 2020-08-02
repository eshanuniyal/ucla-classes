class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    // start location equals end location
    if (sr == er && sc == ec)
        return true;

    maze[sr][sc] = 'V'; // marking current location as visited
    
    // we can move east and haven't visited the cell yet
    if (sc + 1 < nCols && maze[sr][sc + 1] == '.')
        if (pathExists(maze, nRows, nCols, sr, sc + 1, er, ec))
            return true;

    // we can move south and haven't visited the cell yet
    if (sr + 1 < nRows && maze[sr + 1][sc] == '.')
        if (pathExists(maze, nRows, nCols, sr + 1, sc, er, ec))
            return true;

    // we can move west and haven't visited the cell yet
    if (sc - 1 >= 0 && maze[sr][sc - 1] == '.')
        if (pathExists(maze, nRows, nCols, sr, sc - 1, er, ec))
            return true;
    
    // we can move north and haven't visited the cell yet
    if (sr - 1 >= 0 && maze[sr - 1][sc] == '.') {
        if (pathExists(maze, nRows, nCols, sr - 1, sc, er, ec))
            return true;
    }

    return false;

}