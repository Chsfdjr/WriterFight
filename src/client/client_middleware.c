/*
** EPITECH PROJECT, 2024
** client
** File description:
** client
*/

#include "../../include.h"

void handle_read_client(client_t *client)
{
    char *line = NULL;
    size_t len = 0;

    FD_ISSET(client->server_fd, &client->rfds);
    if (getline(&line, &len, stdin) > 0) {
        if (strlen(line) > 1) {
            dprintf(client->server_fd, "%s", line);
        } else
            return;
    }
}

void manage_server_buf(client_t *client, char *buffer)
{
    if (strcmp(buffer, "clear") == 0)
        system("clear");
    else
        printf("%s\n", buffer);
}

void handle_receive_from_server(client_t *client)
{
    char buffer[1024];
    char **tab = NULL;
    size_t len = 0;

    select(client->server_fd + 1, &client->rfds, &client->wfds,
    NULL, NULL);
    FD_ISSET(client->server_fd, &client->rfds);
    len = read(client->server_fd, buffer, sizeof(buffer) - 1);
    buffer[len] = '\0';
    if (len == 0)
        exit(0);
    else
        manage_server_buf(client, buffer);
}

void listening_select_event(client_t *client)
{
    struct timeval timeout;

    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    if (select(client->server_fd + 1, &client->rfds,
    NULL, NULL, NULL) < 0)
        exit(84);
    if (FD_ISSET(client->server_fd, &client->rfds)) {
        handle_receive_from_server(client);
        return;
    }
    if (FD_ISSET(client->fd, &client->rfds)) {
        handle_read_client(client);
        return;
    }
}

void handle_select_client(client_t *client)
{
    int sd = 0;
    int new_socket = 0;

    FD_ZERO(&(client->rfds));
    FD_SET(client->server_fd, &client->rfds);
    FD_SET(client->fd, &client->rfds);
    FD_ZERO(&(client->wfds));
    FD_SET(client->server_fd, &client->wfds);
    FD_SET(client->fd, &client->wfds);
    listening_select_event(client);
}
