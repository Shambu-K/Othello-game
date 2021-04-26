#include "game.h"
#include <fmt/core.h>
#define print fmt::print

void OthelloGame::initializeGame(bool isBlackAI, bool isWhiteAI)
{
    board.initializeBoard();
    blackPlayer.initializePlayer(color ::_BLACK, isBlackAI, board.boardSize);
    whitePlayer.initializePlayer(color ::_WHITE, isWhiteAI, board.boardSize);
}

void OthelloGame::makeMove(color col)
{
    std::pair<unsigned int, unsigned int> coordMove;
    std::optional<std::pair<unsigned int, unsigned int>> res;
    if(col==color::_BLACK)
    {
        
            do{
                res = blackPlayer.getMove(board.legalMoves, blackPlayer.pass);
                if(!res.has_value())
                    break;
                coordMove.first = res.value().first;    coordMove.second = res.value().second;
                } while(!board.placeMove(piece::BLACK, coordMove));
            board.updateBoard(piece::BLACK);
    }
    else
    {
        do{
                res = whitePlayer.getMove(board.legalMoves, whitePlayer.pass);
                if(!res.has_value())
                    break;
                coordMove = res.value();
                } while(!board.placeMove(piece::WHITE, coordMove));
            board.updateBoard(piece::WHITE);
    }
}

bool OthelloGame::checkGameOver()
{
    if(whitePlayer.pass && blackPlayer.pass)
    {
        if(board.blackScore>board.whiteScore)   print("BLACK WINS!\n");
        else if(board.blackScore<board.whiteScore)   print("WHITE WINS!\n");
        else print("IT'S A TIE!\n");
        return true;
    }
    else
    {
        return false;
    }
}