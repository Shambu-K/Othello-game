#include "game.h"
#include <iostream>
int main()
{
    
    OthelloGame game;
    game.initializeGame(false, false);
    while(!game.checkGameOver())
    {
        game.makeMove(color::_BLACK);
        game.makeMove(color::_WHITE);
    }
    std::cout << "Game ended Successfully!\n";
}
