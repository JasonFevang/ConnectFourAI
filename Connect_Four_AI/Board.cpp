#include "all.h"

//pre-condition: board with at least one play
//post-condition: 1 newlines to refresh the console
void clearScreen()
{
//cout << string( 1, '\n' );
	cout << "\n";
}

//default constructor
Board::Board()
{
    getBoardParam();

    board = new Player**[height];
    for(int i=0;i<height;i++)
    {
        board[i] = new Player*[width];
    }
    clearBoard();//Fill board with nullptr
}

//deletes each pointer from the board
Board::~Board()
{
    for(int i=0;i<height;i++)
    {
//        for(int j=0;j<width;j++)
//        {
//            if(board[i][j]!=nullptr)
//                delete board[i][j];
//        }
        delete board[i];
    }
    delete board;
}

//copy constructor
Board::Board(const Board& otherBoard) : width(otherBoard.width), height(otherBoard.height), connectLength(otherBoard.connectLength)
{
    board = new Player**[height];//calling object's board member variable is set to a new board
    for(int i=0;i<height;i++)
    {
        board[i] = new Player*[width];
    }
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            board[i][j] = otherBoard.board[i][j];//calling object's board is set equal to the board being copied
        }
    }
}



//Overloaded assignment operator to do a deep copy of class Board to another class Board
Board & Board::operator=(Board const &otherBoard)
{
    //Copy over Board paramaters
    height = otherBoard.height;
    width = otherBoard.width;
    connectLength = otherBoard.connectLength;

    //create new board
    board = new Player**[height];
    for(int i=0;i<height;i++)
    {
        board[i] = new Player*[width];
    }
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            board[i][j] = otherBoard.board[i][j];//calling object's board is set equal to the board being copied
        }
    }
	return *this;
}

//pre-condition: board
//post-condition: resets board to all empty
void Board::clearBoard()
{
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            board[i][j] = nullptr;
        }
    }
}

//pre-condition: board with at least one play on it
//post-condition: tells whether the latest play resulted in a connect four
bool Board::winDetect(int col, Player *player)
{
    int row = height-1;
    while(row>=0&&(board[row][col]!=nullptr)){row--;}//finds first Empty square in col
    row++;//so it is the index of the top play, not the first zero space
    if(board[row][col] != player)//Check if initial square works
        return false;
    else if(checkConnect(row, col, bottomDir, player) >= connectLength ||//check if squares in all directions work
       checkConnect(row, col, bottomLeftDir, player)+checkConnect(row, col, topRightDir, player)-1 >= connectLength ||//subtract one to account for the double count on the inital square
       checkConnect(row, col, bottomRightDir, player)+checkConnect(row, col, topLeftDir, player)-1 >= connectLength ||//subtract one to account for the double count on the inital square
       checkConnect(row, col, rightDir, player)+checkConnect(row, col, leftDir, player)-1 >= connectLength)
    {
        return true;
    }
    else
        return false;
}

//pre-condition: board with at least one play
//post-condition: returns the number of consecutive spaces occupied by
                //one player in a given direction from a starting square
int Board::checkConnect(int row, int col, const int direction[], Player *player)
{
    if(checkDimensions(row+direction[0], col+direction[1]) && (board[row+direction[0]][col+direction[1]] == player))
        return(checkConnect(row+direction[0], col+direction[1], direction, player)+1);
    else
        return 1;
}

//pre-condition: board with at least one play
//post-condition: returns true if the anticipated play results in a play
                //within board dimensions
bool Board::checkDimensions(int row, int col)
{
    return(row>=0 && row<height && col>=0 && col<width);
}

//pre-condition: Board is being constructed
//post-condition: Paramaters for new Board
void Board::getBoardParam()
{
    char autoGen;//Character used to collect user's input

    do//retrive user's input until it is a 'y' or 'n'
    {
        cout << "Custom Board? (y/n)";
        cin >> autoGen;
    }while(autoGen != 'n' && autoGen != 'y');

    if(autoGen == 'n')
    {
        width = 7;
        height = 6;
        connectLength = 4;
    }
    else
    {
        cout << "Height: ";
        do
        {
            height = (int)(_getch()-'0');
        }while(height<1 || height>maxHeight);
        cout << height << endl;

        cout << "Width: ";
        do
        {
            width = (int)(_getch()-'0');
        }while(width<1 || width>maxWidth);
        cout << width << endl;

        cout << "Connect Length: ";
        do
        {
            connectLength = (int)(_getch()-'0');
        }while(connectLength<1 || connectLength>maxConnectLength);
        cout << connectLength << endl;
//        do//get user's input until it is within range
//        {
//            cout << "Width: ";
//            width = __getch();
//        }while(width<1 || width>maxWidth);
//        do//get user's input until it is within range
//        {
//            cout << "Connect Length: ";
//            connectLength = __getch();
//        }while(connectLength<1 || width>maxConnectLength);
        cout << endl << endl;
    }
}

//pre-condition: constructed board
//post-condition: board with the lowest empty row at the given column
                //replaced with the player's identifier
void Board::playCol(int col, Player *player)
{
    int row = height-1;
    while(row>=0&&(board[row][col]!=nullptr)) {row--;}//finds first Empty square in col
    board[row][col]=player;//place player at that row and column
}

//returns true if the board is completely filled up
bool Board::isTie()
{
    for(int i=0;i<width;i++)
    {
        if(board[0][i]==nullptr)
            return false;
    }
    return true;
}
//Pre-condition: constructed board
//Post-condition: all values stored in the board are printed to the screen
void Board::printBoard()
{
    clearScreen();
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(board[i][j]==nullptr)
                cout << "--" << " ";
            else
                cout << (board[i][j])->getToken() << (board[i][j])->getToken() << " ";
        }
        cout << endl;
        for(int j=0;j<width;j++)
        {
            if(board[i][j]==nullptr)
                cout << "--" << " ";
            else
                cout << (board[i][j])->getToken() << (board[i][j])->getToken() << " ";
        }
        cout << endl<<endl;
    }
    cout << endl;
}

//Pre-condition: constructed board
//Post-condition: all values stored in the board are printed to the screen
//void Board::printBoard()
//{
//    clearScreen();
//    for(int i=0;i<height;i++)
//    {
//        for(int j=0;j<width;j++)
//        {
//            if(board[i][j]==nullptr)
//                cout << "-";
//            else
//                cout << (board[i][j])->getToken();
//        }
//        cout << endl;
//    }
//    cout << endl;
//}


