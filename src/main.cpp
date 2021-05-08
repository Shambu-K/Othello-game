#include "game.h"
#include <iostream>
#include <fmt/core.h>

#define print fmt::print
int main()
{
    
    OthelloGame game;
    game.initializeGame(false, false);
    while(!game.checkGameOver())
    {
        game.makeMove(color::_BLACK);
        game.makeMove(color::_WHITE);
    }
        //Add neccessary code here
        print("\nPress any key to continue:");
        __CONIO_H obj1;
        obj1.getch();
        obj1.getch();
    
}
