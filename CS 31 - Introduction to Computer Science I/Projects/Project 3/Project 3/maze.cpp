#include "grid.h"
#include <iostream>
#include <cctype>

// needed for assert call
#include <cassert>

using namespace std;

bool isCourseWellFormed(string course);
int driveSegmentEast(int r, int c);
int driveSegmentWest(int r, int c);
int driveSegmentNorth(int r, int c);
int driveSegmentSouth(int r, int c);
int driveSegment(int r, int c, char dir, int maxSteps);
int driveCourse(int sr, int sc, int er, int ec, string course, int& nsteps);

int main() {
	setSize(5, 5);
	setWall(1, 4); setWall(2, 2);
	setWall(3, 3); setWall(2, 5);
	setWall(4, 1); setWall(5, 3);
	draw(5, 1, 5, 5);
	cerr << endl;
	
	// isCourseWellFormed tests
	assert(isCourseWellFormed("")); // empty string is valid
	assert(isCourseWellFormed("N2eE01n0s2e1"));
	assert(!isCourseWellFormed("3sn")); // starts with a digit
	assert(!isCourseWellFormed("n2e001e1")); // more than three digits for a direction character
	assert(!isCourseWellFormed("w2+n3")); // invalid character '+'
	assert(!isCourseWellFormed("e1x")); // invalid character 'x'
	assert(!isCourseWellFormed("3")); // only a digit
	assert(!isCourseWellFormed(" ")); // only a space character
	cerr << "All isCourseWellFormed tests passed." << endl;
		
	// driveSegment tests
	assert(driveSegment(-1, 1, 'n', 4) == -1); // start coordinate not in grid
	assert(driveSegment(1, -1, 'n', 4) == -1); // start coordinate not in grid
	assert(driveSegment(6, 1, 'n', 4) == -1); // start coordinate not in grid
	assert(driveSegment(0, 1, 'n', 4) == -1); // start coordinate not in grid
	assert(driveSegment(1, 6, 'n', 4) == -1); // start coordinate not in grid
	assert(driveSegment(2, 2, 'n', 1) == -1); // start position occupied by wall
	assert(driveSegment(1, 1, 'x', 4) == -1); // invalid direction character
	assert(driveSegment(1, 1, 'n', -2) == -1); // negative maxSteps
	assert(driveSegment(3, 4, 'n', 1) == 1); // can travel one step north
	assert(driveSegment(3, 4, 'n', 2) == 1); // can only travel one step north
	assert(driveSegment(3, 4, 's', 0) == 0); // maximum steps are zero
	assert(driveSegment(3, 4, 's', 1) == 1); // can travel one step
	assert(driveSegment(3, 4, 'S', 1) == 1); // capital direction character works
	assert(driveSegment(3, 4, 's', 2) == 2); // can travel two steps
	assert(driveSegment(3, 4, 's', 3) == 2); // can only travel two steps
	assert(driveSegment(3, 4, 'e', 1) == 1); // can travel one step
	assert(driveSegment(3, 4, 'e', 2) == 1); // can only travel one step
	assert(driveSegment(3, 4, 'w', 0) == 0); // can travel 0 steps
	assert(driveSegment(3, 4, 'w', 1) == 0); // cannot travel any steps
	cerr << "All driveSegment tests passed." << endl;
	
	/* grid
	  1 2 3 4 5
	1 . . . * .
	2 . * . . *
	3 . . * . .
	4 * . . . .
	5 S . * . E
	*/

	int nsteps;
	assert(driveCourse(-1, 1, 3, 4, "e02sse1", nsteps) == 2); // invalid start coordinates
	assert(driveCourse(1, 0, 6, 4, "e02sse1", nsteps) == 2); // invalid start coordinates
	assert(driveCourse(1, 1, 6, 4, "e02sse1", nsteps) == 2); // invalid end coordinates
	assert(driveCourse(1, 1, 0, 4, "e02sse1", nsteps) == 2); // invalid end coordinates
	assert(driveCourse(2, 2, 3, 4, "e02sse1", nsteps) == 2); // start coordinates blocked by wall
	assert(driveCourse(1, 1, 3, 3, "e02sse1", nsteps) == 2); // end coordinates blocked by wall
	assert(driveCourse(1, 1, 3, 4, "n2e001e1", nsteps) == 2); // invalid course string
	assert(driveCourse(1, 1, 3, 4, "e02sse1", nsteps) == 3 && nsteps == 3); // course could not be completed
	assert(driveCourse(1, 1, 3, 4, "eesse", nsteps) == 3 && nsteps == 3); // course could not be completed
	assert(driveCourse(1, 1, 3, 4, "w3s1e", nsteps) == 3 && nsteps == 0); // course could not be completed
	assert(driveCourse(1, 1, 3, 4, "S2ese02N1", nsteps) == 0 && nsteps == 7); // course completed at end position
	assert(driveCourse(1, 1, 3, 4, "e02se", nsteps) == 1 && nsteps == 4); // course completed, but not at end position

	cerr << "All driveCourse tests succeeded." << endl;
}

