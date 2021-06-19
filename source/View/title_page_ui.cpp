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
    tgui::RadioButtonGroup::Ptr radiobuttons = gui.get<tgui::RadioButtonGroup>("radiobuttons");


    tgui::RadioButton::Ptr radioButton1 = gui.get<tgui::RadioButton>("RadioButton1");
    tgui::RadioButton::Ptr radioButton2 = gui.get<tgui::RadioButton>("RadioButton2");
    tgui::RadioButton::Ptr radioButton3 = gui.get<tgui::RadioButton>("RadioButton3");
    tgui::RadioButton::Ptr radioButton4 = gui.get<tgui::RadioButton>("RadioButton4");

    playButton->onMousePress([&]{ //add code here
        tgui::RadioButton::Ptr checked = radiobuttons->getCheckedRadioButton();
        int option = 0;

        if(checked == radioButton1)
            option = 1;
        else if(checked == radioButton2)
            option = 2;
        else if(checked == radioButton3)
            option = 3;
        else if(checked == radioButton4)
            option = 4;
        window.setVisible(false);
        Controller controller(option);
        window.setVisible(true);
    });
    gui.mainLoop();
}
