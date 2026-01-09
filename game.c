#include "networking.h"

void print_board(char board[][]){
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

int updateboard(char *move, int player, char board[][]){
  char piece;
  if(player == 0){
    piece = 'X';
  }
  else if(player == 1){
    piece = 'O';
  }
  if(strncmp(move, "TL", 2) == 0){
    board[0][0] = piece;
  }
  else if(strncmp(move, "TM", 2) == 0){
    board[0][1] = piece;
  }
  else if(strncmp(move, "TR", 2) == 0){
    board[0][2] = piece;
  }
  else if(strncmp(move, "ML", 2) == 0){
    board[1][0] = piece;
  }
  else if(strncmp(move, "MM", 2) == 0){
    board[1][1] = piece;
  }
  else if(strncmp(move, "MR", 2) == 0){
    board[1][2] = piece;
  }
  else if(strncmp(move, "BL", 2) == 0){
    board[2][0] = piece;
  }
  else if(strncmp(move, "BM", 2) == 0){
    board[2][1] = piece;
  }
  else if(strncmp(move, "BR", 2) == 0){
    board[2][2] = piece;
  }
  else{
    return 0;
  }
  return 1;
}
