/*
** EPITECH PROJECT, 2024
** WriterFight
** File description:
** game
*/

#include "../../include.h"

void timer(writerfight_t *w)
{
    struct timespec tmp;
    double timelaspe = 0;
    double current_time;
    double l;
    time_t sec1 = w->game.clock.tv_sec;
    long sec2 = w->game.clock.tv_nsec;

    clock_gettime(1, &tmp);
    current_time = tmp.tv_sec + (tmp.tv_nsec / 1.0e9);
    l = sec1 + (sec2 / 1.0e9);
    timelaspe = current_time - l;
    if (timelaspe >= GAME_TIME)
        w->game.status = false;
}

void *thread_timer(void *v)
{
    writerfight_t *w = (writerfight_t *) (v);

    while (w->game.status == true) {
        timer(w);
        usleep(1000);
    }
    stop(w);
}
