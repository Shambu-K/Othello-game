#ifndef AI_H
#define AI_H
#include <utility>
#include "Model/board.h"
#define INVALID_COORD std::make_pair((unsigned)DEFAULT_BOARD_SIZE + (unsigned)1, (unsigned)DEFAULT_BOARD_SIZE + (unsigned)1)

/**
 * @brief This class is the base class for different types of AI in the game.
 * 
 */
class AI
{
    public:
    /**
     * @brief This is a virtual function play() that is overridden by the derived classes.
     * 
     * It returns the best move based on the type of the AI.
     * 
     * @param board This is the model of the game. It has data about the present board configuration, 
     * the valid moves that AI can make, so that the AI can select the required move and place the move.
     * @return std::pair<unsigned int, unsigned int> The coordinate of the square in which the AI makes it move,
     */
    virtual std::pair<unsigned int, unsigned int> play(OthelloBoard board) = 0;

};

#endif
