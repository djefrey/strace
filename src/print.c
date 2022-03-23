/*
** EPITECH PROJECT, 2022
** B-PSU-402-STG-4-1-strace-jeffrey.winkler
** File description:
** print
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/user.h>
#include "strace.h"
#include "syscalls.h"

static int print_arg(uint64_t value, int type, bool detailled)
{
    if (!detailled)
        return fprintf(stderr, "%#lx", value);
    switch (type) {
        case NUM:
            return fprintf(stderr, "%li", value);
        case STRING:
            return fprintf(stderr, "%s", (char*) value);
        case UNSIGNED:
            return fprintf(stderr, "%lu", value);
        default:
            return fprintf(stderr, "%#lx", value);
    }
}

static int print_args(call_t *call, const syscall_t *syscall, bool detailled)
{
    const int syscall_args[6] = {syscall->arg0, syscall->arg1,
    syscall->arg2, syscall->arg3, syscall->arg4, syscall->arg5};
    uint32_t char_printed = 0;

    fprintf(stderr, "(");
    for (int i = 0; i < syscall->nb_args; i++) {
        if (i > 0)
            char_printed += fprintf(stderr, ", ");
        char_printed += print_arg(call->args[i], syscall_args[i], detailled);
    }
    fprintf(stderr, ")");
    return char_printed;
}

void print_syscall(call_t *call, bool detailled)
{
    const syscall_t *syscall = SYSCALL_TABLE + call->id;
    uint32_t char_printed;

    if (call->to_print && call->id < SYSCALL_TABLE_SIZE) {
        char_printed = fprintf(stderr, syscall->name);
        char_printed += print_args(call, syscall, detailled);
        if (char_printed < 39)
            fprintf(stderr, "%*s", (39 - char_printed), "");
        fprintf(stderr, " = ");
        if (call->valid_ret)
            print_arg(call->ret, syscall->ret_type, detailled);
        else
            fprintf(stderr, "?");
        fprintf(stderr, "\n");
        call->to_print = false;
    }
}