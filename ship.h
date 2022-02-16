#ifndef SHIP_H
#define SHIP_H

class Ship
{
    public:
    Ship(int length); //ship constructor with length of the ship as an input
    ~Ship(); //ship deconstructor
    bool isSank(); //returns bool if the ship is sunk
    void setXCoord(int spotNumber, char value); //void function to set the x coordinate of the ship
    char getXCoord(int spotNumber); //returns the char of the x coordinate at the specified length spot on the ship
    void setYCoord(int spotNumber, int value); //void function to set the y cooridnate of the ship
    int getYCoord(int spotNumber); //returns the int of the y coordinate at the specified length spot on the ship
    int getShipLength(); //returns the int of the ship length
    int isExistingShip(int spotNumber, char xCoord, char yCoord);
    void positionAttacked(int spotNumber); //void function to store the length spot as hit
    bool positionDown(int spotNumber); //bool function returns true if the given length spot is hit
    void killShip(); //void function to set the ship as killed

    private:
    int shipLength; // int for the ships length
    int** shipCoords; // 2D array of ints for ship coords
    bool* spotsHit; // array of bools for spots hit
    bool sank; // bool for ship sunk
};
#endif
