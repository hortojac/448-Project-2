#include <iostream>
#include <limits>
#include "game.h"

Game::Game() // game constructor
{
    makeBoard(); // calls maeBoard function
    // row = 11;
    // col = 11;
    shipAmount = 0;    // sets shipAmount to 0 for the start of a board
    player1 = nullptr; // sets the player1 pointer to nullptr
    player2 = nullptr; // sets the player2 pointer to nullptr
}

Game::~Game()
{ // game destructor
    for (int i = 0; i < row; i++)
    {                      // runs for each row in the board
        delete[] board[i]; // deletes the row at int i
    }
    delete[] board; // deletes the empty board
    delete player1; // deletes the player1 instance of player class
    delete player2; // deletes the player2 instance of player class
}

void Game::makeBoard() // game class function 'makeBoard' creates an int 2D array initialized to 0
{
    board = new int *[row];       // sets board as a new array of ints
    for (int i = 0; i < row; i++) // for each row of the board...
    {
        board[i] = new int[col]; // set the row of board at int i to have a columb effectively creating a 2d array
    }

    for (int i = 0; i < row; i++) // for each row of the board...
    {
        for (int j = 0; j < col; j++) // for each columb of the board...
        {
            board[i][j] = 0; // initialze value to 0
        }
    }
    labels(); // call the labels function
}

void Game::labels() // game class function 'labels' sets the values on the edges of the board to their coordinate representations
{
    board[0][0] = '-'; // this line and the following 10 set the first row of the board to visually represent coordinates
    board[0][1] = 'A';
    board[0][2] = 'B';
    board[0][3] = 'C';
    board[0][4] = 'D';
    board[0][5] = 'E';
    board[0][6] = 'F';
    board[0][7] = 'G';
    board[0][8] = 'H';
    board[0][9] = 'I';
    board[0][10] = 'J';

    int val = 1;                  // initializes an int 'val' to 0. only within the scope of labels function
    for (int i = 1; i < row; i++) // for each row of the board...
    {
        board[i][0] = val; // sets the first columb of the board to values 1-10
        val++;             // increases val by 1 each iteration of the for loop
    }
}

void Game::printBoard() // game class function 'printBoard' prints the board to the command line
{
    for (int i = 0; i < row; i++) // for each row of the board...
    {
        for (int j = 0; j < col; j++) // for each columb of the board...
        {
            if (j == 0 && 0 < i && i < 10) // if the coordinate is on the first columb and on row 1 through 9...
            {
                std::cout << board[i][j] << "  "; // print the board value with correct visual spacing
            }
            else
            {
                if ((int)board[i][j] > 10)
                {
                    std::cout << (char)board[i][j] << " ";
                    if (i == 0 && j == 0) // if '-'
                    {
                        std::cout << " ";
                    }
                }
                else
                {
                    std::cout << board[i][j] << " ";
                }
            }
        }
        std::cout << '\n'; // print new line
    }
}

