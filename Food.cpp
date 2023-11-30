#include "Food.h"

Food::Food(){
    foodPos.setObjPos(-1,-1,'o');
}

Food::~Food(){
    // dont need for now
}

void Food::generateFood(objPosArrayList *blockOff, GameMechs* GM){
    srand(time(NULL));
    int xCandidate, yCandidate,duplicateFound;
    objPos tempPos; // going to have each object in the list
    bool samePosition = true;

    while (samePosition)
    {
        // generate random position and set foods position to that
        xCandidate = 1 + rand() % (GM->getBoardSizeX() - 2); //range is 1 to 29 (inclusive)
        yCandidate = 1 + rand() % (GM->getBoardSizeY() - 2); //range is 1 to 14 (inclusive)
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

void Food::getFoodPos(objPos &returnPos){
    returnPos.x = foodPos.x;
    returnPos.y = foodPos.y;
    returnPos.symbol = foodPos.symbol;
}