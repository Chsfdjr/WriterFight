/*
** EPITECH PROJECT, 2024
** WriterFight
** File description:
** include
*/

#pragma once
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <pthread.h>
#include <errno.h>
#include <netdb.h>
#include <ifaddrs.h>
#define GAME_TIME 10
#define MAX_USER 50

typedef struct {
    int server_fd;
    int fd;
    struct sockaddr_in address;
    socklen_t addrlen;
    fd_set rfds;
    fd_set wfds;
    char *name;
} client_t;

typedef struct server_t {
    int fd;
    struct sockaddr_in addr;
    socklen_t addr_tize;
    fd_set readfds;
    fd_set writefds;
    int max_sd;
    int port;
    int nb_player;
} server_t;

typedef struct game_t {
    char **sentences;
    int nb_sentences;
    pthread_t timer;
    struct timespec clock;
    bool status;
} game_t;

typedef struct player_t {
    int fd;
    struct sockaddr_in address;
    socklen_t addrlen;
    int score;
    char *name;
    char *sentence_picked;
    bool allow;
} player_t;

typedef struct writerfight_t {
    server_t server;
    player_t *player;
    game_t game;
} writerfight_t;

char **my_str_to_word_array(char *buf, char *del);
int len_tab(char **tab);
void free_tab(char **tab);

void init_serv(writerfight_t *w);
void get_player_name(player_t *c, int new_socket);
void set_new_player(writerfight_t *w, int new_socket, int i);
void add_new_player(writerfight_t *w, int new_socket);
void handle_new_connection(writerfight_t *w, fd_set *readfds);
void loop_serv(writerfight_t *w, int serv_fd);

char *get_randow_sentence(writerfight_t *w);
bool verify_answer(player_t *player, char *answer);
void start(writerfight_t *w);
void stop(writerfight_t *w);
void sendSentence(writerfight_t *w);
void timer(writerfight_t *w);
void *thread_timer(void *v);
void showscore(int fd, writerfight_t *w);

void handle_read_client(client_t *client);
void handle_receive_from_server(client_t *client);
void listening_select_event(client_t *client);
void handle_select_client(client_t *client);
void client_initialization(client_t *cliUtils, char *ip, int port);
