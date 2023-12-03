#include "Food.h"

Food::Food(){
    foodBucket = new objPosArrayList();
    
    objPos tempFood;
    for (int i = 0; i < 5; i++){
        tempFood.setObjPos(-1,-1,'o');
        foodBucket->insertTail(tempFood);
    }

    collectedFood = 0;
    
   
}

Food::~Food(){
    delete foodBucket;
}

void Food::generateFood(objPosArrayList *blockOff, GameMechs* GM){
    srand(time(NULL));

    int xCandidate, yCandidate;
    objPos tempPos; 
    bool samePosition;

    // (bonus)
    int count = 0, i;
    objPos tempFood;
    int bucketSize = foodBucket->getSize(), coin1 = 0, coin2 = 0;                



    while (count < bucketSize)
    {
        // random x and y:
        xCandidate = 1 + rand() % (GM->getBoardSizeX() - 2); 
        yCandidate = 1 + rand() % (GM->getBoardSizeY() - 2); 

        // random variable for probability of special foods:
        coin1 = rand() % 10;
        coin2 = rand() % 10;


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
        
        // if anything overlaps, retry, and don't let next forloop overwrite samePosition
        if (samePosition) continue;

        // check if temp overlaps previously generated foods
        for (i = 0; i < count; i++){
            foodBucket->getElement(tempPos, i);
            samePosition = tempPos.isPosEqual(&tempFood);

            if (samePosition) break;
        }

        // if anything overlaps, retry
        if (samePosition) continue;
        

        // generate '@'
        if (count == 0){
            if (coin1 < 7){                                            
                tempPos.setObjPos(xCandidate, yCandidate, '@');
                foodBucket->setElement(tempPos, count);
            }
            else{
                tempPos.setObjPos(xCandidate, yCandidate, 'o');
                foodBucket->setElement(tempPos, count);
            }
        }

        // generate '6'
        else if (count == 1){
            if (coin2 < 7){
                tempPos.setObjPos(xCandidate, yCandidate, '6');
                foodBucket->setElement(tempPos, count);
            }
            else{
                tempPos.setObjPos(xCandidate, yCandidate, 'o');
                foodBucket->setElement(tempPos, count);               
            }
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