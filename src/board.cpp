#include "board.h"
#include "fmt/core.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#define CLEAR_SCREEN "\e[1;1H\e[2J"
#define print fmt::print
#define EMPTY_PIECE "   "
#define BLACK_PIECE " \e[38;5;232m\u25CF\e[38;5;255m "
#define WHITE_PIECE " \e[38;5;255m\u25CF\e[38;5;255m "
#define B_LEGAL_PIECE " \e[38;5;232m\u25CB\e[38;5;255m "
#define W_LEGAL_PIECE " \e[38;5;255m\u25CB\e[38;5;255m "

/**
 *  @brief This function is used to initialize the board with the four initial central pieces at the beginning of the game
*/
void OthelloBoard::initializeBoard()
{
    boardConfiguration.resize(boardSize);
    for(int i = 0; i<boardSize; i++)
    {
        boardConfiguration[i].resize(boardSize, piece::EMPTY);
    }
    boardConfiguration[boardSize/2][boardSize/2] = boardConfiguration[boardSize/2 - 1][boardSize/2 - 1] = piece::WHITE;
    boardConfiguration[boardSize/2 - 1][boardSize/2] = boardConfiguration[boardSize/2][boardSize/2 - 1] = piece::BLACK;
    boardConfiguration[2][3] = boardConfiguration[3][2] = boardConfiguration[4][5] = boardConfiguration[5][4] = piece::LEGAL_BLACK;
    legalMoves[{2,3}] = legalMoves[{3,2}] = {{3,3}};
    legalMoves[{4,5}] = legalMoves[{5,4}] = {{4,4}};
    this->displayBoard(piece::BLACK);
}

/**
 * @brief This is a function to display the board on the command line.
*/
void OthelloBoard::displayBoard(piece col)  
{
    system("clear");
    print("--------------------OTHELLO--------------------\n\n");
    print("                 A   B   C   D   E   F   G   H\n");
    std::string top_line_str("");
    std::string mid_line_str("");
    std::string end_line_str("");
	top_line_str += top_start;
	mid_line_str += middle_start;
	end_line_str += bottom_start;

	top_line_str += top_line + top_line + top_line;
	mid_line_str += middle_line + middle_line + middle_line;
	end_line_str += bottom_line + bottom_line + bottom_line;
	for (int i = 1; i < boardSize; i++)
	{
		top_line_str += top_cross + top_line + top_line + top_line;
	    mid_line_str += middle_cross + middle_line + middle_line + middle_line;
	    end_line_str += bottom_cross + bottom_line + bottom_line + bottom_line;
	}
	top_line_str += top_end;
    mid_line_str += middle_end;
    end_line_str += bottom_end;
    print("               \e[48;5;34m{}\e[0m\n", top_line_str);
    for(int i = 1; i<=boardSize; i++)
    {
        print("             {} \e[48;5;34m{}", i, content_cross);
        for(int j = 1; j<=boardSize; j++)
        {
            switch(boardConfiguration[i-1][j-1])
            {
                case piece::EMPTY : print("{}",EMPTY_PIECE);    break;
                case piece::WHITE : print("{}", WHITE_PIECE);    break;
                case piece::BLACK : print("{}", BLACK_PIECE);    break;
                case piece::LEGAL_WHITE : print("{}", W_LEGAL_PIECE);  break;
                case piece::LEGAL_BLACK : print("{}", B_LEGAL_PIECE);  break;
            }
            print("{}", content_cross);
        }
        print("\e[0m\n");
        if(i<boardSize)
            print("               \e[48;5;34m{}\e[0m\n", mid_line_str);
        else
            print("               \e[48;5;34m{}\e[0m\n", end_line_str);
    }
    if(col==piece::WHITE)
    {
        print("It is WHITE's turn\n");
    }
    else if(col == piece::BLACK)
    {
        print("Its is BLACK's turn\n");
    }
    this->displayScores();
    this->displayMoves();
}

void OthelloBoard::displayMoves()
{
    char a, b;
    print("Legal Moves : \n");
    for(auto x : legalMoves)
    {
        a = x.first.first + 'A';
        print("{}{} : ", (char)(x.first.second + 'A'),  (x.first.first + 1));
        for(auto y : legalMoves[x.first])
        {
            print("{}{} ",(char)(y.second + 'A'), (y.first + 1));
        }
        print("\n");
    }
    print("\n");
}

void OthelloBoard::displayScores()
{
    blackScore = whiteScore = 0;
    for(int i = 0; i<boardSize; i++)
    {
        for(int j = 0; j<boardSize; j++)
        {
            if(boardConfiguration[i][j]==piece::BLACK)  blackScore++;
            if(boardConfiguration[i][j]==piece::WHITE)  whiteScore++;
        }
    }
    print("BLACK : {}\n", blackScore);
    print("WHITE : {}\n", whiteScore);
}

piece opposite(piece col)
{
    if(col == piece::BLACK) return piece::WHITE;

    return piece::BLACK;
}

void OthelloBoard::clearMoves()
{
    for(int i = 0; i<boardSize; i++)
    {
        for(int j = 0; j<boardSize; j++)
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
    for(int i = 0; i<boardSize; i++)
    {
        for(int j = 0; j<boardSize; j++)
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

/**
 * @brief This function is used to update the values in boardConfiguration
 */

bool OthelloBoard::placeMove(piece clr, std::pair<unsigned int, unsigned int> coord)
{
    if(legalMoves[coord].empty())
    {
        print("Illegal Move!");
    //std::this_thread::sleep_for(std::chrono::seconds(20));
        return false;
    }
        
    else
    {
    this->clearMoves();

    boardConfiguration[coord.first][coord.second] = clr;
    for(auto x : legalMoves[{coord.first, coord.second}])
    {
        boardConfiguration[x.first][x.second] = clr;
    }
    }
    return true;
}

void OthelloBoard::updateBoard(piece clr)
{
    this->searchLegalMoves(opposite(clr));
    for(auto x : legalMoves)
    {
        if(clr==piece::BLACK)
        boardConfiguration[x.first.first][x.first.second] = piece::LEGAL_WHITE;
        else if(clr==piece::WHITE)
        boardConfiguration[x.first.first][x.first.second] = piece::LEGAL_BLACK;
    }
    this->displayBoard(opposite(clr));
}