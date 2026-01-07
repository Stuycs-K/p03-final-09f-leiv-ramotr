#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//#include "networking.h"

int print_board(){

}

void game_statements(){
  char line[10];
  while(1){
    printf("Would you like to play? (y/n)\n");
    if(fgets(line, 10, stdin) == NULL){
      continue;
    }
    if(line[0] == 'y'){
      //print_board();
      printf("start game\n");
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
