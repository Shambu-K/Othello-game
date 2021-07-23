#ifndef _GAME_PLAY_UI_H
#define _GAME_PLAY_UI_H

#include <TGUI/TGUI.hpp>
#include "View/Observer.h"
class GameplayGUI : public Observer
{
    public:
    ///It is the game window
    sf::RenderWindow window2{{800, 600}, "Othello"};
    ///It makes up the game window using tgui functions
    tgui::GuiSFML gui2{window2};
    ///It is the background image of the game window
    tgui::Picture::Ptr background;
    ///texture of the board pieces
    sf::Texture texture;
    
    ///It is the vector button map of the pieces of the board
    std::vector<std::vector<tgui::BitmapButton::Ptr>> cellButtons;
    tgui::Label::Ptr cellLetterLabels[8];
    tgui::Label::Ptr cellNumberLabels[8];
    tgui::Button::Ptr passButton, quitButton, newGameButton;
    ///It contains the text of pop-up message
    tgui::Label::Ptr nlm_message;
    ///It contains the current score of the game
    tgui::Label::Ptr scoreLabel;
    ///It contains information of all the moves that were made
    tgui::ChatBox::Ptr moveHistory;
    ///It contains the image of the background of pop-up message
    tgui::Picture::Ptr background_nlm;
    ///It contains details of all widgets that are shown during game over
    tgui::Panel::Ptr gameOver;
    ///It conatins the text of gameOver message
    tgui::Label::Ptr gameOverMessage;
    ///It contains the score of the game that is shown during game over
    tgui::Label::Ptr scoreGameOver;
    tgui::Button::Ptr newGame, mainMenu;
    GameplayGUI(unsigned int boardSize);
    void update(piece currentPlayer, int message, std::vector<std::vector<piece>> boardConfiguration, int blackScore, int whiteScore, std::string move) override;
    std::string files[5] = {"./View/Images/green.png", "./View/Images/white.png", "./View/Images/black.png", "./View/Images/legalblack.png", "./View/Images/legalblack.png"};
    void updateBoard(std::vector<std::vector<piece>> boardConfiguration);
    void updateScore(int blackScore, int whiteScore);
    void updateMoveHistory(piece currentPlayer, std::string move);
    void showGameOver(int blackScore, int whiteScore);
};

#endif