/*
** EPITECH PROJECT, 2024
** WriterFight
** File description:
** main
*/

#include "../../include.h"

static void display_usage(int ac, char **av)
{
    if (ac == 1 || (ac == 2 && strcmp(av[1], "-h") == 0)) {
        printf("USAGE: ./hostWriterFight -p port -f filepath\n");
        exit(0);
    }
}

static void check_port(char *av, writerfight_t *w)
{
    int port = atoi(av);

    if (port <= 1023) {
        printf("Bad port");
        exit(84);
    } else
        w->server.port = port;
}

static void check_filepath(char *av, writerfight_t *w)
{
    struct stat desc;
    int rd;
    int fd = open(av, O_RDONLY);
    stat(av, &desc);
    int size = desc.st_size;
    char buffer[size];

    rd = read(fd, buffer, size);
    close(fd);
    buffer[rd] = '\0';
    w->game.sentences = my_str_to_word_array(buffer, "\n");
    if (w->game.sentences == NULL) {
        printf("Empty file\n");
        exit(84);
    }
    w->game.nb_sentences = 0;
    for (int i = 0; w->game.sentences[i] != NULL; i++)
        w->game.nb_sentences++;
    close(fd);
}

static void get_arguments(int ac, char **av, writerfight_t *w)
{
    bool p = false;
    bool f = false;

    for (int i = 0; i < ac; i++) {
        if (strcmp(av[i], "-p") == 0 && av[i + 1]) {
            check_port(av[i + 1], w);
            p = true;
        }
        if (strcmp(av[i], "-f") == 0 && av[i + 1]) {
            check_filepath(av[i + 1], w);
            f = true;
        }
    }
    if (!p) {
        printf("Missing port.\n");
        exit(84);
    }
    if (!f)
        check_filepath(".default.txt", w);
}

int main(int ac, char **av)
{
    writerfight_t *w = malloc(sizeof(writerfight_t));

    display_usage(ac, av);
    get_arguments(ac, av, w);
    init_serv(w);
    loop_serv(w, w->server.fd);
    return 0;
}
