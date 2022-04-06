/*
** EPITECH PROJECT, 2022
** B-PSU-402-STG-4-1-strace-jeffrey.winkler
** File description:
** main
*/

#include <string.h>
#include "strace.h"

int main(int ac, char **av, char **env)
{
    args_t args = {-1, false};
    int nb_args = read_args(ac, av, &args);

    if (ac - 1 - nb_args > 0) {
        if (args.pid == -1) {
            return search_and_start(av[nb_args + 1],
            av + nb_args + 1, env, args.detailled);
        } else
            return trace_program(&args);
    }
    return 84;
}

char *get_env(char **env, char *name)
{
    int name_len = strlen(name);
    int env_len;

    for (; *env; env++) {
        env_len = strlen(*env);
        if (env_len >= name_len + 1
        && !strcmp(*env, name) && (*env)[name_len] == '=')
            return *env + name_len + 1;
    }
    return NULL;
}
