#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdbool.h>


#ifndef NETWORKING_H
#define NETWORKING_H
#define PORT "19230"
#define BUFFER_SIZE 1024
// networking.c
int server_setup();
int server_tcp_handshake(int listen_socket);
int client_tcp_handshake(char*server_address);
void error(int i, char*message);
void err();
// game.c
void print_board();
void print_help();
void reset_board();
int update_board(char *move, int player);
int check_board();
// server.c
void matchmaking(int fd);
void close_client(int fd, fd_set *descriptors, int *max_fd);
// client.c
void begin_play();
void onlineplay();
void online_match();
void online_game(int player);
void localplay();
void reset();
extern char board[3][3];
#endif
