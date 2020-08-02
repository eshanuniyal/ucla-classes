#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <set>			// to create a set of pointers to Actors

using Direction = int; // to allow for use of Direction in parameters of functions such as createProjectile

class Socrates; // to allow creation of private data member socrates, which points to a Socrates object
class Actor;    // to allow declaration of private data member m_actors

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
    public:
        StudentWorld(std::string assetPath);        // constructor
        ~StudentWorld();                            // destructor

        // mutators
        virtual int init();
        virtual int move();
        virtual void cleanUp();                 
        
        // STUDENTWORLD MUTATORS AND ACCESSORS
        int getBacteriaLeft() const;                // return number of bacteria left in game, in pits or otherwise
        void decBacteriaLeft();                     // decrement number of bacteria left in game
        void incBacteriaLeft();                     // increment number of bacteria left in game

        // CREATING NEW OBJECTS
        void createFood(double x, double y);                        // create food object
        template<typename T>
        void createProjectile(double x, double y, Direction dir);   // create projectile of type T (flame or spray)
        template<typename T>
        void createBacterium(double x, double y);                   // create bacterium of type T

        // MODIFYING / ACCESSING SOCRATES
        // mutators
        void restoreSocratesHitPoints();                            // restore Socrates' hit points to full
        void decreaseSocratesHitPoints(int decrement);              // decrease Socrates' hit points by decrement
        void increaseSocratesFlames(int increment);                 // increase Socrates Flames by increment
        // accessors
        double getSocratesX() const;                                            // return x coordinate of socrates
        double getSocratesY() const;                                            // return y coordinate of socrates
        Direction getDirToSocrates(double x, double y) const;                   // return direction to socrates from (x, y)               

        // MODIFY EXISTING OBJECTS
        bool findAndDamage(double x, double y, int damage);         // search for and (if any found) damage an object near (x, y)
        bool findAndEatFood(double x, double y);                    // find a food object that overlap with (x, y) if any; set it to dead

        // RETRIEVING INFORMATION ABOUT THE WORLD AND WORLD OBJECTS
        bool movementValid(double x, double y) const;                           // return whether an actor can move to the specified coordinates
        bool findClosestFoodDir(double x, double y, Direction &dir) const;      // find direction to the closest food object (if any within VIEW_RADIUS)

    private:

        // private member functions
        void findValidCoords(int& x, int& y);       // auxiliary function for init(); finds valid coordinates for new pits/food objects/dirtpiles
        void removeDeadActors();                    // auxiliary function for move(); removes and deletes all dead actors
        void addNewGoodies();                       // auxiliary function for move(); adds goodies and fungi as appropriate
        std::string getStatText();                  // returns a string with the status text line describing the current gamestate
        
        // private data members
        Socrates* m_socrates;                       // pointer to Socrates object representing socrates
        std::set<Actor*> m_actors;                  // vector of pointers to all actors (except socrates) in the world
        int m_bacteriaLeft;                         // number of bacteria left in game, in pits or otherwise
};

// INLINE FUNCTION DEFINITIONS

// CREATING NEW PROJECTILS / BACTERIA
template<typename T>
inline void StudentWorld::createProjectile(double x, double y, Direction dir) {
    // create projectile (spray or flame)
    m_actors.insert(new T(x, y, dir, this));
}

template<typename T>
inline void StudentWorld::createBacterium(double x, double y) {
    // create bacterium (regular/aggressive salmonella or E. coli)
    m_actors.insert(new T(x, y, this));
}

// ACCESSING/MODIFYING BACTERIA LEFT

inline int StudentWorld::getBacteriaLeft() const { return m_bacteriaLeft; }
// get number of bacteria left, in pits or otherwise

inline void StudentWorld::decBacteriaLeft() { m_bacteriaLeft--; }
    // decrement number of bacteria left, in pits or otherwise

inline void StudentWorld::incBacteriaLeft() { m_bacteriaLeft++; }
    // increase number of bacteria left, in pits or otherwise 
        // (only called when bacteria reproduce - number of bacteria in pits is fixed at beginning of game)

#endif // STUDENTWORLD_H_