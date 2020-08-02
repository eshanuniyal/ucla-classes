#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Arena;

///////////////////////////////////////////////////////////////////////////
// Player class definition
///////////////////////////////////////////////////////////////////////////

class Player
{
public:
    // Constructor
    Player(Arena* ap, int r, int c);

    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

    // Mutators
    std::string dropPoisonVial();
    std::string move(int dir);
    void   setDead();

private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

#endif