#include "Actor.h"
#include "StudentWorld.h"
#include <cmath>			// to define pow()
using namespace std;

// ################################################################################################################
// AUXILIARY FUNCTION DEFINITIONS
// ################################################################################################################

double distance(double x1, double y1, double x2, double y2);

double distanceFromCenter(double x, double y);

// ################################################################################################################
// SOCRATES CLASS DEFINITIONS
// ################################################################################################################

Direction Socrates::getPositionalAngle() const {
	// returns the current positional angle of Socrates
	Direction dir = getDirection();
	if (dir < 180)					// direction < 180 -> positional angle = direction + 180
		return dir + 180;
	else							// direction >= 180 -> positional angle = direction - 180
		return dir - 180;
}

void Socrates::doSomething() {
	// if out of health, return immediately
	if (!actorAlive()) 
		return;

	int ch;

	if (getWorld()->getKey(ch)) { // user hit a key during this tick!

		switch (ch) {

			// player moved left or right
			case KEY_PRESS_LEFT:
			case KEY_PRESS_RIGHT: {

				int new_pos_angle = getPositionalAngle();
				switch (ch) {
					// Socrates moves five degrees counterclockwise
				case KEY_PRESS_LEFT:  new_pos_angle += 5;
					break;
					// Socrates moves five degress clockwise
				case KEY_PRESS_RIGHT: new_pos_angle -= 5;
					break;
				}

				// moving socrates and updating direction
				double new_x = VIEW_RADIUS * (1 + cos(new_pos_angle * 1.0 / 360 * 2 * PI));
				double new_y = VIEW_RADIUS * (1 + sin(new_pos_angle * 1.0 / 360 * 2 * PI));
				moveTo(new_x, new_y);
				setDirection(new_pos_angle + 180);
				break;
			}
			
			// player sprayed
			case KEY_PRESS_SPACE:
				// if player has sprays left
				if (getSprays() >= 1) {
					double x, y;
					getPositionInThisDirection(getDirection(), SPRITE_WIDTH, x, y);			// find location of spray object to be created
					getWorld()->createProjectile<Spray>(x, y, getDirection());							// create new spray object
					m_sprays--;										// decrement sprays
					getWorld()->playSound(SOUND_PLAYER_SPRAY);		// play sound
				}
				break;
			// player used flame
			case KEY_PRESS_ENTER:
				// if player has flamethrower charges left
				if (getFlames() >= 1) {
					double x, y;
					for (int i = 0; i != 16; i++) {													// create 16 flames
						getPositionInThisDirection(getDirection() + 22 * i, SPRITE_WIDTH, x, y);	// find location of flame object to be created
						getWorld()->createProjectile<Flame>(x, y, getDirection() + 22 * i);						// create new flame objects
					}
					m_flames--;										// decrement flames
					getWorld()->playSound(SOUND_PLAYER_FIRE);		// play sound
				}
				break;
		}
	}

	// player did not press a key
	else if (getSprays() < 20)
		m_sprays++;	
}

void Socrates::damageActor(int damage){
	
	// decrement health
	m_hitPoints -= damage;

	// player is still alive
	if (getHitPoints() > 0)
		getWorld()->playSound(SOUND_PLAYER_HURT);
	// player died
	else {
		setActorDead();
		getWorld()->playSound(SOUND_PLAYER_DIE);
	}
}

// ################################################################################################################
// PIT CLASS DEFINITIONS
// ################################################################################################################

void Pit::doSomething() {

	// pit has emitted all bacteria
	if (m_regSalmonella == 0 && m_aggSalmonella == 0 && m_eColi == 0) {
		setActorDead();			// set pit to dead
		return;
	}

	// one in fifty chance of emitting a bacterium
	if (randInt(1, 50) == 1) {

		// iterating until we create a bacteria
		while (true) {

			// randomly selecting a bacteria type; 1 = RegularSalmonella, 2 = AggressiveSalmonella, 3 = EColi
			int rand = randInt(1, 3);

			// if 1 selected and regular salmonella left, create regular salmonella
			if (rand == 1 && m_regSalmonella > 0) {
				getWorld()->createBacterium<RegularSalmonella>(getX(), getY());
				m_regSalmonella--;
			}
			// if 2 selected and aggressive salmonella left, crate aggressive salmonella
			else if (rand == 2 && m_aggSalmonella > 0) {
				getWorld()->createBacterium<AggressiveSalmonella>(getX(), getY());
				m_aggSalmonella--;
			}
			// if 3 selected and aggressive salmonella left, create E. coli
			else if (rand == 3 && m_eColi > 0) {
				getWorld()->createBacterium<EColi>(getX(), getY());
				m_eColi--;
			}
			// no bacteria created -> continue with while loop
			else
				continue;

			// bacteria created -> play sound and break out of while loop
			getWorld()->playSound(SOUND_BACTERIUM_BORN);
			break;
		}
	}
}

// ################################################################################################################
// PROJECTILE CLASS DEFINITIONS
// ################################################################################################################

