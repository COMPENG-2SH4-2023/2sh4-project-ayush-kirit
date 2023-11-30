#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

using namespace std;


class Food
{
    private:
        objPosArrayList* foodBucket;
        int collectedFood;                      // added
    public:
        Food();
        ~Food();

        int getCollectedFood();

        void generateFood(objPosArrayList *blockOff, GameMechs* GM);
        objPosArrayList* getFoodPos();
        void incrementCollectedFood();          // added
        void resetCollectedFood();              // added
};


#endif