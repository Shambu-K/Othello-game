#include "board.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <fstream>


/**
 * \brief This function is used to initialize the board with the four initial central pieces at the beginning of the game
 *
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

/**
 * @brief  This function initialises/resets the board configuration and legalMoves map to default.
 * 
 */
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

/**
 * @brief This function calculates the current scores of the players
 * 
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

/**
 * @brief This function returns the color of the opposite player of given player
 * 
 * @param col This represents the color of the given player
 * @return It returns the color of opposite player
 */
piece opposite(piece col)
{
    if(col == piece::BLACK) return piece::WHITE;

    return piece::BLACK;
}

/**
 * @brief This function clears all the legal moves on the board configuration 
 * 
 */
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
 * @brief This function searches all the possible legal moves for a particular player
 * 
 * @param clr This represents the color of the current player
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

/**
 * @brief This function calculates the coins that can be flipped in a specific direction and store the details of them in flipcoins
 * 
 * @param clr This represents the color of the current plyer
 * @param coord This reperesents the coordinates of the board piece around which we are searching for coins that can be flipped
 * @param dir This represents the direction in which we are searching for coins that can be flipped
 * @return std::vector<std::pair<unsigned int,unsigned int>>& 
 */
std::vector<std::pair<unsigned int,unsigned int>>& OthelloBoard::getFlipCoins(piece clr, std::pair<unsigned int, unsigned int> coord, std::pair<int ,int> dir)
{
    flipCoins.clear();
    for(coord.first+= dir.first, coord.second+=dir.second;0<coord.first && coord.first<boardSize && 0<coord.second && coord.second<boardSize; coord.first+= dir.first, coord.second+=dir.second)
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

/**
 * @brief This function checks if it is a legal move on a particular coordinate 
 * 
 * @param coord This represents the coordinate of the board piece which we are checking if a legal move can be made there
 */
bool OthelloBoard::isLegal(std::pair<unsigned int, unsigned int> coord)
{
    if(legalMoves[coord].empty())
    {
        std::cout << "\nIllegal Move!\n" << std::endl;
        std::cout << "You pressed " << coord.first << " , " << coord.second << std::endl;
        if(currentPlayer==piece::BLACK) std::cout << "Its black!" << std::endl;
        else std::cout << "Its white!" << std::endl;
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
 * @brief This function is used to update the values in boardConfiguration due to the move made on coord
 * 
 * @param coord This contains the coordinates of the board piece on which a move is made
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

/**
 * @brief This function updates the boardConfiguration and the score 
 * 
 */
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

/**
 * @brief This function changes the currentPlayer variable from one player to the opposite player
 * 
 */
void OthelloBoard::switchPlayer()
{
    if(currentPlayer==piece::BLACK)
        currentPlayer = piece::WHITE;
    else if(currentPlayer == piece::WHITE)
        currentPlayer = piece::BLACK;
}

/**
 * @brief This function adds a observer to the observer list
 * 
 * @param observer 
 */
void OthelloBoard::registerObserver(Observer *observer)
{
    observer_list.push_back(observer);
}

/**
 * @brief This function computes which message is to be shown in pop-up message
 * 
 */
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

/**
 * @brief This function gives updates to all the observers on the observer list 
 * 
 */
void OthelloBoard::notifyObservers()
{
    for(Observer* observer : observer_list)
    {
        observer->update(currentPlayer, message, boardConfiguration, blackScore, whiteScore, s);
    }
}

/**
 * @brief This function updates the moveLog with a PASS move
 * 
 */
void OthelloBoard::movePassed()
{
    s = "PASS";
    moveLog.push_back(s);
}

/**
 * @brief This function resets all the variables to the default new game situations
 * 
 */
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
