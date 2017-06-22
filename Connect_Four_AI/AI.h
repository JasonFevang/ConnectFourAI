#ifndef AI_H
#define AI_H

#include "all.h"

const int maxLevel = 8;

class AI: public Player
{
private:
    char token;//Character holding the token that is played on each turn
    Board *pboard;//pointer to board being played on
    Player *opponent;//Holds opponent so AI can "see" opponent plays
    int level;//Number of turns AI looks ahead
    bool first;//true if AI is the first player
public:
    int middle(int col, int bestCol);//if two columns are the same value, chooses the column that is closest to the middle
    int miniMax(int col, int depth, Player* maximizingPlayer, Board &prevBoard);//chooses the best column based on given heuristics
    bool isWinSpot(int col, int row, Player *player);
    int heuristicValue(Board &testBoard);//returns a huristicValue rating the current board

    AI(Board *board);
    void levelSelect();
    int chooseCol();
    void chooseToken();
    char getToken() {return token;}
    void setOpponent(Player *opp) {opponent = opp;}
    void setFirst(Player *firstPlay) {first = firstPlay == this;}
    void setToken(const char &token) {this->token = token;}//sets player's token to function paramater

};
#endif // AI_H
