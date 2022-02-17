#include <iostream>
#include "executive.h"

void Executive::run(bool ai) // Executive function called run
{
    myGame.playGame(ai); // calls the playGame function of the game class
}