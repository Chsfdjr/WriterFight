/*
** EPITECH PROJECT, 2024
** WriterFight
** File description:
** game
*/

#include "../../include.h"

char *get_randow_sentence(writerfight_t *w)
{
    int index = 0;

    srand(time(NULL));
    index = rand() % w->game.nb_sentences;
    return w->game.sentences[index];
}

bool verify_answer(player_t *player, char *answer)
{
    if (strcmp(answer, player->sentence_picked) == 0)
        return true;
    else
        return false;
}

void start(writerfight_t *w)
{
    for (int i = 0; i < w->server.nb_player; i++) {
        usleep(1000);
        dprintf(w->player[i].fd, "clear");
        usleep(1000);
        dprintf(w->player[i].fd, "WriteFight | Nouvelle partie\n\nRappelons les règles:\nRéussir à taper le plus de phrases possibles\n\n\n");
        dprintf(w->player[i].fd, "Lancement de la partie ! Bonne chance !\n\n\n"); 
        w->player[i].sentence_picked = get_randow_sentence(w);
    }
    sendSentence(w);
    w->game.status = true;
    clock_gettime(1, &w->game.clock);
    pthread_create(&w->game.timer, NULL, thread_timer, (void *) w);
}

void stop(writerfight_t *w)
{
    w->game.status = false;
    printf("Fin de la partie ! Voici les scores:\n");
    showscore(0, w);
    for (int i = 0; i < w->server.nb_player; i++) {
        usleep(1000);
        dprintf(w->player[i].fd, "clear");
        usleep(1000);
        dprintf(w->player[i].fd, "Fin de la partie ! Voici les scores:\n");
        w->player[i].allow = false;
        showscore(w->player[i].fd, w);
    }
}

void showscore(int fd, writerfight_t *w)
{
    dprintf(fd, "-----------Scoreboard------------\n");
    for (int e = 0; e < w->server.nb_player; e++) {
        dprintf(fd, "%s: %d\n", w->player[e].name, w->player[e].score);
    }
    dprintf(fd, "----------------------------------\n");
}

void sendSentence(writerfight_t *w)
{
    for (int i = 0; i < w->server.nb_player; i++)
        dprintf(w->player[i].fd, "Nouvelle phrase:\n%s\n", w->player[i].sentence_picked);
}
