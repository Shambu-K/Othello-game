#include "game.h"
#include <iostream>
#include <fmt/core.h>
#include <curses.h>
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
    print("\nPress a key to continue...");
    getch();
}
