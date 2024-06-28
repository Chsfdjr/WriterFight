/*
** EPITECH PROJECT, 2024
** B-YEP-400-MLH-4-1-zappy-aya.khadoum
** File description:
** manipulate_2d_array
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../include.h"

int len_tab(char **tab)
{
    int i = 0;

    if (tab == NULL)
        return 0;
    while (tab[i] != NULL)
        i++;
    return i;
}

void free_tab(char **tab)
{
    int len = len_tab(tab);

    for (int i = 0; i < len; i++) {
        free(tab[i]);
    }
    free(tab);
}
