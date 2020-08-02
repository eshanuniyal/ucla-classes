// yorps.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the utterly trivial
// functions (marked TRIVIAL).  Then get Arena::display going.  That gives
// you more flexibility in the order that you choose to tackle the rest of
// the functionality.  As you finish implementing each TODO: item, remove
// its TODO: comment; that makes it easier to find what you have left to do.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
#include <cassert>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;            // max number of rows in the arena
const int MAXCOLS = 20;            // max number of columns in the arena
const int MAXYORPS = 100;          // max number of yorps allowed
const int MAXCOLORS = 3;           // max number of colors
const double WALL_DENSITY = 0.14;  // density of walls

const int NORTH = 0;
const int EAST  = 1;
const int SOUTH = 2;
const int WEST  = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena;  // This is needed to let the compiler know that Arena is a
              // type name, since it's mentioned in the Yorp declaration.

class Yorp
{
  public:
      // Constructor
    Yorp(Arena* ap, int r, int c, char color);

      // Accessors
    int  row() const;
    int  col() const;
    char color() const;
    bool isDead() const;

      // Mutators
    void forceMove(int dir);
    void move();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    char   m_color;
	int    m_health;
};

class Player
{
  public:
      // Constructor
    Player(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    string stand();
    string move(int dir);
    void   setDead();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

class Arena
{
  public:
      // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();

      // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     yorpCount() const;
    bool    hasWallAt(int r, int c) const;
    int     numberOfYorpsAt(int r, int c) const;
    void    display(string msg) const;

      // Mutators
    void   placeWallAt(int r, int c);
    bool   addYorp(int r, int c, char color);
    bool   addPlayer(int r, int c);
    string moveYorps(char color, int dir);

  private:
    bool    m_wallGrid[MAXROWS][MAXCOLS];
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Yorp*   m_yorps[MAXYORPS];
    int     m_nYorps;

      // Helper functions
    void checkPos(int r, int c, string functionName) const;
};

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nYorps);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    string takePlayerTurn();
    string takeYorpsTurn();
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char ch);
int randInt(int lowest, int highest);
bool attemptMove(const Arena& a, int dir, int& r, int& c);
bool recommendMove(const Arena& a, int r, int c, int& bestDir);
void clearScreen();
bool valid_position(const Arena& a, int r, int c);
int adjacent_yorps(const Arena& a, int r, int c);

///////////////////////////////////////////////////////////////////////////
//  Yorp implementation
///////////////////////////////////////////////////////////////////////////

