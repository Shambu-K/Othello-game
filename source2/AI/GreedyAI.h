#ifndef _GREEDY_AI_H
#define _GREEDY_AI_H

#include "AI/AI.h"
/**
 * @brief This is a derived class of AI.
 * This AI selects the best possible move out of all possible moves. 
 */
class GreedyAI : public AI
{
    public:
    /**
     * @brief This function selects the best move out of all possible available moves.
     * 
     * @param board This is the model of the game. It has data about the present board configuration, 
     * the valid moves that AI can make, so that the AI can select the best move and return the move.
     * @return std::pair<unsigned int, unsigned int> Returns the coordinate of the best move.
     */
    std::pair<unsigned int, unsigned int> play(OthelloBoard board) override
    {
        unsigned int max_Captures = 0;
        std::pair<unsigned int, unsigned int> resultCoord;
        for(auto itr : board.legalMoves)
        {
            if(itr.second.size() > max_Captures)
            {
                resultCoord = itr.first;
            }
        }
        return resultCoord;
    }

};

#endif

