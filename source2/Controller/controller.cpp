#include "controller.h"
#include <iostream>
#include <string>
#include <fstream>
#include <fmt/core.h>
#include <optional>

#define pr fmt::print
/**
 * @brief Construct a new Controller:: Controller object based on the options the user selects in the title page
 * It also initializes model and view objects and registers the view as an oberver to the model
 * 
 * It has the main game loop of the application
 * 
 * @param options This variable tells the mode of gameplay the user has selected in the title page.
 */
Controller::Controller(int options) : model(), view(DEFAULT_BOARD_SIZE)
{
    decideAI(options);
    model.registerObserver(&view);
    gameloop();
}

/**
 * @brief This functions selects the type of AI(Random, Greedy, NoAI) based on option selected by the user.
 * 
 * @param options This variable tells the mode of gameplay the user has selected in the title page.
 */
void Controller::decideAI(int options)
{
    switch(options)
    {
        case 1 : AIplayer = new NoAI();         break;
        case 2 : AIplayer = new RandomAI();       break;
        case 3 : AIplayer = new GreedyAI();     break;
        case 4 : AIplayer = new MinimaxAI();    break;
        default : AIplayer = new NoAI();
    }
}

/**
 * @brief This function gets a coordinate from the user and passes it to the model to update the game state.
 * 
 * @param coord This variable is the coordinate of the square the user has clicked on.
 */
void Controller::updateGameState(std::pair<unsigned int, unsigned int> coord)
{
    model.pass_count = 0;
    model.placeMove(coord);
    model.updateBoard();
    model.notifyObservers();
    // model.switchPlayer();
}



/**
 * @brief This function lets the AI play after every move the player makes.
 * 
 * If the AI is NoAI, the program waits until the second player has made a move. 
 * Otherwise, it makes a move as soon as the first player makes a move,
 * 
 * @param board This is the model of the game. It has data about the present board configuration, 
 * the valid moves that AI can make, so that the AI can select the required move and place the move.
 */

void Controller::AIPlay(OthelloBoard board)
{
    std::pair<unsigned int, unsigned int> coord = AIplayer->play(board);
    if(coord != INVALID_COORD)
    {
        updateGameState(coord);
    }
}

std::pair<unsigned int, unsigned int> Controller::getMove()
{
    std::optional<std::pair<unsigned int, unsigned int>> coord = getInput();
    if(coord.has_value())
    {
        return coord.value();
    }
    else
    {
        return getMove();
    }

}

std::optional<std::pair<unsigned int, unsigned int>> Controller::getInput()
{
    std::string str;
    std::pair<unsigned int, unsigned int> coord;
    pr("Enter the coordinate where you want to place your move : ");
    // std::cin >> str;
    std::getline(std::cin, str);
    
    if(str.length()==0)
    {
        return std::make_pair(2*DEFAULT_BOARD_SIZE, 2*DEFAULT_BOARD_SIZE);
    }
    else if(str.length()!=2)
    {
        return {};
    }
    if((str[0]-'A')>=0 && (unsigned int)(str[0]-'A')<boardSize && (str[1]-'1')>=0 && (unsigned int)(str[1]-'1')<boardSize)
    {
        return std::make_pair(str[1]-'1', str[0]-'A' );
    }
    else if((str[0]-'a')>=0 && (unsigned int)(str[0]-'a')<boardSize && (str[1]-'1')>=0 && (unsigned int)(str[1]-'1')<boardSize)
    {
        return std::make_pair(str[1]-'1', str[0]-'a');
    }
    else
    {
        return {};
    }
}

void Controller::pass()
{
    model.updateBoard();
    model.notifyObservers();
}

void Controller::gameloop()
{
    model.notifyObservers();
    std::string buf;
    std::getline(std::cin, buf);

    while(model.message!=3)
    {
        auto move = getMove();
        if(move.first>DEFAULT_BOARD_SIZE && move.second>DEFAULT_BOARD_SIZE)
        {
            pass();
            if(model.legalMoves.empty())
            {
                pass();
            }
            else
            {
                AIPlay(model);
            }
        }
        else
        {
            if(model.isLegal(move))
            {
                updateGameState(move);
                if(model.legalMoves.empty())
                {
                    pass();
                }
                else
                {
                    AIPlay(model);
                }
            }
        }
    }
}