#include "networking.h"

static void sighandler(int signo) {
  if (signo==SIGINT) {
    exit(0);
  }
}

static int opponent[FD_SETSIZE], last_played[FD_SETSIZE];
static int waiting_fd = -1, waiting_fd2 = -1;

void matchmaking(int fd){
  // if queue is empty, put them in queue
  if (waiting_fd == -1) {
    waiting_fd = fd;
    return;
  }
  // if player in queue is who they last played, queue them too
  if (waiting_fd == last_played[fd] && fd == last_played[waiting_fd]) {
    waiting_fd2 = fd;
    return;
  }
  opponent[fd] = waiting_fd;
  opponent[waiting_fd] = fd;
  int p1 = 1, p2 = 2;
  send(fd,&p2,sizeof(int),0);
  send(waiting_fd,&p1,sizeof(int),0);
  // move second client in queue to first spot, set second spot to -1
  // if second spot is empty, this will just set them both to -1
  waiting_fd = waiting_fd2;
  waiting_fd2 = -1;
}

void close_client(int fd, fd_set *descriptors, int *max_fd) {
  FD_CLR(fd,descriptors);
  close(fd);
  opponent[fd] = -1;
  last_played[fd] = -1;
  // reset waiting_fd if it was waiting
  if (waiting_fd==fd) {
    waiting_fd = waiting_fd2;
    waiting_fd2 = -1;
  }
  else if (waiting_fd2==fd)waiting_fd2 = -1;
  if (fd==*max_fd) {
    while(*max_fd>=0 && !FD_ISSET(*max_fd,descriptors)) {
      (*max_fd)--;
    }
  }
  printf("client disconnected\n");
}

int main(int argc, char *argv[] ) {
  signal(SIGINT,sighandler);
  int listen_socket = server_setup();
  printf("listening for connections...\n");
  char buf[1025];
  fd_set descriptors, current;
  FD_ZERO(&descriptors);
  FD_SET(listen_socket,&descriptors);
  int max_fd = listen_socket;
  for (int i = 0; i<FD_SETSIZE; i++) {
    opponent[i] = -1;
    last_played[i] = -1;
  }
  while(1) {
    current = descriptors;
    int sel = select(max_fd+1,&current,NULL,NULL,NULL);
    if (sel<0)err();
    for (int fd = 0; fd<max_fd+1; fd++) {
      if (!FD_ISSET(fd,&current)) continue;
      if (fd==listen_socket) {
        // add new clients to list
        int client_socket = server_tcp_handshake(listen_socket);
        if (client_socket<0)continue;
        FD_SET(client_socket,&descriptors);
        if (client_socket>max_fd)max_fd=client_socket;
        printf("client connected\n");
        matchmaking(client_socket);
      }
      else {
        // accpet new moves
        char move[100];
        int bytes = recv(fd,move,sizeof(move),0);
        int opp = opponent[fd];
        if (bytes<=0 || strncmp(move,"home",4)==0) {
          // if client exited, add the opponent back to queue and close client
          // doesn't set last_played if opponent leaves game
          close_client(fd,&descriptors,&max_fd);
          if (opp!=-1) {
            opponent[opp] = -1;
            last_played[opp] = -1;
            send(opp,"opponent left",13,0);
            matchmaking(opp);
          }
          continue;
        }
        if (strncmp(move,"exit",4)==0) {
          // if client wants a new game, requeue both and set last_played
          send(opp,"opponent left",13,0);
          opponent[fd] = -1;
          opponent[opp] = -1;
          last_played[fd] = opp;
          last_played[opp] = fd;
          matchmaking(fd);
          matchmaking(opp);
          continue;
        }
        // send play again message across game
        if (strncmp(move,"play again",10)==0) {
          send(opp,move,10,0);
          continue;
        }
        // send the move if normal behavior
        send(opponent[fd],move,sizeof(move),0);
      }
    }
  }
}
