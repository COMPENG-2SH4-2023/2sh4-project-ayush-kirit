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
            plr.y --;
            if (plr.y < 1){
                plr.y = mainGameMechsRef->getBoardSizeY() - 1;
            }
            break;

        case DOWN:
            plr.y ++;
            if (plr.y > mainGameMechsRef->getBoardSizeY() - 1){
                plr.y = 1;
            }
            break;

        case LEFT:
            plr.x--;
            if (plr.x < 1){
                plr.x = mainGameMechsRef->getBoardSizeX() - 1;
            }
            break;

        case RIGHT:
            plr.x++;
            if(plr.x > mainGameMechsRef->getBoardSizeX() - 1){
                plr.x = 1;
            }
            break;
    }
}

