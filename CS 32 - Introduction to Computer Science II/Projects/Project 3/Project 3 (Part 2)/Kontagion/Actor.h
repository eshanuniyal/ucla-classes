#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;			// to create pointer to StudentWorld object actors are contained in

// ################################################################################################################
// GLOBAL CONSTANTS
// ################################################################################################################

// max/initial charges and hitpoints for Socrates
const int MAX_SPRAYS = 20;							// maximum spray charges socrates can have
const int INITIAL_FLAMES = 5;
const int SOCRATES_HITPOINTS = 100;					// maximum health socrates can have

// initial bacteria counts for a pit
const int INITIAL_REGULAR_SALMONELLA = 5;			// number of regular salmonella initially in a pit
const int INITIAL_AGGRESSIVE_SALMONELLA = 3;		// number of aggressive salmonella initially in a pit
const int INITIAL_ECOLI = 2;						// number of E. coli initially in a pit
	// total number of bacteria initially in a pit
const int TOTAL_INITIAL_BACTERIA = INITIAL_REGULAR_SALMONELLA + INITIAL_AGGRESSIVE_SALMONELLA + INITIAL_ECOLI;
	
// bacteria, flame, spray hitpoints
const int SALMONELLA_HITPOINTS = 4;					// hitpoints associated with a salmonella bacterium
const int AGGRESSIVE_SALMONELLA_HITPOINTS = 10;		// hitpoints associated with an aggressive salmonella bacterium
const int ECOLI_HITPOINTS = 5;						// hitpoints associated with an E. Coli bacterium

// damage dealt by actors
const int FLAME_DAMAGE = 5;							// damage dealt by a flame
const int SPRAY_DAMAGE = 2;							// damage dealt by a spray
const int REGULAR_SALMONELLA_DAMAGE = 1;			// damage dealt by regular salmonella
const int AGGRESSIVE_SALMONELLA_DAMAGE = 2;
const int ECOLI_DAMAGE = 4;

// maximum travelable distances for Spray, Flame
const int MAX_SPRAY_TRAVELABLE_DIST = 112;			// maximum travelable distance for spray
const int MAX_FLAME_TRAVELABLE_DIST = 32;			// maximum travelable distance for flame

// score increases for player
const int BACTERIUM_DIE_POINTS = 100;
const int RESTORE_HEALTH_POINTS = 250;
const int FLAMETHROWER_POINTS = 300;
const int EXTRA_LIFE_POINTS = 500;
const int FUNGUS_POINTS = -50;

// goodie effects
const int FLAMETHROWER_GOODIE_CHARGES = 5;
const int FUNGUS_DAMAGE = 20;

// miscellaneous
const int MAX_OBJ_DISTANCE = 120;					// maximum distance from the center for a dirt pile, pit
const double PI = 4 * atan(1.0);					// pi value used for calculating polar coordinates
const int MAX_FOOD_EATEN = 3;						// amount of food bacterium can eat before reproducing
const int SALMONELLA_TRAVEL_DIST = 3;				// number of pixels salmonella can travel per tick
const int ECOLI_TRAVEL_DIST = 2;					// number of pixels an E. coli will travel toward socrates
const int MAX_MOVEMENT_PLAN_DIST = 10;				// maximum movement plan distance bacteria can have
const int AGGRESSIVE_SALMONELLA_DR = 72;			// radius within which aggressive salmonella will detect socrates
const int ECOLI_TRIES = 10;							// number of times E. coli will try to move towards or near socrates				

// ################################################################################################################
// ACTOR CLASS DECLARATION
// ################################################################################################################

class Actor : public GraphObject {
	public:
		Actor(int imageID, double startX, double startY, StudentWorld* world, Direction dir = 0,
			int depth = 0, double size = 1.0);
		virtual ~Actor() {};											// virtual destructor
		virtual void doSomething() {};									// virtual function that does nothing by default
		
		// mutators
		void setActorDead() { m_alive = false; }						// set actor to dead
		virtual void damageActor(int) { setActorDead(); }
			// by default, damageActor kills the actor (of all damageable objects, only bacteria behave differently)

