#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"          // to include Socrates class
#include <string>
#include <iostream>         // defines the overloads of the << operator
#include <sstream>          // defines std::ostringstream
#include <iomanip>          // defines the manipulator setw
using namespace std;

// ################################################################################################################
// AUXILIARY FUNCTION DEFINITIONS
// ################################################################################################################

double distance(double x1, double y1, double x2, double y2) { 
    // returns Euclidean distance between coordinates (x1, y1) and (x2, y2)
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)); 
}

double distanceFromCenter(double x, double y) { 
    // returns, given coordinates x and y, distance from the center
    return distance(x, y, VIEW_WIDTH / 2, VIEW_HEIGHT / 2); 
}

void getRandomCircumferenceCoords(double &x, double &y) {
    // find a pair of random coordinates on the circumference of the dish
    int randAngle = randInt(0, 359);    // finding a random angle
    x = VIEW_RADIUS * (1 + cos(randAngle * 1.0 / 360 * 2 * PI));            // modifying x coordinate: x = r(1 + cos theta)
    y = VIEW_RADIUS * (1 + sin(randAngle * 1.0 / 360 * 2 * PI));            // modifying y coordinate: y = r(1 + sin theta)
}

GameWorld* createStudentWorld(string assetPath) {
	return new StudentWorld(assetPath);
}

// ################################################################################################################
// STUDENTWORLD FUNCTION DEFINITIONS
// ################################################################################################################

// ################################################################################################################
// CONSTRUCTOR, INIT, MOVE, CLEANUP, AND DESTRUCTOR FUNCTION DEFINITIONS

StudentWorld::StudentWorld(string assetPath)
    : GameWorld(assetPath), m_socrates(nullptr), m_bacteriaLeft(0) {}

