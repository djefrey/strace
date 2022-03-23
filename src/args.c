/*
** EPITECH PROJECT, 2022
** B-PSU-402-STG-4-1-strace-jeffrey.winkler
** File description:
** args
*/

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "strace.h"

static int read_int(char *str)
{
    int i = 0;

    while (*str) {
        if (*str < '0' || *str > '9')
            exit(84);
        i = i * 10 + (*str - '0');
    }
    return i;
}

int read_args(int ac, char **av, args_t *args)
{
    int i = 1;
    int len;

    for (; i < ac; i++) {
        len = strlen(av[i]);
        if (len == 2 && !strcmp("-s", av[i]))
            args->detailled = true;
        else if (len == 2 && !strcmp("-p", av[i]) && i < ac - 1) {
            args->pid = read_int(av[++i]);
        } else
            break;
    }
    return i - 1;
}