Yorp::Yorp(Arena* ap, int r, int c, char color)
{
    if (ap == nullptr)
    {
        cout << "***** A yorp must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Yorp created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    if (color != 'R'  &&  color != 'Y'  &&  color != 'B')
    {
        cout << "***** Yorp created with invalid color " << color << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_color = color;
	m_health = 3;
}

int Yorp::row() const
{
    return m_row;
}

int Yorp::col() const
{
    return m_col;
}

char Yorp::color() const
{
	return m_color;
}

bool Yorp::isDead() const
{
    return (m_health <= 0);
}

void Yorp::forceMove(int dir)
{
	// current row and column positions
	// attemptMove updates m_row, m_col automatically
	if (attemptMove(*m_arena, dir, m_row, m_col))
		return;
	// move not possible --> decrementing health
	else
		m_health--;
}

void Yorp::move()
{
      // Attempt to move in a random direction; if can't move, don't move
    if (!isDead())
        attemptMove(*m_arena, randInt(0, NUMDIRS-1), m_row, m_col);
}

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_dead = false;
}

int Player::row() const
{
	return m_row;
}

int Player::col() const
{      
    return m_col;
}

string Player::stand()
{
    return "Player stands.";
}

string Player::move(int dir)
{
	// move not possible
	if (!attemptMove(*m_arena, dir, m_row, m_col))
		return "Player couldn't move; player stands.";
	// move possible; m_row and m_col updated automatically in if statement by attemptMove
	else {

		// checking for yorp at new player position
		if (m_arena->numberOfYorpsAt(m_row, m_col) > 0) {
			setDead(); // setting m_dead to true
			return "Player walked into a yorp and died.";
		}

		// no yorps found at new position; returning appropriate text
		switch (dir) {
			case NORTH: return "Player moved north.";
			case SOUTH: return "Player moved south.";
			case EAST: return "Player moved east.";
			case WEST: return "Player moved west.";
			default: return "Invalid dir!"; // will never happen, dir is checked before passing into move()
					// just to get rid of Visual C++ warning about control paths
		}
	}
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementation
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nYorps = 0;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            m_wallGrid[r-1][c-1] = false;
}

Arena::~Arena()
{
	delete m_player; // deleting player

	// deleting yorps
	for (int i = 0; i != m_nYorps; i++)
		delete m_yorps[i];
}

int Arena::rows() const
{
    return m_rows;
}

int Arena::cols() const
{
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::yorpCount() const
{
	return m_nYorps;
}

bool Arena::hasWallAt(int r, int c) const
{
    checkPos(r, c, "Arena::hasWallAt");
    return m_wallGrid[r-1][c-1];
}

int Arena::numberOfYorpsAt(int r, int c) const
{
	int count = 0; // keeps track of number of yorps
	
	for (int i = 0; i != m_nYorps; i++)
		if (m_yorps[i]->row() == r && m_yorps[i]->col() == c) // coordinates of yorp match (r, c)
			count++; // incrementing count

    return count;
}

void Arena::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
    
      // Fill displayGrid with dots (empty) and stars (wall)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r-1][c-1] = (hasWallAt(r, c) ? '*' : '.');

      // Indicate yorp positions by their colors.  If more than one yorp
      // occupies a cell, show just one (any one will do).
	for (int i = 0; i != m_nYorps; i++) {
		Yorp* yorp = m_yorps[i];
		displayGrid[yorp->row() - 1][yorp->col() - 1] = yorp->color();
	}

      // Indicate player's position
    if (m_player != nullptr)
        displayGrid[m_player->row()-1][m_player->col()-1] = (m_player->isDead() ? 'X' : '@');

      // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;

      // Write message, yorp, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << yorpCount() << " yorps remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
}

void Arena::placeWallAt(int r, int c)
{
    checkPos(r, c, "Arena::placeWallAt");
    m_wallGrid[r-1][c-1] = true;
}

bool Arena::addYorp(int r, int c, char color)
{
    if (hasWallAt(r, c))
        return false;
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;
    if (color != 'R'  &&  color != 'Y'  &&  color != 'B')
        return false;
    if (m_nYorps == MAXYORPS)
        return false;
    m_yorps[m_nYorps] = new Yorp(this, r, c, color);
    m_nYorps++;
    return true;
}

bool Arena::addPlayer(int r, int c)
{
    if (m_player != nullptr  ||  hasWallAt(r, c))
        return false;
    if (numberOfYorpsAt(r, c) > 0)
        return false;
    m_player = new Player(this, r, c);
    return true;
}

string Arena::moveYorps(char color, int dir)
{
      // Yorps of the indicated color will follow that color with probability 1/2
    bool willFollow = (randInt(0, 1) == 0);

      // Move all yorps
    int nYorpsOriginally = m_nYorps;

	// running thorugh m_nYorps array
	for (int i = 0; i != m_nYorps; i++) {
		Yorp* yorp = m_yorps[i]; // pointer to a yorp
		
		// yorp has same color, and will follow
		if (willFollow && yorp->color() == color)
			yorp->forceMove(dir); // forcing move
		// yorp of different colour, or yorp of same colour won't follow
		else
			yorp->move();

		// releasing yorp if dead
		if (yorp->isDead()) {
			delete yorp; // deleting yorp object
			m_yorps[i] = m_yorps[m_nYorps - 1]; // moving last yorp pointer to replace the dangling pointer
			i--; // decrementing i so the yorp now at index i is also moved
			m_nYorps--; // updating number of yorps
		}
		// yorp didn't die; checking if player died
		else if (m_player->col() == yorp->col() && m_player->row() == yorp->row())
			m_player->setDead(); // marking player as dead
	}

    if (m_nYorps < nYorpsOriginally)
        return "Some yorps have been destroyed.";
    else
        return "No yorps were destroyed.";
}

void Arena::checkPos(int r, int c, string functionName) const
{
    if (r < 1  ||  r > m_rows  ||  c < 1  || c > m_cols)
    {
        cout << "***** " << "Invalid arena position (" << r << ","
             << c << ") in call to " << functionName << endl;
        exit(1);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nYorps)
{
    if (nYorps < 0  ||  nYorps > MAXYORPS)
    {
        cout << "***** Game created with invalid number of yorps:  "
             << nYorps << endl;
        exit(1);
    }
    int nEmpty = rows * cols - nYorps - 1;  // 1 for Player
    if (nEmpty < 0)
    {
        cout << "***** Game created with a " << rows << " by "
             << cols << " arena, which is too small too hold a player and "
             << nYorps << " yorps!" << endl;
        exit(1);
    }

      // Create arena
    m_arena = new Arena(rows, cols);

      // Add some walls in WALL_DENSITY of the empty spots
    assert(WALL_DENSITY >= 0  &&  WALL_DENSITY <= 1);
    int nWalls = static_cast<int>(WALL_DENSITY * nEmpty);
    while (nWalls > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (m_arena->hasWallAt(r, c))
            continue;
        m_arena->placeWallAt(r, c);
        nWalls--;
    }

      // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_arena->hasWallAt(rPlayer, cPlayer));
    m_arena->addPlayer(rPlayer, cPlayer);

      // Populate with yorps
    while (nYorps > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (m_arena->hasWallAt(r, c)  ||  (r == rPlayer && c == cPlayer))
            continue;
        const char colors[MAXCOLORS] = { 'R', 'Y', 'B' };
        m_arena->addYorp(r, c, colors[randInt(1, MAXCOLORS)-1]);
        nYorps--;
    }
}

Game::~Game()
{
    delete m_arena;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/x or nothing): ";
        string playerMove;
        getline(cin, playerMove);

        Player* player = m_arena->player();
        int dir;

        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_arena, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->stand();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'x')
                return player->stand();
            else
			{
			dir = decodeDirection(tolower(playerMove[0]));
			if (dir != -1)
						return player->move(dir);
			}
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/x." << endl;
    }
}

