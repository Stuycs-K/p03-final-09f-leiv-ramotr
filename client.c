#include "networking.h"

static int server_socket;

static void sighandler(int signo) {
  if (signo==SIGINT) {
    char message[20] = "home";
    send(server_socket,message,4,0);
    close(server_socket);
    printf("\n");
    exit(0);
  }
}

int main(int argc, char *argv[] ) {
  signal(SIGINT,sighandler);
  begin_play();
}

void begin_play() {
  printf("Enter 1 to play locally. Enter 2 to play against a random opponent.\n");
  printf("Type \'help\' to show manual.\n");
  char mode[100];
  while(1) {
    char *in = fgets(mode,sizeof(mode),stdin);
    mode[strlen(mode)-1] = 0;
    if (in==NULL)err();
    if(strcmp(mode,"help")==0){
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
  char newIP[100];
  while (1) {
    char *input = fgets(newIP,sizeof(newIP),stdin);
    if (input==NULL)err();
    newIP[strlen(newIP)-1] = 0;
    if(strlen(newIP)!=0){
      IP=newIP;
    }
    if(strcmp(newIP,"home")==0) {
      begin_play();
      return;
    }
    server_socket = client_tcp_handshake(IP);
    if (server_socket>-1)break;
    printf("Couldn't connect to server. Please enter IP Address or press enter if server is local.\n");
  }
  printf("Connected to server.\n");
  online_match();
}

void online_match() {
  printf("Waiting to be matched.... Enter \'home\' to return to home page.\n");
  int player, bytes;
  fd_set descriptors;
  char *input;
  while (1) {
    FD_ZERO(&descriptors);
    FD_SET(server_socket,&descriptors);
    FD_SET(STDIN_FILENO,&descriptors);
    int i = select(server_socket+1,&descriptors,NULL,NULL,NULL);
    if (FD_ISSET(STDIN_FILENO,&descriptors)) {
      char buf[100];
      input = fgets(buf,sizeof(buf),stdin);
      if (input==NULL)err();
      buf[strlen(buf)-1] = 0;
      if(strcmp(buf,"home")==0) {
        send(server_socket,buf,4,0);
        close(server_socket);
        begin_play();
        return;
      }
      printf("Still not matched... Enter \'home\' to return to home page.\n");
    }
    if(FD_ISSET(server_socket, &descriptors)) {
      bytes = recv(server_socket,&player,sizeof(int),0);
      if (bytes == 0) {
        reset();
        return;
      }
      break;
    }
  }
  printf("Matched!\n");
  online_game(player);
}

void online_game(int player) {
  int bytes;
  char *input;
  fd_set descriptors;
  int initialPlayer = player;
  reset_board();
  while(check_board()==0) {
    char move[100];
    print_board();
    if (player==2) {
      printf("Waiting for opponent to move...\n");
      bytes = recv(server_socket,move,sizeof(move),0);
      if (bytes<(int)sizeof(move))move[bytes] = 0;
      if (bytes==0) {
        reset();
        return;
      }
      if (strncmp(move,"opponent left",13)==0) {
        printf("Opponent left. Searching for new opponent.\n");
        online_match();
        return;
      }
      update_board(move,initialPlayer%2+1);
    }
    else {
      while(1) {
        printf("Your turn to move: \n");
        FD_ZERO(&descriptors);
        FD_SET(server_socket,&descriptors);
        FD_SET(STDIN_FILENO,&descriptors);
        int i = select(server_socket+1,&descriptors,NULL,NULL,NULL);
        if (FD_ISSET(STDIN_FILENO,&descriptors)) {
          input = fgets(move,sizeof(move),stdin);
          if (input==NULL)err();
          move[strlen(move)-1] = 0;
          if (strcmp(move,"help")==0)print_help();
          else if(strcmp(move,"home")==0) {
            send(server_socket,move,4,0);
            close(server_socket);
            begin_play();
            return;
          }
          else {
            int success = update_board(move,initialPlayer);
            if (success)break;
            printf("invalid move. enter \'help\' for more info. ");
          }
        }
        if (FD_ISSET(server_socket,&descriptors)) {
          bytes = recv(server_socket,move,sizeof(move),0);
          if (bytes<(int)sizeof(move))move[bytes] = 0;
          if (bytes==0) {
            reset();
            return;
          }
          if (strncmp(move,"opponent left",13)==0) {
            printf("Opponent left. Searching for new opponent.\n");
            online_match();
            return;
          }
        }
      }
      send(server_socket,move,strlen(move)+1,0);
    }
    player = player%2+1;
  }
  print_board();
  int result = check_board();
  if ((result==1 && initialPlayer==1) || (result==2 && initialPlayer==2)) {
    printf("You win!\n");
  }
  else if ((result==1 && initialPlayer==2) || (result==2 && initialPlayer==1)) {
    printf("You lose... better luck next time.\n");
  }
  else if (result==3) {
    printf("Draw. What an intense match.\n");
  }
  printf("\nIf you would like to play again, hit enter. If you want to find a new opponent, enter \'exit\'. To return to the home menu, enter \'home\'.\n");
  char in[100];
  int play = 0, playopp = 0;
  while(1) {
    FD_ZERO(&descriptors);
    FD_SET(server_socket,&descriptors);
    FD_SET(STDIN_FILENO,&descriptors);
    int i = select(server_socket+1,&descriptors,NULL,NULL,NULL);
    if (FD_ISSET(STDIN_FILENO,&descriptors)) {
      input = fgets(in,sizeof(in),stdin);
      if (input==NULL)err();
      in[strlen(in)-1] = 0;
      if (strlen(in)==0) {
        send(server_socket,"play again",10,0);
        char response[100];
        play = 1;
        if (playopp==1)break;
        printf("Waiting to play again...\n");
      }
      else if (strcmp(in,"exit")==0) {
        send(server_socket,in,strlen(in)+1,0);
        online_match();
        return;
      }
      else if (strcmp(in,"home")==0) {
        send(server_socket,in,strlen(in)+1,0);
        close(server_socket);
        begin_play();
        return;
      }
      else
        printf("Please press enter to play again, \'exit\' to find a new opponent, or \'home\' to return home.\n");
    }
    if (FD_ISSET(server_socket,&descriptors)) {
      bytes = recv(server_socket,in,sizeof(in),0);
      if (bytes<(int)sizeof(in))in[bytes] = 0;
      if (bytes == 0) {
        reset();
        return;
      }
      if (strncmp(in,"opponent left",13)==0) {
        printf("Opponent left. Searching for new opponent.\n");
        online_match();
        return;
      }
      if (strncmp(in,"play again",10)==0) {
        printf("Opponent would like to play again. ");
        playopp = 1;
        if (play==1)break;
        printf("Press enter to play.\n");
      }
    }
  }
  printf("Beginning new game.\n");
  online_game(initialPlayer%2+1);
  return;
}

void localplay() {
  reset_board();
  char *input;
  int player = 1;
  while(check_board()==0) {
    char move[100];
    print_board();
    char piece = player==1 ? 'X' : 'O';
    while(1) {
      printf("%c's turn: ",piece);
      input = fgets(move,sizeof(move),stdin);
      if (input==NULL)err();
      move[strlen(move)-1] = 0;
      if (strcmp(move,"help")==0)print_help();
      else if (strcmp(move,"home")==0) {
        begin_play();
        return;
      }
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
  char in[100];
  printf("\nIf you would like to play again, hit enter. To return to the home menu, enter \'home\'.\n");
  while(1) {
    input = fgets(in,sizeof(in),stdin);
    if (input==NULL)err();
    in[strlen(in)-1] = 0;
    if (strlen(in)==0) {
      localplay();
      return;
    }
    if (strcmp(in,"home")==0) {
      begin_play();
      return;
    }
    printf("Please press enter to play again or enter \'home\' to return home.\n");
  }
}

void reset() {
  printf("Server disconnected.\n");
  close(server_socket);
  begin_play();
}
