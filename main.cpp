#include <iostream>
#include "executive.h"

int main(){
    int kind_of_game;
    std::cout<<"Battleship!\n";
    std::cout<<"Would you like to play '1 player' or '2 player'?\nChoose 1 or 2: ";
    std::cin>>kind_of_game;
    Executive exec; // creates an instance of the Executive class
    if(kind_of_game==1)
    {
        exec.run_ai(); // calls the run function within the Executive class
    }
    else if(kind_of_game==2)
    {
        exec.run(); // calls the run function within the Executive class
    }

    return 0;
}