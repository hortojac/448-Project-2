#ifndef PLAYER_H
#define PLAYER_H
#include "ship.h"

class Player
{
    public:
    Player(int amountShips); // Player constructor with ship amount as an integer input
    ~Player(); // Player destructor
    void addShip(int shipNumber, Ship* ship); // addShip function with shipNumber and ship pointer

    void addShip(int shipNumber, int coordIndex, char xCoord, int yCoord, int shipSize); // addShip function with shipNumber and its data manually
    void getShipInfo(int shipNumber, int coordIndex); //  Temp line - Lee
    void printShipBoard();
    void printAttackBoard();
    void editAttackBoard(char xCoord, int yCoord, bool hit);
    int** getAttackBoard();
    Ship* getShip(int shipNumber); // returns the ship pointer when given the shipNumber
    int getPrevXCoord(int shipNumber, int coordIndex); // returns the previous X coordinate when given the shipNumber and the coordinate index
    int getPrevYCoord(int shipNumber, int coordIndex); // returns the previous Y coordinate when given the shipNumber and the coordinate index

    bool shipAttacked(char xGuess, int yGuess); // returns a bool if the given coordinate matches the ships
    bool allShipDown(); // returns a bool if all ships are sunk

    private:
    Ship** ships; // declares a ship pointer 'ships'
    int** shipBoard;
    int** attackBoard;
    int numberOfShips; // declares an int 'numberOfShips'
};
#endif