int driveCourse(int sr, int sc, int er, int ec, string course, int& nsteps) {
	// (sr, sc) or (er, ec) are not valid empty grid positions or course is not syntactically valid
	if (sr > getRows() || sr <= 0 ||
		er > getRows() || er <= 0 ||
		sc > getCols() || sc <= 0 ||
		ec > getCols() || ec <= 0 ||
		isWall(sr, sc) || isWall(er, ec) || 
		!isCourseWellFormed(course))
		return 2;

	// (sr, sc) and (er, ec) are valid empty grid positions and course is syntactically valid
	
	const int zero = '0'; // initialising zero to store the encoding for '0'

	int cr = sr; int cc = sc; // intialising integers cr (current row) and cc (current column)

	int n_steps = 0; // total number of steps taken in course
	int status = 1; // default status - indicates course was successfuly completed

	// determining segments
	for (size_t i = 0; i < course.size(); i++) {

		// -------------------------------------------
		// testing whether ch is a direction character
		if (isalpha(course[i])) {

			string segment = ""; // if ch is a direction character, initialise segment with the character (in lowercase)
			char dir = tolower(course[i]); // initialising dir with the direction character
			segment += dir; // adding the direction character to segment

			// testing the characters after direction character to complete the segment
			for (size_t k = i + 1; k < course.size(); k++) {

				if (isdigit(course[k])) // if next character is a digit, add it to segment
					segment += course[k];
				else // if next character isn't a digit, segment ends
					break;
			}
				
			// -----------------------------------------------------------------------
			// going through the segment to make the appropriate movements on the grid
				
			int steps = 0; 

			if (segment.length() == 1) { // no digit characters
				if (driveSegment(cr, cc, dir, 1) == 1) {
					steps = 1;
				}
				else {
					status = 0; // course failed
					break;
				}
			}
			// number of steps specified in segment
			else {
					
				int maxSteps = 0; // initialising maxSteps to represent the number of steps the segment requests

				switch (segment.length()) {
				// only one digit character
				case 2: maxSteps = segment[1] - zero; 
					break;
				// two digit characters
				case 3: maxSteps = (segment[1] - zero) * 10 + (segment[2] - zero);
				}

				steps = driveSegment(cr, cc, dir, maxSteps);
					// driveSegment() could not return negative one, since maxSteps > 0 and cr, cc, dir are all valid
				if (steps < maxSteps)
					status = 0; // course failed; cannot move the number of steps specified in course segment
			}
			n_steps += steps; // adding to total steps taken so far

			// updating (cr, cc)
			if (dir == 'n')
				cr -= steps;
			else if (dir == 's')
				cr += steps;
			else if (dir == 'e')
				cc += steps;
			else if (dir == 'w')
				cc -= steps;
			
			if (status == 0)
				break;
		}
	}		

	nsteps = n_steps; // updating nsteps with the number of steps moved

	if (status == 0) // course could not be completed	
		return 3;
	else // course was completed
		if (cr == er && cc == ec) // course finished at end position
			return 0;
		else // course did not finish at end position
			return 1;
}

int driveSegment(int r, int c, char dir, int maxSteps) {
	// if r or c exceed the dimensions of the grid, return -1
	if (r > getRows() || r <= 0 || c > getCols() || c <= 0 ||
		isWall(r, c) || maxSteps < 0) // wall at (r, c) or negative maxSteps
		return -1;

	int possible_steps = 0;
	dir = tolower(dir);

	if (dir == 'n') // north
		possible_steps = driveSegmentNorth(r, c);
	else if (dir == 's') // south
		possible_steps = driveSegmentSouth(r, c);
	else if (dir == 'e') // east
		possible_steps = driveSegmentEast(r, c);
	else if (dir == 'w') // west
		possible_steps = driveSegmentWest(r, c);
	else // invalid direction character
		return -1;

	// returning the number of steps
	if (possible_steps >= maxSteps)
		return maxSteps;
	else
		return possible_steps;
}

bool isCourseWellFormed(string course) {

	// testing whether all of the characters are digits or direction characters (n, s, e, w)
	for (size_t i = 0; i < course.size(); i++) {
		char ch = course[i];
		if (tolower(ch) != 'n' && tolower(ch) != 's' && tolower(ch) != 'e' && tolower(ch) != 'w' && !isdigit(ch))
			return false;
	}

	// testing whether the first character is a letter
	if (isdigit(course[0]))
		return false;

	for (size_t i = 0; i < course.size(); i++) {

		string segment;
		char ch = course[i];

		// testing whether ch is a direction character
		if (tolower(ch) == 'n' || tolower(ch) == 's' || tolower(ch) == 'e' || tolower(ch) == 'w') {

			segment = ch; // if ch is a direction character, initialise segment with the character

			// testing the characters after direction character
			for (size_t k = i + 1; k < course.size(); k++) {

				if (isdigit(course[k])) // if next character is a digit, add it to segment
					segment += course[k];
				else // if next character isn't a digit, segment ends
					break;
			}
			if (segment.size() > 3) // if segment longer than three characters, syntactically invalid
				return false;
		}
	}
	return true;
}

int driveSegmentNorth(int r, int c) {
	for (int i = 1; i < r; i++)
		if (isWall(r - i, c))
			return i - 1; // when (r - i, c) has a wall, only i - 1 steps possible 
	return r - 1; // if no wall when going north, can move r - 1 steps
}
int driveSegmentSouth(int r, int c) {
	for (int i = 1; r + i <= getRows(); i++)
		if (isWall(r + i, c))
			return i - 1; // when (r + i, c) has a block, only i - 1 steps are possible
	return getRows() - r; // if no wall when going south, can move getRows() - r steps
}
int driveSegmentEast(int r, int c) {
	for (int i = 1; c + i <= getCols(); i++)
		if (isWall(r, c + i))
			return i - 1; // when (r, c + i) has a block, can only have taken i - 1 steps
	return getCols() - c; // if no wall when going east, can move getCols() - c steps
}
int driveSegmentWest(int r, int c) {
	for (int i = 1; i < c; i++)
		if (isWall(r, c - i))
			return i - 1; // when (r, c - i) has a block, can only have taken i - 1 steps
	return c - 1; // if no wall when going west, can move c - 1 steps
}