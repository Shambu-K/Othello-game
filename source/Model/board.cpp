#include "board.h"
#include "fmt/core.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <fstream>

#define print fmt::print

/**
 * \brief This function is used to initialize the board with the four initial central pieces at the beginning of the game
 * 
 * This function also initialises the legalMoves map. 
*/
OthelloBoard::OthelloBoard()
{
    //std::cout<< "This is from OthelloBoard() constructor" << std::endl;

    boardConfiguration.resize(boardSize);
    for(unsigned int i = 0; i<boardSize; i++)
    {
        boardConfiguration[i].resize(boardSize, piece::EMPTY);
    }
    initialise();
}

void OthelloBoard::initialise()
{
    boardConfiguration[boardSize/2][boardSize/2] = boardConfiguration[boardSize/2 - 1][boardSize/2 - 1] = piece::WHITE;
    boardConfiguration[boardSize/2 - 1][boardSize/2] = boardConfiguration[boardSize/2][boardSize/2 - 1] = piece::BLACK;
    boardConfiguration[2][3] = boardConfiguration[3][2] = boardConfiguration[4][5] = boardConfiguration[5][4] = piece::LEGAL_BLACK;
    legalMoves[{2,3}] = legalMoves[{3,2}] = {{3,3}};
    legalMoves[{4,5}] = legalMoves[{5,4}] = {{4,4}};
    message = 0;
    turnNum = 0;
    s = "";
    pass_count = 0;
}

/**
 * \brief This is a function to display the board on the command line.
 * 
 * This function clears everything previously present in the terminal, and displays new board configuration. 
 * This function calls displayScores() and displayMoves() to display scores of both the players and legal moves of the current player.
 * 
 * \param col is used to specify whose turn it is currently.
*/

void OthelloBoard::computeScores()
{
    blackScore = whiteScore = 0;
    for(unsigned int i = 0; i<boardSize; i++)
    {
        for(unsigned int j = 0; j<boardSize; j++)
        {
            if(boardConfiguration[i][j]==piece::BLACK)  blackScore++;
            if(boardConfiguration[i][j]==piece::WHITE)  whiteScore++;
        }
    }
}

piece opposite(piece col)
{
    if(col == piece::BLACK) return piece::WHITE;

    return piece::BLACK;
}

void OthelloBoard::clearMoves()
{
    for(unsigned int i = 0; i<boardSize; i++)
    {
        for(unsigned int j = 0; j<boardSize; j++)
        {
            if((boardConfiguration[i][j]==piece::LEGAL_WHITE) || (boardConfiguration[i][j]==piece::LEGAL_BLACK))
            {
                boardConfiguration[i][j]=piece::EMPTY;
            }
        }
    }
}

/**
 * @brief This function is used to get Legalmoves and store them in legalMoves
*/

void OthelloBoard::searchLegalMoves(piece clr)
{
    legalMoves.clear();
    this->clearMoves();
    for(unsigned int i = 0; i<boardSize; i++)
    {
        for(unsigned int j = 0; j<boardSize; j++)
        {
            if((boardConfiguration[i][j]==piece::EMPTY))
            {
                flippedCoins.clear();
                flippedCoins.insert(flippedCoins.end(), getFlipCoins(clr, {i,j}, {1,1}).begin(), getFlipCoins(clr, {i,j}, {1,1}).end());
                flippedCoins.insert(flippedCoins.end(), getFlipCoins(clr, {i,j}, {-1,1}).begin(), getFlipCoins(clr, {i,j}, {-1,1}).end());
                flippedCoins.insert(flippedCoins.end(), getFlipCoins(clr, {i,j}, {1,-1}).begin(), getFlipCoins(clr, {i,j}, {1,-1}).end());
                flippedCoins.insert(flippedCoins.end(), getFlipCoins(clr, {i,j}, {-1,-1}).begin(), getFlipCoins(clr, {i,j}, {-1,-1}).end());
                flippedCoins.insert(flippedCoins.end(), getFlipCoins(clr, {i,j}, {0,1}).begin(), getFlipCoins(clr, {i,j}, {0,1}).end());
                flippedCoins.insert(flippedCoins.end(), getFlipCoins(clr, {i,j}, {0,-1}).begin(), getFlipCoins(clr, {i,j}, {0,-1}).end());
                flippedCoins.insert(flippedCoins.end(), getFlipCoins(clr, {i,j}, {1,0}).begin(), getFlipCoins(clr, {i,j}, {1,0}).end());
                flippedCoins.insert(flippedCoins.end(), getFlipCoins(clr, {i,j}, {-1,0}).begin(), getFlipCoins(clr, {i,j}, {-1,0}).end());

                if(!flippedCoins.empty())
                {
                    legalMoves[{i,j}] = flippedCoins;
                }
            }
        }
    }
}


