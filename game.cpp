#include <iostream>
#include <limits>
#include <random>
#include <string>
#include "game.h"

Game::Game() // game constructor
{
    makeBoard(); // calls maeBoard function
    // row = 11;
    // col = 11;
    shipAmount = 0;    // sets shipAmount to 0 for the start of a board
    ai_mode = 0;
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

void Game::easyMode(int shipAmount)
{
    obtainShips(); // calls the obtainShips function
    playerGuess(); // calls the playerGuess function
}

void Game::smartMode(int shipAmount)
{
    obtainShips(); // calls the obtainShips function
    playerGuess(); // calls the playerGuess function
}

void Game::hackerMode(int shipAmount)
{
    obtainShips(); // calls the obtainShips function
    playerGuess(); // calls the playerGuess function
}

void Game::playSound(std::string State, int Player){

    if(State == "Win")
    {
        std::cout << "Player " << Player << " wins the game! \n"; // informs players who won
        std::string command = "afplay -v 0.9 Assets/you_won.mp3";
        system(command.c_str());

    }
    else if(State == "Miss"){
        std::string command = "afplay -v 0.5 Assets/miss.mp3"; 
        system(command.c_str());

    }else if(State == "Hit"){
        std::string command = "afplay -v 0.5 Assets/hit.mp3"; 
        system(command.c_str());
    }
}


void Game::playGame() // game class function 'playGame' controls much of the game logic
{
    int kind_of_game = 0;
    std::cout << "Welcome to Battleship!" << std::endl; // prints out welcome message
    std::cout << "----------------------" << std::endl; // prints out visual break
    std::cout<<"[SYSTEM] - Would you like to play '1 player' or '2 player'?\n[SYSTEM] - Choose 1 or 2: ";
    std::cin>>kind_of_game;
    std::cout << std::endl;
    while (std::cin.fail() || (kind_of_game != 1) && (kind_of_game != 2)) // while input failed
    {
        std::cin.clear();                                                   // clear the cache
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore double input values
        std::cout << "[SYSTEM] - Choose(1 or 2)\n1)1 Player Game\n2)2 Player Game\nselection: "; // ask again for 1 or 2 player game
        std::cin >> kind_of_game;       // store player entry to kind_of_game
    }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore double input values
        if (kind_of_game < 1 || kind_of_game > 2)                               // if the selection isn't 1 or 2...
        {
            std::cout << "[SYSTEM] - Mode selection must be either 1 or 2." << std::endl; // tell player selection must be between 1-2
        }
    if(kind_of_game==1)
    {
        ai = true;
    }
    else if(kind_of_game==2)
    {
        ai = false;
    }

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
    if(ai)
    {
        do
        {
            std::cout << "[SYSTEM] - Would you like to play\n1)Easy\n2)Medium\n3)Hard\nChoose(1-3): ";
            std::cin >> ai_mode;
            std::cout << std::endl;
            while (std::cin.fail()) // while input failed
            {
                std::cin.clear();                                                   // clear the cache
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore double input values

                std::cout << "[SYSTEM] - Choose(1-3)\n1)EasyMode\n2)SmartMode\n3)Hacker Mode\nselection: "; // ask again for the mode
                std::cin >> ai_mode;       // store player entry to ai_mode
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore double input values
            if (ai_mode < 1 || ai_mode > 3)                               // if the shipAmount isn't 1-3...
            {
                std::cout << "[SYSTEM] - Mode selection must be between 1-3." << std::endl; // tell player mode must be between 1-3
            }

            if(ai_mode==1)
            {
                easyMode(shipAmount);
            }
            else if(ai_mode==2)
            {
                smartMode(shipAmount);
            }
            else if(ai_mode==3)
            {
                hackerMode(shipAmount);
            }
        } while(ai_mode<1 || ai_mode>3);
    }
    else
    {
        obtainShips(); // calls the obtainShips function
        playerGuess(); // calls the playerGuess function
    }
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

    if(!ai)
    {
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
    else// our ai stuff
    {
        char convertLetter[] = {'A','B','C','D','E','F','G','H','I','J'}; //this array is called in order to convert a number into a char
        char randX; //variable that will store the letter of the column where the ai is placing their ship
        int randY = 0; //variable that will store the number of the row where the ai is placing their ship
        int index; //variable used to convert a chart back into an int
        bool isValidCoord = false; // bool to check if the index is a valid coordinate
        bool vertical = false; //bool to check if the ai has begun placing their ships horizontal or vertical
        char previousX; //stores the previous column letter of the index placed
        int previousY = 0; //stores the previous row number of the index placed
        char orientation; //states what direction the ai should place their ships (either horizontal vertical or either)
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr_x(0, 9); // define the range for the random numbers
        std::uniform_int_distribution<> distr_y(1, 10); // define the range for the random numbers
        randX = convertLetter[distr_x(gen)]; //Ai places ship 1 at any X coordinate (A-J)
        randY = distr_y(gen); //Ai places ship 1 at any Y coordinate (1-10)
        player2->addShip(0, 0, randX, randY, 1); // adds ship to ai's board
        player2->getShipInfo(0, 0);  // outputs to user what index the ai placed their ship (will delete later)          
        std::cout << std::endl; // new line
        std::cout << "AI SHIP BOARD" << std::endl; 
        std::cout << "-------------------" << std::endl; 
        player2->printShipBoard(); // print ais board (will delete later)
        std::cout << std::endl; // new line
        
        /* AI - Ship creation when shipAmount is more than 1 */
        for (int i = 2; i <= shipAmount; i++) // for the second ship and each one after...
        {
            for (int j = 0; j < i; j++) // for each coordinate of the new ship...
            {
                if(j==0)//if a new ship is being placed
                {
                    do
                    {
                        randX = convertLetter[distr_x(gen)]; //Ai generates random x coordinate (letter)
                        randY = distr_y(gen); //Ai generates random y coordinate (number)
                        orientation = EnoughSpace(randX, randY, i);
                    } while (isOverlapCoord(player2, randX, randY) || orientation=='O');//the ai will continue to generate coordinates until an empty and valid index is found
                    previousX = randX; //store where the x coordinate was placed
                    previousY = randY; //store where the y coordinate was placed
                    player2->addShip(i - 1, j, randX, randY, i); //add the coordinate to the ai's board
                    player2->getShipInfo(i - 1, j); // outputs to user what index the ai placed their ship (will delete later)                          
                    std::cout << std::endl; // new line
                    std::cout << "AI SHIP BOARD" << std::endl; // informs player on whos board it is
                    std::cout << "-------------------" << std::endl; // extra spacing
                    player2->printShipBoard(); // print ais board (will delete later)
                    std::cout << std::endl; // new line
                }
                else if(j==1)//if the second coordinate of a ship is being placed 
                {
                    do
                    {
                        randX = convertLetter[distr_x(gen)]; //Ai generates random x coordinate (letter)
                        randY = distr_y(gen); //Ai generates random y coordinate (number)
                        for(int k=0; k <= 9; k++) //loop to go through every possible letter
                        {
                            if(randX == convertLetter[k])//if the random letter generated is equal to one of the possible letters...
                            {
                                index = k;//store what position in the array that random letter is 
                            }
                        }

                        if( (abs(randY-previousY)==1) && (previousX == randX))//if the second value of the ship being placed is one row above or below the previous row and in the same column...
                        {
                            if( (orientation=='B') || (orientation=='V') )
                            {
                                isValidCoord = true; //this is a valid coordinate
                                vertical = true; //record that the ai is starting to place their ships vertically
                            }
                        }
                        else if( (abs(randY-previousY)==0) && ((previousX == convertLetter[index+1]) || (previousX == convertLetter[index-1])) && ((index-1)>=0) && ((index+1)<=9))//if the second value is in the same row as the original coordinate and one column to the left/right...
                        {
                            if( (orientation=='B') || (orientation=='H') )
                            {
                                isValidCoord = true;//this is a valid coordinate
                                vertical = false;//record that the ai is starting to placed their ships horizontally
                        
                            }
                        }
                        else
                        {
                            isValidCoord = false;//this is not a valid coordinate
                        }
                    }while(!isValidCoord || isOverlapCoord(player2, randX, randY));//this function will continue to run if the ai did not generate a valid coordinate or if the coordinate generated overlaps with a previous coordinate
                    previousX = randX; //store where the x coordinate was placed
                    previousY = randY; //store where the y coordinate was placed
                    isValidCoord = false; //reset isValidCoord back to false
                    player2->addShip(i - 1, j, randX, randY, i); //add the coordinate to the ai's board
                    player2->getShipInfo(i - 1, j); // outputs to user what index the ai placed their ship (will delete later)                                       
                    std::cout << std::endl; // new line
                    std::cout << "AI SHIP BOARD" << std::endl; // informs player on whos board it is
                    std::cout << "-------------------" << std::endl; // extra spacing
                    player2->printShipBoard(); // print ai's board (will delete later)
                    std::cout << std::endl; // new line
                }
                else//if the third, fourth, or fifth coordinate of a ship is being placed 
                {
                    do
                    {
                        randX = convertLetter[distr_x(gen)]; //Ai generates random x coordinate (letter)
                        randY = distr_y(gen); //Ai generates random y coordinate (letter)
                        for(int k=0; k <= 9; k++) //loop to go through every possible letter
                        {
                            if(randX == convertLetter[k])//if the random letter generated is equal to one of the possible letters...
                            {
                                index = k; //store what position in the array that random letter is 
                            }
                        }

                        if(vertical)//if the second coordinate was placed vertically to the original
                        {
                            if( (abs(randY-previousY)==1) && (previousX == randX) ) //if the second value of the ship being placed is one row above or below the previous row and in the same column...
                            {
                                isValidCoord = true; //this is a valid coordinate
                            }
                            else if(isVerticalTo(player2, randX, randY, i))//if the the ship is being blocked by another ship or the border of the board, then try placing in the other direction to fit the rest of the ship
                            {
                                isValidCoord = true; //this is a valid coordinate 
                            }
                            else
                            {
                                isValidCoord = false; //this is not a valid coordinate
                            }
                        }
                        else // if the second coordinate was placed horizontally to the original
                        {
                            if(abs(randY-previousY)==0)//if the second value is in the same row as the original coordinate 
                            {
                                if( (previousX == convertLetter[index+1]) && ((index+1)<=9) )//if the coordiante is to the right of the original index
                                {
                                    isValidCoord = true;//this is a valid coordinate
                                }
                                else if( (previousX == convertLetter[index-1]) && ((index-1)>=0) )//if the coordinate is to the left of the original index
                                {
                                    isValidCoord = true;//this is a valid coordinate
                                }
                                else if(isHorizontalTo(player2, randX, randY, i))//if the coordinate is either directly to the left or right of the previous ship coordinates
                                {
                                    isValidCoord = true;//this is a valid coordinate
                                }
                                else
                                {
                                    isValidCoord = false;//this is not a valid coordinate
                                }
                            }
                            else
                            {
                                isValidCoord = false;//this is not a valid coordinate
                            }
                        }
                    }while(!isValidCoord || isOverlapCoord(player2, randX, randY));//if the generated coordinate is not valid or overlaps with another ship then generate two coordinates again
                    previousX = randX; //store where the x coordinate was placed
                    previousY = randY; //store where the y coordinate was placed
                    isValidCoord = false; //reset isValidCoord back to false
                    player2->addShip(i - 1, j, randX, randY, i); //add the coordinate to the ai's board
                    player2->getShipInfo(i - 1, j);  // outputs to user what index the ai placed their ship (will delete later)                                                         
                    std::cout << std::endl; // new line
                    std::cout << "AI SHIP BOARD" << std::endl; // informs player on whos board it is
                    std::cout << "-------------------" << std::endl; // extra spacing
                    player2->printShipBoard(); // print ai's board (will delete later)
                    std::cout << std::endl; // new line
                }
            }
        }
    }
}

char Game::EnoughSpace(char xLetter, int yNumber, int shipNumber)
{
    bool cont = true;
    int aboves = 0;
    int belows = 0;
    int lefts = 0;
    int rights = 0;

    //above counter
    for(int i=0; cont; i++)
    {
        if( ((yNumber+i)>10) || (player2->ExistingShip(xLetter, yNumber)) )
        {
            cont = false;
        }
        else
        {
            aboves++;
        }
    }
    //below counter
    for(int i=0; cont; i++)
    {
        if( ((yNumber-i)<1) || (player2->ExistingShip(xLetter, yNumber)) )
        {
            cont = false;
        }
        else
        {
            belows++;
        }
    }
    //right counter
    for(int i=0; cont; i++)
    {
        if( ( (ConvertToNumber(xLetter)+i) >9 ) || (player2->ExistingShip(xLetter, yNumber)) )
        {
            cont = false;
        }
        else
        {
            rights++;
        }
    }
    //left counter
    for(int i=0; cont; i++)
    {
        if( ( (ConvertToNumber(xLetter)-i) <0 ) || (player2->ExistingShip(xLetter, yNumber)) )
        {
            cont = false;
        }
        else
        {
            lefts++;
        }
    }
    //both counter
    if( ((aboves+belows+1) >= shipNumber) &&  ((lefts+rights+1) >= shipNumber))
    {
        return('B');
    }
    //vertical counter
    else if( ((aboves+belows+1) >= shipNumber) )
    {
        return('V');
    }
    //horizontal counter
    else if( (lefts+rights+1) >= shipNumber )
    {
        return('H');
    }
    return('O');
}

bool Game::isHorizontalTo(Player* thisPlayer, char xLetter, int yNumber, int shipNumber) //checks if the ai has started to place their ships horizontally
{
    char convertLetter[] = {'A','B','C','D','E','F','G','H','I','J'};//used to convert char to int
    int index = 0;//used to convert random generated column letter to an int
    int index_2 = 0;//used to convert previously placed ship column letters to an int
    for(int k=0; k <= 9; k++)//loop to go through every possible letter
    {
        if(xLetter == convertLetter[k]) //if the random letter generated is equal to one of the possible letters...
        {
            index = k;//store what position in the array that random letter is
        }
    }

    for (int i = 0; i < shipAmount; i++) // for each ship
    {
        for (int j = 0; j < (i + 1); j++) // for each position of coordinates
        {
            if(i==shipNumber-1)// if trying to place a certain ship, we only care about where the previous coordinates of that ship are
            {
                for(int k=0; k<=9; k++)//loop to go through every possible letter
                {
                    if(thisPlayer->getShip(i)->getXCoord(j) == convertLetter[k])//if the previously placed coordinates of a ship is equal to one of the possible letters...
                    {
                        index_2 = k;//store what position in the array that coordinate is
                    }
                }
                if (thisPlayer->getShip(i)->getYCoord(j) == yNumber && index_2 == index-1) //if the random generated y coordinate is in the same row as the previous coordinates and the random generated x coordinate is 1 column to the left of the previously placed ships...
                {
                    return true; //this is a valid coordinate to place the next ship coordinate
                }
                else if(thisPlayer->getShip(i)->getYCoord(j) == yNumber && index_2 == index+1) //if the random generated y coordinate is in the same row as the previous coordinates and the random generated x coordinate is 1 column to the right of the previously placed ships... 
                {
                    return true;//this is a valid coordinate to place the next ship coordinate
                }
            }
        }
    }
    return false; // this is not a valid coordinate to place the next ship coordinate and thus another two values should be generated
}

int Game::ConvertToNumber(char letter)
{
    char convertLetter[] = {'A','B','C','D','E','F','G','H','I','J'};//used to convert char to int
    for(int k=0; k <= 9; k++)//loop to go through every possible letter
    {
        if(letter == convertLetter[k]) //if the random letter generated is equal to one of the possible letters...
        {
            return k;
        }
    }
}

bool Game::isVerticalTo(Player* thisPlayer, char xLetter, int yNumber, int shipNumber) 
{
    for (int i = 0; i < shipAmount; i++) // for each ship
    {
        for (int j = 0; j < (i + 1); j++) // for each position of coordinates
        {
            if(i==shipNumber-1)// if trying to place a certain ship, we only care about where the previous coordinates of that ship are
            {
                if (thisPlayer->getShip(i)->getXCoord(j) == xLetter && thisPlayer->getShip(i)->getYCoord(j) == yNumber-1) //if the x coordinate being placed is in the same column as the other previously placed coordinates and one row above the previously placed coordinate
                {
                    return true; //this is a valid coordinate to place the next ship coordinate
                }
                else if(thisPlayer->getShip(i)->getXCoord(j) == xLetter && thisPlayer->getShip(i)->getYCoord(j) == yNumber+1) //if the x coordinate being placed is in the same column as the other previously placed coordinates and one row below the previously placed coordinate
                {
                    return true; //this is a valid coordinate to place the next ship coordinate
                }
            }
        }
    }
    return false; // this is not a valid coordinate to place the next ship coordinate and thus another two values should be generated
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
            playSound("Hit", 0);
            (player1->getAttackBoard())[yGuess][(int)(xGuess-64)] = 'R'; // sets the spot as hit on the map
            if (player2->allShipDown()) // if all the ships are sunk
            {
                finishGame(1); // finish the game 
            }
        }
        else // otherwise...
        {
            //player1->editAttackBoard((int)(xGuess - 64), yGuess, false); // if it didn't hit anything, update board coord to 'WHITE'
            playSound("Miss", 0);
            (player1->getAttackBoard())[yGuess][(int)(xGuess-64)] = 'W'; // sets the spot as a miss on the map
        }
        // printBoardP1();

        if (!ai)
        {
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
        }
        else{
            if (ai_mode == 1) // easy mode
            {
                if (!gameFinished) // if the game isn't finished...
                {
                    ////Setup for random
                    std::random_device rd;
                    std::default_random_engine e1(rd());
                    ////

                    sleep(3); //wait three seconds
                    std::cout << std::endl; // new line
                    std::cout << "AI ATTACK BOARD" << std::endl; // lets player know it's AI's turn
                    std::cout << "------------------------------------" << std::endl; // extra spacing
                    player2->printAttackBoard(); // print player AI's attack board
                    std::cout << std::endl; // new line

                    /* AI : Guessing Coordinates */
                    std::cout << "[ATTACK] AI enters X coordinate (A-J): "; // ask for x coordinate
                    char xChoices[] = {'A','B','C','D','E','F','G','H','I','J'};
                    std::uniform_int_distribution<int> random_x(0, 9); // sets random_x to generate a random integer (an index for xChoices) between 0 and 9 inclusive
                    xGuess = xChoices[random_x(e1)];
                    std::cout << xGuess << "\n";
                    
                    std::cout << "[ATTACK] AI - enters Y coordinate (1-10): "; // ask player for y coordinate
                    std::uniform_int_distribution<int> random_y(1, 10); // sets random_y to generate a random integer between 1 and 10 inclusive
                    yGuess = random_y(e1);
                    std::cout << yGuess << "\n";

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
            }
            if (ai_mode == 2) // smart mode
            {
                (player2->getAttackBoard())[yGuess][(int)(xGuess-64)] = 'R'; // sets the spot as hit on the map
                if (player1->allShipDown()) // if all the ships are sunk
                {

                    int tempx = xGuess; // tempx is equal to last x guess from AI
                    int tempy = yGuess; // tempy is equal to last y guess from AI

                    ////Setup for random
                    std::random_device rd;
                    std::default_random_engine e1(rd());
                    ////

                    sleep(3); //wait three seconds
                    std::cout << std::endl; // new line
                    std::cout << "AI ATTACK BOARD" << std::endl; // lets player know it's AI's turn
                    std::cout << "------------------------------------" << std::endl; // extra spacing
                    player2->printAttackBoard(); // print player AI's attack board
                    std::cout << std::endl; // new line

                    if((player2->getAttackBoard())[tempy][(int)(tempx-64)] == 'R')
                    {
                        //goes right first
                        /* AI : Guessing Coordinates */
                            std::cout << "[ATTACK] AI enters X coordinate (A-J): "; // ask for x coordinate
                            xGuess = tempx + 1;
                            tempx = xGuess;
                            std::cout << xGuess << "\n";
                            
                            std::cout << "[ATTACK] AI - enters Y coordinate (1-10): "; // ask player for y coordinate
                            yGuess = tempy;
                            std::cout << yGuess << "\n";
                    }
                    else  // Initial AI attack and if a ship was not hit last turn
                    {
                        /* AI : Guessing Coordinates */
                            std::cout << "[ATTACK] AI enters X coordinate (A-J): "; // ask for x coordinate
                            char xChoices[] = {'A','B','C','D','E','F','G','H','I','J'};
                            std::uniform_int_distribution<int> random_x(0, 9); // sets random_x to generate a random integer (an index for xChoices) between 0 and 9 inclusive
                            xGuess = xChoices[random_x(e1)];
                            tempx = xGuess;
                            std::cout << xGuess << "\n";
                            
                            std::cout << "[ATTACK] AI - enters Y coordinate (1-10): "; // ask player for y coordinate
                            std::uniform_int_distribution<int> random_y(1, 10); // sets random_y to generate a random integer between 1 and 10 inclusive
                            yGuess = random_y(e1);
                            tempy = yGuess;
                            std::cout << yGuess << "\n";
                    }

                    /* Where we need to update new board */
                    if (player1->shipAttacked(xGuess,yGuess)) // if the attack hit a ship...
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
            }
            if (ai_mode == 3) // hacker mode
            {
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
            }
        }
        sleep(3); // wait 3 seconds
    }
}

void Game::finishGame(int winner) // game class 'finishGame' function declares the inputted player as the victor
{
    playSound("Win", winner);
    gameFinished = true; // sets 'gameFinished' to true
}
