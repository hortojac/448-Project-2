#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "ship.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

class Game
{
public:
    Game(); //decalres game constructor
    ~Game(); //decalres game destructor
    void playGame(); //declares playGame function with public scope
    bool ai;
    void makeBoard(); //declares makeBoard function with public scope
    void printBoard(); //declares printBoard function with public scope
    void printScore(Player* thisPlayer, Player* otherPlayer); //declares printScore function with public scope
    void obtainShips(); //declares obtainShips function with public scope
    void playerGuess(); //declares playerGuess function with public scope
    void labels(); //declares labels function with public scope
    bool isOverlapCoord(Player* thisPlayer, char xLetter, int yNumber);
    bool isVerticalTo(Player* thisPlayer, char xLetter, int yNumber, int shipNumber);
    bool isHorizontalTo(Player* thisPlayer, char xLetter, int yNumber, int shipNumber);
    void finishGame(int playerID); //declares finishGame function with public scope
    void easyMode(int ship);
    void smartMode(int ship);
    void hackerMode(int ship);
    int ConvertToNumber(char letter);
    char EnoughSpace(char xLetter, int yNumber, int shipNumber);
    int row = 11; //declares an integer 'row' in public scope set to 11
    int col = 11; //declares an integer 'col' in public scope set to 11
    int shipAmount; //declares an integer 'shipAmount' in public scope set to null
    int ai_mode;
    int ai_hardmode_shipIndex;
    int ai_hardmode_spotIndex;
    bool gameFinished = false; //declares a bool 'gameFinished' initialized to false
    Player *player1; //creates a player1 pointer in the public scope
    Player *player2; //creates a player2 pointer in the public scope

    void playSound(std::string State, int player);

private:
    int **board; // declares an int 'board' in the private scope
};
#endif
