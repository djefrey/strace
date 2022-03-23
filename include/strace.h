/*
** EPITECH PROJECT, 2022
** B-PSU-402-STG-4-1-strace-jeffrey.winkler
** File description:
** strace
*/

#pragma once

#include <aio.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/user.h>

typedef struct args_s {
    pid_t pid;
    bool detailled;
} args_t;

typedef struct call_s {
    bool to_print;
    bool valid_ret;
    uint64_t id;
    uint64_t ret;
    uint64_t args[6];
} call_t;

char *get_env(char **env, char *name);

int read_args(int ac, char **av, args_t *args);

int search_and_start(char *name, char **args, char **env, bool detailled);
int trace_program(pid_t pid, bool detailled);

char *get_binary_path(char *name, char **env);

void print_syscall(call_t *call, bool detailled);