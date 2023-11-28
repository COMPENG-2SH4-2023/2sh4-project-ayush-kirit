#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseflag = false;
    score = 0;
    boardSizeX = 30;
    boardSizeY = 15;
    foodPos.setObjPos(-1,-1,'o');
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseflag = false;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;
    foodPos.setObjPos(-1,-1,'o');
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

    if (input == ' ')
    {
        exitFlag = true;
    }
}

void GameMechs::clearInput()
{
    input = 0;
}

void GameMechs::incrementScore()
{
    score++;
}

void GameMechs::generateFood(objPosArrayList *blockOff)
{
    srand(time(NULL));
    int xCandidate, yCandidate,duplicateFound;
    objPos tempPos; // going to have each object in the list
    bool samePosition = true;

    while (samePosition)
    {
        // generate random position and set foods position to that
        xCandidate = 1 + rand() % (boardSizeX - 2); //range is 1 to 29 (inclusive)
        yCandidate = 1 + rand() % (boardSizeY - 2); //range is 1 to 14 (inclusive)
        foodPos.x = xCandidate;
        foodPos.y = yCandidate;

        // check if any element in the list has the same poistion as food
        // if it does, break out the loop and generate new ones
        for (int i = 0; i < blockOff->getSize(); i++)
        {
            blockOff->getElement(tempPos, i);
            samePosition = tempPos.isPosEqual(&foodPos);

            if (samePosition)
            {
                break;
            }
        }
    }
}

void GameMechs::getFoodPos(objPos &returnPos)
{

    returnPos.x = foodPos.x;
    returnPos.y = foodPos.y;
    returnPos.symbol = foodPos.symbol;
}