void Game::playGame() // game class function 'playGame' controls much of the game logic
{
    std::cout << "Welcome to Battleship!" << std::endl; // prints out welcome message
    std::cout << "----------------------" << std::endl; // prints out visual break
    do                                                  // loop at least once
    {
        std::cout << "[SYSTEM] - Ship amount: "; // ask for ship amount
        std::cin >> shipAmount;       // store player entry to shipAmount variable

        while (std::cin.fail()) // while input failed
        {
            std::cin.clear();                                                   // clear the cache
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore double input values

            std::cout << "[SYSTEM] - Ship amount (1-5): "; // ask again for the ship amount
            std::cin >> shipAmount;       // store player entry to shipAmount
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore double input values
        if (shipAmount < 1 || shipAmount > 5)                               // if the shipAmount isn't 1-5...
        {
            std::cout << "[SYSTEM] - Ship amount must be between 1-5." << std::endl; // tell player ship amount must be between 1-5
        }
    } while (shipAmount < 1 || shipAmount > 5); // loop if the shipAmount isn't between 1 and 5
    player1 = new Player(shipAmount);           // declares player1 as a new Player with the shipAmount
    player2 = new Player(shipAmount);           // declares player2 as a new Player with the shipAmount
    std::cout << std::endl;
    obtainShips(); // calls the obtainShips function
    playerGuess(); // calls the playerGuess function
}

void Game::obtainShips() // game class function 'obtainShips'
{
    char tempxLetter;       // declares char tempxLetter
    int tempyNumber;        // declares int tempyNumber
    std::cout << "PLAYER 1 SHIP BOARD" << std::endl;
    std::cout << "-------------------" << std::endl;
    printBoard();           // prints the board
    std::cout << std::endl; // creates a new line

    /* PLAYER 1 STARTS HERE */
    do // loop at least once
    {
        std::cout << "[SETUP] Player 1 - enter X coordinate for [1x1] ship (A-J): "; // ask player 1 for the x coordinate of their 1x1 ship
        std::cin >> tempxLetter;                                           // store player input to tempxLetter

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // if double input such as AA, will only take A as input
        //  std::cout << (char)tempxLetter << '\n';
        if ((int)tempxLetter < 65 || (int)tempxLetter > 74) // if unicode for the player input isn't between 65 and 74 (A-J)
        {
            std::cout << "[SYSTEM] - Must enter letter between A and J." << std::endl; // inform player of the error
        }
    } while ((int)tempxLetter < 65 || (int)tempxLetter > 74); // then loop again
    do                                                        // loop at least once
    {
        std::cout << "[SETUP] Player 1 - enter Y coordinate for [1x1] ship (1-10): "; // ask player for the y coordinate for their 1x1 ship
        std::cin >> tempyNumber;                                            // store player input

        while (std::cin.fail()) // while the input is invalid...
        {
            std::cin.clear();                                                   // clear cache
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore double input values

            std::cout << "[SETUP] Player 1 - enter Y coordinate for 1x1 ship (1-10): "; // ask player again for the value
            std::cin >> tempyNumber;                                            // store player input
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore double input values

        if (tempyNumber < 1 || tempyNumber > 10) // if the player input isn't between 1 and 10...
        {
            std::cout << "[SYSTEM] - Must enter number between 1 and 10." << std::endl; // inform player of error
        }
    } while (tempyNumber < 1 || tempyNumber > 10); // loop if input isn't between 1 and 10

    player1->addShip(0, 0, tempxLetter, tempyNumber, 1); // temp line - Lee
    player1->getShipInfo(0, 0);                          // temp line - Lee :: it seems like it is updating the information above function.
    std::cout << std::endl;
    std::cout << "PLAYER 1 SHIP BOARD" << std::endl;
    std::cout << "-------------------" << std::endl;
    player1->printShipBoard();
    std::cout << std::endl;


    /* Player 1 - Ship creation when shipAmount is more than 1 */
    for (int i = 2; i <= shipAmount; i++) // for the second ship and each one after...
    {
        for (int j = 0; j < i; j++) // for each coordinate of the new ship...
        {
            int prevX, prevY; // declare ints prevX and prevY
            /* Asking for X Coordinate */
            bool isValidCoord = false; // declare bool isValidCoord initialized to false

            /* Check if coordinates are valid */
            do
            {
                do // run at least once
                {
                    std::cout << "[SETUP] Player 1 - enter X coordinate " << (j + 1) << " for [1x" << i << "] ship (A-J): "; // ask player one for ships x coordinate
                    std::cin >> tempxLetter; // store player 1 x coord input

                    // Input Check (1) :: if input is not single char
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // if double input such as AA, will only take A as input
                    // Input Check (2) :: if input is not in range
                    if ((int)tempxLetter < 65 || (int)tempxLetter > 74) // if stored value isn't between A and J...
                    {
                        std::cout << "[SYSTEM] - Must enter letter between A and J." << std::endl; // inform player of the error
                    }

                } while ((int)tempxLetter < 65 || (int)tempxLetter > 74); // loop while the error persists

                /* Asking for Y Coordinate */
                do
                {
                    std::cout << "[SETUP] Player 1 - enter Y coordinate " << (j + 1) << " for [1x" << i << "] ship (1-10): "; // ask player one for ships y coordinate
                    std::cin >> tempyNumber; // store player 1 y coord input

                    while (std::cin.fail()) // if input is invalid
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore duplicate inputs

                        std::cout << "[SETUP] Player 1 - enter Y coordinate " << (j + 1) << " for [1x" << i << "] ship (1-10): ";
                        std::cin >> tempyNumber;
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // duplicate failsafe

                    if (tempyNumber < 1 || tempyNumber > 10) // if player y coord input isn't between 1 and 10...
                    {
                        std::cout << "[SYSTEM] - Must enter number between 1 and 10." << std::endl; // inform player of the error
                    }
                } while (tempyNumber < 1 || tempyNumber > 10); // run while the error persists

                // *need to add condition check if coord overlaps with prev ship coords*
                if (j == 0) // when it is first time entering coordinate with multiple coord ship
                {
                    if (isOverlapCoord(player1,tempxLetter, tempyNumber)) // if the input coordinates overlap with pre-exsisting ones
                    {
                        isValidCoord = false; // set coords to invalid
                        std::cout << "[SYSTEM] - Coordinate overlapes with existing coordinate!" << std::endl; // inform player what the error is
                        std::cout << "[SYSTEM] - Overlapping Coordinate : " << tempxLetter << ", " << tempyNumber << std::endl; // inform player of the incorrect coordinate
                    }
                    else // otherwise...
                    {
                        isValidCoord = true; // sets coords to valid
                    }
                }
                else // otherwise...
                {
                    if ( // Input Check (4) :: Coord is next to previous coordinate (e.g. should not be A1, A3)
                        // if coordinates are not next to previous coordinates
                        ((abs((int)tempxLetter - prevX > 1)) || (abs(tempyNumber - prevY) > 1))
                        // if coordinates overlap with previous coord
                        || ((abs((int)tempxLetter - prevX) == 0) && (abs(tempyNumber - prevY) == 0))

                    )
                    {
                        std::cout << "[SYSTEM] - Must enter a new coordinate that is next to your previous coordinate." << std::endl; // inform player what the error is
                        std::cout << "[SYSTEM] - Previous Coordinate : " << (char)prevX << ", " << prevY << std::endl; // inform player of the pervious coordinate
                    }
                    else // otherwise...
                    {
                        if (!isOverlapCoord(player1,tempxLetter, tempyNumber)) // if coordinates are not overlapping...
                        {
                            isValidCoord = true; // sets coords to valid
                        }
                        else // otherwise...
                        {
                            std::cout << "[SYSTEM] - Coordinate overlapes with existing coordinate!" << std::endl; // inform player what the error is
                            std::cout << "[SYSTEM] - Overlapping Coordinate : " << tempxLetter << ", " << tempyNumber << std::endl; // inform player of the overlapping coordinates
                        }
                    }
                }
            } while (!isValidCoord); // loop if coordinates are invalid
            prevX = (int)tempxLetter; // set prevX to the ASCII of tempxLetter
            prevY = tempyNumber; // set prevY to tempynumber
            player1->addShip(i - 1, j, tempxLetter, tempyNumber, i); // temp line - Lee
            player1->getShipInfo(i - 1, j);                          // temp line - Lee :: it seems like it is updating the information above function.
            std::cout << std::endl; // new line
            std::cout << "PLAYER 1 SHIP BOARD" << std::endl; // tell player who's board it is
            std::cout << "-------------------" << std::endl; // extra spacing
            player1->printShipBoard(); // print player1s board
            std::cout << std::endl; // new line
        }
    }
    std::cout << std::endl; // new ling
    for (int i = 0; i < 100; i++) // loop 100 times
    {
        std::cout << std::endl; // create a new line (effectively clearing the command prompt)
    }

    /* PLAYER 2 STARTS HERE */
    std::cout << "PLAYER 2 SHIP BOARD" << std::endl; // tell player who's board it is
    std::cout << "-------------------" << std::endl; // extra spacing
    printBoard(); // print the default board
    do // loop at least once
    {
        std::cout << "[SETUP] Player 2 - enter X coordinate for 1x1 ship (A-J): "; // ask for x coordinate of 1x1 ship
        std::cin >> tempxLetter; // store player input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // if double input such as AA, will only take A as input
        if ((int)tempxLetter < 65 || (int)tempxLetter > 74) // if ASCII of player input isn't between 65 and 74 (A - J)...
        {
            std::cout << "[SYSTEM] - Must enter letter between A and J." << std::endl; // inform player of the error
        }
    } while ((int)tempxLetter < 65 || (int)tempxLetter > 74); // loop while input is incorrect
    do // loop at least once
    {
        std::cout << "[SETUP] Player 2 - enter Y coordinate for [1x1] ship (1-10): "; // ask for y coordinate of 1x1 ship
        std::cin >> tempyNumber; // store value

        while (std::cin.fail()) // while input fails...
        {
            std::cin.clear(); // clear cache
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore double inputs

            std::cout << "[SETUP] Player 2 - enter Y coordinate for [1x1] ship (1-10): "; // ask again
            std::cin >> tempyNumber; // store
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore double input values

        if (tempyNumber < 1 || tempyNumber > 10) // if stored y value isn't between 1 and 10...
        {
            std::cout << "[SYSTEM] - Must enter number between 1 and 10." << std::endl; // inform player of the error
        }
    } while (tempyNumber < 1 || tempyNumber > 10); // loop while error persists

    player2->addShip(0, 0, tempxLetter, tempyNumber, 1); // temp line - Lee
    player2->getShipInfo(0, 0);                          // temp line - Lee :: it seems like it is updating the information above function.
    std::cout << std::endl; // new line
    std::cout << "PLAYER 2 SHIP BOARD" << std::endl; // print information for whos board
    std::cout << "-------------------" << std::endl; // extra spacing
    player2->printShipBoard(); // print player 2s board
    std::cout << std::endl; // new line

    /* PLAYER 2 When ship amount is more than one */
    for (int i = 2; i <= shipAmount; i++) // for the second ship and each one after...
    {
        for (int j = 0; j < i; j++) // for the length of that ship...
        {
            int prevX, prevY; // declare ints 'prevX' and 'prevY'

            /* Asking for X Coordinate */
            bool isValidCoord = false; // declare bool 'isValidCoord' initialized to false
            do // loop at least once
            {

                do // loop at least once
                {
                    std::cout << "[SETUP] Player 2 - enter X coordinate " << (j + 1) << " [for 1x" << i << "] ship (A-J): "; // ask for the x coordinates
                    std::cin >> tempxLetter; // store player input
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // if double input such as AA, will only take A as input
                    if ((int)tempxLetter < 65 || (int)tempxLetter > 74) // if input isn't between A and J...
                    {
                        std::cout << "[SYSTEM] - Must enter letter between A and J." << std::endl; // inform player of the error
                    }
                } while ((int)tempxLetter < 65 || (int)tempxLetter > 74); // loop while error persists

                /* Asking for Y Coordinate */
                do // loop at least once
                {
                    std::cout << "[SETUP] Player 2 - enter Y coordinate " << (j + 1) << " for [1x" << i << "] ship (1-10): "; // ask for y coordinate
                    std::cin >> tempyNumber; // store player input

                    while (std::cin.fail()) // if input fails
                    {
                        std::cin.clear(); // clear cache
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove duplicate inputs

                        std::cout << "[SETUP] Player 2 - enter Y coordinate " << (j + 1) << " for [1x" << i << "] ship (1-10): "; // ask for y coordinate again
                        std::cin >> tempyNumber; // store player input
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore duplicate inputs

                    if (tempyNumber < 1 || tempyNumber > 10) // if y coord isn't between 1 and 10...
                    {
                        std::cout << "[SYSTEM] - Must enter number between 1 and 10." << std::endl; // inform player of the error
                    }

                } while (tempyNumber < 1 || tempyNumber > 10); // loop while error persists

                // *need to add condition check if coord overlaps with prev ship coords*
                if (j == 0) // when it is first time entering coordinate with multiple coord ship
                {
                    if (isOverlapCoord(player2,tempxLetter, tempyNumber)) // if coordinates overlap...
                    {
                        isValidCoord = false; // set coordinates as invalid
                        std::cout << "[SYSTEM] - Coordinate overlapes with existing coordinate!" << std::endl; // inform player of overlapping coords
                        std::cout << "[SYSTEM] - Overlapping Coordinate : " << tempxLetter << ", " << tempyNumber << std::endl; // inform player of which coordinates
                    }
                    else // otherwise...
                    {
                        isValidCoord = true; // set coordinates as valid
                    }
                }
                else // otherwise...
                {
                    if ( // Input Check (4) :: Coord is next to previous coordinate (e.g. should not be A1, A3)
                        // if coordinates are not next to previous coordinates
                        ((abs((int)tempxLetter - prevX > 1)) || (abs(tempyNumber - prevY) > 1))
                        // if coordinates overlap with previous coord
                        || ((abs((int)tempxLetter - prevX) == 0) && (abs(tempyNumber - prevY) == 0))

                    )
                    {
                        std::cout << "[SYSTEM] - Must enter a new coordinate that is next to your previous coordinate." << std::endl; // inform player of the error
                        std::cout << "[SYSTEM] - Previous Coordinate : " << (char)prevX << ", " << prevY << std::endl; // tells player the previous coordinates
                    }
                    else // otherwise...
                    {
                        if (!isOverlapCoord(player2,tempxLetter, tempyNumber)) // if coordinates are not overlapping
                        {
                            isValidCoord = true; // set coordinates as valid
                        }
                        else // otherwise...
                        {
                            std::cout << "[SYSTEM] - Coordinate overlapes with existing coordinate!" << std::endl; // inform player of the error
                            std::cout << "[SYSTEM] - Overlapping Coordinate : " << tempxLetter << ", " << tempyNumber << std::endl; // inform player which coordinates overlap
                        }
                    }
                }
            } while (!isValidCoord); // loop while coordinates are invalid
            prevX = (int)tempxLetter; // sets 'prevX' as the ASCII of 'tempxLetter'
            prevY = tempyNumber; // sets 'prevY' as 'tempyNumber'
            player2->addShip(i - 1, j, tempxLetter, tempyNumber, i); // temp line - Lee
            player2->getShipInfo(i - 1, j);                          // temp line - Lee :: it seems like it is updating the information above function.
            std::cout << std::endl; // new line
            std::cout << "PLAYER 2 SHIP BOARD" << std::endl; // informs player on whos board it is
            std::cout << "-------------------" << std::endl; // extra spacing
            player2->printShipBoard(); // print player 2s board
            std::cout << std::endl; // new line
        }
    }
    for (int i = 0; i < 100; i++) // loop 100 times
    {
        std::cout << std::endl; // new line (effectively clears command prompt)
    }
}

bool Game::isOverlapCoord(Player* thisPlayer, char xLetter, int yNumber) // game class 'isOverlapCoord' function inputs the player class and coordinates and returns bool if they overlap
{
    // Input Check (3) :: if input overlaps with coordinates of existing ship
    for (int i = 0; i < shipAmount; i++) // for each ship
    {
        for (int j = 0; j < (i + 1); j++) // for each position of coordinates
            if (thisPlayer->getShip(i)->getXCoord(j) == xLetter && thisPlayer->getShip(i)->getYCoord(j) == yNumber) // if the coordinates overlap
            {
                return true; // returns true 
            }
    }
    return false; // returns false
}

void Game::playerGuess() // game class 'playerGuess' function that asks for player coordinate input and then applies it to the relevant game board
{
    char xGuess; // declares char 'xGuess'
    int yGuess; // declares int 'yGuess'

    /* PLAYER 1 : Guessing Coordinates */
    while (!gameFinished) // while the game is still going...
    {
        for (int i = 0; i < 100; i++) // loop 100 times
        {
            std::cout << std::endl; // new line (effectively clears the command prompt)
        }
        std::cout << "PLAYER 1 ATTACK BOARD (R=hit W=miss)" << std::endl; // inform which board and a basic key
        std::cout << "------------------------------------" << std::endl; // extra spacing
        player1->printAttackBoard(); // print player 1s board
        std::cout << std::endl; // new line
        do // loop at least once
        {
            std::cout << "[ATTACK] Player 1 - enter X coordinate (A-J): "; // ask for x coordinate
            std::cin >> xGuess; // store player input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // if double input such as AA, will only take A as input
            if ((int)xGuess < 65 || (int)xGuess > 74) // if ASCII of player input isn't between 65 and 74 (A - J)...
            {
                std::cout << "Must enter letter between A and J\n"; // inform player of the error
            }
        } while ((int)xGuess < 65 || (int)xGuess > 74); // loop while error persists
        // std::cout << xGuess << '\n';
        do // loop at least once
        {
            std::cout << "[ATTACK] Player 1 - enter Y coordinate (1-10): "; // ask player for y coordinate
            std::cin >> yGuess; // store player input

            while (std::cin.fail()) // loop while an error occurs
            {
                std::cin.clear(); // clear cache
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // test for duplicate inputs

                std::cout << "[ATTACK] Player 1 - enter Y coordinate (1-10): "; // ask to re-enter y coordinate
                std::cin >> yGuess; // store player input
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore duplicates
            if (yGuess < 1 || yGuess > 10) // if player input isn't between 1 and 10...
            {
                std::cout << "Must enter number between 1 and 10\n"; // inform player of the error
            }

        } while (yGuess < 1 || yGuess > 10); // loop while the error persists
        // std::cout << yGuess << '\n';

        /* Where we need to update new board */
        if (player2->shipAttacked(xGuess, yGuess)) // if the attack hit a ship...
        {
            // 65 is A, to make A number 1 index, -64
            //player1->editAttackBoard((int)(xGuess - 64), yGuess, true); // if it hits ship, update board coord to 'RED'
            (player1->getAttackBoard())[yGuess][(int)(xGuess-64)] = 'R'; // sets the spot as hit on the map
            if (player2->allShipDown()) // if all the ships are sunk
            {
                finishGame(1); // finish the game 
            }
        }
        else // otherwise...
        {
            //player1->editAttackBoard((int)(xGuess - 64), yGuess, false); // if it didn't hit anything, update board coord to 'WHITE'
            (player1->getAttackBoard())[yGuess][(int)(xGuess-64)] = 'W'; // sets the spot as a miss on the map
        }
        // printBoardP1();

        if (!gameFinished) // if the game isn't finished...
        {
            sleep(3); //wait three seconds
            for (int i = 0; i < 100; i++) // loop 100 times
            {
                std::cout << std::endl; // new line (effectively clearing the command prompt)
            }
            std::cout << "PLAYER 2 ATTACK BOARD (R=hit W=miss)" << std::endl; // inform that it's player 2s turn with a basic key
            std::cout << "------------------------------------" << std::endl; // extra spacing
            player2->printAttackBoard(); // print player 2s attack board
            std::cout << std::endl; // new line
            /* PLAYER 2 : Guessing Coordinates */
            do // loop at least once
            {
                std::cout << "[ATTACK] Player 2 - enter X coordinate (A-J): "; // ask for x coordinate
                std::cin >> xGuess; // store player input
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // if double input such as AA, will only take A as input
                if ((int)xGuess < 65 || (int)xGuess > 74) // if ASCII of player input isn't between 65 and 74 (A - J)...
                {
                    std::cout << "Must enter letter between A and J\n"; // inform player of the error
                }
            } while ((int)xGuess < 65 || (int)xGuess > 74); // loop while error persists
            // std::cout << xGuess << '\n';
            do
            {
                std::cout << "[ATTACK] Player 2 - enter Y coordinate (1-10): "; // ask player for y coordinate
                std::cin >> yGuess; // store player input

                while (std::cin.fail()) // loop while an error occurs
                {
                    std::cin.clear(); // clear cache
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // test for duplicate inputs

                    std::cout << "[ATTACK] Player 2 - enter Y coordinate (1-10): "; // ask to re-enter y coordinate
                    std::cin >> yGuess; // store player input
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore duplicates
                if (yGuess < 1 || yGuess > 10) // if player input isn't between 1 and 10...
                {
                    std::cout << "Must enter number between 1 and 10\n"; // inform player of the error
                }

            } while (yGuess < 1 || yGuess > 10); // loop while the error persists
            // std::cout << yGuess << '\n';

            /* Where we need to update new board */
            if (player1->shipAttacked(xGuess, yGuess)) // if the attack hit a ship...
            {
                // 65 is A, to make A number 1 index, -64
                //player2->editAttackBoard((int)(xGuess-64), yGuess, true);// if it hits ship, update board coord to 'RED'
                (player2->getAttackBoard())[yGuess][(int)(xGuess-64)] = 'R'; // sets the spot as hit on the map
                if (player1->allShipDown()) // if all the ships are sunk
                {
                    finishGame(2); // finish the game 
                }
            }
            else // otherwise
            {
                //player2->editAttackBoard((int)(xGuess-64), yGuess, false); // if it didn't hit anything, update board coord to 'WHITE'
                (player2->getAttackBoard())[yGuess][(int)(xGuess-64)] = 'W'; // sets the spot as a miss on the map
            }
            // printBoardP2();
        }
        sleep(3); // wait 3 seconds
    }
}

void Game::finishGame(int winner) // game class 'finishGame' function declares the inputted player as the victor
{
    std::cout << "Player " << winner << " wins the game! \n"; // informs players who won
    gameFinished = true; // sets 'gameFinished' to true
}