int StudentWorld::init() {

    // creating socrates
    m_socrates = new Socrates(this);

    int x, y;       // store valid coordinates for all objects

    // creating getLevel() pits
    for (int i = 0; i != getLevel(); i++) {
        findValidCoords(x, y);      // find valid coordinates
        m_actors.insert(new Pit(x, y, this));       // create new Pit
    }
    m_bacteriaLeft = getLevel() * TOTAL_INITIAL_BACTERIA;        
        // to track number of pits with bacteria in them

    // creating min(5 * getLevel(), 25) food objects
    for (int i = 0; i != min(5 * getLevel(), 25); i++) {
        findValidCoords(x, y);      // find valid coordinates
        m_actors.insert(new Food(x, y, this));      // create new Food object
    }

    // creating max(180 - 20 * getLevel(), 20) dirt piles
    set<DirtPile*> dirtpiles; // set to store created dirtpiles

    for (int i = 0; i != max(180 - 20 * getLevel(), 20); i++) {
        findValidCoords(x, y); // since new dirtpiles have not been added to m_actors, 
            // we're only checking for overlap with pits and food objects
        dirtpiles.insert(new DirtPile(x, y, this));
    }
    // inserting created dirtpiles into m_actors
    for (set<DirtPile*>::const_iterator it = dirtpiles.cbegin(); it != dirtpiles.cend(); it++)
        m_actors.insert(*it);

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() {

    // asking Socrates to do something
    m_socrates->doSomething();

    // asking all other actors to do something
    for (set<Actor*>::iterator it = m_actors.begin(); it != m_actors.end(); it++) {
        
        (*it)->doSomething();       // asking actor to do something
      
        // if Socrates died
        if (!m_socrates->actorAlive()) {
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
        // socrates has cleared dish of all bacteria (no bacteria left in pits either)
        if (getBacteriaLeft() == 0) {
            playSound(SOUND_FINISHED_LEVEL);
            return GWSTATUS_FINISHED_LEVEL;
        }
    }
    
    // removing dead actors
    removeDeadActors();

    // creating new goodies or fungi
    addNewGoodies();
    
    // setting game status text
    setGameStatText(getStatText());

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp() {

    // delete Socrates object; we test for socrates being nullptr to avoid multiple deletion
    if (m_socrates != nullptr) {
        delete m_socrates;
        m_socrates = nullptr;
    }

    // delete actors
    for (set<Actor*>::iterator it = m_actors.begin(); it != m_actors.end(); it++)
        delete (*it);
    m_actors.clear();       // clear actors set
}

StudentWorld::~StudentWorld() {
    cleanUp();
}

void StudentWorld::decBacteriaLeft() { m_bacteriaLeft--; }
    // decrement number of bacteria left, in pits or otherwise

int StudentWorld::getBacteriaLeft() const { return m_bacteriaLeft; }
    // get number of bacteria left, in pits or otherwise

// ################################################################################################################
// MODIFYING AND ACCESSING SOCRATES

// MUTATORS

void StudentWorld::restoreSocratesHitPoints() { 
    // restore socrates' hit points
    m_socrates->restoreHitPoints(); 
}

void StudentWorld::decreaseSocratesHitPoints(int decrement) { 
    // decrease socrates' hitpoints
    m_socrates->damageActor(decrement); 
}

void StudentWorld::increaseSocratesFlames(int increment) { 
    // increase socrates' flame charges
    m_socrates->increaseFlames(increment); 
}

// ACCESSORS

double StudentWorld::getSocratesX() const { 
    return m_socrates->getX(); 
}

double StudentWorld::getSocratesY() const { 
    return m_socrates->getY(); 
}

bool StudentWorld::movementValid(double x, double y) const {

    // checking if coordinates are inside dish
    if (distance(x, y, VIEW_WIDTH / 2, VIEW_HEIGHT / 2) >= VIEW_RADIUS)
        return false;

    // checking if some other actor (e.g. a dirt pile) blocks the movement
    for (set<Actor*>::const_iterator it = m_actors.cbegin(); it != m_actors.cend(); it++)
            // actor blocks movement and  distance between actor and (x, y) is less than SPRITE_WIDTH / 2
        if ((*it)->actorBlocksMovement() && distance(x, y, (*it)->getX(), (*it)->getY()) <= SPRITE_WIDTH / 2)
            return false;

    // (x, y) is a valid position to move to
    return true;
}

bool StudentWorld::findClosestFoodDir(double x, double y, Direction& dir) const {
    // if any food object is within VIEW_RADIUS pixels of specified (x, y), modify dir to the direction of that food object

    bool food_found = false;                        // to track whether a food object has been found within VIEW_RADIUS pixels of (x, y)

    Direction closestDir;                          // direction to closest food object
    double closestDist  = VIEW_RADIUS;             // distance to closest food object (initialised to maximum distance we're concerned with)

    // iterating over actors to find food objects 
    for (set<Actor*>::const_iterator it = m_actors.cbegin(); it != m_actors.cend(); it++) {
        
        // food object found
        if ((*it)->actorEatable()) {

            // distance to food object
            double foodDist = distance(x, y, (*it)->getX(), (*it)->getY());

            // if food object is closest found thus far
            if (foodDist <= closestDist) {
                closestDist = foodDist;
                closestDir = atan2((*it)->getY() - y, (*it)->getX() - x) * 360 / (2 * PI);
                    // closest direction = atan((y2 - y1) / (x2 - x1)) * 360/2PI
            }
        }
    }

    // updating dir if food found
    if (food_found)
        dir = closestDir;

    // returning food_found (true if food found, false otherwise)
    return food_found;

}

// ################################################################################################################
// MODIFYING EXISTING OBJECTS

bool StudentWorld::findAndDamage(double x, double y, int damage) {
    // iterating over actors in current play
    for (set<Actor*>::iterator it = m_actors.begin(); it != m_actors.end(); it++) {
        // found an alive, damageable actor SPRITE_WIDTH distance or closer
        if ((*it)->actorDamageable() && (*it)->actorAlive() && distance(x, y, (*it)->getX(), (*it)->getY()) <= SPRITE_WIDTH) {
            (*it)->damageActor(damage);
            return true;
        }
    }
    // didn't find any valid actor to damage
    return false;
}

bool StudentWorld::findAndEatOverlappingFood(double x, double y) {
    for (set<Actor*>::iterator it = m_actors.begin(); it != m_actors.end(); it++) {
        // found an alive, eatable actor (i.e. food) SPRITE_WIDTH distance or closer
        if ((*it)->actorEatable() && (*it)->actorAlive() && distance(x, y, (*it)->getX(), (*it)->getY()) <= SPRITE_WIDTH) {
            (*it)->setActorDead();
            return true;
        }
    }
    // didn't find any eatable actor
    return false;
}

// ################################################################################################################
// CREATING NEW OBJECTS

void StudentWorld::createFood(double x, double y) {
    m_actors.insert(new Food(x, y, this));
}

// ################################################################################################################
// STUDENTWORLD AUXILIARY FUNCTION DEFINITIONS
// ################################################################################################################

void StudentWorld::findValidCoords(int &x, int &y) const {

    // iterating until we find a valid object coordinate
    while (true) {
        x = 0; y = 0;
        bool valid_coordinate = true;

        // finding a coordinate within no more than 120 pixels from the center
        while (distanceFromCenter(x, y) > MAX_OBJ_DISTANCE) {
            x = randInt(0, VIEW_WIDTH - 1);
            y = randInt(0, VIEW_HEIGHT - 1);
        }

        // checking whether new object would overlap with any (non-DirtPile) objects already created
        for (set<Actor*>::const_iterator it = m_actors.cbegin(); it != m_actors.cend(); it++)
            if (distance(x, y, (*it)->getX(), (*it)->getY()) <= SPRITE_WIDTH) {
                valid_coordinate = false;
                break;
            }

        // valid coordinate found
        if (valid_coordinate)
            return;
    }
}

void StudentWorld::removeDeadActors() {
    // auxiliary function for move(); removes and deletes all dead actors

    // iterating over m_actors to find and delete dead actors
    for (set<Actor*>::iterator it = m_actors.begin(); it != m_actors.end();)

        // actor is dead
        if (!(*it)->actorAlive()) {
            delete (*it);                   // delete actor
            it = m_actors.erase(it);        // remove actor from m_actors, increment it
        }
        else it++;          // actor is alive
}

void StudentWorld::addNewGoodies() {
    // auxiliary function for move(); adds goodies and fungi as appropriate

    // simulates the chance of a fungus being created
    int chanceFungus = max(510 - getLevel() * 10, 200);
    int createFungus = randInt(0, chanceFungus - 1);

    // create fungus if createFungus == 0
    if (createFungus == 0) {
        
        // generate coordinates for fungus
        double x, y;
        getRandomCircumferenceCoords(x, y);

        // create fungus
        m_actors.insert(new Fungus(x, y, this));
    }

    int chanceGoodie = max(510 - getLevel() * 10, 250);
    int createGoodie = randInt(0, chanceGoodie - 1);

    if (createGoodie == 0) {

        // generate coordinates for goodie
        double x, y;
        getRandomCircumferenceCoords(x, y);

        // determine type of goodie
        int goodie_type = randInt(1, 10);
        // 60% chance goodie is a Restore Health goodie
        if (goodie_type <= 6)
            m_actors.insert(new RestoreHealthGoodie(x, y, this));
        // 30% chance goodie is a Flamethrower Charge goodie
        else if (goodie_type <= 9)
            m_actors.insert(new FlamethrowerGoodie(x, y, this));
        // 10% chance goodie is an extra life goodie
        else
            m_actors.insert(new ExtraLifeGoodie(x, y, this));
    }
}

string StudentWorld::getStatText() const {
       // returns the text of the status line; auxiliary function for move()
    ostringstream statText;
    
    // display score
    statText.fill('0');
    statText << "Score: " << setw(6) << getScore();
    statText << "  ";

    // display level
    statText << "Level: " << getLevel();
    statText << "  ";
    
    // display lives
    statText << "Lives: " << getLives();
    statText << "  "; 
    
    // display health
    statText << "Health: " << m_socrates->getHitPoints();
    statText << "  ";
    
    // display spray charges
    statText << "Sprays: " << m_socrates->getSprays();
    statText << "  ";
    
    // display flamethrower charges
    statText << "Flames: " << m_socrates->getFlames();
    
    return statText.str();  // return status line text
}