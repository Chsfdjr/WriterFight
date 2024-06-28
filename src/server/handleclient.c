/*
** EPITECH PROJECT, 2024
** WriterFight
** File description:
** handleclient
*/

#include "../../include.h"

void get_player_name(player_t *c, int new_socket)
{
    char *buffer = malloc(sizeof(char) * 256 + 1);
    if (buffer == NULL) {
        perror("Memory allocation error");
        c->name = "default";
        return;
    }

    ssize_t bytes_received = read(new_socket, buffer, 256);
    if (bytes_received > 0) {
        buffer[bytes_received - 1] = '\0';
        c->name = buffer;
    } else {
        free(buffer);
        c->name = "default";
    }
}

void set_new_player(writerfight_t *w, int new_socket, int i)
{
    get_player_name(&w->player[i], new_socket);
    w->player[i].fd = new_socket;
    w->player[i].score = 0;
    if (w->game.status == true) {
        w->player[i].allow = false;
        dprintf(new_socket, "You have to wait the end of previous game!\n");
    } else {
        w->player[i].allow = true;
        dprintf(new_socket, "Get ready to play!\n");
    }
    printf("%s is connected !\n", w->player[i].name);
    w->server.nb_player++;
}

void add_new_player(writerfight_t *w, int new_socket)
{
    int i = 0;

    for (i = 0; i < MAX_USER; i++) {
        if (w->player[i].fd == 0) {
            set_new_player(w, new_socket, i);
            break;
        }
    }
}

int accept_new_connection(int server_fd, struct sockaddr *addr)
{
    int new_socket;
    socklen_t addrlen = sizeof(*addr);

    new_socket = accept(server_fd, addr, &addrlen);
    if (new_socket < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    return new_socket;
}

void handle_new_connection(writerfight_t *w, fd_set *readfds)
{
    int new_socket;
    struct sockaddr_in client_addr;

    if (FD_ISSET(w->server.fd, readfds)) {
        new_socket = accept_new_connection(w->server.fd,
        (struct sockaddr *)&client_addr);
        if (new_socket >= 0) {
            add_new_player(w, new_socket);
        }
    }
}
