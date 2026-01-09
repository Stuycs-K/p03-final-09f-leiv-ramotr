#include "networking.h"

static void sighandler(int signo) {
  if (signo==SIGINT) {
    printf("\n");
    exit(0);
  }
}

void clientLogic(int server_socket){
  char player;
  int bytes = recv(server_socket,player,sizeof(player),0);
  if (bytes==0) err();
  while(1) {
    char move[100];
    if (player) {
      bytes = recv(server_socket,move,sizeof(move),0);
      if (bytes==0)err();
      updateboard(move,player);
    }
    else {
      while(1) {
        char *input = fgets(move,sizeof(move),stdin);
        if (input==NULL)err();
        int success = updateboard(move,player);
        if (success)break;
      }
    }
    player = (player+1)%2;
  }
}

int main(int argc, char *argv[] ) {
  signal(SIGINT,sighandler);
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  int server_socket = client_tcp_handshake(IP);
  printf("client connected.\n");
  clientLogic(server_socket);
}