		// accessors
		StudentWorld* getWorld() const { return m_world; };
		bool actorAlive() const { return m_alive; }
		bool actorDamageable() const { return m_damageable; }
		bool actorEatable() const { return m_eatable; }
		bool actorBlocksMovement() const { return m_blocksMovement; }

	private:
		StudentWorld* m_world;		// pointer to the StudentWorld object Actor is based in
		bool m_alive;				// reflects whether or not actor is alive
		bool m_damageable;			// reflects whether or not an actor can be damaged
		bool m_eatable;				// reflects whether or not an actor can be eaten (e.g. Food)
		bool m_blocksMovement;		// reflects whether or not an actor blocks movement
};

// ################################################################################################################
// SOCRATES CLASS DECLARATION
// ################################################################################################################
class Socrates : public Actor {
	public:
		// constructor
		Socrates(StudentWorld* world)
			: Actor(IID_PLAYER, 0, VIEW_HEIGHT / 2, world), 
			m_sprays(MAX_SPRAYS), m_flames(INITIAL_FLAMES), m_hitPoints(SOCRATES_HITPOINTS) {}

		// mutators
		virtual void doSomething();
		virtual void damageActor(int damage);			// note: m_damageable = false for actor; damageActor() will only be called directly
		virtual void restoreHitPoints() { m_hitPoints = SOCRATES_HITPOINTS; }
		virtual void increaseFlames(int increment) { m_flames += increment; }

		// accessors
		int getSprays() const { return m_sprays; }
		int getFlames() const { return m_flames; }
		int getHitPoints() const { return m_hitPoints; }
	private:
		// private member functions
		int getPositionalAngle() const; // returns positional angle of Socrates
		// private data members
		int m_sprays;			// number of sprays left
		int m_flames;			// number of flame thrower charges left
		int m_hitPoints;			// hit points left
};

// ################################################################################################################
// DIRTPILE CLASS DECLARATION
// ################################################################################################################
class DirtPile : public Actor {
	public:
		// constructor
		DirtPile(double startX, double startY, StudentWorld* world)
			: Actor(IID_DIRT, startX, startY, world, 90, 1) {}
		virtual void doSomething() {};
};

// ################################################################################################################
// PIT CLASS DECLARATION
// ################################################################################################################

class Pit : public Actor {
	public:
		// constructor
		Pit(double startX, double startY, StudentWorld* world)
			: Actor(IID_PIT, startX, startY, world, 0, 1), 
			m_regSalmonella(INITIAL_REGULAR_SALMONELLA), m_aggSalmonella(INITIAL_AGGRESSIVE_SALMONELLA), m_eColi(INITIAL_ECOLI) {}

		// mutators
		virtual void doSomething();
	private:
		int m_regSalmonella;
		int m_aggSalmonella;
		int m_eColi;
};

// ################################################################################################################
// FOOD CLASS DECLARATION
// ################################################################################################################

class Food : public Actor {
	public:
		// constructor
		Food(double startX, double startY, StudentWorld* world)
			: Actor(IID_FOOD, startX, startY, world, 90, 1) {}			// food is only eatable object
	private:
};

// ################################################################################################################
// PROJECTILE CLASS DECLARATION
// ################################################################################################################

class Projectile : public Actor {
	public:
		// constructor
		Projectile(int imageID, double startX, double startY, Direction dir, StudentWorld* world);
		virtual ~Projectile() {};
		// mutators
		virtual void doSomething();
		void decTravelableDist(int decrement) { m_travelableDist -= decrement; }		// decrease travelable distance by decrement

		// accessors
		virtual int getDamage() = 0;
		int getTravelableDist() const { return m_travelableDist; }						// return remaining travelable distance

	private:
		int m_travelableDist;
};


// ################################################################################################################
// FLAME CLASS DECLARATION

class Flame : public Projectile {
	public:
		// constructor
		Flame(double startX, double startY, Direction dir, StudentWorld* world)
			: Projectile(IID_FLAME, startX, startY, dir, world) {}
		virtual int getDamage() { return FLAME_DAMAGE; }
};

// ################################################################################################################
// DISINFECTANT SPRAY CLASS DECLARATION

