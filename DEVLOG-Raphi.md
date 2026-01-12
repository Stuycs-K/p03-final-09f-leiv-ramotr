# Dev Log:

This document must be updated daily every time you finish a work session.

## Raphi Ramot

### 2026-01-05 - Planning
Spent class deciding which project to attempt and filling out the proposal document.

### 2026-01-06 - Networking with sockets
Pasted old files for networking and server/client connections. Changed files to work properly and tested across multiple computers.

### 2026-01-07 - Select
Added select in the server file to read from listening_socket and stdin. It will read a buffer from stdin and send to a function that handles the game. It will add any new clients to a list where they get matched.

### 2026-01-08 - Client Logic
Set up matchmaking function in server and did most of client logic to have a game with another client.
At home: Reworked client logic. Changed functions in game to just change the status of the board. In the client file, you are asked whether you want to play locally or online. The online version will receive a player number from the server which will determine if you are X's or O's. Then it takes turns waiting for moves from the server or receiving moves from a user.

### 2026-01-09 - Game Logic w/ local play
Created local play to test the game. Made a way to return to main menu. Added clearer instructions. Next will work on matchmaking so online play works and will add ability to get help info from anywhere in game.

### 2026-01-11 - Matchmaking and online play
Fixed client logic - split up into multiple functions, allowed for help screen, allowed either finding a new opponent or returning to home screen, used select to allow exiting while waiting for an opponent, added precautions for server or opponent disconnecting.
Built server logic - created list to store opponents, matchmaking function that keeps one waiting_fd and pairs new clients with that or sets waiting_fd to the new client, used select to loop through listening_socket and all players to send moves between players and accept new clients, added precations to handle clients quitting.
