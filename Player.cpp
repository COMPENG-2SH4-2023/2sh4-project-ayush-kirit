#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included

    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');

}


Player::~Player()
{
    // delete any heap members here
    //      no heap member yet, leave empty for now

}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);

}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic   
    
    // How to get input!?!?
    
    char input = mainGameMechsRef->getInput();

    switch(input)
    {   
        case 'w':
            if (myDir == STOP || myDir == LEFT || myDir == RIGHT) {
                myDir = UP;
            }
            break;

        case 'a':
            if (myDir == STOP || myDir == UP || myDir == DOWN) {
                myDir = LEFT;
            }
            break;

        case 's':
            if (myDir == STOP || myDir == LEFT || myDir == RIGHT) {
                myDir = DOWN;
            }
            break;

        case 'd':
            if (myDir == STOP || myDir == UP || myDir == DOWN) {
                myDir = RIGHT;
            }
            break;
        default:
            break;


    }

}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    switch(myDir)
    {
        case UP:
            playerPos.y --;
            if (playerPos.y < 1){
                playerPos.y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;

        case DOWN:
            playerPos.y ++;
            if (playerPos.y > mainGameMechsRef->getBoardSizeY() - 2){
                playerPos.y = 1;
            }
            break;

        case LEFT:
            playerPos.x--;
            if (playerPos.x < 1){
                playerPos.x = mainGameMechsRef->getBoardSizeX() - 2;
            }
            break;

        case RIGHT:
            playerPos.x++;
            if(playerPos.x > mainGameMechsRef->getBoardSizeX() - 2){
                playerPos.x = 1;
            }
            break;
    }



    
}

