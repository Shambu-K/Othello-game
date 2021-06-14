#include "controller.h"
#include <iostream>
Controller::Controller() : model(), view(DEFAULT_BOARD_SIZE)
{
    model.registerObserver(&view);
    view.updateBoard(model.boardConfiguration);
    view.updateMoveHistory(piece::EMPTY, "");
    view.updateScore(model.blackScore, model.whiteScore);
    connect_bitmap_buttons();
    connect_other_buttons();
    view.gui2.mainLoop();
}

void Controller::connect_bitmap_buttons()
{

    for(unsigned int i = 0; i<DEFAULT_BOARD_SIZE; i++)
    {
        for(unsigned int j = 0; j<DEFAULT_BOARD_SIZE; j++)
        {
            view.cellButtons[i][j]->onPress([=]() {
                
                if(model.placeMove(std::make_pair(i, j)))
                {
                    pass_count = 0;
                    model.updateBoard();
                    model.notifyObservers();
                    model.switchPlayer();
                }
                });
        }
    }
}

void Controller::connect_other_buttons()
{
    view.passButton->onPress([&]() {
        pass_count++;
        model.movePassed();
        model.updateBoard();
        if(pass_count==2)
        {
            model.message = 3;
        }
        model.notifyObservers();
        model.switchPlayer();
    });

    view.quitButton->onPress([&]() {
        view.window2.close();
    });
}