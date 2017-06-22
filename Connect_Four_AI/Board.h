#ifndef BOARD_H
#define BOARD_H

#include "all.h"

//Storage of directions for checking for a connection
const int bottomDir[2] = {1, 0};
const int bottomLeftDir[2] = {1, -1};
const int bottomRightDir[2] = {1, 1};
const int rightDir[2] = {0, 1};
const int leftDir[2] = {0, -1};
const int topRightDir[2] = {-1, 1};
const int topLeftDir[2] = {-1, -1};

//board paramater limits
const int maxHeight = 50;
const int maxWidth = 9;
const int maxConnectLength = 50;

class Board
{
private:
    int width;
    int height;
    int connectLength;//Number of consecutive plays to result in a win
    Player*** board;//2d array of pointers to Player types
public:
    //default constructor
    Board();

    //deletes each pointer from the board
    ~Board();

    //Constructs a board of defined width and height
    Board(const Board& boardCopy);

    //overloaded assignment operator for copy constructor
    Board & operator=(const Board& otherBoard);

    //pre-condition: board
    //post-condition: resets board to all empty
    void clearBoard();

    //Pre-condition: constructed board
    //Post-condition: all values stored in the board are printed to the screen
    void printBoard();

    //pre-condition: board with at least one play on it
    //post-condition: tells whether the latest play resulted in a connect four
    bool winDetect(int col, Player *player);

    //pre-condition: board with at least one play
    //post-condition: returns the number of consecutive spaces occupied by
                    //one player in a given direction from a starting square
    int checkConnect(int row, int col, const int direction[], Player *player);

    //pre-condition: board with at least one play
    //post-condition: returns true if the anticipated play results in a play
                    //within board dimensions
    bool checkDimensions(int row, int col);

    //pre-condition: Board is being constructed
    //post-condition: Paramaters for new Board
    void getBoardParam();

    //pre-condition: constructed board
    //post-condition: board with the lowest empty row at the given column
                    //replaced with the player's identifier
    void playCol(int col, Player *player);

    //returns true if the board is completely filled up
    bool isTie();
    //returns width of board
    int getWidth() const {return width;}

    //returns height of board
    int getHeight() const {return height;}

    //returns connectLength of board
    int getConnectLength() const {return connectLength;}
    //returns a pointer to the current board
    Player*** getBoard() const {return board;}

};

#endif // BOARD_H
