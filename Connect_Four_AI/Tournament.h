#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "all.h"

class Tournament
{
private:
    int numP1Wins;
    int numP2Wins;
    int numTies;
    int numMatches;
    int winLimit;//Number of wins needed to win tournament
    Player *firstPlay;//Who goes first for the next match
    Player *P1;//pointer to player 1
    Player *P2;//pointer to player 2
    Board board;//board holding all the plays so far in the match
public:
    //default constructor
    Tournament();//board is constructed/declared here

    //destructor
    ~Tournament();

    //Plays a tournament
    void playTournament();

    //Plays a single match
    Player* playMatch();

    //selects and sets player settings
    void playerSelect();

    //selects and sets player settings without any output or user input
    void playerSelectNoOutput();

    //Choose how many wins to play to
    void winLimitSelect();

    //Returns winLimit
    int getWinLimit() const {return winLimit;}

    //Switches firstPlay to P2 if P1 and vice versa
    void alternateTurn(Player **turn);

    //Prints the winner of the match
    void printWinner(Player *winner);
};
#endif // TOURNAMENT_H
