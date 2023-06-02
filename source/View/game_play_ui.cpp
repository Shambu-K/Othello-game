#include "game_play_ui.h"
#include <thread>
#include <chrono>
#include <string>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <fstream>

/** 
 * @brief It creates the default version of game window
 * @param boardSize It is the number of squares per side of board 
 */
GameplayGUI::GameplayGUI(unsigned int boardSize)
{
    //loading the image of icon of the game to icon
    auto icon=sf::Image();
    icon.loadFromFile("./View/Images/icon.png");
    //setting the image of icon to the game window
    window2.setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());

    //setting the background of the game window to white using a blank image
    background = tgui::Picture::create("./index.png");
    background->setSize("100%", "100%");
    gui2.add(background);

    for(unsigned int i = 0; i<boardSize; i++)
    {
        cellLetterLabels[i] = tgui::Label::create();
        cellNumberLabels[i] = tgui::Label::create();
        cellLetterLabels[i]->setText(char('A'+i));
        cellNumberLabels[i]->setText(char('1'+i));
        cellLetterLabels[i]->setTextSize(24);
        cellNumberLabels[i]->setTextSize(24);
        cellLetterLabels[i]->setPosition(i*60*1.f + 70.0f,20.0f);
        cellNumberLabels[i]->setPosition(25.0f, i*60*1.f + 69.0f);
        gui2.add(cellLetterLabels[i]);
        gui2.add(cellNumberLabels[i]);
    }
    


    //loading the texture of green background of a game piece
    sf::Texture texture;
    texture.loadFromFile(files[0]);


    cellButtons.resize(boardSize);

    for(unsigned int i = 0; i<boardSize; i++)
    {
        cellButtons[i].resize(boardSize);

        for(unsigned int j = 0; j<boardSize; j++)
        {
            //creating the board pieces one at a time
            cellButtons[i][j] = tgui::BitmapButton::create();
            //setting the texture of board piece to empty green block
            cellButtons[i][j]->setImage(texture);
            //setting the size of board piece
            cellButtons[i][j]->setSize(60, 60);
            //setting the position of board piece
            cellButtons[i][j]->setPosition(i*60*1.f + 50.0f,j*60*1.f + 50.0f);
            //adding the board piece to game window
            gui2.add(cellButtons[i][j]);
        }
    }
        sf::Sprite sprite;
        //loading the background texture of pop-up message
        texture.loadFromFile("./View/Images/background.png");
        //setting the background texture of pop-up message
        sprite.setTexture(texture);
        background_nlm = tgui::Picture::create(texture);
        //setting the position of the background of pop-up message
        background_nlm->setPosition(0, 570);
        //setting the status of the background of pop-up message to invisible
        background_nlm->setVisible(false);
        //adding the background of pop-up message widget to game window
        gui2.add(background_nlm);

        //creating a widget to deliver pop-up message
        nlm_message = tgui::Label::create();
        //setting the position of pop-up text
        nlm_message->setPosition(300, 580);
        //setting the status of pop-up text to invisible
        nlm_message->setVisible(false);
        //adding the pop-up text widget to the game window
        gui2.add(nlm_message);

        //creating a widget to deliver the scores of the players
        scoreLabel = tgui::Label::create();
        //setting the position of score widget
        scoreLabel->setPosition(575, 150);
        //setting the score to default initial score of 2 and 2
        scoreLabel->setText("2:2");
        //setting the size of score text
        scoreLabel->setTextSize(50);
        //addding the score widget to game window
        gui2.add(scoreLabel);

        //creating a widget for pass button
        passButton = tgui::Button::create();
        //setting the position of the pass button
        passButton->setPosition(600, 450);
        //setting the text of pass button
        passButton->setText("Pass");
        //adding the pass button widget to game window
        gui2.add(passButton);


        //creating a widget for quit button
        quitButton = tgui::Button::create();
        //setting the position of the quit button
        quitButton->setPosition(650, 450);
        //setting the text of quit button
        quitButton->setText("Quit");
        //adding the quit button widget to game window
        gui2.add(quitButton);


        //creating a widget for new game button
        newGameButton = tgui::Button::create();
        //setting the position of the new game button
        newGameButton->setPosition(600, 470);
        //setting the text of new game button
        newGameButton->setText("New Game");
        //adding the new game button widget to game window
        gui2.add(newGameButton);

        //creating a chatbox widget for displaying the move history
        moveHistory = tgui::ChatBox::create();
        //setting the size of chat box
        moveHistory->setSize(200, 200);
        //setting the position of chat box
        moveHistory->setPosition(550, 220);
        //addding the chat box widget to game window
        gui2.add(moveHistory);

        //creating a widget to deliver game over message
        gameOver = tgui::Panel::create({"100%", "100%"});
        //setting the text of game over message
        gameOverMessage = tgui::Label::create("Game Over!");
        //creating a widget to show the scores of players during game over
        scoreGameOver = tgui::Label::create();
        //creating a new game button during game over
        newGame = tgui::Button::create("New Game");
        //creating a button to go back to main menu during game over
        mainMenu = tgui::Button::create("Back to Main Menu");
}