string Game::takeYorpsTurn()
{
    for (;;)
    {
        cout << "Color thrown and direction (e.g., Rn or bw): ";
        string colorAndDir;
        getline(cin, colorAndDir);
        if (colorAndDir.size() != 2)
        {
            cout << "You must specify a color followed by a direction." << endl;
            continue;
        }
        char color = toupper(colorAndDir[0]);
        if (color != 'R'  &&  color != 'Y'  &&  color != 'B')
        {
            cout << "Color must be upper or lower R, Y, or B." << endl;
            continue;
        }
        int dir = decodeDirection(tolower(colorAndDir[1]));
        if (dir != -1)
            return m_arena->moveYorps(color, dir);
        cout << "Direction must be n, e, s, or w." << endl;
    }
}

void Game::play()
{
    m_arena->display("");
    Player* player = m_arena->player();
    if (player == nullptr)
        return;
    while ( ! player->isDead()  &&  m_arena->yorpCount() > 0)
    {
        string msg = takePlayerTurn();
        m_arena->display(msg);
        if (player->isDead())
            break;
        msg = takeYorpsTurn();
        m_arena->display(msg);
    }
    if (player->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
      case 'n':  return NORTH;
      case 'e':  return EAST;
      case 's':  return SOUTH;
      case 'w':  return WEST;
    }
    return -1;  // bad argument passed in!
}

  // Return a random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

