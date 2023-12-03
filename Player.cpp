#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    // gets the gamemechs and food objects being used and updated in the main game
    mainGameMechsRef = thisGMRef;
    apple = thisFoodRef;

    myDir = STOP;

    objPos tempPos;
    // snake initialized at the center of the board
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

}


Player::~Player()
{
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;

}

void Player::updatePlayerDir()
{
    
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
    // calculate the position of the next head
    
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);
    switch(myDir)
    {
        case UP:
            currentHead.y --;
            if (currentHead.y < 1){
                currentHead.y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;

        case DOWN:
            currentHead.y ++;
            if (currentHead.y > mainGameMechsRef->getBoardSizeY() - 2){
                currentHead.y = 1;
            }
            break;

        case LEFT:
            currentHead.x--;
            if (currentHead.x < 1){
                currentHead.x = mainGameMechsRef->getBoardSizeX() - 2;
            }
            break;

        case RIGHT:
            currentHead.x++;
            if(currentHead.x > mainGameMechsRef->getBoardSizeX() - 2){
                currentHead.x = 1;
            }
            break;
    }

    
    // collision with food check:

    objPosArrayList* basket = apple->getFoodPos();
    objPos tempFood, increaseS;
    bool flag = false;
    char eaten;
    int i, j;

    for (int i = 0; i < basket->getSize(); i++){                    
        basket->getElement(tempFood, i);                        

        if(tempFood.isPosEqual(&currentHead)){

            // get the symbol of the collected food
            eaten = tempFood.getSymbol();
                        
            // take nessessary action
            if (eaten == '@'){                       
                playerPosList->getTailElement(increaseS);      // +10 score, +4 size
                playerPosList->insertHead(currentHead);
                for (j = 0; j < 3; j++)   
                    playerPosList->insertTail(increaseS);           

                for (j = 0; j < 10; j++){
                    mainGameMechsRef->incrementScore();                      
                }
            }
            else if (eaten == '6'){                             
                playerPosList->insertHead(currentHead);         // +2 score, -3 size (1 insert and 4 remove)
                if (playerPosList->getSize() > 4){             
                    for (j = 0; j < 4; j++){
                        playerPosList->removeTail();
                    }
                    
                }
                mainGameMechsRef->incrementScore();
                mainGameMechsRef->incrementScore();
            }
            else if (eaten == 'o'){                              // +1 score, +1 size
                playerPosList->insertHead(currentHead);
                mainGameMechsRef->incrementScore();
                
            }         


            // remove collected item
            objPos outOfBound(-1, -1, 'Z');
            basket->setElement(outOfBound, i);

            // add a counter here for how many food items where collected
            apple->incrementCollectedFood();

            // stop other situation:
            flag = true;
            break;
        }

    }

    // no collision:
    if (flag == false)
    {
        playerPosList->insertHead(currentHead);
        playerPosList->removeTail();
    }

    // when all items collected, generate new ones
    if (apple->getCollectedFood() == basket->getSize()){
        apple->generateFood(playerPosList, mainGameMechsRef);
        apple->resetCollectedFood();
    }
    

    // suicide snake implementation:
    
    objPos tempPos; 
    bool samePosition = false;

    // check if the head of the snake has the same position with any of the rest of the body
    for (int i = 1; i < playerPosList->getSize(); i++)
    {
        playerPosList->getElement(tempPos, i);
        samePosition = tempPos.isPosEqual(&currentHead);

        if (samePosition)
        {
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
            break;
        }
    }

    // win condition (if snake length reaches max array length)
    if (playerPosList->getSize() == ARRAY_MAX_CAP)
    {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }
    
}

