#ifndef _PLAYER_H
#define _PLAYER_H

#include "board.h"
#include <vector>
#include <map>
#include <optional>
#include <string>

enum class color{
    _BLACK,
    _WHITE
};

class OthelloPlayer
{
    public:
    color col;
    bool isAI;
    unsigned int boardSize;
    bool pass;
    void initializePlayer(color _col, bool _isAI, unsigned int _boardSize);
    std::optional<std::pair<unsigned int, unsigned int>> getMove(std::map<std::pair<unsigned int, unsigned int>, std::vector<std::pair<unsigned int, unsigned int>>>& legalMoves, bool& pass);
    std::optional<std::pair<unsigned int, unsigned int>> getMoveHuman(std::map<std::pair<unsigned int, unsigned int>, std::vector<std::pair<unsigned int, unsigned int>>>& legalMoves, bool& pass);
    std::optional<std::pair<unsigned int, unsigned int>> getMoveAI(std::map<std::pair<unsigned int, unsigned int>, std::vector<std::pair<unsigned int, unsigned int>>>& legalMoves, bool& pass); 
    std::optional<std::pair<unsigned int, unsigned int>> getCoordinate();
};

#endif 