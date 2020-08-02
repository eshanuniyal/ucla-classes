#ifndef HISTORY_H
#define HISTORY_H

#include "globals.h"

class Arena;

///////////////////////////////////////////////////////////////////////////
//  History class definition
///////////////////////////////////////////////////////////////////////////

class History{	
	// corresponds to an Arena with nRows rows and nCols columns

	public:
		History(int nRows, int nCols);
		bool record(int r, int c);
		void display() const;
	private:
		int m_grid[MAXROWS][MAXCOLS];
		int m_rows;
		int m_cols;	
};

#endif