/**
 * @brief This function takes the variables that are needed to be updated and updates them as per the move made byb user
 * 
 * @param currentPlayer This contains the details of who is the player that just made a move
 * @param message This contains details regarding whether a pop-up message is to be shown ,if yes then which one
 * @param boardConfiguration This contains details of configuration of board after the move is made
 * @param blackScore This contains the value of score of black player
 * @param whiteScore This contains the value of score of white player
 * @param move This contains details of the move made by current player
 */
void GameplayGUI::update(piece currentPlayer, int message, std::vector<std::vector<piece>> boardConfiguration, int blackScore, int whiteScore, std::string move)
{
    //calling the function updateBoard
    updateBoard(boardConfiguration);
    //calling the function updateScore
    updateScore(blackScore, whiteScore);
    //calling the function updateMoveHistory
    updateMoveHistory(currentPlayer, move);

    //hiding the pop-up message
    if(nlm_message->isVisible() && message==0)
    {
            nlm_message->hideWithEffect(tgui::ShowEffectType::SlideToBottom, 500);
            background_nlm->hideWithEffect(tgui::ShowEffectType::SlideToBottom, 500);
    }

    //displaying no legal moves pop-up message for black player
    if(message==1)
    {
        //setting the text for no legal moves for black
        nlm_message->setText("No legal moves for Black Player");
        //displaying the text for no legal moves for black with a motion effect
        nlm_message->showWithEffect(tgui::ShowEffectType::SlideFromBottom, 1000);
        //displaying the background for pop-up message with a motion effect
        background_nlm->showWithEffect(tgui::ShowEffectType::SlideFromBottom, 1000);
    }
    //displaying no legal moves pop-up message for white player
    else if(message==2)
    {
        //setting the text for no legal moves for white
        nlm_message->setText("No legal moves for White Player!");
        //displaying the text for no legal moves for white with a motion effect
        nlm_message->showWithEffect(tgui::ShowEffectType::SlideFromBottom, 1000);
        //displaying the background for pop-up message with a motion effect
        background_nlm->showWithEffect(tgui::ShowEffectType::SlideFromBottom, 1000);
    }
    //displaying game over
    else if(message==3)
    {
        //calling showGameOver function
        showGameOver(blackScore, whiteScore);
    }
    //display Illegal Move
    else if(message==4)
    {
        //setting up text for illegal move
        nlm_message->setText("Illegal Move!!");
        //displaying the text for illegal move with a motion effect
        nlm_message->showWithEffect(tgui::ShowEffectType::SlideFromBottom, 1000);
        //displaying the background for pop-up message with a motion effect
        background_nlm->showWithEffect(tgui::ShowEffectType::SlideFromBottom, 1000);
    }
}

