#include "all.h"

using namespace std;


//Creates a game
void GameStarter::startGame()
{
    tournament.playerSelect();
    tournament.winLimitSelect();
    if(tournament.getWinLimit() == 1)
        tournament.playMatch();
    else tournament.playTournament();
}

void GameStarter::testGame()
{
    tournament.playerSelectNoOutput();
    tournament.playMatch();
}
//Quits a game
void GameStarter::quitGame()
{
    char gameQuitAnswer;
    cout << "Quit game?(y/n): ";
    do
    {
        gameQuitAnswer = _getch();
        if(gameQuitAnswer == 'y')
        {
            cout << endl << "Game Over: No winner" << endl << "Press any key to exit: ";
            _getch();
            exit(1);
        }
        else if(gameQuitAnswer == 'n')
        {
            //somehow go back
            cout << "got emmm" << endl;
        }
    }while(gameQuitAnswer != 'n' || gameQuitAnswer != 'y');
}
