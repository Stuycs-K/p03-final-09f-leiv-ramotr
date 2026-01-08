#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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
      if(player == 0){
        piece[0] = 'O';
        printf("Your Turn --> ");
      }
      else if(player == 1){
        piece[0] = 'X';
        printf("Opponent Turn --> ");
      }
      fgets(move, 10, stdin);
      if(strncmp(move, "TL", 2) == 0){
        board[0][0] = piece[0];
      }
      else if(strncmp(move, "TM", 2) == 0){
        board[0][1] = piece[0];
      }
      else if(strncmp(move, "TR", 2) == 0){
        board[0][2] = piece[0];
      }
      else if(strncmp(move, "ML", 2) == 0){
        board[1][0] = piece[0];
      }
      else if(strncmp(move, "MM", 2) == 0){
        board[1][1] = piece[0];
      }
      else if(strncmp(move, "MR", 2) == 0){
        board[1][2] = piece[0];
      }
      else if(strncmp(move, "BL", 2) == 0){
        board[2][0] = piece[0];
      }
      else if(strncmp(move, "BM", 2) == 0){
        board[2][1] = piece[0];
      }
      else if(strncmp(move, "BR", 2) == 0){
        board[2][2] = piece[0];
      }
      else{
        printf("Invalid move. \n");
        continue;
        //need to allow user to move again.
      }
      print_board(board);
      player = (player + 1) % 2;
      printf("Waiting for opponent...\n");
      }
    }
    else if(strncmp(line, "n\0", 1) == 0){
      exit(0);
    }
    else{
      printf("please type only y (for yes) or n (for no) \n");
    }
  }
}

int main(){
  game_statements();
  return 0;
}
