#ifndef GAMESTARTER_H
#define GAMESTARTER_H

#include "all.h"

class GameStarter
{
private:
    Tournament tournament;//points to a tournament
public:

    //Creates a game
    void startGame();

    //creates a game that starts from a certain point for testing
    void testGame();
    //ends the game
    void quitGame();

};
#endif // GAMESTARTER_H
