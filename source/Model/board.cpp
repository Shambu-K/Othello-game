#include "board.h"
#include "fmt/core.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <fstream>

#define print fmt::print

#define EMPTY_PIECE "   "
#define BLACK_PIECE " \033[38;5;232m\u25CF\033[38;5;255m "
#define WHITE_PIECE " \033[38;5;255m\u25CF\033[38;5;255m "
#define B_LEGAL_PIECE " \033[38;5;232m\u25CB\033[38;5;255m "
#define W_LEGAL_PIECE " \033[38;5;255m\u25CB\033[38;5;255m "

#define TOP_START       "\033[38;5;255m\u250F"
#define TOP_LINE        "\033[38;5;255m\u2501"
#define TOP_CROSS       "\033[38;5;255m\u2533"
#define TOP_END         "\033[38;5;255m\u2513"
#define MIDDLE_START    "\033[38;5;255m\u2523"
#define MIDDLE_LINE     "\033[38;5;255m\u2501"
#define MIDDLE_CROSS    "\033[38;5;255m\u254B"
#define MIDDLE_END      "\033[38;5;255m\u252B"
#define BOTTOM_START    "\033[38;5;255m\u2517"
#define BOTTOM_LINE     "\033[38;5;255m\u2501"
#define BOTTOM_CROSS    "\033[38;5;255m\u253B"
#define BOTTOM_END      "\033[38;5;255m\u251B"
#define CONTENT_CROSS   "\033[38;5;255m\u2503"


/**
 * \brief This function is used to initialize the board with the four initial central pieces at the beginning of the game
 * 
 * This function also initialises the legalMoves map. It also automatically calls the displayBoard() function to display the board first time.
*/
OthelloBoard::OthelloBoard()
{
    //std::cout<< "This is from OthelloBoard() constructor" << std::endl;

    boardConfiguration.resize(boardSize);
    for(unsigned int i = 0; i<boardSize; i++)
    {
        boardConfiguration[i].resize(boardSize, piece::EMPTY);
    }
    boardConfiguration[boardSize/2][boardSize/2] = boardConfiguration[boardSize/2 - 1][boardSize/2 - 1] = piece::WHITE;
    boardConfiguration[boardSize/2 - 1][boardSize/2] = boardConfiguration[boardSize/2][boardSize/2 - 1] = piece::BLACK;
    boardConfiguration[2][3] = boardConfiguration[3][2] = boardConfiguration[4][5] = boardConfiguration[5][4] = piece::LEGAL_BLACK;
    legalMoves[{2,3}] = legalMoves[{3,2}] = {{3,3}};
    legalMoves[{4,5}] = legalMoves[{5,4}] = {{4,4}};
    turnNum = 0;
}

/**
 * \brief This is a function to display the board on the command line.
 * 
 * This function clears everything previously present in the terminal, and displays new board configuration. 
 * This function calls displayScores() and displayMoves() to display scores of both the players and legal moves of the current player.
 * 
 * \param col is used to specify whose turn it is currently.
*/

#if 0

void OthelloBoard::displayBoard(piece col)  
{
    system("clear");
    
    std::ifstream f("resources/title2.txt");

    if (f.is_open())
        std::cout << "\033[38;5;39m" << f.rdbuf() << "\033[38;5;255m";


    print("              		              A   B   C   D   E   F   G   H\n");
    std::string top_line_str("");
    std::string mid_line_str("");
    std::string end_line_str("");
	top_line_str += TOP_START;
	mid_line_str += MIDDLE_START;
	end_line_str += BOTTOM_START;

	top_line_str += TOP_LINE;
	top_line_str += TOP_LINE;
	top_line_str += TOP_LINE;
	
    mid_line_str += MIDDLE_LINE;
    mid_line_str += MIDDLE_LINE;
    mid_line_str += MIDDLE_LINE;
	
    end_line_str += BOTTOM_LINE;
	end_line_str += BOTTOM_LINE;
	end_line_str += BOTTOM_LINE;
	
    for (unsigned int i = 1; i < boardSize; i++)
	{
		top_line_str += TOP_CROSS;
        top_line_str += TOP_LINE;
        top_line_str += TOP_LINE;
        top_line_str += TOP_LINE;
        
	    mid_line_str += MIDDLE_CROSS;
        mid_line_str += MIDDLE_LINE;
        mid_line_str += MIDDLE_LINE;
        mid_line_str += MIDDLE_LINE;
        
	    end_line_str += BOTTOM_CROSS;
        end_line_str += BOTTOM_LINE;
        end_line_str += BOTTOM_LINE;
        end_line_str += BOTTOM_LINE;

	}
	top_line_str += TOP_END;
    mid_line_str += MIDDLE_END;
    end_line_str += BOTTOM_END;
    print("            		            \033[48;5;34m{}\033[0m\n", top_line_str);
    for(unsigned int i = 1; i<=boardSize; i++)
    {
        print("           		          {} \033[48;5;34m{}", i, CONTENT_CROSS);
        for(unsigned int j = 1; j<=boardSize; j++)
        {
            switch(boardConfiguration[i-1][j-1])
            {
                case piece::EMPTY : print("{}",EMPTY_PIECE);    break;
                case piece::WHITE : print("{}", WHITE_PIECE);    break;
                case piece::BLACK : print("{}", BLACK_PIECE);    break;
                case piece::LEGAL_WHITE : print("{}", W_LEGAL_PIECE);  break;
                case piece::LEGAL_BLACK : print("{}", B_LEGAL_PIECE);  break;
            }
            print("{}", CONTENT_CROSS);
        }
        print("\033[0m {} \n", i);
        if(i<boardSize)
            print("            		            \033[48;5;34m{}\033[0m\n", mid_line_str);
        else
            print("                                    \033[48;5;34m{}\033[0m\n", end_line_str);
    }
    print("                  		      A   B   C   D   E   F   G   H\n");
    if(col==piece::WHITE)
    {
        print("\nIt is WHITE's turn\n");
    }
    else if(col == piece::BLACK)
    {
        print("\nIt is BLACK's turn\n");
    }
    this->displayScores();
    this->displayMoves();
}
/**
 * \brief This function is used to display the legal moves of the current player from legalMoves map.
*/
void OthelloBoard::displayMoves()
{
    
    print("\nLegal Moves : \n");
    for(auto x : legalMoves)
    {
        print("\t{}{} : ", (char)(x.first.second + 'A'),  (x.first.first + 1));
        for(auto y : legalMoves[x.first])
        {
            print("{}{} ",(char)(y.second + 'A'), (y.first + 1));
        }
        print("\n");
    }
    print("\n");
}
#endif

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

/**
 * @brief This function is used to update the values in boardConfiguration
 */

bool OthelloBoard::placeMove(std::pair<unsigned int, unsigned int> coord)
{
    
    if(legalMoves[coord].empty())
    {
        print("\nIllegal Move!\n");
        print("You pressed {}, {}!!\n", coord.first, coord.second);
        return false;
    }
        
    else
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
        return true;
    }
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
            {return 3;}
        if(cplayer==piece::BLACK)
            {return 1;}
        if(cplayer==piece::WHITE)
            {return 2;}
    }
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