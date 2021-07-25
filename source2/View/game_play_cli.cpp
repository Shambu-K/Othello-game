#include "game_play_cli.h"
#include <thread>
#include <chrono>
#include <string>
#include <iostream>
#include <fmt/core.h>
#include <fmt/os.h>
#include <cstdlib>
#include <fstream>
#define pr fmt::print


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
 * @brief It creates the default version of game window
 * @param boardSize It is the number of squares per side of board 
 */
GameplayGUI::GameplayGUI(unsigned int boardSize)
{
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
}

/**
 * @brief This function takes the variables that are needed to be updated and updates them as per the move made byb user
 * 
 * @param currentPlayer This contains the details of who is the player that just made a move
 * @param message This contains details regarding whether a pop-up message is to be shown ,if yes then which one
 * @param boardConfiguration This contains details of configuration of board after the move is made
 * @param blackScore This contains the value of score of black player
 * @param whiteScore This contains the value of score of white player
 * @param move This contains details of the move made by current player
 */
void GameplayGUI::update(piece currentPlayer, int message, std::vector<std::vector<piece>> boardConfiguration, int blackScore, int whiteScore, std::string move)
{
    if(message!=4)
    {
        system("clear");
        std::ifstream f("resources/title2.txt");

        if (f.is_open())
            std::cout << "\033[38;5;39m" << f.rdbuf() << "\033[38;5;255m";

        displayBoard(boardConfiguration);
    }
    if(message == 0)
    {
        if(currentPlayer==piece::WHITE)
        {
            pr("\nIt is WHITE's turn\n");
        }
        else if(currentPlayer == piece::BLACK)
        {
            pr("\nIt is BLACK's turn\n");
        }
    }
    else if(message==1)
    {
        pr("No legal moves for Black Player\n");
        // pr("Enter \"PASS\" to continue\n");
    }
    else if(message==2)
    {
        pr("No legal moves for White Player\n");
        // pr("Enter \"PASS\" to continue\n");
    }
    else if(message==3)
    {
        showGameOver(blackScore, whiteScore);
        // pr("Enter \"PASS\" to continue\n");
    }
    else if(message==4)
    {
        pr("\nIllegal Move!!\n");
    }
    if(message!=4)
    {
        displayScore(blackScore, whiteScore);
    }
}

/**
 * @brief This is a sub-function of the update function that takes the boardconfiguration and updates the visual interface of the board
 * 
 * @param boardConfiguration This contains details of configuration of board after the move is made
 */
void GameplayGUI::displayBoard(std::vector<std::vector<piece>> boardConfiguration)
{
    unsigned int boardSize = boardConfiguration.size();
    pr("              		              A   B   C   D   E   F   G   H\n");
    pr("            		            \033[48;5;34m{}\033[0m\n", top_line_str);
    for(unsigned int i = 1; i<=boardSize; i++)
    {
        pr("           		          {} \033[48;5;34m{}", i, CONTENT_CROSS);
        for(unsigned int j = 1; j<=boardSize; j++)
        {
            switch(boardConfiguration[i-1][j-1])
            {
                case piece::EMPTY : pr("{}",EMPTY_PIECE);    break;
                case piece::WHITE : pr("{}", WHITE_PIECE);    break;
                case piece::BLACK : pr("{}", BLACK_PIECE);    break;
                case piece::LEGAL_WHITE : pr("{}", W_LEGAL_PIECE);  break;
                case piece::LEGAL_BLACK : pr("{}", B_LEGAL_PIECE);  break;
            }
            pr("{}", CONTENT_CROSS);
        }
        pr("\033[0m {} \n", i);
        if(i<boardSize)
            pr("            		            \033[48;5;34m{}\033[0m\n", mid_line_str);
        else
            pr("                                    \033[48;5;34m{}\033[0m\n", end_line_str);
    }
    pr("                  		      A   B   C   D   E   F   G   H\n");
}

/**
 * @brief This is a sub-function of the update function that takes the value of scores of both players and updates the visual interface of the user
 * 
 * @param blackScore This contains the value of score of black player
 * @param whiteScore This contains the value of score of white player
 */
void GameplayGUI::displayScore(int blackScore, int whiteScore)
{
    pr("\nBLACK : {}\n", blackScore);
    pr("WHITE : {}\n", whiteScore);
}


/**
 * @brief This function handles the event of game over situation like showing the final scores of the players 
 * 
 * @param blackScore This contains the value of score of black player
 * @param whiteScore This contains the value of score of white player
 */
void GameplayGUI::showGameOver(int blackScore, int whiteScore)
{
    pr("GAME OVER!!");
    if(blackScore>whiteScore)
    {
        pr("BLACK WINS!");
    }
    else if (whiteScore>blackScore)
    {
        pr("WHITE WINS!");
    }
    else if(blackScore==whiteScore)
    {
        pr("IT'S A TIE!");
    }
}
