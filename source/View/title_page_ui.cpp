#include <TGUI/TGUI.hpp>
#include <iostream>
#include "Controller/controller.h"
int main()
{
    //creating the basic window of title page
    sf::RenderWindow window{{800, 600}, "Othello"};
    //setting up the tgui-title page window
    tgui::GuiSFML gui{window};
    //loading the image of icon of the game to icon
     auto icon=sf::Image();
    icon.loadFromFile("./View/Images/icon.png");
    //setting the icon to the game
    window.setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());
    //loading the details of all widgets to the tgui-title page window (visit title_page.txt for more info of the widgets)
    gui.loadWidgetsFromFile("./View/Forms/title_page.txt");
    //setiing up the quit button
    tgui::Button::Ptr quitbutton = gui.get<tgui::Button>("quitButton");
    quitbutton->onMousePress([&]{ window.close(); });
    //setting up the play button
    tgui::Button::Ptr playButton = gui.get<tgui::Button>("playButton");

    //setting up set of buttons of modes of play such as (player vs player (or) player vs ai( greedy (or) random (or) min_max ))
    tgui::RadioButtonGroup::Ptr radiobuttons = gui.get<tgui::RadioButtonGroup>("radiobuttons");
    //setting up player vs player mode of play
    tgui::RadioButton::Ptr radioButton1 = gui.get<tgui::RadioButton>("RadioButton1");
    //setting up player vs greedy ai mode of play
    tgui::RadioButton::Ptr radioButton2 = gui.get<tgui::RadioButton>("RadioButton2");
    //setting up player vs random ai mode of play
    tgui::RadioButton::Ptr radioButton3 = gui.get<tgui::RadioButton>("RadioButton3");

    //handling the event of clicking the play button
    playButton->onMousePress([&]{
        //checking which mode of play is selected
        tgui::RadioButton::Ptr checked = radiobuttons->getCheckedRadioButton();
        int option = 0;
        if(checked == radioButton1)
            option = 1;
        else if(checked == radioButton2)
            option = 2;
        else if(checked == radioButton3)
            option = 3;
        //makes the title page window invisible
        window.setVisible(false);
        //passing on which mode was selected to the controller(controller.cpp)
        Controller controller(option);
        window.setVisible(true);
        playButton->setFocused(false);
    });
    gui.mainLoop();
}
