#include "Actor.h"
#include "StudentWorld.h"
#include <cmath>			// to define pow()
using namespace std;

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// ################################################################################################################
// ACTOR CLASS DEFINITIONS
// ################################################################################################################

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
	if (m_health <= 0) return;

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
					// new (x, y) = (r(1 + co theta ), r(1 + sin theta)); theta in radians
				double new_x = VIEW_RADIUS * (1 + cos(new_pos_angle * 1.0 / 360 * 2 * PI)); 
				double new_y = VIEW_RADIUS * (1 + sin(new_pos_angle * 1.0 / 360 * 2 * PI));
				moveTo(new_x, new_y);
				setDirection(new_pos_angle + 180);
				break;
			}
		}
	}
	else if (getSprays() < 20)
		m_sprays++;	
}