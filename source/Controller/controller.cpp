#include "controller.h"
#include <iostream>
Controller::Controller() : model(), view(DEFAULT_BOARD_SIZE)
{
    connect_bitmap_buttons();
}

void Controller::connect_bitmap_buttons()
{
    model.registerObserver(&view);

    for(unsigned int i = 0; i<DEFAULT_BOARD_SIZE; i++)
    {
        for(unsigned int j = 0; j<DEFAULT_BOARD_SIZE; j++)
        {
            view.cellButtons[i][j]->onPress([=]() {
                
                if(model.placeMove(std::make_pair(i, j)))
                {
                    model.updateBoard();
                    model.notifyObservers();
                }
                });
        }
    }
    
    view.gui2.mainLoop();
}

