# Final Project Proposal

## Group Members:

Raphi Ramot and Vanna Lei

# Intentions:

We want to create a Tic Tac Toe Game where you have the option to play with people from other clients and to play two player on one computer. If you choose the two player option, the game memory will be saved on the local computer so you can come back to it.

# Intended usage:

 - The player will connect to the server that will match them with a random client who joins.
 - They'll see a tic tac toe board and they will type in the coordinates of their chosen tile.
 - Both their and their opponent's board will update and they'll wait for the player to respond.
 - The process will repeat and the game will indicate a win loss or draw.
 - Afterwards the game will restart and the score will be kept.  
 - They will have the option to play again with the same client or never again.

# Technical Details:

 - Sockets to connect severs to random clients.
 - Stores game board locally and win-loss rate.
 - use select to listen for new sockets and get user input
 - Working with files to save local memory of that game in the two player option
 - ncurses if have time to make a chat
 - Finding a new opponent: saves PID of client already played with before and if matched again, it will leave the game and search for a different player and it will send the opponent a message that "you displayed horrible sportsmanship".

# How you are breaking down the project and who is responsible for which parts.

Whoever is free to work on the next part will work on it.
Raphi’s main focus will be debugging and making the server and clients connect
Vanna’s main focus will be documentation and designing the gameboard and creative ideas

# Intended pacing:

Wednesday 1/7 - We will have the sockets and documentation layout done.
Thursday 1/8 - Match pairing system
Friday 1/9 - Game board design
Weekend - Make turns
Monday 1/12 - MVP Done
Tues-Thurs - Additional Features
Friday 1/16 - Final checks on Project
