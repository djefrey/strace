/*
** EPITECH PROJECT, 2022
** B-PSU-402-STG-4-1-strace-jeffrey.winkler
** File description:
** print_process
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

static void read_child_bytes(pid_t pid, uint64_t ptr, char *buf, size_t size)
{
    long ret;
    char c;

    for (size_t i = 0; i < size; i++) {
        ret = (char) ptrace(PTRACE_PEEKDATA, pid, ptr + i);
        c = (char) (ret & 0x00000000000000FF);
        if (ret == -1 && errno != 0) {
            perror(strerror(errno));
            exit(84);
        }
        buf[i] = c;
    }
}

int print_process_string(pid_t pid, uint64_t ptr)
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
        if (c == 0)
            break;
        fprintf(stderr, "%c", c);
        i++;
    } while (true);
    fprintf(stderr, "\"");
    return i + 1;
}

int print_process_stat(pid_t pid, uint64_t ptr)
{
    struct stat statbuf;

    read_child_bytes(pid, ptr, (char*) &statbuf, sizeof(struct stat));
    return fprintf(stderr, "{st_mode=%u, st_size=%lu, ...}",
    statbuf.st_mode, statbuf.st_size);
}
