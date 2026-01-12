#include "networking.h"

static void sighandler(int signo) {
  if (signo==SIGINT) {
    printf("\n");
    exit(0);
  }
}

int main(int argc, char *argv[] ) {
  signal(SIGINT,sighandler);
  begin_play();
}

void begin_play() {
  printf("Type \'help\' to show manual.\n");
  printf("Enter 1 to play locally. Enter 2 to play against a random opponent.\n");
  char mode[10];
  while(1) {
    char *in = fgets(mode,sizeof(mode),stdin);
    if (in==NULL)err();
    if(strncmp(mode,"help",4)==0){
      print_help();
    }
    if (mode[0]=='1' || mode[0]=='2')break;
    else {
      printf("Please only type 1 or 2.\n");
    }
  }
  if (mode[0]=='2') {
    onlineplay();
  }
  else {
    localplay();
  }
}

void onlineplay() {
  char* IP = "127.0.0.1";
  printf("Enter the IP Address of the server (Press enter if server is local or enter \'home\' to go back to main menu):\n");
  char newIP[20];
  char *input = fgets(newIP,sizeof(newIP),stdin);
  newIP[strlen(newIP)-1] = 0;
  if(strlen(newIP)!=0){
    IP=newIP;
  }
  if(strcmp(newIP,"home")==0)begin_play();
  int server_socket = client_tcp_handshake(IP);
  printf("Connected to server.\n");
  online_match(server_socket);
}

void online_match(int server_socket) {
  printf("Waiting to be matched.... Enter \'home\' to return to home page.\n");
  int player, bytes;
  fd_set descriptors;
  char *input;
  FD_ZERO(&descriptors);
  FD_SET(server_socket,&descriptors);
  FD_SET(STDIN_FILENO,&descriptors);
  while (1) {
    int i = select(server_socket+1,&descriptors,NULL,NULL,NULL);
    if (FD_ISSET(STDIN_FILENO,&descriptors)) {
      char buf[100];
      input = fgets(buf,sizeof(buf),stdin);
      buf[strlen(buf)-1] = 0;
      if(strcmp(buf,"home")==0) {
        send(server_socket,buf,sizeof(buf),0);
        close(server_socket);
        begin_play();
        return;
      }
    }
    if(FD_ISSET(server_socket, &descriptors)) {
      bytes = recv(server_socket,&player,sizeof(int),0);
      if (bytes == 0) {
        reset(server_socket);
        return;
      }
      break;
    }
  }
  reset_board();
  int initialPlayer = player;
  while(check_board()==0) {
    char move[100];
    printf_board();
    if (player==2) {
      printf("Waiting for opponent to move...\n");
      bytes = recv(server_socket,move,sizeof(move),0);
      if (bytes==0) {
        reset(server_socket);
        return;
      }
      if (strcmp(move,"opponent left")==0) {
        printf("Opponent left. Searching for new opponent.");
        online_match(server_socket);
        return;
      }
      update_board(move,initialPlayer%2+1);
    }
    else {
      printf("Your turn to move: \n");
      while(1) {
        input = fgets(move,sizeof(move),stdin);
        if (input==NULL)err();
        int success = update_board(move,initialPlayer);
        if (success)break;
      }
      send(server_socket,move,sizeof(move),0);
    }
    player = player%2+1;
  }
  print_board();
  int result = check_board();
  if ((result==1 && player==1) || (result==2 && player==2)) {
    printf("You win!\n");
  }
  else if ((result==1 && player==2) || (result==2 && player==1)) {
    printf("You lose... better luck next time.\n");
  }
  else if (result==3) {
    printf("Draw. What an intense match.\n");
  }
}

void localplay() {
  reset_board();
  int player = 1;
  while(check_board()==0) {
    char move[100];
    print_board();
    char piece = player==1 ? 'X' : 'O';
    while(1) {
      printf("%c's turn: ",piece);
      char *input = fgets(move,sizeof(move),stdin);
      if (input==NULL)err();
      move[strlen(move)-1] = 0;
      if (strcmp(move,"help")==0)print_help();
      else {
        int success = update_board(move,player);
        if (success)break;
        printf("invalid move. enter \'help\' for more info. ");
      }
    }
    player = player%2+1;
  }
  print_board();
  int result = check_board();
  if (result==1) {
    printf("X's win!\n");
  }
  else if (result==2) {
    printf("O's win!\n");
  }
  else if (result==3) {
    printf("Draw. What an intense match.\n");
  }
}

void reset(int server_socket) {
  printf("Server disconnected.\n");
  close(server_socket);
  begin_play();
}
