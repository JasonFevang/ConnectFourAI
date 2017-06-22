#include "all.h"

User::User(Board *board)
{
    pboard = board;//Dependancy injection
}

void User::chooseToken()
{
    cout << "Enter any character to be your player token: ";
    token = _getch();
    cout << endl << endl << "You choose '" << token << "'" << endl;
}

int User::chooseCol()
{
    char input;//User's input for playing
    int chosenCol = 0;
    do
    {
        input = _getch();
        if(input == 'x')//To exit
            exit(1);

        else if(input == 'u')//To undo previous move(s), only if it isn't the first play
            return -1;

        else chosenCol = input-'0'-1;//convert input to int corrosponding to column number
        //Get uesr inut again if chosen column is out of range or the chosen column is full
    }while(chosenCol<0 || chosenCol>(pboard->getWidth()-1) || pboard->getBoard()[0][chosenCol]!=nullptr);
    return chosenCol;
}
