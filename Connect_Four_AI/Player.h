#ifndef PLAYER_H_
#define PLAYER_H_

#include "all.h"

class Player
{
protected:
    //Board *pboard;
public:
    virtual int chooseCol() = 0;//dtermines the player's choice of column
    virtual char getToken() = 0;//returns the player's token
    virtual void chooseToken() = 0;//allows player to choose which character is used to represent them on the board
    virtual void setOpponent(Player *opp) = 0;//stores a pointer to the opponent
    virtual void setFirst(Player *firstPlay) = 0;//chooses whether a player is the first player for that match or not
    virtual void setToken(const char &token) = 0;//sets player's token to function paramater
};

#endif // PLAYER_H_INCLUDED
