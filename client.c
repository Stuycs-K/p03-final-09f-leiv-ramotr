#include "networking.h"

static void sighandler(int signo) {
  if (signo==SIGINT) {
    printf("\n");
    exit(0);
  }
}

int main(int argc, char *argv[] ) {
  signal(SIGINT,sighandler);
  printf("Enter 1 to play locally. Enter 2 to play against a random opponent.\n");
  char mode[10];
  while(1) {
    char *in = fgets(mode,sizeof(mode),stdin);
    if (in==NULL)err();
    if (strcmp(mode,"1")==0 || strcmp(mode,"2"))break;
    else {
      printf("Please only type 1 or 2.\n");
    }
  }
  if (strcmp(mode,"1")==0) {
    onlineplay();
  }
  else {
    localplay();
  }
}

void onlineplay() {
  char* IP = "127.0.0.1";
  printf("Enter the IP Address of the server (Press enter if server is local)\n");
  char newIP[20];
  char *input = fgets(newIP,sizeof(newIP),stdin);
  newIP[strlen(newIP)-1] = 0;
  if(strlen(newIP)!=0){
    IP=newIP;
  }
  int server_socket = client_tcp_handshake(IP);
  printf("Connected to server.\n");
  char board[3][3] = malloc(9);
  for(int i = 0; i<3; i++){
    for(int j = 0; j<3; j++){
      board[i][j] = ' ';
    }
  }
  printf("Waiting to be matched....\n");
  char player;
  int bytes = recv(server_socket,player,sizeof(player),0);
  if (bytes==0) err();
  char initialPlayer = player;
  while(1)  {     // change to function that assesses condition of game board
    char move[100];
    if (player) {
      bytes = recv(server_socket,move,sizeof(move),0);
      if (bytes==0)err();
      updateboard(move,initialPlayer,board);
      printboard(board);
    }
    else {
      while(1) {
        input = fgets(move,sizeof(move),stdin);
        if (input==NULL)err();
        int success = updateboard(move,initialPlayer,board);
        if (success)break;
      }
      printboard(board);
    }
    player = (player+1)%2;
  }
}

void localplay() {

}
