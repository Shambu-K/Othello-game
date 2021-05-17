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
        
    system("bash src/press_any_key_to_continue.sh");
        return 0;
        
    
}
