Team 11 Project 2 Documentation

# Person-Hours and Story Points 

### Person-Hour Estimation
15 Hours per person. This rough estimate came from projecting that Project 2 would take less time than the first project, as we didn't have to learn any GUI libraries or change any core functionality; we only had to add supplementary functions. 

In the end, we averaged around 17 hours a person ([our actual accounting of the in-person hours](https://docs.google.com/spreadsheets/d/1lUsOUC2fbRDljCjvxWwighowklgWpwoVV_gzfDf-2TM/edit?usp=sharing)), which was very close to our estimate.  

### Story Point Estimation

| 1 | 2 | 3 | 5 | 8 | 13 | 
| :-- | :-- | :-- | :-- | :-- | :-- | 
|Importing Project|Adding to the Documentation|Sounds|Debugging|Placing ships for Easy Mode|Attack method for Easy Mode|
|Dividing tasks|Existing Ship function|Scoreboard|Adding to Game.cpp|Placing ships for Smart Mode|Attack method for Smart Mode|
|Determining projected hours|Outlining AI Logic|Understanding the code from the last group|Checking if there is enough space for ai to fit their ship|Placing ships for Hacker Mode|Attack method for Hacker Mode|


We estimated that for every story point, we would spend about 2 hours on the project. 

To arrive at this estimate, we split up the requirements of the project into tasks based on initial assessments of their complexity. This breakdown was comprised of guesses, but each guess was based on thorough discussion and outlining — for example, we took into account the multiple helper functions that would have to be written in order to place the AI ships. 

After laying out this framework, we estimated how long each function and method would take us based on how long similar functions took us in project 1. Then we generalized this estimate to the story points.


### Project 1 Team's Software Architecture

We think Group 12, the team our group inherited from, used the client-server architecture in developing their game. 

Usually, a client-server designed program has a resource (server) that the end-user (client) requests data from. This generally comes in the form of a website or some other service that a user would like to access. During usage, The client and server falls into a pattern of requesting and sending data according to a pre-established set of rules of how requests/responses can be sent.

An example of this is Google Maps. A user who would like to access Google Maps goes to the app and sends a request (an address they'd like directions to). The server (Google Maps) then processes this request and sends a response (the directions to the requested address). 

In Group 12's battleship game, the game program itself is analogous to the server. A user who would like to play Battleship starts the program through the terminal and then selects their ship placement, sending a request to the program. The program then sends a response — whether their ship placements are valid. Then, this process is repeated for the second player. Once ship placements are finalized, the next mode of the Battleship game begins. Players begin sending requests — locations to attack. The program processes the requests and sends a response — whether the player was successful in landing a hit. This process repeats itself until a player has won. 

The player and program fall into a pattern of sending messages of requests/responses. Each request/response is outlined according to the communications protocol (i.e. while sending requests, players can *only* select locations for placing ships and attacking, and invalid input is rejected. The program sends responses through terminal output). Because the game follows the messaging pattern commonly seen in client-server architecture, we think that is what Group 12 used in developing their game.


#  The Code

## AI Modes
### Easy: Attacks Randomly
During this mode, the AI chooses a random character from A–J, and a random number from 1–10 during its attack. Once the AI has made a hit, it does not change its attack pattern or strategy. 

This mode has the same functionality as the 2 player game by updating the board with either a R for hit or a W for miss, with the added functionality of playing a sound for either a miss or hit.

### Medium: Attacks Orthogonally
During this mode, the AI will have the same attack pattern as in **Easy** mode (i.e. guessing randomly) until it lands a hit. Then, on subsequent turns, it will guess in four directions (right, left, up, down) from the original attack point until it misses. Once guesses in all four directions return misses, it will return to the Easy mode attack pattern. 

This mode uses our own implemented character array and returns the characters index in the array to be used to traverse on the board, by adding either +1, or -1, for going right or left, and returns the associated character with that index value. For traversing up or down, the index is the same by adding either -1 or +1, for going up or down. If the AI gets to the edge of the board and hits the outer index ranges, it will stop going in that coorespnding direction and will go the other directions.

### Hard: Cheats

During this mode, the AI will locate the Player's ships and attack them every turn until it wins.

## Our Other Additions
- Sound for Players and AI
  - Starting  
  - Hit 
  - Miss 
  - Sunk 
  - Win 
- Score Board
  - How many ships are left
  - Number of ships you’ve sunk
  - Number of ships the opponent has sunk
