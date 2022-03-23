/*
** EPITECH PROJECT, 2022
** B-PSU-402-STG-4-1-strace-jeffrey.winkler
** File description:
** syscalls
*/

#pragma once

#define     NUM     1
#define     STRING  2
#define     UNSIGNED    3
#define     VOID_P  (4)
#define     CONST_VOID_P    (5)
#define     STRUCT_P    (7)
#define     STRUCT_STAT_P   (8)
#define     STRUCT_FD_P     (9)
#define     PVOID   (12)
#define     CONST_KERNEL_SIGSET_T_P     (13)
#define     KERNEL_SIGSET_T_P   (14)
#define     VARGS   (16)
#define     CONST_STRUCT_IOVEC_P    (17)
#define     FD_SET_P    (18)
#define     STRUCT_TIMEVAL_P    (19)
#define     VOID    (20)
#define     STRUCT_SHMID_DS_P   (23)
#define     CONST_STRUCT_TIMESPEC_P     (24)
#define     STRUCT_TIMESPEC_P   (25)
#define     STRUCT_ITIMERVAL_P      (26)
#define     CONST_STRUCT_ITIMERVAL_P        (28)
#define     CONST_STRUCT_SOCKADDR_P     (31)
#define     SOCKLEN_T       (32)
#define     STRUCT_SOCKADDR_P       (33)
#define     SOCKLEN_T_P     (34)
#define     CONST_STRUCT_MSGHDR_P       (35)
#define     STRUCT_MSGHDR_P     (36)
#define     STRUCT_RUSAGE_P     (39)
#define     STRUCT_UTSNAME_P        (40)
#define     STRUCT_SEMBUF_P     (41)
#define     STRUCT_MSQID_DS_P       (43)
#define     STRUCT_LINUX_DIRENT_P       (44)
#define     MODE_T      (49)
#define     UID_T       (51)
#define     GID_T       (52)
#define     STRUCT_TIMEZONE_P       (53)
#define     STRUCT_RLIMIT_P     (54)
#define     CLOCK_T     (55)
#define     STRUCT_TMS_P        (56)
#define     ENUM_____REQUEST        (57)
#define     CONST_GID_T_P       (58)
#define     UID_T_P     (59)
#define     GID_T_P     (60)
#define     CAP_USER_HEADER_T       (61)
#define     CAP_USER_DATA_T     (62)
#define     CONST_CAP_USER_DATA_T       (63)
#define     CONST_STACK_T_P     (64)
#define     STACK_T_P       (65)
#define     CONST_STRUCT_UTIMBUF_P      (66)
#define     DEV_T       (67)
#define     STRUCT_STATFS_P     (68)
#define     ID_T        (69)
#define     CONST_STRUCT_SCHED_PARAM_P      (70)
#define     STRUCT_SCHED_PARAM_P        (71)
#define     STRUCT_TIMESPEC_P_      (72)
#define     STRUCT____ARGS_P        (73)
#define     STRUCT_TIMEX_P      (74)
#define     CONST_STRUCT_RLIMIT_P       (75)
#define     CONST_STRUCT_TIMEVAL_P      (76)
#define     CONST_STRUCT_TIMEZONE_P     (77)
#define     CADDR_T     (78)
#define     STRUCT_KERNEL_SYM_P     (79)
#define     NUM_P       (80)
#define     STRUCT_NFSCTL_ARG_P     (81)
#define     UNION_NFSCTL_RES_P      (82)
#define     OFF64_T     (83)
#define     TIME_T      (84)
#define     _T___T_P        (85)
#define     CONST_CPU_SET_T_P       (86)
#define     CPU_SET_T_P     (87)
#define     STRUCT_USER_DESC_P      (88)
#define     AIO_CONTEXT_T_P     (90)
#define     AIO_CONTEXT_T       (91)
#define     STRUCT_IO_EVENT_P       (92)
#define     STRUCT_IOCB_P       (93)
#define     U64     (94)
#define     STRUCT_LINUX_DIRENT64_P     (95)
#define     CLOCKID_T       (96)
#define     STRUCT_SIGEVENT_P       (97)
#define     TIMER_T_P       (98)
#define     TIMER_T     (99)
#define     CONST_STRUCT_ITIMERSPEC_P       (100)
#define     STRUCT_ITIMERSPEC_P     (101)
#define     STRUCT_EPOLL_EVENT_P        (102)
#define     CONST_STRUCT_TIMEVAL        (103)
#define     CONST_UNSIGNED_P        (104)
#define     UNSIGNED_P      (105)
#define     MQD_T       (106)
#define     CONST_STRUCT_SIGEVENT_P     (108)
#define     STRUCT_MQ_ATTR_P        (109)
#define     STRUCT_KEXEC_SEGMENT_P      (110)
#define     IDTYPE_T        (111)
#define     SIGINFO_T_P     (112)
#define     KEY_SERIAL_T        (113)
#define     UNUM32_T        (114)
#define     STRUCT_POLLFD_P     (115)
#define     CONST_SIGSET_T_P        (116)
#define     STRUCT_ROBUST_LIST_HEAD_P       (117)
#define     LNUM_P      (118)
#define     CONST_NUM_P     (119)
#define     CONST_STRUCT_TIMESPEC       (120)
#define     STRUCT_PERF_EVENT_ATTR_P        (121)
#define     STRUCT_MMSGHDR_P        (122)
#define     UNUM64_T        (123)
#define     STRUCT_FILE_HANDLE_P        (124)
#define     STRUCT__CACHE_P     (126)
#define     STRUCT_SCHED_ATTR_P     (127)
#define     UNION__ATTR_P       (128)

typedef struct syscall_s {
    int id;
    const char *name;
    int nb_args;
    int ret_type;
    int arg0;
    int arg1;
    int arg2;
    int arg3;
    int arg4;
    int arg5;
} syscall_t;

extern const unsigned int SYSCALL_TABLE_SIZE;
extern const syscall_t SYSCALL_TABLE[330];
