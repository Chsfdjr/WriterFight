/*
** EPITECH PROJECT, 2022
** header
** File description:
** minishell
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int check_elem(char charac, char *del)
{
    int i = 0;

    for (i = 0; del[i] != '\0'; i++) {
        if (charac == del[i] || charac == '\0')
            return 1;
    }
    return 2;
}

int count_delimiter(char *buf, char *del)
{
    int len = 0;
    int i = 0;
    int del_check = 0;
    int old_check = 0;

    for (i = 0; buf[i] != '\0'; i++) {
        del_check = check_elem(buf[i], del);
        if ((del_check == 0 || del_check == 2) && (del_check != old_check))
            len++;
        old_check = del_check;
    }
    return len;
}

int count_len_buf(char *buf, char *del)
{
    int len = 0;
    int i = 0;

    while (check_elem(buf[i], del) != 1) {
        len++;
        i++;
    }
    return len;
}
