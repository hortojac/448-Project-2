#include <iostream>
#include "ship.h"

Ship::Ship(int length) // ship class constructor given ship length
{
    shipLength = length; // sets shipLength to the input length
    shipCoords = new int*[length]; // sets shipCoords as a 2D array of ints of the inputted ship length
    spotsHit = new bool[length]; // sets spotsHit as an array of bools the length of the inputted ship length 
    for (int i = 0; i < length; i++) // for each spot on the ship...
    {
        shipCoords[i] = new int[2]; // set the spots coordinates as a new array of integers with two spots 
        spotsHit[i] = false; // set the spot to not hit (false)
    }
    sank = false; // set the ship as not sunk
    /* Initialize coord values to avoid seg fault */
    for (int i = 0; i < length; i++) // for each spot on the ship...
    {
        shipCoords[i][0] = 0; // sets the x coordinate of the spot to 0
        shipCoords[i][1] = 0; // sets the y coordinate of the spot to 0
    }
}

Ship::~Ship(){ // ship class destructor
    delete[] spotsHit; // deletes spotsHit bool array
    for(int i=0; i<shipLength; i++){ // for each spot on the ship...
        delete[] shipCoords[i]; // delete its coordinates
    }
    delete[] shipCoords; // delete the shipCoords int array
}

bool Ship::isSank() // ship class 'isSank' function will return a bool if the ship is sunk
{
    return sank; // returns status of sank
}

void Ship::setXCoord(int spotNumber, char value) // ship class 'setXCoord' function sets the x coordinate of the given length spot with the given value
{
    shipCoords[spotNumber][0] = value; // sets the spot to the value
}

char Ship::getXCoord(int spotNumber) // ship class 'getXCoord' function returns the char of the given length spot
{
    return shipCoords[spotNumber][0]; // return char of the spot
}

void Ship::setYCoord(int spotNumber, int value) // ship class 'setYCoord' function sets the y coordinate of the given length spot with the given value
{
    shipCoords[spotNumber][1] = value; // sets the spot to the value
}

int Ship::getYCoord(int spotNumber) // ship class 'getYCoord' function returns the int y value of the given length spot
{
    return shipCoords[spotNumber][1]; // returns the y value of the spot
}

int Ship::getShipLength() // ship class 'getShipLength' function returns the length of the ship
{
    return shipLength; // returns ship length int
}

void Ship::positionAttacked(int spotNumber) // ship class 'positionAttacked' function sets the given spot number as hit
{
    spotsHit[spotNumber] = true; // sets the spot as hit
}

bool Ship::positionDown(int spotNumber) // ship class 'positionDown' function returns bool if position is hit
{
    if (spotsHit[spotNumber] == true) // if spot is hit...
    {
        return true; // return true
    }
    return false; // otherwise, return false
}

void Ship::killShip() // sets the ship as sunk
{
    sank = true; // set sank as true
}