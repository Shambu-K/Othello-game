#include "ebony.h"
#include <utility>



//Evaluating appropriate move
ai::ai()
{
    //hello
}

move ai::evaluateMove()
{
    int searchDepth = getSearchDepth();
    mini tempmini;
    piece currentPlayer = getCurrentPlayer();
    if(_moveCount<24)
    {
    tempmini = algorithm(_currentGame,searchDepth,std::make_pair(0,0),currentPlayer,true);
    }
    else 
    {
        tempmini = algorithm(_currentGame,12,std::make_pair(0,0),currentPlayer,false);
    }
    _moveCount++;
    return tempmini.second;
}

mini ai::algorithm(OthelloBoard node,int depth,move movemade,piece currentPlayer,bool useHue)
{
    //for initial moves when move count is less,which ever move has best heuristic be selected
    if(useHue)
    {
        node.searchLegalMoves(_aiColor);
        move bestMove = std::make_pair(0, 0);
        moves allMoves;
        int bestScore=-5000;
        for(auto it: node.legalMoves)
     {
         allMoves.push_back(it.first);
     }
     while(!allMoves.empty())
     {
         move tempMove = allMoves.back(); allMoves.pop_back();
         int tempScore = heuristicValue(node,_aiColor);
         if(tempScore>bestScore)
         {
             bestScore=tempScore;
             bestMove=tempMove;
         }
     }
     std::pair<int,std::pair<unsigned int,unsigned int>> hmove;
     hmove.first=bestScore;hmove.second=bestMove;
     return hmove;
    }
    else
    {
        //recursion code for minimax;
        std::vector<std::vector<piece>> tempboardConfiguration=node.boardConfiguration;
        int bestScore=0;
        move bestMove=std::make_pair(0,0);
        for(int i=1;i<=depth;i++)
        {
            std::vector<std::vector<piece>> tBoard=tempboardConfiguration;
            node.searchLegalMoves(_aiColor);moves allMoves;
            for(auto it: node.legalMoves)
             {
                  allMoves.push_back(it.first);
             }
             while(!allMoves.empty())
             {

             }
            
            
        }


    }

}

int ai::heuristicValue(OthelloBoard _game, piece maximizingColor)
{
    return mobilityTester(_game, maximizingColor) +
           cornerTester(_game, maximizingColor) +
           fieldTester(_game, maximizingColor);

}

// The mobility tester function. It is benifitial to have many move and to
// restrict the amount of possible moves for the opponent.
int ai::mobilityTester(OthelloBoard _game, piece maximizingColor)
{
    // This function will return a value between 16 and -16 depending on how
    // many moves the maximizing color has above the minimizing color. 
    piece minimizingColor = reverseColor(maximizingColor);
    _game.searchLegalMoves(maximizingColor);
    float maxValue = _game.legalMoves.size();
     _game.searchLegalMoves(minimizingColor);
    float minValue = _game.legalMoves.size();

    if (minValue == 0)
    {
        // Opponent can't make any moves.
        return 16;
    }
    else if (maxValue == 0)
    {
        // User can't make any moves.
        return -16;
    }
    else
    {
        // Weight values.
        int returnValue = 16 * ((maxValue - minValue) / (maxValue + minValue));
        return returnValue;
    }
}

// The corener tester function. Returns a value based on how many corner the ai
// have vs how many the opponent have.
int ai::cornerTester(OthelloBoard _game, piece maximizingColor)
{
    // Corner weight.
    constexpr int WEIGHT = 40;

    // This funciton will return the value of a game depending on who has more 
    // corners. It will give the heuristic value of 40 for each own corner.
    int maxCorners{}, minCorners{};
    piece minimizingColor = reverseColor(maximizingColor);

    constexpr std::pair<int, int> corner[4] {
        { 0, 0 }, { 0, 7 }, { 7, 0 }, { 7, 7 }
    };
    for (auto &&pair : corner)
    {
        // Maximizing and minimizing color tests.
        int a = pair.first, b = pair.second;
        if (_game.boardConfiguration[a][b] == maximizingColor) maxCorners++;
        if (_game.boardConfiguration[a][b] == minimizingColor) minCorners++;
    }

    // Add the heuristic Value (40) to the corners.
    maxCorners = maxCorners * WEIGHT;
    minCorners = minCorners * WEIGHT;
    return maxCorners - minCorners;
}

int ai::fieldTester(OthelloBoard _game, piece maximizingColor)
{
    // This function returns the amount of tiles that a player holds over the
    // opponent.
    int returnValue{};
    for (unsigned x = 0; x < 8; x++) 
    {
        for (unsigned y = 0; y < 8; y++)
        {
            if (_game.boardConfiguration[x][y] != piece::EMPTY)
            {
                // Tile isn't empty.
                returnValue += tileWeight(x, y, _game, maximizingColor);
            }
        }
    }

    //Reutrn the return value.
    return returnValue;
}

int ai::tileWeight(unsigned x, unsigned y, OthelloBoard _game, piece maximizingColor)
{
    // Tile weight function for give some tiles extra weight. This function does
    // not perform weights on the sharp corners.
    constexpr int WIDTH = 8, HEIGHT = 8;
    constexpr int weights[HEIGHT][WIDTH] = {
        {  0, -2,  2,  2,  2,  2, -2,  0 },
        { -2, -3,  1,  1,  1,  1, -3, -2 },
        {  2,  1,  1,  1,  1,  1,  1,  2 },
        {  2,  1,  1,  1,  1,  1,  1,  2 },
        {  2,  1,  1,  1,  1,  1,  1,  2 },
        {  2,  1,  1,  1,  1,  1,  1,  2 },
        { -2, -3,  1,  1,  1,  1, -3, -2 },
        {  0, -2,  2,  2,  2,  2, -2,  0 }
    };

    // Return the propriate value
    piece tile = _game.boardConfiguration[x][y];
    if (tile == piece::EMPTY)
    {
        return 0;
    }
    else if (tile == maximizingColor)
    {
        return weights[y][x];
    }
    else
    {
        return -weights[y][x];
    }
}

mini ai::makeMini(int value, unsigned x, unsigned y) const
{
    return { value, { x, y } };
}

int ai::getSearchDepth()
{
    // Shorten the search depth if there are overwhelming many moves available.
    _currentGame.searchLegalMoves(_aiColor);
    int moveCount = _currentGame.legalMoves.size();
    if(moveCount<=7)
    {
        return _searchDepth;
    }
    else 
    {
        return _searchDepth-1;
    }
}

// Set the searchdepth.
void ai::setSearchDepth(unsigned int searchDepth)
{
    _searchDepth = searchDepth;
}
piece ai::reverseColor(piece color)
{
    if(color==piece::BLACK)
    {
        return piece::WHITE;
    }
    if(color==piece::WHITE)
    {
        return piece::BLACK;
    }
    return piece::EMPTY;

}

piece ai::getCurrentPlayer()
{
    piece currentPLayer=_currentPlayer;
}