**Story Points:**
1: Importing Project, Divinding Tasks, Creating projected hours for project
2: Adding to the Documentation, Checking if there is an Existing Ship, Outlining AI Logic
3: Sounds, Scoreboard, Understanding the code from the last group
5: Re-coding bugs in code, Adding to Game.cpp, Checking if there is enough space for ai to fit their ship
8: Placing ships for Easy Mode, Placing ships for Smart Mode, Placing ships for Hacker Mode
13: Attack method for Easy Mode, Attack method for Smart Mode, Attack method for Hacker Mode

**2 hours/ 1 story point: **
We estimate that for every story point it will take about 2 hours of our time. We arrived at this estimate by first splitting up the more complicated tasks into higher story point categories. We know that if a task has a higher story point, this takes more time. We then discussed the many sub tasks each of the more complicated tasks have — for example, the multiple functions that would have to be written in order to place the AI ships. After laying out this framework, looking back on how long it took us to complete project 1, and discussing our time estimate for project two, we arrived at this hour/story point estimate. 

**Identify the Software Architecture you think the Project 1 team used and explain why you think that:**
We think the team our group inherited from used Pipes and Filter Architecture because they have different classes with specific role and methods pertaining to that class. For example, they have Player class that has getShipInfo method, which when called returns information about specific coordinate. Similarly, they have another class called Game, which has method printBoard when called prints player’s board to the terminal. Because they have different classes for different roles but they depend on each other inputs and outputs, We believe they used Pipes and Filter Architecture.

**Addition to Project 1 (5%):**
Sound for Players and Ai
    Starting
    Hit
    Miss
    Sunk
    Win

Score Board
    How many ships are left
    Number of ships you’ve sunk
    Number of ships the opponent has sunk