Projectile::Projectile(int imageID, double startX, double startY, Direction dir, StudentWorld* world)
	: Actor(imageID, startX, startY, world, dir, 1), m_travelableDist(0) {

	switch (imageID) {
		// projectile is a spray
		case IID_SPRAY:
			m_travelableDist = MAX_SPRAY_TRAVELABLE_DIST;
			break;
		// projectile is a flame
		case IID_FLAME:
			m_travelableDist = MAX_FLAME_TRAVELABLE_DIST;
			break;
	}
}

void Projectile::doSomething() {
	bool damage_success = getWorld()->findAndDamage(getX(), getY(), getDamage());

	// flame/spray successfully damaged some object -> flame/spray dies
	if (damage_success) {
		setActorDead();
		return;
	}
	// flame/spray didn't damage any object -> move forward

	// finding new coordinates
	double new_x, new_y;
	getPositionInThisDirection(getDirection(), SPRITE_WIDTH, new_x, new_y);

	// moving forward to (new_x, new_y) and decreasing travelable distance
	moveTo(new_x, new_y); decTravelableDist(SPRITE_WIDTH);

	// if can't travel any more, set to dead
	if (getTravelableDist() <= 0)
		setActorDead();
}

// ################################################################################################################
// GOODIE CLASS DEFINITIONS
// ################################################################################################################

Goodie::Goodie(int imageID, double startX, double startY, StudentWorld* world)
	: Actor(imageID, startX, startY, world, 0, 1), 
	m_life(max(randInt(0, 300 - 10 * getWorld()->getLevel() - 1), 50)) { }


void Goodie::doSomething() {

	// if goodie is dead, return immediately
	if (!actorAlive())
		return;

	// if goodie overlaps with socrates
	else if (distance(getX(), getY(), getWorld()->getSocratesX(), getWorld()->getSocratesY()) <= SPRITE_WIDTH) {
		getWorld()->increaseScore(getScoreChange());		// change score by appropriate amount(e.g. 250 for restore health goodie)
		setActorDead();										// set goodie to dead
		getWorld()->playSound(SOUND_GOT_GOODIE);			// play appropriate sound
		updateSocrates();									// update socrates' health/flame charges/lives/take damage
	}

	else {
		
		// decrease lifetime
		m_life--;

		// if lifetime has expired, set goodie to dead
		if (m_life <= 0)
			setActorDead();
	}
}

// ################################################################################################################
// RESTORE HEALTH, FLAMETHROWER, and EXTRA LIFE GOODIE CLASS DEFINITIONS

void RestoreHealthGoodie::updateSocrates() const { 
	// restore Socrates' health
	getWorld()->restoreSocratesHitPoints(); 
}
void FlamethrowerGoodie::updateSocrates() const { 
	// increase Socrates' flame charges
	getWorld()->increaseSocratesFlames(FLAMETHROWER_GOODIE_CHARGES); 
}

void ExtraLifeGoodie::updateSocrates() const { 
	// increment Socrates' lives
	getWorld()->incLives(); 
}

void Fungus::updateSocrates() const {
	// decrease Socrates' health
	getWorld()->decreaseSocratesHitPoints(FUNGUS_DAMAGE);
}

// ################################################################################################################
// BACTERIUM CLASS DEFINITIONS
// ################################################################################################################

void Bacterium::doSomething() {

	// if bacterium isn't alive, return immediately
	if (!actorAlive())
		return;

	bool executeMovement = !searchForSocrates();
	// if aggressive salmonella found socrates and attempted to move towards socrates, we don't need to execute movement plan
	// if it didn't find socrates or if it's some other bacterium, we execute the movement plan

// check if bacterium overlaps with socrates and deals damage as appropriate
	if (distance(getX(), getY(), getWorld()->getSocratesX(), getWorld()->getSocratesY()) <= SPRITE_WIDTH)
		getWorld()->decreaseSocratesHitPoints(getDamage());		// damage socrates with bacterium's hitpoints
	// bacterium has eaten enough food -> reproduce
	else if (m_foodEaten == 3) {
		reproduce();		// create new bacterium of the appropriate type at the appropriate coordinates
		m_foodEaten = 0;	// reset count of food eaten
	}

	// checking for overlapping food objects and consuming one if any
	if (getWorld()->findAndEatFood(getX(), getY()))
		m_foodEaten++;		// found and ate a food object

	if (executeMovement)
		moveBacterium();
}

void Bacterium::damageActor(int damage) {
	
	// decrement health
	m_hitPoints -= damage;

	// bacterium is still alive
	if (getHitPoints() > 0)
		getWorld()->playSound(getHurtSound());
	// bacterium died
	else {
		// set bacterium to dead, play the appropriate sound, and increase player score
		setActorDead();
		getWorld()->playSound(getDieSound());
		getWorld()->increaseScore(BACTERIUM_DIE_POINTS);

		// 50% chance bacterium turns into food before it dies
			// pseudo-coin toss; if 0, turn to food
		if (randInt(0, 1) == 0)
			getWorld()->createFood(getX(), getY());		// create new food object at same coordinates
	}
}

