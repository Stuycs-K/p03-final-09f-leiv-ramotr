#include "networking.h"

static void sighandler(int signo) {
  if (signo==SIGINT) {
    exit(0);
  }
}

static int opponent[100];
static int waiting_fd = -1;

void matchmaking(int client_socket){

}

void close_client(int fd, fd_set *descriptors) {
  FD_CLR(fd,descriptors);
  close(fd);
  opponent[fd] = -1;
}

int main(int argc, char *argv[] ) {
  signal(SIGINT,sighandler);
  int listen_socket = server_setup();
  printf("listening for connections...\n");
  char buf[1025];
  fd_set descriptors;
  FD_ZERO(&descriptors);
  FD_SET(listen_socket,&descriptors);
  int max_fd = listen_socket;
  while(1) {
    int sel = select(max_fd+1,&descriptors,NULL,NULL,NULL);
    if (sel<0)err();
    for (int fd = 0; fd<max_fd+1; fd++) {
      if (!FD_ISSET(fd,&descriptors)) continue;
      if (fd==listen_socket) {
        // add new clients to list
        int client_socket = server_tcp_handshake(listen_socket);
        if (client_socket<0)continue;
        if (client_socket>max_fd)max_fd=client_socket;
        printf("client connected\n");
        matchmaking(client_socket);
      }
      else {
        // accpet new moves
        char move[100];
        int bytes = recv(fd,move,sizeof(move),0);
        int opp = opponent[fd];
        if (bytes<=0) {
          // if client exited, add the opponent back to queue and close client
          close_client(fd,&descriptors);
          if (opp!=-1) {
            opponent[opp] = -1;
            send(opp,"opponent left",13,0);
            matchmaking(opp);
          }
          // reset waiting_fd if it was waiting
          if (waiting_fd==fd)waiting_fd = 0;
          continue;
        }
        if (strncmp(move,"exit",4)==0) {
          // if client wants a new game, requeue both
          opponent[fd] = -1;
          opponent[opp] = -1;
          matchmaking(fd);
          matchmaking(opp);
          continue;
        }
        // send the move if normal behavior
        send(opponent[fd],move,sizeof(move),0);
      }
    }

  }
}
