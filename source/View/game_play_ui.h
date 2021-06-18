#ifndef _GAME_PLAY_UI_H
#define _GAME_PLAY_UI_H

#include <TGUI/TGUI.hpp>
#include "View/Observer.h"
class GameplayGUI : public Observer
{
    public:
    sf::RenderWindow window2{{800, 600}, "Othello"};
    tgui::GuiSFML gui2{window2};
    tgui::Picture::Ptr background;
    sf::Texture texture;
    
    std::vector<std::vector<tgui::BitmapButton::Ptr>> cellButtons;
    tgui::Button::Ptr passButton, quitButton, newGameButton;
    tgui::ButtonRenderer render;
    tgui::Label::Ptr nlm_message;
    tgui::Label::Ptr endgame_label;
    tgui::Label::Ptr scoreLabel;
    tgui::ChatBox::Ptr moveHistory;
    tgui::Picture::Ptr background_nlm;
    tgui::Panel::Ptr gameOver;
    tgui::Label::Ptr gameOverMessage, scoreGameOver;
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