#include "controller.h"
#include <iostream>

Controller::Controller(int options) : model(), view(DEFAULT_BOARD_SIZE)
{
    decideAI(options);
    model.registerObserver(&view);
    view.updateBoard(model.boardConfiguration);
    view.updateMoveHistory(piece::EMPTY, "");
    view.updateScore(model.blackScore, model.whiteScore);
    connect_bitmap_buttons();
    connect_other_buttons();
    // view.gui2.mainLoop();
    while(view.window2.isOpen())
    {
        sf::Event event;
        while (view.window2.pollEvent(event))
        {
        view.gui2.handleEvent(event);

        if (event.type == sf::Event::Closed)
            view.window2.close();
        }
        view.window2.clear();
        view.gui2.draw();
        view.window2.display();
    }
}

void Controller::decideAI(int options)
{
    switch(options)
    {
        case 1 : AIplayer = new NoAI();         break;
        // case 2 : AIplayer = new RandAI();       break;
        case 3 : AIplayer = new GreedyAI();     break;
        // case 4 : AIplayer = new MinimaxAI();    break;
        default : AIplayer = new NoAI();
    }
}

void Controller::connect_bitmap_buttons()
{

    for(unsigned int i = 0; i<DEFAULT_BOARD_SIZE; i++)
    {
        for(unsigned int j = 0; j<DEFAULT_BOARD_SIZE; j++)
        {
            view.cellButtons[i][j]->onPress([=]() {
                
                if(model.isLegal(std::make_pair(i, j)))
                {
                    updateGameState(std::make_pair(i, j));
                    AIPlay(model);
                }
                });
        }
    }
}

void Controller::connect_other_buttons()
{
    view.passButton->onPress([&]() {
        model.pass_count++;
        model.movePassed();
        model.updateBoard();
        if(model.pass_count==2)
        {
            model.message = 3;
        }
        model.notifyObservers();
        model.switchPlayer();
        AIPlay(model);
    });

    view.quitButton->onPress([&]() {
        view.window2.close();
    });

    view.newGameButton->onPress([&]() {
        model.reset();
        
        view.moveHistory->removeAllLines();
        view.updateBoard(model.boardConfiguration);
        view.updateMoveHistory(piece::EMPTY, "");
        view.updateScore(model.blackScore, model.whiteScore);
    });

    view.mainMenu->onPress([&]() {
        view.window2.close();
    });

    view.newGame->onPress([&]() {
        // Reset the entire game!!!
        model.reset();
        view.gui2.remove(view.gameOver);
        view.moveHistory->removeAllLines();
        view.updateBoard(model.boardConfiguration);
        view.updateMoveHistory(piece::EMPTY, "");
        view.updateScore(model.blackScore, model.whiteScore);
    });
}

void Controller::updateGameState(std::pair<unsigned int, unsigned int> coord)
{
    model.pass_count = 0;
    model.placeMove(coord);
    model.updateBoard();
    model.notifyObservers();
    model.switchPlayer();
}

void Controller::AIPlay(OthelloBoard board)
{
    std::pair<unsigned int, unsigned int> coord = AIplayer->play(board);
    if(coord != INVALID_COORD)
    {    
        updateGameState(coord);
    }
}