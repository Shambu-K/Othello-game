#include "game_play_ui.h"
#include <thread>
#include <chrono>
#include <string>
#include "fmt/core.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <fstream>

#define print fmt::print

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
        sf::Sprite sprite;
        texture.loadFromFile("./View/Images/background.png");
        sprite.setTexture(texture);
        background_nlm = tgui::Picture::create(texture);
        background_nlm->setPosition(0, 570);
        background_nlm->setVisible(false);
        gui2.add(background_nlm);

        nlm_message = tgui::Label::create();
        nlm_message->setPosition(300, 580);
        nlm_message->setVisible(false);
        gui2.add(nlm_message);

        scoreLabel = tgui::Label::create();
        scoreLabel->setPosition(575, 150);
        scoreLabel->setText("2:2");
        scoreLabel->setTextSize(50);
        gui2.add(scoreLabel);

        passButton = tgui::Button::create();
        passButton->setPosition(600, 450);
        passButton->setText("Pass");
        gui2.add(passButton);

        quitButton = tgui::Button::create();
        quitButton->setPosition(650, 450);
        quitButton->setText("Quit");
        gui2.add(quitButton);

        moveHistory = tgui::ChatBox::create();
        moveHistory->setSize(200, 200);
        moveHistory->setPosition(550, 220);
        gui2.add(moveHistory);

        gameOver = tgui::Panel::create({"100%", "100%"});
        gameOverMessage = tgui::Label::create("Game Over!");
        scoreGameOver = tgui::Label::create();
        newGame = tgui::Button::create("New Game");
        mainMenu = tgui::Button::create("Back to Main Menu");
}

void GameplayGUI::update(piece currentPlayer, int message, std::vector<std::vector<piece>> boardConfiguration, int blackScore, int whiteScore, std::string move)
{
    updateBoard(boardConfiguration);
    updateScore(blackScore, whiteScore);
    updateMoveHistory(currentPlayer, move);


    if(nlm_message->isVisible() && message==0)
    {
            nlm_message->hideWithEffect(tgui::ShowAnimationType::SlideToBottom, 500);
            background_nlm->hideWithEffect(tgui::ShowAnimationType::SlideToBottom, 500);
    }

    if(message==1)
    {   //display nlm for black
        nlm_message->setText("No legal moves for Black Player");
        nlm_message->showWithEffect(tgui::ShowAnimationType::SlideFromBottom, 1000);
        background_nlm->showWithEffect(tgui::ShowAnimationType::SlideFromBottom, 1000);
    }
    else if(message==2)
    {   //display nlm for white
        nlm_message->setText("No legal moves for White Player!");
        nlm_message->showWithEffect(tgui::ShowAnimationType::SlideFromBottom, 1000);
        background_nlm->showWithEffect(tgui::ShowAnimationType::SlideFromBottom, 1000);
    }
    else if(message==3)
    {   //display game over
        showGameOver(blackScore, whiteScore);


        
    }
    else if(message==4)
    {   //display Illegal Move
        nlm_message->setText("Illegal Move!!");
        nlm_message->showWithEffect(tgui::ShowAnimationType::SlideFromBottom, 1000);
        background_nlm->showWithEffect(tgui::ShowAnimationType::SlideFromBottom, 1000);
    }
}

void GameplayGUI::updateBoard(std::vector<std::vector<piece>> boardConfiguration)
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
}

void GameplayGUI::updateScore(int blackScore, int whiteScore)
{
    scoreLabel->setText(std::to_string(blackScore) + " : " + std::to_string(whiteScore));
}

void GameplayGUI::updateMoveHistory(piece currentPlayer, std::string move)
{
    std::string player;
    if(currentPlayer==piece::BLACK)
        player = "BLACK";
    else if(currentPlayer==piece::WHITE)
        player = "WHITE";
    else if(currentPlayer==piece::EMPTY)
        player = "The game has started:";
    
    moveHistory->addLine(player + " : " + move);
}

void GameplayGUI::showGameOver(int blackScore, int whiteScore)
{    
    gameOver->getRenderer()->setBackgroundColor({0, 0, 100, 180});
    gui2.add(gameOver);

    gameOverMessage = tgui::Label::create("Game Over!");
    gameOverMessage->setTextSize(72);
    gameOverMessage->setPosition(200, 20);
    gameOver->add(gameOverMessage);

    scoreGameOver->setText("BLACK : " + std::to_string(blackScore) + "\nWHITE : " + std::to_string(whiteScore));
    scoreGameOver->setTextSize(50);
    scoreGameOver->setPosition(300, 100);
    gameOver->add(scoreGameOver);

    mainMenu->setPosition(350, 300);
    gameOver->add(mainMenu);

    newGame->setPosition(350, 400);
    gameOver->add(newGame);
}