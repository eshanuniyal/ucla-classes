#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <set>			// to create a set of pointers to Actors

class Socrates; // to allow creation of private data member socrates, which points to a Socrates object
class Actor;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
    public:
        StudentWorld(std::string assetPath);        // constructor
        ~StudentWorld();                            // destructor
        virtual int init();
        virtual int move();
        virtual void cleanUp();

    private:
        Socrates* m_socrates;                 // pointer to Socrates object representing socrates
        std::set<Actor*> m_actors;         // vector of pointers to all actors (except socrates) in the world
};

#endif // STUDENTWORLD_H_
