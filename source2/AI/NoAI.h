#ifndef _NO_AI_H
#define _NO_AI_H

#include "AI/AI.h"
/**
 * @brief This is a derived class of AI. It is a "Null Object" class which does nothing.
 * It allows Player vs Player mode by not making any move.
 */
class NoAI : public AI
{
    public:
    /**
     * @brief This function does nothing and returns an invalid coord. 
     * It allows the next player to make a move with this behaviour.
     * 
     * @param board This is the model of the game. It has data about the present board configuration, 
     * the valid moves that AI can make, so that the AI can select the required move and place the move.
     * @return std::pair<unsigned int, unsigned int> It returns an invalid coordinate of a square. 
     */
    std::pair<unsigned int, unsigned int> play(OthelloBoard board) override
    {
        return INVALID_COORD;
    }
};

#endif
