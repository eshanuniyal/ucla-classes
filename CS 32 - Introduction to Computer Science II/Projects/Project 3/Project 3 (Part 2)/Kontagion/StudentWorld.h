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
        void decBacteriaLeft();                     // decrement number of bacteria left in game

        // change existing objects
        bool findAndDamage(double x, double y, int damage);         // search for and (if any found) damage an object near (x, y)
        void restoreSocratesHitPoints();                            // restore Socrates' hit points to full
        void decreaseSocratesHitPoints(int decrement);              // decrease Socrates' hit points by decrement
        void increaseSocratesFlames(int increment);                 // increase Socrates Flames by increment
        bool findAndEatOverlappingFood(double x, double y);         // find a food object that overlap with (x, y) if any; set it to dead

        // create new objects
        void createFood(double x, double y);                        // create food object
        template<typename T>
        void createProjectile(double x, double y, Direction dir);   // create projectile of type T (flame or spray)
        template<typename T>
        void createBacterium(double x, double y);                   // create bacterium of type T
        

        // accessors
        double getSocratesX() const;                                            // return x coordinate of socrates
        double getSocratesY() const;                                            // return y coordinate of socrates
        int getBacteriaLeft() const;                                            // return number of bacteria left in game, in pits or otherwise
        bool movementValid(double x, double y) const;                           // return whether an actor can move to the specified coordinates
        bool findClosestFoodDir(double x, double y, Direction &dir) const;      // find direction to the closest food object (if any within VIEW_RADIUS)

    private:

        // private member functions
        void findValidCoords(int& x, int& y) const; // auxiliary function for init(); finds valid coordinates for new pits/food objects/dirtpiles
        void removeDeadActors();                    // auxiliary function for move(); removes and deletes all dead actors
        void addNewGoodies();                       // auxiliary function for move(); adds goodies and fungi as appropriate
        std::string getStatText() const;                 // return status line text in a string

        // private data members
        Socrates* m_socrates;                       // pointer to Socrates object representing socrates
        std::set<Actor*> m_actors;                  // vector of pointers to all actors (except socrates) in the world
        int m_bacteriaLeft;                         // number of bacteria left in game, in pits or otherwise
};

// INLINE FUNCTION DEFINITIONS

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


#endif // STUDENTWORLD_H_