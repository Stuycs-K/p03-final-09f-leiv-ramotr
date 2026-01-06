#include "networking.h"

static void sighandler(int signo) {
  if (signo==SIGINT) {
    exit(0);
  }
}

void subserver_logic(int client_socket){

}

int main(int argc, char *argv[] ) {
  signal(SIGINT,sighandler);
  int listen_socket = server_setup();
  printf("listening for connections...\n");
  while(1) {
    int client_socket = server_tcp_handshake(listen_socket);
    printf("client connected\n");
    pid_t p = fork();
    if (p==-1)perror("fork failed");
    else if (p==0)subserver_logic(client_socket);
  }
}