/**
 * @brief This is a sub-function of the update function that takes the boardconfiguration and updates the visual interface of the board
 * 
 * @param boardConfiguration This contains details of configuration of board after the move is made
 */
void GameplayGUI::updateBoard(std::vector<std::vector<piece>> boardConfiguration)
{
    sf::Texture texture;
    std::string file;
    sf::Sprite sprite;
    sf::FloatRect sprite_bounds;
    int i = 0, j = 0;
    //updating the board configuration
    for(std::vector<piece> row : boardConfiguration)
    {
        j = 0;
        for(piece cell : row)
        {
            switch(cell)
            {
                //selecting the respective file for the configuration of the board piece
                case piece::EMPTY : file = files[0]; break;
                case piece::WHITE : file = files[1]; break;
                case piece::BLACK : file = files[2]; break;
                case piece::LEGAL_WHITE : file = files[3]; break;
                case piece::LEGAL_BLACK : file = files[4]; break;
            }
            //loading the texture of the board piece
            if(!texture.loadFromFile(file)) return;
            //setting the texture of the board piece
            cellButtons[i][j]->setImage(texture);
            j++;
        }
        i++;
    }
}

/**
 * @brief This is a sub-function of the update function that takes the value of scores of both players and updates the visual interface of the user
 * 
 * @param blackScore This contains the value of score of black player
 * @param whiteScore This contains the value of score of white player
 */
void GameplayGUI::updateScore(int blackScore, int whiteScore)
{
    //updating the scores of the players
    scoreLabel->setText(std::to_string(blackScore) + " : " + std::to_string(whiteScore));
}

/**
 * @brief This is sub-function of the update function that takes the details of the current player and move that has been made and updates the moveHistory which inturn is shown on the chatbox
 * 
 * @param currentPlayer This contains the details of who is the player that just made a move
 * @param move This contains details of the move made by current player
 */
void GameplayGUI::updateMoveHistory(piece currentPlayer, std::string move)
{
    std::string player;
    //setting the value of player to currentplayer
    if(currentPlayer==piece::BLACK)
        player = "BLACK";
    else if(currentPlayer==piece::WHITE)
        player = "WHITE";
    else if(currentPlayer==piece::EMPTY)
        player = "The game has started:";
    //adding the details of current move to the move history
    moveHistory->addLine(player + " : " + move);
}

/**
 * @brief This function handles the event of game over situation like showing the final scores of the players 
 * 
 * @param blackScore This contains the value of score of black player
 * @param whiteScore This contains the value of score of white player
 */
void GameplayGUI::showGameOver(int blackScore, int whiteScore)
{
    //setting the background of the game over
    gameOver->getRenderer()->setBackgroundColor({43, 102, 173, 180});
    //adding the gameover widget to game window
    gui2.add(gameOver);

    //setting the text of game over
    gameOverMessage = tgui::Label::create("Game Over!");
    gameOverMessage->setTextSize(72);
    //setting the position of the game over
    gameOverMessage->setPosition(200, 20);
    //adding the details of game over test to game over widget
    gameOver->add(gameOverMessage);

    //setting the text of the scores of the players
    scoreGameOver->setText("BLACK : " + std::to_string(blackScore) + "\nWHITE : " + std::to_string(whiteScore));
    scoreGameOver->setTextSize(50);
    //setting the position of the scores of players text
    scoreGameOver->setPosition(300, 100);
    //setting the color of the scores text
    scoreGameOver->getRenderer()->setTextColor({127,230,18});
    //adding the details of scores text to the game  over widger
    gameOver->add(scoreGameOver);

    //setting the position of the mainMenu button
    mainMenu->setPosition(350, 300);
    //adding the mainMenu button to the gameover widget
    gameOver->add(mainMenu);

    //setting the position of the newgame button
    newGame->setPosition(370, 400);
    //adding the newgame button to the game over widget
    gameOver->add(newGame);
}
