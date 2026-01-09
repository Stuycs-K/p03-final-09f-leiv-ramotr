#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
//#include "networking.h"

void print_board(char board[3][3]){
  printf("     |     |     \n");
  printf("  %c  |  %c  |  %c  \n", board[0][0], board[0][1], board[0][2]);
  printf("_____|_____|_____\n");
  printf("     |     |     \n");
  printf("  %c  |  %c  |  %c  \n", board[1][0], board[1][1], board[1][2]);
  printf("_____|_____|_____\n");
  printf("     |     |     \n");
  printf("  %c  |  %c  |  %c  \n", board[2][0], board[2][1], board[2][2]);
  printf("     |     |     \n\n");
}

void game_statements(){
  char line[10];
  int score[8]; //[r0, r1, r2, c3, c4, c5, d6, d7]
  // should be initalized in where client connects;
  char board[3][3];
  for(int i = 0; i<3; i++){
    for(int j = 0; j<3; j++){
      board[i][j] = ' ';
    }
  }
  while(1){
    printf("Would you like to play? (y/n) --> ");
    if(fgets(line, 10, stdin) == NULL){
      continue;
    }
    if(strncmp(line, "y", 1)==0){
      printf("Game Starting...\n");
      print_board(board);

///game features
    int player = 0;
    while(1){
      char move[10];
      char piece[10];
      //assign player piece
      if(player == 0){
        piece[0] = 'O';
        printf("Your Turn --> ");
      }
      else if(player == 1){
        piece[0] = 'X';
        printf("Opponent Turn --> ");
      }
      //have player move
      fgets(move, 10, stdin);
      if((strncmp(move, "TL", 2) == 0) && (board[0][0] == ' ')){
        board[0][0] = piece[0];
        int moveBR[3] = {0,3,6};
        for(int i = 0; i<3; i++){
          if(player == 0) score[moveBR[i]] += 1;
          if(player == 1) score[moveBR[i]] -= 1;
        }
      }
      else if((strncmp(move, "TM", 2) == 0) && (board[0][1] == ' ')){
        board[0][1] = piece[0];
        int moveBR[2] = {0,4};
        for(int i = 0; i<2; i++){
          if(player == 0) score[moveBR[i]] += 1;
          if(player == 1) score[moveBR[i]] -= 1;
        }
      }
      else if((strncmp(move, "TR", 2) == 0) && (board[0][2] == ' ')){
        board[0][2] = piece[0];
        int moveBR[3] = {0,5,7};
        for(int i = 0; i<3; i++){
          if(player == 0) score[moveBR[i]] += 1;
          if(player == 1) score[moveBR[i]] -= 1;
        }
      }
      else if((strncmp(move, "ML", 2) == 0) && (board[1][0] == ' ')){
        board[1][0] = piece[0];
        int moveBR[2] = {1,3};
        for(int i = 0; i<2; i++){
          if(player == 0) score[moveBR[i]] += 1;
          if(player == 1) score[moveBR[i]] -= 1;
        }
      }
      else if((strncmp(move, "MM", 2) == 0) && (board[1][1] == ' ')){
        board[1][1] = piece[0];
        int moveBR[4] = {1,4,6,7};
        for(int i = 0; i<4; i++){
          if(player == 0) score[moveBR[i]] += 1;
          if(player == 1) score[moveBR[i]] -= 1;
        }
      }
      else if((strncmp(move, "MR", 2) == 0) && (board[1][2] == ' ')){
        board[1][2] = piece[0];
        int moveBR[2] = {1,5};
        for(int i = 0; i<2; i++){
          if(player == 0) score[moveBR[i]] += 1;
          if(player == 1) score[moveBR[i]] -= 1;
        }
      }
      else if((strncmp(move, "BL", 2) == 0) && (board[2][0] == ' ')){
        board[2][0] = piece[0];
        int moveBR[3] = {2,3,6};
        for(int i = 0; i<3; i++){
          if(player == 0) score[moveBR[i]] += 1;
          if(player == 1) score[moveBR[i]] -= 1;
        }
      }
      else if((strncmp(move, "BM", 2) == 0) && (board[2][1] == ' ')){
        board[2][1] = piece[0];
        int moveBR[2] = {2,4};
        for(int i = 0; i<2; i++){
          if(player == 0) score[moveBR[i]] += 1;
          if(player == 1) score[moveBR[i]] -= 1;
        }
      }
      else if((strncmp(move, "BR", 2) == 0) && (board[2][2] == ' ')){
        board[2][2] = piece[0];
        int moveBR[3] = {2,5,7};
        for(int i = 0; i<3; i++){
          if(player == 0) score[moveBR[i]] += 1;
          if(player == 1) score[moveBR[i]] -= 1;
        }
      }
      else{
        printf("Invalid move. \n");
        continue;
        //need to allow user to move again.
      }
/*

Game commands end

*/
      print_board(board);
      //check if there's a winner
      for(int i = 0; i<8; i++){
        if(score[i] == 3){
          printf("Winner: You");
          exit(0);
        }
        else if(score[i] == -3){
          printf("Winner: Opponent");
          exit(0);
        }
      }
      //check draw
      bool draw = true; 
      for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
          if(board[i][j] == ' '){
            draw = false;
          }
        }
      }
      if(draw == true){
        printf("Draw!");
        exit(0);
      }

      // next turn
      
      player = (player + 1) % 2;
      printf("Waiting for opponent...\n");
      }
    }
    //leave if typed n
    else if(strncmp(line, "n\0", 1) == 0){
      exit(0);
    }
    // prevents user from typing anything else
    else{
      printf("please type only y (for yes) or n (for no) \n");
    }
  }
}

int main(){
  game_statements();
  return 0;
}
