/*
** EPITECH PROJECT, 2024
** client
** File description:
** client
*/

#include "../../include.h"

void clientloop(client_t *client)
{
    while (1) {
        handle_select_client(client);
        usleep(1000);
    }
    free(client);
}

int client(char **av)
{
    client_t *cliUtils = malloc(sizeof(client_t));

    write(0, "Enter your name: ", strlen("Enter your name: "));
    usleep(1000);
    client_initialization(cliUtils, av[1], atoi(av[2]));
    if (cliUtils->fd < 0)
        return 84;
    clientloop(cliUtils);
    close(cliUtils->fd);
    return 0;
}

int handle_arguments(char **av)
{
    if (strcmp(av[1], "-help") == 0) {
        printf("USAGE: ./playerWriterFight ip port\n");
        printf
        ("%s\n%s\n",
        "\tip is the server ip address on which the server socket listens",
        "\tport is the port number on which the server socket listens");
        exit(0);
    } else {
        printf("Invalid arguments\nTry ./playerWriterFight -help\n");
        exit(84);
    }
}

int main(int ac, char **av)
{
    if (ac == 2)
        return handle_arguments(av);
    if (ac == 3)
        return client(av);
    else {
        printf("Invalid arguments\nTry ./playerWriterFight -help\n");
        return 84;
    }
    return 0;
}