std::vector<std::pair<unsigned int,unsigned int>>& OthelloBoard::getFlipCoins(piece clr, std::pair<unsigned int, unsigned int> coord, std::pair<int ,int> dir)
{
    flipCoins.clear();
    for(coord.first+= dir.first, coord.second+=dir.second; coord.first<boardSize && coord.second<boardSize; coord.first+= dir.first, coord.second+=dir.second)
    {
        if(boardConfiguration[coord.first][coord.second]==opposite(clr))
        {
            flipCoins.push_back({coord});
            continue;
        }
        if(boardConfiguration[coord.first][coord.second]==clr)
        {
            return flipCoins;
        }
        if(boardConfiguration[coord.first][coord.second]==piece::EMPTY)
            break;
    }
    flipCoins.clear();
    return flipCoins;
}

bool OthelloBoard::isLegal(std::pair<unsigned int, unsigned int> coord)
{
    if(legalMoves[coord].empty())
    {
        print("\nIllegal Move!\n");
        print("You pressed {}, {}!!\n", coord.first, coord.second);
        if(currentPlayer==piece::BLACK) print("Its black!");
        else print("Its white!");
        message = 4;
        s = "Illegal Move!";
        moveLog.push_back(s);
        notifyObservers();
        return false;
    }

    else
    {
        return true;
    }
}


/**
 * @brief This function is used to update the values in boardConfiguration
 */

void OthelloBoard::placeMove(std::pair<unsigned int, unsigned int> coord)
{
        turnNum++;
        boardConfiguration[coord.first][coord.second] = currentPlayer;
        for(auto x : legalMoves[{coord.first, coord.second}])
        {
            boardConfiguration[x.first][x.second] = currentPlayer;
        }
        a = (char)(coord.second + 65);
        b = (char)(coord.first + 49);
        s = "";
        s = s + a;
        s = s + b;
        moveLog.push_back(s);
}

void OthelloBoard::updateBoard()
{
    this->clearMoves();
    message = computeMessage();
    switchPlayer();
    this->searchLegalMoves(currentPlayer);
    for(auto x : legalMoves)
    {
        if(currentPlayer==piece::BLACK)
            boardConfiguration[x.first.first][x.first.second] = piece::LEGAL_BLACK;
        else if(currentPlayer==piece::WHITE)
            boardConfiguration[x.first.first][x.first.second] = piece::LEGAL_WHITE;
    }
    computeScores();
    switchPlayer();
}

void OthelloBoard::switchPlayer()
{
    if(currentPlayer==piece::BLACK)
        currentPlayer = piece::WHITE;
    else if(currentPlayer == piece::WHITE)
        currentPlayer = piece::BLACK;
}

void OthelloBoard::registerObserver(Observer *observer)
{
    observer_list.push_back(observer);
}

int OthelloBoard::computeMessage()
{
    switchPlayer();
    piece cplayer = currentPlayer;
    switchPlayer();
    piece nplayer = currentPlayer;
    searchLegalMoves(cplayer);
    if(!legalMoves.empty())
    {
        return 0;
    }
    else 
    {
        searchLegalMoves(nplayer);
        if(legalMoves.empty())
            {
                return 3;
            }
        if(cplayer==piece::BLACK)
            {
                return 1;
            }
        if(cplayer==piece::WHITE)
            {
                return 2;
            }
    }
    return 0;
}

void OthelloBoard::notifyObservers()
{
    for(Observer* observer : observer_list)
    {
        observer->update(currentPlayer, message, boardConfiguration, blackScore, whiteScore, s);
    }
}

void OthelloBoard::movePassed()
{
    s = "PASS";
    moveLog.push_back(s);
}

void OthelloBoard::reset()
{
    moveLog.clear();
    legalMoves.clear();
    blackScore = 2; 
    whiteScore = 2;
    currentPlayer = piece::BLACK;
    boardConfiguration.clear();
    s = "";
    boardConfiguration.resize(boardSize);
    for(unsigned int i = 0; i<boardSize; i++)
    {
        boardConfiguration[i].resize(boardSize, piece::EMPTY);
    }
    initialise();
}