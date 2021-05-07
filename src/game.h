#include "board.h"
#include "player.h"
#include <string>
class OthelloGame
{
    public:
    OthelloBoard board;
    OthelloPlayer blackPlayer;
    OthelloPlayer whitePlayer;
    color currentPlayer = color::_BLACK;
    bool gameOver;
    void initializeGame(bool isBlackAI, bool isWhiteAI);
    void makeMove(color col);
    bool checkGameOver();
};
