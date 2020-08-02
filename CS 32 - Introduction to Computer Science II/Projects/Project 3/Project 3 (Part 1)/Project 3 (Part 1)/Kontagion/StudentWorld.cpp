#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"          // to include Socrates class
#include <string>
using namespace std;

// ################################################################################################################
// AUXILIARY FUNCTION DEFINITIONS
// ################################################################################################################

double Distance(double x1, double y1, double x2, double y2) { 
    // returns Euclidean distance between coordinates (x1, y1) and (x2, y2)
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)); 
}

double DistanceFromCenter(double x, double y) { 
    // returns, given coordinates x and y, distance from the center
    return Distance(x, y, VIEW_WIDTH / 2, VIEW_HEIGHT / 2); 
}

// ################################################################################################################
// AUXILIARY FUNCTION DECLARATIONS
// ################################################################################################################


GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)   
    : GameWorld(assetPath), m_socrates(nullptr) {
    
}

int StudentWorld::init() {

    // creating Socrates
    m_socrates = new Socrates(this);

    // creating dirt piles
    for (int i = 0; i != max(180 - 20 * getLevel(), 20); i++) {
        int x = 0, y = 0;
        while (DistanceFromCenter(x, y) > MAX_DIRT_DISTANCE) {
                // dirt piles must be no more than 120 pixels from the center
            x = randInt(0, VIEW_WIDTH - 1);
            y = randInt(0, VIEW_HEIGHT - 1);
        }
        m_actors.insert(new DirtPile(x, y, this));
            // adding DirtPile to actors set
    }

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() {
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    decLives();

    // asking Socrates to do something
    m_socrates->doSomething();

    // asking all other actors to do something
    for (set<Actor*>::iterator ip = m_actors.begin(); ip != m_actors.end(); ip++)
        (*ip)->doSomething();

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp() {

    // delete Socrates object; we test for socrates being nullptr to avoid multiple deletion
    if (m_socrates != nullptr) {
        delete m_socrates;
        m_socrates = nullptr;
    }

    // delete actors
    for (set<Actor*>::iterator ip = m_actors.begin(); ip != m_actors.end(); ip++)
        delete (*ip);
    
    m_actors.clear();       // clear actors set
}

StudentWorld::~StudentWorld() {
    cleanUp();
}