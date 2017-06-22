#include <iostream>
#include "all.h"
using namespace std;

int main()
{
    cout << "hello world";
    GameStarter creator;
    int playThrough[10] = {4, 4, 4, 3, 3, 1, 1, 1, 1, 4};
    creator.startGame();
    //creator.testGame(playThrough);
    return 0;
}
