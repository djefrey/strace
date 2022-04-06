/*
** EPITECH PROJECT, 2022
** B-PSU-402-STG-4-1-strace-jeffrey.winkler
** File description:
** trace
*/

#include <errno.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <stdio.h>
#include "strace.h"
#include "syscalls.h"

static void set_call_values(call_t *call, struct user_regs_struct *regs,
bool print, bool start_execve)
{
    call->to_print = print;
    call->id = regs->rax;
    call->start_execve = start_execve;
    call->args[0] = regs->rdi;
    call->args[1] = regs->rsi;
    call->args[2] = regs->rdx;
    call->args[3] = regs->rcx;
    call->args[4] = regs->r8;
    call->args[5] = regs->r9;
}

static int read_instruction(pid_t pid, call_t *call,
struct user_regs_struct *regs, bool *print)
{
    unsigned long instr;
    unsigned long opcode;
    bool start_execve = false;

    errno = 0;
    instr = ptrace(PTRACE_PEEKTEXT, pid, regs->rip, 0);
    if (errno && instr == -1)
        return -1;
    opcode = instr & 0x000000000000FFFF;
    if (opcode == 0x050F) {
        if (!(*print) && regs->rax == 59) {
            *print = 1;
            start_execve = true;
        }
        set_call_values(call, regs, *print, start_execve);
    } else
        call->to_print = false;
    return 1;
}

static int handle_instruction(args_t *args,
call_t call_buff[2], bool *print, int i)
{
    struct user_regs_struct regs;
    int run;

    ptrace(PTRACE_GETREGS, args->pid, 0, &regs);
    run = read_instruction(args->pid, call_buff + i % 2, &regs, print);
    (call_buff + (i + 1) % 2)->ret = regs.rax;
    (call_buff + (i + 1) % 2)->valid_ret = true;
    print_syscall(call_buff + (i + 1) % 2, args->detailled, args->pid);
    ptrace(PTRACE_SINGLESTEP, args->pid, 0, 0);
    return run;
}

int trace_program(args_t *args)
{
    call_t call_buff[2] = {0};
    int run = 1;
    bool print = 0;
    int i = 0;
    int status;

    ptrace(PTRACE_ATTACH, args->pid, 0, 0);
    for (; run; i++) {
        waitpid(args->pid, &status, 0);
        if (!WIFEXITED(status)) {
            run = handle_instruction(args, call_buff, &print, i);
        } else
            run = 0;
    }
    (call_buff + i % 2)->valid_ret = false;
    print_syscall(call_buff + i % 2, args->detailled, args->pid);
    ptrace(PTRACE_DETACH, args->pid, 0, 0);
    print_exit(status);
    return run == -1 ? 84 : 0;
}
