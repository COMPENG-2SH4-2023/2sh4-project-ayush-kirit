#include "GameMechs.h"

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseflag = false;
    score = 0;
    boardSizeX = 30;
    boardSizeY = 15;
    foodPoss.setObjPos(-1,-1,'o');
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseflag = false;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;
    foodPoss.setObjPos(-1,-1,'0');
}

// do you need a destructor?
/*
GameMechs::~GameMechs()
{

}
*/


bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseflag;
}

char GameMechs::getInput()
{
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseflag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = NULL;
}

void GameMechs::incrementScore()
{
    score++;
}

void generateFood(objPos blockOff)
{
    srand(time(NULL));
    int xCandidate, yCandidate,duplicateFound;

     do{
            xCandidate = 1 + rand() % (boardSizeX - 2); //range is 1 to 29 (inclusive)
            yCandidate = 1 + rand() % (boardSizeY - 2); //range is 1 to 14 (inclusive)
            foodPos.x = xCandidate;
            foodPos.y = yCandidate;
        } while (blockOff.isPosEqual(&foodPos));

    foodPos.x = xCandidate;
    foodPos.y = yCandidate;
}

void getFoodPos(objPos &returnPos)
{

    returnPos.x = foodPos.x;
    returnPos.y = foodPos.y;
    returnPos.symbol = food.symbol;

}