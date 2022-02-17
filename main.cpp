#include <iostream>
#include "executive.h"

int main(){
    int kind_of_game;
    std::cout<<"Battleship!\n";
    std::cout<<"Would you like to play '1 player' or '2 player'?\nChoose 1 or 2: ";
    std::cin>>kind_of_game;
    while (std::cin.fail()) // while input failed
    {
        std::cin.clear();                                                   // clear the cache
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore double input values
        std::cout << "Choose(1 or 2)\n1)1 Player Game\n2)2 Player Game\nselection: "; // ask again for 1 or 2 player game
        std::cin >> kind_of_game;       // store player entry to kind_of_game
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore double input values
        if (kind_of_game < 1 || kind_of_game > 2)                               // if the selection isn't 1 or 2...
        {
            std::cout << "Mode selection must be between 1-2." << std::endl; // tell player selection must be between 1-2
        }
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