#ifndef _GAME_PLAY_UI_H
#define _GAME_PLAY_UI_H

#include "View/Observer.h"
#include <string>
#include <vector>
/**
 * @brief This is the view part of the application. It gets game information from the model
 * and displays it on the screen.
 * 
 * It is a derived class of Observer, as it observes from the model which acts like a Subject.
 * 
 */
class GameplayGUI : public Observer
{
    std::string top_line_str = "";
    std::string mid_line_str = "";
    std::string end_line_str = "";
    public:
    GameplayGUI(unsigned int boardSize);
    void update(piece currentPlayer, int message, std::vector<std::vector<piece>> boardConfiguration, int blackScore, int whiteScore, std::string move) override;
    void displayBoard(std::vector<std::vector<piece>> boardConfiguration);
    void displayScore(int blackScore, int whiteScore);
    void showGameOver(int blackScore, int whiteScore);
};

#endif
