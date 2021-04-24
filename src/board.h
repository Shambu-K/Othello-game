#ifndef _BOARD_H
#define _BOARD_H

#include <vector>
#include <map>



enum class piece
{
    BLACK,
    WHITE,
    LEGAL_BLACK,
    LEGAL_WHITE,
    EMPTY
};

class OthelloBoard
{
    public:
    unsigned int boardSize = 8;
    unsigned int blackScore, whiteScore;
    std::vector<std::vector<piece>> boardConfiguration;
    std::vector<std::pair<unsigned int,unsigned int>> flipCoins;
    std::vector<std::pair<unsigned int,unsigned int>> flippedCoins;
    std::map<std::pair<unsigned int, unsigned int>, std::vector<std::pair<unsigned int, unsigned int>>> legalMoves;
    void initializeBoard();
    void displayBoard(piece col);
    void displayMoves();
    void displayScores();
    void clearMoves();
    void searchLegalMoves(piece col);
    std::vector<std::pair<unsigned int, unsigned int>>& getFlipCoins(piece clr, std::pair<unsigned int, unsigned int> coord, std::pair<int ,int> dir);
    bool placeMove(piece clr, std::pair<unsigned int, unsigned int> coord);
    void updateBoard(piece clr);
    
};


#endif