#include <TGUI/TGUI.hpp>
#include <iostream>
#include "Controller/controller.h"
int main()
{
    sf::RenderWindow window{{800, 600}, "Othello"};
    tgui::GuiSFML gui{window};
    gui.loadWidgetsFromFile("./View/Forms/title_page.txt");
    tgui::Button::Ptr quitbutton = gui.get<tgui::Button>("quitButton");
    quitbutton->onMousePress([&]{ window.close(); });
    tgui::Button::Ptr playButton = gui.get<tgui::Button>("playButton");
    playButton->onMousePress([&]{ //add code here
        Controller controller;
    });
    gui.mainLoop();
}
