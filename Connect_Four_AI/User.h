#ifndef USER_H
#define USER_H

#include "all.h"

class User: public Player
{
private:
    char token;
    Board *pboard;//pointer to object board holding current board values
    Player *opponent;
    bool first;
public:
    //default constructor
    User(Board *board);
    int chooseCol();
    void chooseToken();
    char getToken() {return token;}
    void setOpponent(Player *opp) {opponent = opp;}
    void setFirst(Player *firstPlay) {first = firstPlay == this;}
    void setToken(const char &token) {this->token = token;}//sets player's token to function paramater

};
#endif // USER_H