bool attemptMove(const Arena& a, int dir, int& r, int& c)
{
	// current row and column positions
	int current_r = r;
	int current_c = c;

	// updating coordinates depending on direction characters
	switch (dir) {
		case NORTH: current_r--;
			break;
		case SOUTH: current_r++;
			break;
		case EAST: current_c++;
			break;
		case WEST: current_c--;
			break;
	}

	// (current_r, current_c) coordinates are out of arena or have a wall
	if (current_r < 1 || current_c < 1 ||
		current_r > a.rows() || current_c > a.cols() ||
		a.hasWallAt(current_r, current_c))
		return false; // returning false

	// updating r and c
	r = current_r;
	c = current_c;
    return true; // returning true
}

  // Recommend a move for a player at (r,c):  A false return means the
  // recommendation is that the player should stand; otherwise, bestDir is
  // set to the recommended direction to move.
bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
	// number of yorps adjacent to north/south/east/west positions
	int adjacent_yorps_arr[4] = { -1, -1, -1, -1 };
	// array represents number of yorps adjacent to player if player moves north, east, south, west

	// north is valid position with no yorps --> player can move
	if (valid_position(a, r - 1, c) && a.numberOfYorpsAt(r - 1, c) == 0)
		adjacent_yorps_arr[NORTH] = adjacent_yorps(a, r - 1, c);
	// east is valid position with no yorps --> player can move
	if (valid_position(a, r, c + 1) && a.numberOfYorpsAt(r, c + 1) == 0)
		adjacent_yorps_arr[EAST] = adjacent_yorps(a, r, c + 1);
	// south is valid position with no yorps --> player can move
	if (valid_position(a, r + 1, c) && a.numberOfYorpsAt(r + 1, c) == 0)
		adjacent_yorps_arr[SOUTH] = adjacent_yorps(a, r + 1, c);
	// west is valid position with no yorps --> player can move
	if (valid_position(a, r, c - 1) && a.numberOfYorpsAt(r, c - 1) == 0)
		adjacent_yorps_arr[WEST] = adjacent_yorps(a, r, c - 1);

	int min_yorps = adjacent_yorps(a, r, c); // keeps track of the minimum yorps adjacent to position after best playing best move
		// default to number of yorps around current position
	int best_direction = -1; // keeps track of the best direction; -1 represents standing

	// going through through adjacent_yorps_arr
	for (int i = 0; i != 4; i++) {
		int current_yorps = adjacent_yorps_arr[i]; // the number of yorps adjacent to player if move in direction i is made
			// current_yorps equals -1 if a move in direction i is invalid (wall or out of grid) or unideal (yorps in direction i)

		// move in direction i is valid (not walking into yorps, wall, or out of grid) and current_yorps is the lowest yet encountered
		if (current_yorps != -1 && current_yorps < min_yorps) {
			min_yorps = current_yorps; // updating min_yorps
			best_direction = i; // updating best_direction
		}
	}

	if (best_direction == -1)
		return false; // best_direction not modified; the best move is to stand
	else
		bestDir = best_direction; // updating bestDir

    return true;
}

// function that returns whether a position is valid (i.e. in grid and not occupied by wall)
bool valid_position(const Arena& a, int r, int c) {
	return (r >= 1 && r <= a.rows() && c >= 1 && c <= a.cols() && !a.hasWallAt(r, c));
}

int adjacent_yorps(const Arena& a, int r, int c) {
	
	int n_yorps = 0; // total number of yorps adjacent to (r, c)
	
	// north is valid position
	if (valid_position(a, r - 1, c)) 
		n_yorps += a.numberOfYorpsAt(r - 1, c);
	// south is valid position
	if (valid_position(a, r + 1, c))
		n_yorps += a.numberOfYorpsAt(r + 1, c);
	// east is valid position
	if (valid_position(a, r, c + 1))
		n_yorps += a.numberOfYorpsAt(r, c + 1);
	// west is valid position
	if (valid_position(a, r, c - 1))
		n_yorps += a.numberOfYorpsAt(r, c - 1);

	return n_yorps;
}

///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////

int main()
{
      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 5, 2);
    Game g(10, 12, 50);

      // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif
