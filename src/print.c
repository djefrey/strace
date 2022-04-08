/*
** EPITECH PROJECT, 2022
** B-PSU-402-STG-4-1-strace-jeffrey.winkler
** File description:
** print
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/ptrace.h>
#include <sys/stat.h>
#include "strace.h"
#include "syscalls.h"

static int print_process_string(pid_t pid, uint64_t ptr)
{
    int i = 0;
    char c;
    long ret;

    fprintf(stderr, "\"");
    do {
        errno = 0;
        ret = (char) ptrace(PTRACE_PEEKDATA, pid, ptr + i);
        c = (char) (ret & 0x00000000000000FF);
        if (ret == -1 && errno != 0) {
            perror(strerror(errno));
            exit(84);
        }
        fprintf(stderr, "%c", c);
        i++;
    } while (c != 0);
    fprintf(stderr, "\"");
    return i + 1;
}

static int print_arg(uint64_t value, int type, bool start_execve, args_t *args)
{
    if (!args->detailled)
        return fprintf(stderr, "%#lx", value);
    switch (type) {
        case NUM:
            return fprintf(stderr, "%li", value);
        case STRING:
            return start_execve ? fprintf(stderr, "\"%s\"", (char*) value)
            : print_process_string(args->pid, value);
        case UNSIGNED:
            return fprintf(stderr, "%lu", value);
        default:
            return fprintf(stderr, "%#lx", value);
    }
}

static int print_args(call_t *call, const syscall_t *syscall, args_t *args)
{
    const int syscall_args[6] = {syscall->arg0, syscall->arg1,
    syscall->arg2, syscall->arg3, syscall->arg4, syscall->arg5};
    uint32_t char_printed = 0;

    fprintf(stderr, "(");
    for (int i = 0; i < syscall->nb_args; i++) {
        if (i > 0)
            char_printed += fprintf(stderr, ", ");
        char_printed +=
        print_arg(call->args[i], syscall_args[i], call->start_execve, args);
    }
    fprintf(stderr, ")");
    return char_printed;
}

void print_syscall(call_t *call, bool detailled, pid_t pid)
{
    const syscall_t *syscall = SYSCALL_TABLE + call->id;
    uint32_t char_printed;
    args_t args = {pid, detailled};

    if (call->to_print && call->id < SYSCALL_TABLE_SIZE) {
        char_printed = fprintf(stderr, syscall->name);
        char_printed += print_args(call, syscall, &args);
        if (char_printed < 39)
            fprintf(stderr, "%*s", (39 - char_printed), "");
        fprintf(stderr, " = ");
        if (call->valid_ret)
            print_arg(call->ret, syscall->ret_type, call->start_execve, &args);
        else
            fprintf(stderr, "?");
        fprintf(stderr, "\n");
        call->to_print = false;
    }
}

void print_exit(int status)
{
    int exit = WEXITSTATUS(status);

    fprintf(stderr, "+++ exited with %u +++\n", exit);
}
