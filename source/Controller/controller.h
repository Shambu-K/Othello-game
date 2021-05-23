#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "Model/board.h"
#include "View/game_play_ui.h"
#include "CommonTypes.h"
class Controller
{
    public:
    piece currentPLayer = piece::BLACK;
    OthelloBoard model;
    GameplayGUI view;
    void connect_bitmap_buttons();
    void connect_nlm_ok_button(); 
    Controller();
};


#endif