class Spray : public Projectile {
	public:
		// constructor
		Spray(double startX, double startY, Direction dir, StudentWorld* world)
			: Projectile(IID_SPRAY, startX, startY, dir, world) {}
		virtual int getDamage() { return SPRAY_DAMAGE; }
};


// ################################################################################################################
// GOODIE CLASS DECLARATION
// ################################################################################################################

class Goodie : public Actor {
	public:
		// constructor
		Goodie(int imageID, double startX, double startY, StudentWorld* world);
		virtual ~Goodie() {};
		// mutators
		virtual void doSomething();
		virtual void updateSocrates() = 0;			// update Socrates as appropriate (not technically a mutator)

		// accessors
		virtual int getScoreChange() const = 0;

	private:
		int m_life;		// lifetime of goodie
};

// ################################################################################################################
// RESTORE HEALTH GOODIE CLASS DECLARATION

class RestoreHealthGoodie : public Goodie {
	public:
		// constructor
		RestoreHealthGoodie(double startX, double startY, StudentWorld* world)
			: Goodie(IID_RESTORE_HEALTH_GOODIE, startX, startY, world) { }

		virtual void updateSocrates();		// restore Socrates' health

		virtual int getScoreChange() const { return RESTORE_HEALTH_POINTS; }
};

// ################################################################################################################
// FLAMETHROWER GOODIE CLASS DECLARATION

class FlamethrowerGoodie : public Goodie {
	public:
		// constructor
		FlamethrowerGoodie(double startX, double startY, StudentWorld* world)
			: Goodie(IID_FLAME_THROWER_GOODIE, startX, startY, world) { }

		virtual void updateSocrates();		// increase socrates' charges

		virtual int getScoreChange() const { return FLAMETHROWER_POINTS; }
};

// ################################################################################################################
// EXTRA LIFE GOODIE CLASS DECLARATION

class ExtraLifeGoodie : public Goodie {
	public:
		// constructor
		ExtraLifeGoodie(double startX, double startY, StudentWorld* world)
			: Goodie(IID_EXTRA_LIFE_GOODIE, startX, startY, world) { }

		virtual void updateSocrates();		// increase socrates' lives

		virtual int getScoreChange() const { return EXTRA_LIFE_POINTS; }
};

// ################################################################################################################
//  FUNGUS GOODIE CLASS DECLARATION

class Fungus : public Goodie {
	public:
		// constructor
		Fungus(double startX, double startY, StudentWorld* world)
			: Goodie(IID_FUNGUS, startX, startY, world) { }
		
		virtual void updateSocrates();
		virtual int getScoreChange() const { return FUNGUS_POINTS; }
};

// ################################################################################################################
// BACTERIUM CLASS DECLARATION
// ################################################################################################################

class Bacterium : public Actor {
	public:
		// constructor
		Bacterium(int imageID, double startX, double startY, StudentWorld* world, int hitPoints)
			: Actor(imageID, startX, startY, world, 90, 0), m_movementPlanDist(0), m_hitPoints(hitPoints), m_foodEaten(0) {}
		virtual ~Bacterium() {};

		// mutators
		virtual void doSomething();
		virtual void damageActor(int damage);		// when damaged, bacteria lose hitpoints (and die if appropriate)
		virtual void setActorDead();				// bacterium's setActorDead() function also has to notify StudentWorld it died
		void decMovementPlanDist();					// decrease bacterium's movement plan distance
		void resetMovementPlan();					// reset bacterium's movement plan distance

		// pure virtual mutators
		virtual void createNewBacterium(double x, double y) = 0;	// instructs StudentWorld to create a new Bacterium of the appropriate class
		virtual bool searchForSocrates() = 0;						// only applicable to Aggressive Salmonella; other bacteria return false
		virtual void move() = 0;									// executes movement plan of bacterium
		
		// accessors
		int getHitPoints() const;					// returns hit points (health) of bacterium
		int getFoodEaten() const;					// returns amount of food eaten by bacterium
		int getMovementPlanDist() const;			// returns movement plan distance of bacterium
		virtual int getHurtSound() const = 0;		// returns sound to make when bacterium hurt
		virtual int getDieSound() const = 0;		// returns sound to make when bacterium dies
		virtual int getDamage() const = 0;			// returns damage dealt by bacterium

