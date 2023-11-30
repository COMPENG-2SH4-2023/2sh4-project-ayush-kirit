#include "Food.h"

Food::Food(){
    foodBucket = new objPosArrayList();
    
    objPos tempFood;
    for (int i = 0; i < 5; i++){
        tempFood.setObjPos(-1,-1,'o');
        foodBucket->insertTail(tempFood);
    }

    collectedFood = 0;
    
    // tempFood.setObjPos(-1,-1,'@');
    // foodBucket->insertTail(tempFood);

    // tempFood.setObjPos(-1,-1,'6');
    // foodBucket->insertTail(tempFood);
    
}

Food::~Food(){
    delete foodBucket;
}

void Food::generateFood(objPosArrayList *blockOff, GameMechs* GM){
    srand(time(NULL));

    int xCandidate, yCandidate;
    objPos tempPos; // each snake element
    bool samePosition;

    // (bonus)
    int count = 0, i;
    objPos tempFood;
    int bucketSize = foodBucket->getSize();                 // 5 for this project, but now more customizable for future developers

    // // empty out current food Bucket
    // for (i = 0; i < foodBucket->getSize(); i++){            // 0 to 4 (inclusive)
    //     foodBucket->removeTail();
    // }

    // while (count < foodBucket->getSize())
    while (count < bucketSize)
    {
        // random x and y:
        xCandidate = 1 + rand() % (GM->getBoardSizeX() - 2); //range is 1 to 29 (inclusive)
        yCandidate = 1 + rand() % (GM->getBoardSizeY() - 2); //range is 1 to 14 (inclusive)

        // set to a temp variable
        tempFood.x = xCandidate;
        tempFood.y = yCandidate;

        // check if temp overlaps with snake
        for (int i = 0; i < blockOff->getSize(); i++)
        {
            blockOff->getElement(tempPos, i);
            samePosition = tempPos.isPosEqual(&tempFood);

            if (samePosition) break;
        }

        // check if temp overlaps previously generated foods
        for (i = 0; i < count; i++){
            foodBucket->getElement(tempPos, i);
            samePosition = tempPos.isPosEqual(&tempFood);

            if (samePosition) break;
        }

        // if anything overlaps, retry
        if (samePosition) continue;
        
        // set coordinates to specific food element

        // generate '@'
        if (count == 0){
            tempPos.setObjPos(xCandidate, yCandidate, '@');
            foodBucket->setElement(tempPos, count);
        }

        // generate '6'
        else if (count == 1){
            tempPos.setObjPos(xCandidate, yCandidate, '6');
            foodBucket->setElement(tempPos, count);
        }

        // generate three guaranteed o's
        else{
            tempPos.setObjPos(xCandidate, yCandidate, 'o');
            foodBucket->setElement(tempPos, count);
        }

        count++;
        
    }
}

objPosArrayList* Food::getFoodPos(){
    return foodBucket;
}


void Food::incrementCollectedFood(){
    collectedFood++;

}
void Food::resetCollectedFood(){
    collectedFood = 0;
}

int Food::getCollectedFood(){
    return collectedFood;
}