/*
** EPITECH PROJECT, 2022
** B-PSU-402-STG-4-1-strace-jeffrey.winkler
** File description:
** execute
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include "strace.h"

static pid_t start_program(char *bin, char **args, char **env)
{
    pid_t pid = fork();

    if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        execve(bin, args, env);
        exit(0);
    } else
        return pid;
}

int search_and_start(char *name, char **args, char **env, bool detailled)
{
    char *bin = get_binary_path(name, env);
    pid_t pid;
    int ret;

    if (!bin)
        return 84;
    pid = start_program(bin, args, env);
    if (pid == -1) {
        free((char*) bin);
        return 84;
    }
    ret = trace_program(&((args_t) {pid, detailled}));
    free((char*) bin);
    return ret;
}
