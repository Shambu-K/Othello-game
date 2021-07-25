#ifndef _BOARD_H
#define _BOARD_H

#include <vector>
#include <map>
#include <string>
#include "Subject.h"
#include "CommonTypes.h"

/**
 * @brief This class is the model of the application. It has all the game logic inside it.
 * It is a derived class of Subject, and it is observed by View of the application.
 * 
 */
class OthelloBoard : public Subject
{
    public :
    ///This contains details of configuration of board 
    std::vector<std::vector<piece>> boardConfiguration;
    ///This contains the details of the coins that will be flipped by a move in a specific direction
    std::vector<std::pair<unsigned int,unsigned int>> flipCoins;
    ///This contains the details of all the coins that can be flipped in all directions
    std::vector<std::pair<unsigned int,unsigned int>> flippedCoins;
    void computeScores();
    void clearMoves();
    void searchLegalMoves(piece col);
    std::vector<std::pair<unsigned int, unsigned int>>& getFlipCoins(piece clr, std::pair<unsigned int, unsigned int> coord, std::pair<int ,int> dir);
    unsigned int blackScore = 2, whiteScore = 2;
    unsigned int boardSize = 8;
    ///This contains the details of all the possible moves for a player
    std::map<std::pair<unsigned int, unsigned int>, std::vector<std::pair<unsigned int, unsigned int>>> legalMoves;
    OthelloBoard();
    void placeMove(std::pair<unsigned int, unsigned int> coord);
    void updateBoard();
    ///This contains the details of who the current player is
    piece currentPlayer = piece::BLACK;
    void switchPlayer();
    ///This contains the value of number of turns took place between both players
    unsigned int turnNum;
    ///This contains the details of all the observers
    std::vector<Observer*> observer_list;
    void registerObserver(Observer *observer) override;
    void notifyObservers() override;
    ///This contains the details of which message is to be delivered as pop-up message
    int message = 0;
    int computeMessage();
    void movePassed();
    ///This contains details of all the moves that have been made by the players in the current game
    std::vector<std::string> moveLog;
    ///This contains the details of what non-legal move is to be added to moveLog ( such as PASS )
    std::string s = "";
    ///This contains the details of the Y-coordinate in string form
    char a;
    ///This contains the details of the X-coordinate in string form
    char b;
    void reset();
    void initialise();
    ///This contains value of number of passes made between players
    int pass_count = 0;
    ///This contains whether a move is legal or not
    bool isLegal(std::pair<unsigned int, unsigned int> coord);
};


#endif