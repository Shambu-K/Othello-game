#ifndef _RANDOM_AI_H
#define _RANDOM_AI_H

#include "AI/AI.h"

/**
 * @brief This is a derived class of AI. 
 * @brief It selects a random move out of possible valid moves. 
 */
class RandomAI : public AI
{
    public:
    /**
     * @brief This function selects a random move out of all possible moves.
     * 
     * @param board This is the model of the game. It has data about the present board configuration, 
     * the valid moves that AI can make, so that the AI can select the required move and place the move.
     * @return std::pair<unsigned int, unsigned int> Returns coordinate of a random valid square on the board.
     */
    std::pair<unsigned int, unsigned int> play(OthelloBoard board) override
    {
        int siz = board.legalMoves.size();
     int i = std::rand()% siz;
     std::vector<std::pair<unsigned int,unsigned int>> coordlist;

     for(auto it: board.legalMoves)
     {
         coordlist.push_back(it.first);
     }
        std::pair<unsigned int, unsigned int> resultCoord;
        resultCoord = coordlist[i];
        return resultCoord;
    }

};

#endif 

