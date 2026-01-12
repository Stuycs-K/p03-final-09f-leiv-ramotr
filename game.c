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
  printf("1. Playing locally means you are playing on the same computer with your opponent.\n Playing against a random opponent means you will be connected to a specified server and given an opponent.\n");
  printf("2. To play the game, type the coordinates of an empty box.\n");
  printf("Top (T), Middle(M), Bottom (B), Left (L), Right(R)\n");
  printf("TL | TM | TR \n———|————|——— \nML | MM | MR \n———|————|——— \nBL | BM | BR\n");
  printf("3. If already taken, you will be prompted to choose a different spot.\n");
  printf("4. Wait for your opponent's turn and repeat. Enter exit at any time to leave the game.\n");
  printf("5. Have your pieces three in a row or diagonally to win.\n");
  printf("6. When the game is over, you will have the option to play again with the same client, never play again with the same client, or connect with a random person.\n");
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
  if((strncmp(move, "TL", 2) == 0) && (board[0][0] == ' ')){
    board[0][0] = piece;
    int moveBR[3] = {0,3,6};
    for(int i = 0; i<3; i++){
      if(player == 1) score[moveBR[i]] += 1;
      if(player == 2) score[moveBR[i]] -= 1;
    }
  }
  else if((strncmp(move, "TM", 2) == 0) && (board[0][1] == ' ')){
    board[0][1] = piece;
    int moveBR[2] = {0,4};
    for(int i = 0; i<2; i++){
      if(player == 1) score[moveBR[i]] += 1;
      if(player == 2) score[moveBR[i]] -= 1;
    }
  }
  else if((strncmp(move, "TR", 2) == 0) && (board[0][2] == ' ')){
    board[0][2] = piece;
    int moveBR[3] = {0,5,7};
    for(int i = 0; i<3; i++){
      if(player == 1) score[moveBR[i]] += 1;
      if(player == 2) score[moveBR[i]] -= 1;
    }
  }
  else if((strncmp(move, "ML", 2) == 0) && (board[1][0] == ' ')){
    board[1][0] = piece;
    int moveBR[2] = {1,3};
    for(int i = 0; i<2; i++){
      if(player == 1) score[moveBR[i]] += 1;
      if(player == 2) score[moveBR[i]] -= 1;
    }
  }
  else if((strncmp(move, "MM", 2) == 0) && (board[1][1] == ' ')){
    board[1][1] = piece;
    int moveBR[4] = {1,4,6,7};
    for(int i = 0; i<4; i++){
      if(player == 1) score[moveBR[i]] += 1;
      if(player == 2) score[moveBR[i]] -= 1;
    }
  }
  else if((strncmp(move, "MR", 2) == 0) && (board[1][2] == ' ')){
    board[1][2] = piece;
    int moveBR[2] = {1,5};
    for(int i = 0; i<2; i++){
      if(player == 1) score[moveBR[i]] += 1;
      if(player == 2) score[moveBR[i]] -= 1;
    }
  }
  else if((strncmp(move, "BL", 2) == 0) && (board[2][0] == ' ')){
    board[2][0] = piece;
    int moveBR[3] = {2,3,6};
    for(int i = 0; i<3; i++){
      if(player == 1) score[moveBR[i]] += 1;
      if(player == 2) score[moveBR[i]] -= 1;
    }
  }
  else if((strncmp(move, "BM", 2) == 0) && (board[2][1] == ' ')){
    board[2][1] = piece;
    int moveBR[2] = {2,4};
    for(int i = 0; i<2; i++){
      if(player == 1) score[moveBR[i]] += 1;
      if(player == 2) score[moveBR[i]] -= 1;
    }
  }
  else if((strncmp(move, "BR", 2) == 0) && (board[2][2] == ' ')){
    board[2][2] = piece;
    int moveBR[3] = {2,5,7};
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
