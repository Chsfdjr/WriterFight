/*
** EPITECH PROJECT, 2024
** client
** File description:
** client
*/

#include "../../include.h"

void client_initialization(client_t *cliUtils, char *ip, int port)
{
    struct sockaddr_in client;
    int server_fd = 0;
    int client_fd = 0;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
        exit(84);
    client.sin_family = AF_INET;
    client.sin_port = htons(port);
    client.sin_addr.s_addr = inet_addr(ip);
    client_fd = connect(server_fd,
    (struct sockaddr *)&client, sizeof(client));
    if (client_fd < 0)
        exit(84);
    cliUtils->server_fd = server_fd;
    cliUtils->fd = client_fd;
    cliUtils->name = malloc(sizeof(char) * 100 + 1);
    cliUtils->name[100] = '\0';
}
