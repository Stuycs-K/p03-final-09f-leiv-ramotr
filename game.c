#include "networking.h"
char board[3][3];
int score[8];

void print_board(){
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

void print_help() {
  printf("\n");
  printf("Game Manual\n");
  printf("1. Playing locally means you are playing on the same computer with your opponent.\n Playing against a random opponent means you will be connected to a specified server and given an opponent.\n");
  printf("2. To play the game, type the coordinates of an empty box.\n");
  printf("Top (T), Middle(M), Bottom (B), Left (L), Right(R)\n");
  printf("TL | TM | TR \n———|————|——— \nML | MM | MR \n———|————|——— \nBL | BM | BR\n\n");
  printf("3. If already taken, you will be prompted to choose a different spot.\n");
  printf("4. Wait for your opponent's turn and repeat. Enter \'home\' at any time to return to the home menu.\n");
  printf("5. Have your pieces three in a row or diagonally to win.\n");
  printf("6. If you are playing online, when the game is over, you will have the option to play again with the same opponent, play with a new opponent, or return to the home menu.\n");
  printf("7. If your opponent leaves, you will be sent to the queue to wait for a new opponent. If the server disconnects, you will be sent to the home menu.\n");
  printf("8. If you are playing locally, you can play again or return home by typing \'home\' after the game ends. \n");
  printf("\n");
}

void reset_board() {
  // set board to spaces
  for(int i = 0; i<3; i++){
    for(int j = 0; j<3; j++){
      board[i][j] = ' ';
    }
  }
  // set scores to 0
  for (int i=0; i<8; i++) {
    score[i]=0;
  }
}

int update_board(char *move, int player){
  char piece;
  if(player == 1){
    piece = 'X';
  }
  else if(player == 2){
    piece = 'O';
  }
  if((strcmp(move, "TL") == 0) && (board[0][0] == ' ')){
    board[0][0] = piece;
    int moveBR[3] = {0,3,6};
    for(int i = 0; i<3; i++){
      if(player == 1) score[moveBR[i]] += 1;
      if(player == 2) score[moveBR[i]] -= 1;
    }
  }
  else if((strcmp(move, "TM") == 0) && (board[0][1] == ' ')){
    board[0][1] = piece;
    int moveBR[2] = {0,4};
    for(int i = 0; i<2; i++){
      if(player == 1) score[moveBR[i]] += 1;
      if(player == 2) score[moveBR[i]] -= 1;
    }
  }
  else if((strcmp(move, "TR") == 0) && (board[0][2] == ' ')){
    board[0][2] = piece;
    int moveBR[3] = {0,5,7};
    for(int i = 0; i<3; i++){
      if(player == 1) score[moveBR[i]] += 1;
      if(player == 2) score[moveBR[i]] -= 1;
    }
  }
  else if((strcmp(move, "ML") == 0) && (board[1][0] == ' ')){
    board[1][0] = piece;
    int moveBR[2] = {1,3};
    for(int i = 0; i<2; i++){
      if(player == 1) score[moveBR[i]] += 1;
      if(player == 2) score[moveBR[i]] -= 1;
    }
  }
  else if((strcmp(move, "MM") == 0) && (board[1][1] == ' ')){
    board[1][1] = piece;
    int moveBR[4] = {1,4,6,7};
    for(int i = 0; i<4; i++){
      if(player == 1) score[moveBR[i]] += 1;
      if(player == 2) score[moveBR[i]] -= 1;
    }
  }
  else if((strcmp(move, "MR") == 0) && (board[1][2] == ' ')){
    board[1][2] = piece;
    int moveBR[2] = {1,5};
    for(int i = 0; i<2; i++){
      if(player == 1) score[moveBR[i]] += 1;
      if(player == 2) score[moveBR[i]] -= 1;
    }
  }
  else if((strcmp(move, "BL") == 0) && (board[2][0] == ' ')){
    board[2][0] = piece;
    int moveBR[3] = {2,3,7};
    for(int i = 0; i<3; i++){
      if(player == 1) score[moveBR[i]] += 1;
      if(player == 2) score[moveBR[i]] -= 1;
    }
  }
  else if((strcmp(move, "BM") == 0) && (board[2][1] == ' ')){
    board[2][1] = piece;
    int moveBR[2] = {2,4};
    for(int i = 0; i<2; i++){
      if(player == 1) score[moveBR[i]] += 1;
      if(player == 2) score[moveBR[i]] -= 1;
    }
  }
  else if((strcmp(move, "BR") == 0) && (board[2][2] == ' ')){
    board[2][2] = piece;
    int moveBR[3] = {2,5,6};
    for(int i = 0; i<3; i++){
      if(player == 1) score[moveBR[i]] += 1;
      if(player == 2) score[moveBR[i]] -= 1;
    }
  }
  else {
    return 0;
  }
  return 1;
}

int check_board() {
  //check if there's a winner
  for(int i = 0; i<8; i++){
    if(score[i] == 3){
      return 1;
    }
    else if(score[i] == -3){
      return 2;
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
    return 3;
  }
  return 0;
}
