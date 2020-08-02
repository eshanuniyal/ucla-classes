#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;			// to create pointer to StudentWorld object actors are contained in

// ################################################################################################################
// GLOBAL CONSTANTS
// ################################################################################################################

const int MAX_DIRT_DISTANCE = 120;		// maximum distance from the center for a dirt pile
const double PI = 4 * atan(1.0);	// pi value used for calculating polar coordinates

// ################################################################################################################
// ACTOR CLASS DECLARATION
// ################################################################################################################
class Actor : public GraphObject {
	public:
		Actor(int imageID, double startX, double startY, StudentWorld* world, Direction dir = 0, int depth = 0, double size = 1.0)
			: GraphObject(imageID, startX, startY, dir, depth, size), m_world(world), m_alive(true) {}
		virtual void doSomething() {}; // virtual function that does nothing by default
		
		// mutators
		void setActorDead() { m_alive = false; }

		// accessors
		StudentWorld* getWorld() const { return m_world; };
		bool isActorAlive() const { return m_alive; }
	private:
		StudentWorld* m_world;		// pointer to the StudentWorld object Actor is based in
		bool m_alive;				// true by default; reflects whether or not actor is alive
};

// ################################################################################################################
// SOCRATES CLASS DECLARATION
// ################################################################################################################
class Socrates : public Actor {
	public:
		// constructor
		Socrates(StudentWorld* world)
			: Actor(IID_PLAYER, 0, VIEW_HEIGHT / 2, world), m_sprays(20), m_flames(5), m_health(100) {}
		// mutators
		virtual void doSomething();
		// accessors
		int getSprays() const { return m_sprays; }
		int getFlames() const { return m_flames; }
		int getHealth() const { return m_health; }
	private:
		// private member functions
		int getPositionalAngle() const; // returns positional angle of Socrates
		// private data members
		int m_sprays;			// number of sprays left
		int m_flames;			// number of flame thrower charges left
		int m_health;			// hit points left
};

// ################################################################################################################
// DIRTPILE CLASS DECLARATION
// ################################################################################################################
class DirtPile : public Actor {
	public:
		// constructor
		DirtPile(double startX, double startY, StudentWorld* world)
			: Actor(IID_DIRT, startX, startY, world, 90, 1) {}
};

#endif // ACTOR_H_