#include "networking.h"

static void sighandler(int signo) {
  if (signo==SIGINT) {
    exit(0);
  }
}
static int client[100];
void matchmaking(int client_socket){
  
}

int main(int argc, char *argv[] ) {
  signal(SIGINT,sighandler);
  int listen_socket = server_setup();
  printf("listening for connections...\n");
  char buf[1025];
  while(1) {
    fd_set descriptors;
    FD_ZERO(&descriptors);
    FD_SET(listen_socket,&descriptors);
    FD_SET(STDIN_FILENO,&descriptors);
    int i = select(listen_socket+1,&descriptors,NULL,NULL,NULL);
    if (FD_ISSET(STDIN_FILENO,&descriptors)) {
      fgets(buf,sizeof(buf),stdin);
      buf[strlen(buf)-1]=0;
      printf("%s\n",buf); // put the game function here
    }
    if (FD_ISSET(listen_socket,&descriptors)) {
      int client_socket = server_tcp_handshake(listen_socket);
      printf("client connected\n");
      matchmaking(client_socket);
    }
  }
}
