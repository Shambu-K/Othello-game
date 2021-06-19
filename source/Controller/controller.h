#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "Model/board.h"
#include "View/game_play_ui.h"
#include "CommonTypes.h"
#include "AI/NoAI.h"
#include "AI/GreedyAI.h"


class Controller
{
    public:
    piece currentPLayer = piece::BLACK;
    OthelloBoard model;
    GameplayGUI view;
    AI* AIplayer;
    void connect_bitmap_buttons();
    void connect_other_buttons(); 
    void updateGameState(std::pair<unsigned int, unsigned int> coord);
    void AIPlay(OthelloBoard board);
    sf::Clock blackTimer, whiteTimer;
    Controller(int options);
    void decideAI(int options);
};


#endif