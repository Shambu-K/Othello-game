#include "player.h"
#include <iostream>
#include <fmt/core.h>
#include <chrono>
#include <thread>
#define print fmt::print

void OthelloPlayer::initializePlayer(color _col, bool _isAI, unsigned int _boardSize)
{
    pass = false;
    col = _col;
    isAI = _isAI;
    boardSize = _boardSize; 
}

std::optional<std::pair<unsigned int, unsigned int>> OthelloPlayer::getMove(
    std::map<std::pair<unsigned int, unsigned int>, std::vector<std::pair<unsigned int, unsigned int>>>& legalMoves, bool& pass)
{
    if(!isAI)
    {
        return getMoveHuman(legalMoves, pass);
    }
    else
    {
        return getMoveAI(legalMoves, pass);
    }
}

std::optional<std::pair<unsigned int, unsigned int>> OthelloPlayer::getMoveHuman(std::map<std::pair<unsigned int, unsigned int>, std::vector<std::pair<unsigned int, unsigned int>>>& legalMoves, bool& pass)
{
    std::string str;
    std::pair<unsigned int, unsigned int> coord;
    bool validMove;
    if(legalMoves.empty())
    {
        pass = true;
        print("\nNo legal Moves\n");
        system("bash src/press_any_key_to_continue.sh");
        //std::this_thread::sleep_for(std::chrono::seconds(20));
        return {};
    }
    do
    {
        std::optional<std::pair<unsigned int, unsigned int>> coordinate = getCoordinate();
        if(coordinate.has_value())
        {
            coord = coordinate.value();
            validMove = true;
        }
        else
        {
            print("\nInvalid Move!\n");
            validMove = false;
        }
        
    } while (!validMove);

    return std::make_pair(coord.first, coord.second);
}

std::optional<std::pair<unsigned int, unsigned int>> OthelloPlayer::getCoordinate()
{
    std::string str;
    std::pair<unsigned int, unsigned int> coord;
    print("Enter the coordinate where you want to place your move : ");
    std::cin >> str;
    
    if(str.length()!=2)
    {
        return {};
    }
    if((str[0]-'A')>=0 && (str[0]-'A')<boardSize && (str[1]-'1')>=0 && (str[1]-'1')<boardSize)
    {
        return std::make_pair(str[1]-'1', str[0]-'A' );
    }
    else if((str[0]-'a')>=0 && (str[0]-'a')<boardSize && (str[1]-'1')>=0 && (str[1]-'1')<boardSize)
    {
        return std::make_pair(str[1]-'1', str[0]-'a');
    }
    else
    {
        return {};
    }
}

std::optional<std::pair<unsigned int, unsigned int>> OthelloPlayer::getMoveAI(std::map<std::pair<unsigned int, unsigned int>, std::vector<std::pair<unsigned int, unsigned int>>>& legalMoves, bool& pass)
{
    return {};
} 