	private:
		// auxiliary private member functions
		void reproduce();							// creates a new bacterium at appropriate coordinates; auxiliary function for doSomething()
		// private data members
		int m_movementPlanDist;			// movement plan distance of bacterium
		int m_hitPoints;				// remaining hit points of bactierum
		int m_foodEaten;				// amount of food eaten by bacterium
};

// inline mutator functions
inline void Bacterium::decMovementPlanDist() { m_movementPlanDist--; }
inline void Bacterium::resetMovementPlan() { m_movementPlanDist = MAX_MOVEMENT_PLAN_DIST; }

// inline accessor functions
inline int Bacterium::getHitPoints() const { return m_hitPoints; }
inline int Bacterium::getFoodEaten() const { return m_foodEaten; }
inline int Bacterium::getMovementPlanDist() const { return m_movementPlanDist; }

// ################################################################################################################
// SALMONELLA CLASS DECLARATION
// ################################################################################################################

class Salmonella :public Bacterium {
	public:
		// constructor
		Salmonella(int imageID, double startX, double startY, StudentWorld* world, int hitpoints)
			: Bacterium(imageID, startX, startY, world, hitpoints) {}
		virtual ~Salmonella() {};

		// mutators
		virtual void createNewBacterium(double x, double y) = 0;	// instructs StudentWorld to create a new Bacterium of the appropriate class
		virtual void move();
		virtual bool searchForSocrates() = 0;			// pure virtual function; only aggressive salmonella effectively does anything
		// void checkClosestFood();						// salmonella searches for closest food object and acts accordingly

		// accessors
		virtual int getDamage() const = 0;										// returns damage dealt by bacterium
		virtual int getHurtSound() const { return SOUND_SALMONELLA_HURT; }		// returns sound to make when salmonella is hurt
		virtual int getDieSound() const { return SOUND_SALMONELLA_DIE; }		// returns sound to make when salmonella dies
};

// ################################################################################################################
// REGULAR SALMONELLA CLASS DECLARATION

class RegularSalmonella : public Salmonella {
	public:
		// constructor
		RegularSalmonella(double startX, double startY, StudentWorld* world)
			: Salmonella(IID_SALMONELLA, startX, startY, world, SALMONELLA_HITPOINTS) {}

		// mutators
		virtual void createNewBacterium(double x, double y);	// instructs StudentWorld to create a new Bacterium of the appropriate class
		virtual bool searchForSocrates() { return false; }

		// accessors
		virtual int getDamage() const { return REGULAR_SALMONELLA_DAMAGE; }
};

// ################################################################################################################
// AGGRESSIVE SALMONELLA CLASS DECLARATION

class AggressiveSalmonella : public Salmonella {
	public:
		// constructor
		AggressiveSalmonella(double startX, double startY, StudentWorld* world)
			: Salmonella(IID_SALMONELLA, startX, startY, world, AGGRESSIVE_SALMONELLA_HITPOINTS) {}

		// mutators
		virtual void createNewBacterium(double x, double y);	// instructs StudentWorld to create a new Bacterium of the appropriate class
		virtual bool searchForSocrates();

		// accessors
		virtual int getDamage() const { return AGGRESSIVE_SALMONELLA_DAMAGE; }
};

// ################################################################################################################
// E.COLI CLASS DECLARATION

class EColi : public Bacterium {
	public:
		// constructor
		EColi(double startX, double startY, StudentWorld* world)
			: Bacterium(IID_ECOLI, startX, startY, world, ECOLI_HITPOINTS) {}
		
		// mutators
		virtual void createNewBacterium(double x, double y);	// instructs StudentWorld to create a new Bacterium of the appropriate class
		virtual bool searchForSocrates() { return false; }		// E. Coli doesn't search for Socrates; it moves toward it in move()
		virtual void move();

		// accessors
		virtual int getHurtSound() const { return SOUND_ECOLI_HURT; }
		virtual int getDieSound() const { return SOUND_ECOLI_DIE; }
		virtual int getDamage() const { return AGGRESSIVE_SALMONELLA_DAMAGE; }
};

#endif // ACTOR_H_