#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000
GameMechs *myGM;
Player *myPlayer;
objPosArrayList *myList;
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();
    while(myGM->getExitFlagStatus() == false || myGM->getLoseFlagStatus == false)
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
    myPlayer = new Player(myGM);
    myList = new objPosArrayList;
    objPos tempPos;
    myPlayer->getPlayerPos(tempPos);
    myGM->generateFood(tempPos);
}

void GetInput(void)
{
    myGM->getInput();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    myGM->clearInput();

    objPos tempPos;
    objPos tempFood;
    myPlayer->getPlayerPos(tempPos);
    myGM->getFoodPos(tempFood);

    if(tempPos.isPosEqual(&tempFood))
    {
        myGM->generateFood(tempPos);
        myGM->incrementScore();
    }


}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
    objPos tempPos;
    objPos tempFood;
    myPlayer->getPlayerPos(tempPos);
    myGM->getFoodPos(tempFood);
    for (int y = 0; y < myGM->getBoardSizeY(); y++)
    {
        for (int x = 0; x < myGM->getBoardSizeX(); x++)
        {
            if (x == 0 || x == myGM->getBoardSizeX() - 1 || y == 0 || y == myGM->getBoardSizeY() - 1)
            {  
                MacUILib_printf("#");
            }
            else if (x == tempFood.x && y == tempFood.y)
            {
                MacUILib_printf("%c", tempFood.symbol);
            } 
            else if (x == tempPos.x && y == tempPos.y)
            {
                MacUILib_printf("%c", tempPos.symbol);
            }
            else
            {
                /*for (int i = 0; i < myList->getSize(); i++)
                {
                    if (x == tempPos.x && y == tempPos.y)
                }
                */
                MacUILib_printf(" ");
            }
        }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
    delete myPlayer;
    delete myGM;
    delete myList;
}
