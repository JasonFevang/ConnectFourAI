#include "all.h"
#include <iostream>

using namespace std;

//default constructor
Tournament ::Tournament() : numP1Wins(0), numP2Wins(0), numTies(0), numMatches(0), winLimit(0){}

Tournament::~Tournament(){}

//Plays a tournament
void Tournament::playTournament()
{
    Player *winner;
    cout << "****Tournament Started****\n'x': Exit during gameplay\n'u' Undo the previous play";
    while(numP1Wins<winLimit && numP2Wins<winLimit)
    {
        alternateTurn(&firstPlay);

        board.clearBoard();//Clears the board for the next match

        winner = playMatch();//Play match then increment corrsponding incrementer
        if(winner == P1)
            numP1Wins++;
        else if(winner == P2)
            numP2Wins++;
        else
            numTies++;

        cout << "Player 1 wins: " << numP1Wins << "      Player 2 wins: " << numP2Wins << "      Ties: " << numTies << endl << endl << endl;

        if(numP1Wins>=winLimit)
            cout << "********Player one wins tournament********" << endl << endl;
        else if(numP2Wins>=winLimit)
            cout << "********Player two wins tournament********" << endl << endl;
        else
        {
            cout << "Press any key to continue to the next match" << endl;
            if(_getch() == 'x')
                exit(1);
            numMatches++;
        }
    }
    cout << "press any key to exit";
    _getch();
}

//Plays a single match
Player* Tournament::playMatch()
{
    Player *turn = firstPlay;//Who plays the next move, initialized to firstPlay
    Player *winner = nullptr;//Who wins the match
    int numPlays = 0;//increments after every player's turn
    int *prevPlay = new int[board.getWidth()*board.getHeight()];//array storing all previous plays, used for undo function
    int play = 0;//chosen column, from 1 to width

    board.printBoard();//print empty board initially

    P2->setFirst(firstPlay);
    P1->setFirst(firstPlay);
    while(winner == nullptr && numPlays<board.getWidth()*board.getHeight())//alternate turns until the end of the game
    {
        do
        {
            play = turn->chooseCol();//get column to be played from whoever's turn it is
        }while(numPlays<1&&play==-1);//Ensure that undo is not called on the first turn
        //if(play==-1)
            //undoCol();
        //else
            board.playCol(play, turn);//play that column with that turn's token

        if(board.winDetect(play, turn))//If that play resulted in a win
            winner = turn;
        prevPlay[numPlays] = play;//store previous play
        numPlays++;//increment number of plays
        alternateTurn(&turn);
        board.printBoard();
    }

    if(winner!=nullptr)
        printWinner(winner);
    else
        cout << "It's a tie" << endl;
    return winner;
}

//selects and sets player settings
void Tournament::playerSelect()
{
    int playerSelector;
    cout << endl << "Player1 is:" << endl << "(1)User" << endl << "(2)AI" << endl << "enter (1) or (2)" << endl;
    do{
    playerSelector = _getch();
    }while(playerSelector != '1' && playerSelector != '2');

    if(playerSelector == '1')
    {
        P1 = new User(&board);//of type User
        cout << "Player 1 is a user" << endl;
    }
    else
    {
        P1 = new AI(&board);//of type AI
        cout << "Player 1 is an AI" << endl;
    }
    //P1->chooseToken();
    P1->setToken(219);

    do{
    cout << endl << "Player2 is:" << endl << "(1)User" << endl << "(2)AI" << endl << "enter (1) or (2)" << endl;
    playerSelector = _getch();
    //playerSelector = '2';
    }while(playerSelector != '1' && playerSelector != '2');

    if(playerSelector == '1')
    {
        P2 = new User(&board);//of type User
        cout << "Player 2 is a user" << endl;
    }
    else
    {
        P2 = new AI(&board);//of type AI
        cout << "Player 2 is an AI" << endl;
    }

//    do
//    {
//        P2->chooseToken();
//    }while(P2->getToken() == P1->getToken());//Ensure that Player2 token does not equal Player1 token
    P2->setToken(176);
    firstPlay = P1;//choose player 1 to go first for first game
    P1->setOpponent(P2);//Ensure each player knows what it's opponent "looks like" on the board
    P2->setOpponent(P1);
}

void Tournament::playerSelectNoOutput()
{
    int playerSelector;
    P1 = new User(&board);//of type User
    P1->setToken(219);

    P2 = new AI(&board);//of type User
    P2->setToken('O');
    firstPlay = P1;//choose player 1 to go first for first game
    P1->setOpponent(P2);//Ensure each player knows what it's opponent "looks like" on the board
    P2->setOpponent(P1);
}

//Choose how many wins to play to
void Tournament::winLimitSelect()
{
    cout << endl << "First to ___ wins: (insert number) ";
    do
    {
        winLimit = int(_getch()-'0');
    }while(winLimit<1);
    cout << endl << "You chose first to  " << winLimit << "  wins:" << endl;
}

void Tournament::alternateTurn(Player **turn)
{
    if(*turn == P2)
        *turn = P1;
    else
        *turn = P2;
}
void Tournament::printWinner(Player *winner)
{
    cout << "Player ";
    if(winner == P1)
        cout << "1";
    else
        cout << "2";
     cout << "(" << winner->getToken() << ") wins!" << endl;
}
