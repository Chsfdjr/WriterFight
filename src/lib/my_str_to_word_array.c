/*
** EPITECH PROJECT, 2022
** header
** File description:
** minishell
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "header.h"

int count_len_buf_2(char *buf, char *del)
{
    int len = 0;

    for (int i = 0; buf[i] != '\0'; i++) {
        if (check_elem(buf[i], del) != 2)
            len++;
        else
            return len;
    }
    return len;
}

void include_in_tab(char *tab, char *buf, char *del, int x)
{
    int i = 0;

    while (check_elem(buf[i], del) != 1) {
        tab[i] = buf[i];
        x++;
        i++;
    }
    tab[i] = '\0';
}

char **my_str_to_word_array(char *buf, char *del)
{
    int i = 0;
    int x = 0;
    int len_tab = 0;
    char **tab = NULL;

    if (buf == NULL)
        return tab;
    len_tab = count_delimiter(buf, del);
    tab = malloc(sizeof(char *) * (len_tab + 1));
    tab[len_tab] = NULL;
    for (i = 0; i < len_tab; i++) {
        buf = buf + count_len_buf_2(buf, del);
        x = count_len_buf(buf, del);
        tab[i] = malloc(sizeof(char) * (x + 1));
        include_in_tab(tab[i], buf, del, x);
        buf = buf + x;
    }
    return tab;
}