void Bacterium::setActorDead() {
		// set bacterium to dead and notify StudentWorld
	Actor::setActorDead();
	getWorld()->decBacteriaLeft();
}

// ################################################################################################################
// SALMONELLA CLASS DEFINITIONS

void Salmonella::moveBacterium() {
	// move salmonella

	// movement plan distance is greater than 0
	if (m_movementPlanDist > 0) {

		// decrement movement plan distance
		m_movementPlanDist--;
		
		// checking new coordinates
		double newX, newY;
		getPositionInThisDirection(getDirection(), SALMONELLA_TRAVEL_DIST, newX, newY);

		// new coordinates are valid -> move to new coordinates
		if (getWorld()->movementValid(newX, newY))
			moveTo(newX, newY);
		// new coordinates are invalid -> reset movement
		else
			resetMovement();
	}
	// movement plan distance is 0 -> move toward food
	else {

		Direction foodDir;

		// food found within VIEW_RADIUS pixels
		if (getWorld()->findClosestFoodDir(getX(), getY(), foodDir)) {

			// find new coordinates
			double newX, newY;
			getPositionInThisDirection(foodDir, SALMONELLA_TRAVEL_DIST, newX, newY);

			// bacterium can move in food direction -> try to move toward food
			if (getWorld()->movementValid(newX, newY)) {
				setDirection(foodDir);
				moveTo(newX, newY);
			}

			// bacterium can't move in food direction -> reset movement
			else
				resetMovement();
		}
		// no food found within VIEW_RADIUS pixels -> reset movement
		else
			resetMovement();
	}
}

void Salmonella::resetMovement() {
	// sets direction to random direction and resets movement plan
	setDirection(randInt(0, 359));
	m_movementPlanDist = MAX_MOVEMENT_PLAN_DIST;
}
// ################################################################################################################
// REGULAR SALMONELLA CLASS DEFINITIONS

void RegularSalmonella::createNewBacterium(double x, double y) const {
	getWorld()->createBacterium<EColi>(x, y);
}
// ################################################################################################################
// AGGRESSIVE SALMONELLA CLASS DEFINITIONS

void AggressiveSalmonella::createNewBacterium(double x, double y) const {
	getWorld()->createBacterium<AggressiveSalmonella>(x, y);
}

bool AggressiveSalmonella::searchForSocrates() {
	// checks whether socrates is within detection radius and acts accordingly

	double socratesX = getWorld()->getSocratesX();
	double socratesY = getWorld()->getSocratesY();

	// distance to socrates is less than or equal to detection radius
	if (distance(getX(), getY(), socratesX, socratesY) <= AGGRESSIVE_SALMONELLA_DR) {

		// find direction towards socrates
		Direction socratesDir = getWorld()->getDirToSocrates(getX(), getY());
		setDirection(socratesDir);

		// find new coordinates
		double x, y;
		getPositionInThisDirection(socratesDir, SALMONELLA_TRAVEL_DIST, x, y);

		// movement is valid -> move to new coordinates
		if (getWorld()->movementValid(x, y))
			moveTo(x, y);

		return true;	// successfully found and attempted to move toward socrates
	}

	return false;		// couldn't find socrates
}

// ################################################################################################################
// ECOLI CLASS DEFINITIONS

void EColi::moveBacterium() {

	// finding direction of socrates
	Direction socratesDir = getWorld()->getDirToSocrates(getX(), getY());
	
	// trying to move toward socrates
	for (int i = 0; i != ECOLI_TRIES; i++) {

		// finding new coordinates
		double newX, newY;
		getPositionInThisDirection(socratesDir, ECOLI_TRAVEL_DIST, newX, newY);

		// if new coordinates are valid, update direction and move to (newX, newY); return immediately
		if (getWorld()->movementValid(newX, newY)) {
			setDirection(socratesDir);
			moveTo(newX, newY);
			return;
		}
		// movement towards socrates is blocked, try a different angle
		else
			socratesDir = (socratesDir + 10) % 360;
	}
}

void EColi::createNewBacterium(double x, double y) const {
	getWorld()->createBacterium<EColi>(x, y);
}


// ################################################################################################################
// AUXILIARY FUNCTIONS FOR BACTERIUM CLASS

void Bacterium::reproduce() {
	// create a new bacterium at the appropriate location and reset food eaten

	// finding x and y coordinates for new bacterium
	double new_x = getX();
	double new_y = getY();

	// adjusting new_x coordinate as necesary
	if (getX() < VIEW_WIDTH / 2) { new_x += SPRITE_WIDTH / 2; }
	else if (getX() > VIEW_WIDTH / 2) { new_x -= SPRITE_WIDTH / 2; }

	// adjust new_y coordinate as necessary
	if (getX() < VIEW_HEIGHT / 2) { new_x += SPRITE_WIDTH / 2; }
	else if (getX() > VIEW_HEIGHT / 2) { new_x -= SPRITE_WIDTH / 2; }

	// create new bacterium of the appropriate type at the given coordinates
	createNewBacterium(new_x, new_y);
	getWorld()->incBacteriaLeft();
	getWorld()->playSound(SOUND_BACTERIUM_BORN);
}