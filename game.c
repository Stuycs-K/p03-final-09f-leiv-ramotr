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
      board[i][j] = 'X';
    }
  }
  while(1){
    printf("Would you like to play? (y/n)\n");
    if(fgets(line, 10, stdin) == NULL){
      continue;
    }
    if(line[0] == 'y'){
      printf("start game\n");
      print_board(board);
      exit(0);
    }
    else if(line[0] == 'n'){
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
