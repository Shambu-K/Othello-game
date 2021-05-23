#ifndef _GAME_PLAY_UI_H
#define _GAME_PLAY_UI_H

#include <TGUI/TGUI.hpp>
#include "View/Observer.h"
class GameplayGUI : public Observer
{
    public:
    sf::RenderWindow window2{{800, 600}, "Othello"};
    tgui::GuiSFML gui2{window2};
    sf::Texture texture;
    
    std::vector<std::vector<tgui::BitmapButton::Ptr>> cellButtons;
    tgui::Label::Ptr nlm_message;
    tgui::Label::Ptr endgame_label;
    tgui::Label::Ptr scoreLabel;
    GameplayGUI(unsigned int boardSize);
    void update(int message, std::vector<std::vector<piece>> boardConfiguration, int blackScore, int whiteScore) override;
    std::string files[5] = {"./View/Images/green.png", "./View/Images/white.png", "./View/Images/black.png", "./View/Images/legalblack.png", "./View/Images/legalblack.png"};
};

#endif