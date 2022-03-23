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

static void set_call_values(call_t *call,
struct user_regs_struct *regs, bool print)
{
    call->to_print = print;
    call->id = regs->rax;
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

    errno = 0;
    instr = ptrace(PTRACE_PEEKTEXT, pid, regs->rip, 0);
    if (errno && instr == -1)
        return -1;
    opcode = instr & 0x000000000000FFFF;
    if (opcode == 0x050F) {
        if (!(*print) && regs->rax == 59)
            *print = 1;
        set_call_values(call, regs, *print);
    } else
        call->to_print = false;
    return 1;
}

int trace_program(pid_t pid, bool detailled)
{
    struct user_regs_struct regs;
    call_t call_buff[2] = {0};
    int run = 1;
    bool print = 0;
    int i = 0;
    int status;

    ptrace(PTRACE_ATTACH, pid, 0, 0);
    for (; run == 1; i++) {
        waitpid(pid, &status, 0);
        if (!WIFEXITED(status)) {
            ptrace(PTRACE_GETREGS, pid, 0, &regs);
            run = read_instruction(pid, call_buff + i % 2, &regs, &print);
            (call_buff + (i + 1) % 2)->ret = regs.rax;
            (call_buff + (i + 1) % 2)->valid_ret = true;
            print_syscall(call_buff + (i + 1) % 2, detailled);
            ptrace(PTRACE_SINGLESTEP, pid, 0, 0);
        } else
            run = 0;
    }
    (call_buff + i % 2)->valid_ret = false;
    print_syscall(call_buff + i % 2, detailled);
    return run == -1 ? 84 : 0;
}
