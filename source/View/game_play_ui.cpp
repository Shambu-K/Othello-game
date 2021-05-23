#include "game_play_ui.h"
#include <thread>
#include <chrono>
#include <string>

GameplayGUI::GameplayGUI(unsigned int boardSize)
{
    sf::Texture texture;
    texture.loadFromFile(files[0]);

    cellButtons.resize(boardSize);

    for(int i = 0; i<boardSize; i++)
    {
        cellButtons[i].resize(boardSize);

        for(int j = 0; j<boardSize; j++)
        {

            cellButtons[i][j] = tgui::BitmapButton::create();
            cellButtons[i][j]->setImage(texture);
            cellButtons[i][j]->setSize(60, 60);
            cellButtons[i][j]->setPosition(i*60*1.f,j*60*1.f);
            gui2.add(cellButtons[i][j]);
        }
    }
        nlm_message = tgui::Label::create();
        nlm_message->setPosition(300, 500);
        gui2.add(nlm_message);
        scoreLabel = tgui::Label::create();
        scoreLabel->setPosition(600, 200);
        scoreLabel->setText("2:2");
        scoreLabel->setTextSize(50);
        gui2.add(scoreLabel);


}

void GameplayGUI::update(int message, std::vector<std::vector<piece>> boardConfiguration, int blackScore, int whiteScore)
{
    sf::Texture texture;
    std::string file;
    sf::Sprite sprite;
    sf::FloatRect sprite_bounds;
    int i = 0, j = 0;
    for(std::vector<piece> row : boardConfiguration)
    {
        j = 0;
        for(piece cell : row)
        {
            switch(cell)
            {
                case piece::EMPTY : file = files[0]; break;
                case piece::WHITE : file = files[1]; break;
                case piece::BLACK : file = files[2]; break;
                case piece::LEGAL_WHITE : file = files[3]; break;
                case piece::LEGAL_BLACK : file = files[4]; break;
            }
            if(!texture.loadFromFile(file)) return;
            cellButtons[i][j]->setImage(texture);
            j++;
        }
        i++;
    }

    scoreLabel->setText(std::to_string(blackScore) + " : " + std::to_string(whiteScore));

    if(message==1)
    {   //display nlm for black
        nlm_message->setText("No legal moves for Black Player");
        nlm_message->showWithEffect(tgui::ShowAnimationType::SlideFromBottom, 2000);
        nlm_message->hideWithEffect(tgui::ShowAnimationType::SlideToBottom, 2000);

    }
    else if(message==2)
    {   //display nlm for white
        nlm_message->setText("No legal moves for White Player!");
        nlm_message->showWithEffect(tgui::ShowAnimationType::SlideFromBottom, 2000);
        nlm_message->hideWithEffect(tgui::ShowAnimationType::SlideToBottom, 2000);
    }
    else if(message==3)
    {   //display game over

    }
}

