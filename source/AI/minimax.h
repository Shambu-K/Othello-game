#ifndef _EBONY_H
#define _EBONY_H

#include "AI/AI.h"
#include <utility>
#include <deque>

using mini = std::pair<int, std::pair<unsigned, unsigned>>;
using move = std::pair<unsigned, unsigned>;
using moves = std::vector<std::pair<unsigned int,unsigned int>>;

class ai
{
public:
    // Public methods. Methods for interacting with the AI and its different
    // components.
    ai();
    move  evaluateMove();
   
    int getSearchDepth();
    void  setSearchDepth(unsigned int searchDepth);
    
private:
    // The alphabeta algorithm with alpha-beta prunings.
    mini algorithm(OthelloBoard node,int depth,move movemade,piece currentPlayer,bool lategame);

    // Heurisitc valuing functions.
    int heuristicValue(OthelloBoard _game, piece maximizingColor);
    int mobilityTester(OthelloBoard _game, piece maximizingColor);
    int cornerTester(OthelloBoard _game, piece maximizingColor);
    int fieldTester(OthelloBoard _game, piece maximizingColor);
    int tileWeight(unsigned int x, unsigned int y, OthelloBoard _game, piece maximizingColor);


    // Other private methods.
    piece getCurrentPlayer();
    piece reverseColor(piece color) ;
    mini  makeMini(int value, unsigned int x, unsigned int y) const;
  
  

private:
    // Ai local field variables.
    OthelloBoard     _currentGame{};
    piece    _aiColor{ piece::WHITE };
    piece _playerColor{piece::BLACK};
    piece _currentPlayer = _aiColor;
    unsigned _moveCount{ 0 };
    unsigned _searchDepth{ 7 };
    
};




#endif

