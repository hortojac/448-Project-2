#ifndef EXECUTIVE_H
#define EXECUTIVE_H
#include "game.h" // adds the game class to the scope of the executive class

class Executive
{
public:
    void run(); // declares the run function 

private:
    Game myGame; // creates an instance of the game class in private scope of the executive class
};
#endif