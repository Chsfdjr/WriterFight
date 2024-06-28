/*
** EPITECH PROJECT, 2024
** WriterFight
** File description:
** server
*/

#include "../../include.h"

void check_close(int fd)
{
    int ret = close(fd);

        if (ret == -1)
            perror("close error");
}

void update_fd(int fd, fd_set *readfds, int *max_sd)
{
    if (fd > 0) {
        FD_SET(fd, readfds);
        if (fd > *max_sd) {
            *max_sd = fd;
        }
    }
}

void update_fd_set(writerfight_t *w, fd_set *readfds, int *max_sd)
{
    FD_ZERO(readfds);
    FD_SET(0, readfds);
    update_fd(w->server.fd, readfds, max_sd);
    for (int i = 0; i < MAX_USER; i++) {
        update_fd(w->player[i].fd, readfds, max_sd);
    }
}

void handle_player_gameplay(writerfight_t *w, player_t *player, char *answer)
{
    if (player->allow == true) {
        if (verify_answer(player, answer) == true) {
            player->score++;
            player->sentence_picked = get_randow_sentence(w);
            usleep(1000);
            dprintf(player->fd, "clear");
            usleep(1000);
            dprintf(player->fd, "Correct! Score: %d\n", player->score);
            dprintf(player->fd, "New sentences:\n%s\n", player->sentence_picked);
        } else
            dprintf(player->fd, "Try again!\n");
    } else
        dprintf(player->fd, "You have to wait the end of previous game or a new game!\n");
}

void handle_activity(writerfight_t *w, int index)
{
    char buffer[10000];
    int bytes_received;

    bytes_received = read(w->player[index].fd, buffer, 10000);
    if (bytes_received > 0) {
        buffer[bytes_received - 1] = '\0';
        handle_player_gameplay(w, &w->player[index], buffer);
    } else if (bytes_received == 0) {
        check_close(w->player[index].fd);
        w->player[index].fd = 0;
        w->server.nb_player--;
    } else {
        perror("read");
    }
}

void check_client_activity(writerfight_t *w, int index, fd_set *readfds)
{
    if (w->player[index].fd > 0 &&
    FD_ISSET(w->player[index].fd, readfds)) {
        handle_activity(w, index);
    }
}

void handle_client_activity(writerfight_t *w, fd_set *readfds)
{
    for (int i = 0; i < MAX_USER; i++) {
        check_client_activity(w, i, readfds);
    }
}

void handling_server_cli(writerfight_t *w)
{
    char **tab_arg;
    char buffer[1024];
    size_t bytes_read;

    bytes_read = read(0, buffer, 1024);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        tab_arg = my_str_to_word_array(buffer, " \n");
        if (tab_arg != NULL && tab_arg[0] != NULL) {
            if (strcmp(tab_arg[0], "/start") == 0)
                start(w);
            if (strcmp(tab_arg[0], "/stop") == 0)
                stop(w);
        }
    }
}

void loop_serv(writerfight_t *w, int serv_fd)
{
    int activity;

    w->server.max_sd = serv_fd;
    FD_ZERO(&w->server.readfds);
    while (1) {
        update_fd_set(w, &w->server.readfds, &w->server.max_sd);
        activity = select(w->server.max_sd + 1, &w->server.readfds,
        NULL, NULL, NULL);
        if (activity < 0) {
            perror("selecttttttt");
            exit(EXIT_FAILURE);
        }
        if (FD_ISSET(serv_fd, &w->server.readfds))
            handle_new_connection(w, &w->server.readfds);
        if (FD_ISSET(0, &w->server.readfds))
            handling_server_cli(w);
        handle_client_activity(w, &w->server.readfds);
    }
}

void init_serv(writerfight_t *w)
{
    int port = w->server.port;
    int bnd;

    w->server.fd = socket(AF_INET, SOCK_STREAM, 0);
    if (w->server.fd < 0) {
        printf("Socket Failed\n");
        exit(1);
    }
    w->server.addr.sin_family = AF_INET;
    w->server.addr.sin_port = htons(port);
    w->server.addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bnd = bind(w->server.fd, (struct sockaddr*) &w->server.addr,
    sizeof(w->server.addr));
    if (bnd < 0) {
        printf("Error in binding.\n");
        exit(1);
    }
    w->server.nb_player = 0;
    if (listen(w->server.fd, MAX_USER) == -1) {
        perror("listen error");
        exit(1);
    }
    w->player = malloc(sizeof(player_t) * MAX_USER);
    for (int i = 0; i < MAX_USER; i++) {
        w->player[i].fd = 0;
        w->player[i].score = 0;
    }
    printf("Ready to get people !\n");
    w->game.status = false;
}
