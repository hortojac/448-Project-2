#include <iostream>
#include "executive.h"

void Executive::run() // Executive function called run
{
    myGame.playGame(); // calls the playGame function of the game class
}

void Executive::run_ai() // Executive function called run
{
    myGame.playGame_ai(); // calls the playGame function of the game class
}