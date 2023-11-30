#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Food.h"           // added post iteration 3
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
    candy = new Food();                 // default food, free????
    myPlayer = new Player(myGM, candy);
    
    
    objPosArrayList *tempList = myPlayer->getPlayerPos();
    candy->generateFood(tempList, myGM);       // generate food
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
    myPlayer->movePlayer();         // uses food
    myGM->clearInput();

}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
    bool drawn;
    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;
    objPos tempFood;
    candy->getFoodPos(tempFood);
    for (int y = 0; y < myGM->getBoardSizeY(); y++)
    {
        for (int x = 0; x < myGM->getBoardSizeX(); x++)
        {
            drawn = false;
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
    

            if (x == 0 || x == myGM->getBoardSizeX() - 1 || y == 0 || y == myGM->getBoardSizeY() - 1)
            {  
                MacUILib_printf("#");
            }

            else if (x == tempFood.x && y == tempFood.y)
            {
                MacUILib_printf("%c", tempFood.symbol);
            } 

            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d\n", myGM->getScore());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    
    if (myGM->getLoseFlagStatus())
    {
        MacUILib_printf("You Ate Yourself :( \nScore: %d\n", myGM->getScore());
    }
    else
    {
        MacUILib_printf("Game Exited!\nScore: %d\n", myGM->getScore());
    }
    MacUILib_uninit();
    delete myPlayer;
    delete myGM;
}
