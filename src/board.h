#ifndef _BOARD_H
#define _BOARD_H

#include <vector>
#include <map>
#include <string>


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
    std::vector<std::vector<piece>> boardConfiguration;
    //int arr[64];
    std::vector<std::pair<unsigned int,unsigned int>> flipCoins;
    std::vector<std::pair<unsigned int,unsigned int>> flippedCoins;
    void displayBoard(piece col);
    void displayMoves();
    void displayScores();
    void clearMoves();
    void searchLegalMoves(piece col);
    std::vector<std::pair<unsigned int, unsigned int>>& getFlipCoins(piece clr, std::pair<unsigned int, unsigned int> coord, std::pair<int ,int> dir);

    public :
    unsigned int blackScore, whiteScore;
    unsigned int boardSize = 8;
    std::map<std::pair<unsigned int, unsigned int>, std::vector<std::pair<unsigned int, unsigned int>>> legalMoves;
    void initializeBoard();
    bool placeMove(piece clr, std::pair<unsigned int, unsigned int> coord);
    void updateBoard(piece clr);
    unsigned int turnNum;
    
};


#endif