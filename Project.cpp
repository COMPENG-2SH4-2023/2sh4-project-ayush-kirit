#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Food.h"           
#include "Player.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000
GameMechs *myGM;
Player *myPlayer;
Food *candy;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();
    while(myGM->getExitFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    myGM = new GameMechs;
    candy = new Food();                 
    myPlayer = new Player(myGM, candy);
    
    
    objPosArrayList *tempList = myPlayer->getPlayerPos();
    candy->generateFood(tempList, myGM);       
}

void GetInput(void)
{
    if (MacUILib_hasChar() != 0)
    {
        myGM->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();        
    myGM->clearInput();

}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
    bool drawn;
    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;
    
    objPosArrayList* tempBucket = candy->getFoodPos();
    objPos bucketItem;
    
    for (int y = 0; y < myGM->getBoardSizeY(); y++)
    {
        for (int x = 0; x < myGM->getBoardSizeX(); x++)
        {
            drawn = false;
            // print snake
            for (int i = 0; i < playerBody->getSize(); i++)
            {
                playerBody->getElement(tempBody, i);
                if(tempBody.x == x && tempBody.y == y)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }
            if(drawn) continue;

            // print the foodBucket
            for (int j = 0; j < tempBucket->getSize(); j++){
                tempBucket->getElement(bucketItem, j);
                if (bucketItem.x == x && bucketItem.y == y){
                    MacUILib_printf("%c", bucketItem.symbol);
                    drawn = true;
                    break;
                }
            }

            if(drawn) continue;
    
            // print border
            if (x == 0 || x == myGM->getBoardSizeX() - 1 || y == 0 || y == myGM->getBoardSizeY() - 1)
            {  
                MacUILib_printf("#");
            }

            // print "nothing"
            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d\nSPECIAL FOODS:\n    Cherry '6'     -- +2 score,  -3 size\n    Watermelon '@' -- +10 score, +4 size", myGM->getScore());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    
    if (myGM->getLoseFlagStatus())
    {
        objPosArrayList* checkwin = myPlayer->getPlayerPos(); // to check if snake is at its max length
        if (checkwin->getSize() == ARRAY_MAX_CAP)
        {
            MacUILib_printf("\n\n       YOU WIN!\n");
        }
        else
        {
            MacUILib_printf("\n\n       YOU ATE YOURSELF :(\n");
        }
    }
    else
    {
        MacUILib_printf("\n\n       GAME EXITED!\n");
    }
    MacUILib_uninit();
    delete myPlayer;
    delete myGM;
    delete candy;
}
