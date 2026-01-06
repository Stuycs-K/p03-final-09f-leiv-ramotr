#include "networking.h"

static void sighandler(int signo) {
  if (signo==SIGINT) {
    printf("\n");
    exit(0);
  }
}

void clientLogic(int server_socket){

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
