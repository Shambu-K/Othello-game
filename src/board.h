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
    const std::string top_start{"\e[38;5;255m\u250F"};
	const std::string top_line{"\e[38;5;255m\u2501"};
	const std::string top_cross{"\e[38;5;255m\u2533"};
	const std::string top_end{"\e[38;5;255m\u2513"};

	const std::string middle_start{"\e[38;5;255m\u2523"};
	const std::string middle_line{"\e[38;5;255m\u2501"};
	const std::string middle_cross{"\e[38;5;255m\u254B"};
	const std::string middle_end{"\e[38;5;255m\u252B"};

	const std::string bottom_start{"\e[38;5;255m\u2517"};
	const std::string bottom_line{"\e[38;5;255m\u2501"};
	const std::string bottom_cross{"\e[38;5;255m\u253B"};
	const std::string bottom_end{"\e[38;5;255m\u251B"};

	const std::string content_cross{"\e[38;5;255m\u2503"};
    std::vector<std::vector<piece>> boardConfiguration;
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
    
};


#endif