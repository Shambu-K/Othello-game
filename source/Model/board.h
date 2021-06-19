#ifndef _BOARD_H
#define _BOARD_H

#include <vector>
#include <map>
#include <string>
#include "Subject.h"
#include "CommonTypes.h"

class OthelloBoard : public Subject
{
    public :
    std::vector<std::vector<piece>> boardConfiguration;
    std::vector<std::pair<unsigned int,unsigned int>> flipCoins;
    std::vector<std::pair<unsigned int,unsigned int>> flippedCoins;
    void computeScores();
    void clearMoves();
    void searchLegalMoves(piece col);
    std::vector<std::pair<unsigned int, unsigned int>>& getFlipCoins(piece clr, std::pair<unsigned int, unsigned int> coord, std::pair<int ,int> dir);
    unsigned int blackScore = 2, whiteScore = 2;
    unsigned int boardSize = 8;
    std::map<std::pair<unsigned int, unsigned int>, std::vector<std::pair<unsigned int, unsigned int>>> legalMoves;
    OthelloBoard();
    void placeMove(std::pair<unsigned int, unsigned int> coord);
    void updateBoard();
    piece currentPlayer = piece::BLACK;
    void switchPlayer();
    unsigned int turnNum;
    std::vector<Observer*> observer_list;
    void registerObserver(Observer *observer) override;
    void notifyObservers() override;
    int message = 0;
    int computeMessage();
    void movePassed();
    std::vector<std::string> moveLog;
    std::string s = "";
    char a, b;
    void reset();
    void initialise();
    int pass_count = 0;
    bool isLegal(std::pair<unsigned int, unsigned int> coord);
};


#endif