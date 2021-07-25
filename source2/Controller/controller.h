#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <optional>

#include "Model/board.h"
#include "View/game_play_cli.h"
#include "CommonTypes.h"
#include "AI/NoAI.h"
#include "AI/GreedyAI.h"
#include "AI/RandomAI.h"

/**
 * @brief This class is the controller of the application. It integrates model and 
 * the view of the application. It also takes input from the user and passes information to the model.
 */

class Controller
{
    public:
    piece currentPLayer = piece::BLACK;
    OthelloBoard model;
    GameplayGUI view;
    AI* AIplayer;
    unsigned int boardSize = model.boardSize;
    // void connect_bitmap_buttons();
    // void connect_other_buttons(); 
    void updateGameState(std::pair<unsigned int, unsigned int> coord);
    void AIPlay(OthelloBoard board);
    std::optional<std::pair<unsigned int, unsigned int>> getInput();
    std::pair<unsigned int, unsigned int> getMove();
    void gameloop();
    Controller(int options);
    void pass();
    void decideAI(int options);
};


#endif
