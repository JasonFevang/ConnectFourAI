#include "all.h"

AI::AI(Board *board)
{
    pboard = board;//Dependancy injection
    levelSelect();
}

void AI::levelSelect()
{
    level = 4;
    return;
    cout << "Enter AI level(1 - 6): ";
    do
    {
        level = (int)(_getch()- '0');
    }while(level<1 && level>maxLevel);
    cout << level << endl << endl;
}
void AI::chooseToken()
{
    cout << "Enter AI token: ";
    token = _getch();
    cout << endl << endl << "You choose '" << token << "'" << endl;
}

int AI::chooseCol()
{
    int bestValue = -10000;//heuristic value the current best board. Higher is better
    int *value = new int[pboard->getWidth()];//Heuristic values of each column of current board
    int bestCol=0;//column which results in the least amount of success for the opponent
    for(int col=0;col<pboard->getWidth();col++)
    {
        if(pboard->getBoard()[0][col]==nullptr)//if the column can be played in
        {
            Board newBoard(*pboard);//duplicate current board into newBoard
            newBoard.playCol(col, this);//play in newBoard
            value[col] = miniMax(col, level, this, newBoard);//determine the heuristic value of that play

            if(value[col]>bestValue)//if the play is better than all the others, store it in bestValue
            {
                bestValue = value[col];
                bestCol = col;
                //cout << "\nbestCol= " << bestCol << "=" << col << endl;
            }
            else if(value[col]==bestValue)
                bestCol = middle(col, bestCol);
        }
    }
    for(int i=0;i<pboard->getWidth();i++)//Outputs hueristic value of all columns
    {
        if(pboard->getBoard()[0][i]==nullptr)//if the column can be played in
        {
            cout << "column " << i << "is " << value[i] << endl;
        }
        else
            cout << "column " << i << "is Full" << endl;
    }
    delete[] value;
    return bestCol;
}

//if two columns are the same value, chooses the column that is closest to the middle
int AI::middle(int col1, int col2)
{
//double everything so no need for decimals, still returns nearest column
    int middleCol, col1Dist, col2Dist;
    middleCol = pboard->getWidth()-1;//subtract 1 to account for starting from 0
    col1Dist = abs(2*col1-middleCol);//distance from col1 to middle column
    col2Dist = abs(2*col2-middleCol);//distance from col2 to middle column
    if(col1Dist>col2Dist)
        return col2;
    else return col1;//if they are the same, it doesn't matter which one is returned
}
//chooses the best column based on given heuristics
int AI::miniMax(int col, int depth, Player* maximizingPlayer, Board &prevBoard)
{
    int value = 0;
    int bestValue = 0;
    if(depth == 0)
        return heuristicValue(prevBoard);
        //return heuristicValue(prevBoard);
    //cout << "depth: " << depth << "   " << maximizingPlayer->getToken();
    //prevBoard.printBoard();

    if(prevBoard.winDetect(col, opponent))
    {
        //cout << "loss\n";
        return -10000; //guaranteed loss
    }
    if(prevBoard.winDetect(col, this))
    {
        //cout << "win\n";
        return 10000; //guaranteeed win
    }
    if(prevBoard.isTie())
    {
        //cout << "tie\n";
        return 0;
    }
    if(maximizingPlayer == this)
    {
        bestValue = 100000;
        for(int col=0;col<prevBoard.getWidth();col++)
        {
            if(prevBoard.getBoard()[0][col]==nullptr)//if that column is not full
            {
                Board newBoard(prevBoard);
                newBoard.playCol(col, opponent);
                value = miniMax(col, depth-1, opponent, newBoard);
                //cout << "value" << depth << ": " << value << endl;
                if(value<bestValue)
                {
                    bestValue = value;
                    //cout << " is now bestValue.\n";
                }
            }
        }
    }
    else
    {
       bestValue = -100000;
        for(int col=0;col<prevBoard.getWidth();col++)
        {
            if(prevBoard.getBoard()[0][col]==nullptr)//if that column is not full
            {
                Board newBoard(prevBoard);
                newBoard.playCol(col, this);
                value = miniMax(col, depth-1, this, newBoard);
                //cout << "value" << depth << ": " << value;
                if(value>bestValue)
                {
                    bestValue = value;
                    //cout << " is now bestValue.\n";
                }
            }
        }
    }
    return bestValue;
}

int AI::heuristicValue(Board &testBoard)//returns a huristicValue rating the current board
{
    Player *colWinner = this;
    int heuristicValue = 0;
//    for(int col=0;col<testBoard.getWidth();col++)//iterate through columns
//    {
//        for(int row=testBoard.getHeight()-1;row>-1;row--)//iterate through rows from the bottom
//        {
//            if(testBoard.getBoard()[row][col]==nullptr)//if current board spot is empty
//            {
//                if(isWinSpot(col, row, this))//if this is a winspot for AI
//                {
//                    heuristicValue++;
//                }
//                else if(isWinSpot(col, row, opponent))
//                {
//                    heuristicValue--;
//                }
//            }
//        }
//    }

    for(int col=0;col<testBoard.getWidth();col++)//iterate through columns
    {
        for(int row=testBoard.getHeight()-1;row>-1&&colWinner!=nullptr;row--)//iterate through rows from the bottom
        {
            if(testBoard.getBoard()[row][col]==nullptr)//if current board spot is empty
            {
                if(isWinSpot(col, row, this))//if this is a winspot for AI
                {
                    if((testBoard.getHeight()-row)%2==(int)first)//if this is an odd row if first is true, or even if first is false
                    {
                        heuristicValue += 499;
                        colWinner = this;
                    }
                    else
                        heuristicValue += 99;
                }
                else if(isWinSpot(col, row, opponent))//if this is a winspot for AI
                {
                    if((testBoard.getHeight()-row)%2==(int)(!first))//if this is an odd row if first is true, or even if first is false
                    {
                        heuristicValue += -499;
                        colWinner = opponent;
                    }
                    else
                        heuristicValue += -99;
                }
            }
        }
    }

    return heuristicValue;
}

bool AI::isWinSpot(int col, int row, Player *player)
{
    if(pboard->checkConnect(row, col, bottomLeftDir, player)+pboard->checkConnect(row, col, topRightDir, player)-1 >= pboard->getConnectLength() ||//subtract one to account for the double count on the inital square
       pboard->checkConnect(row, col, bottomRightDir, player)+pboard->checkConnect(row, col, topLeftDir, player)-1 >= pboard->getConnectLength() ||//subtract one to account for the double count on the inital square
       pboard->checkConnect(row, col, rightDir, player)+pboard->checkConnect(row, col, leftDir, player)-1 >= pboard->getConnectLength())
        return true;
    else
        return false;
}
