/**********************************
* Filename: pinfo.c
* Description: Program prints information about a process id inputted via command line or the called process using system calls
*
* Author: Holden Truman
* Date 11/5/2024
***********************************/

#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h> 
#include <sched.h>

int main(int argc, char* argv[])
{
    int which = PRIO_PROCESS;
    id_t pid;
    int ret;
    
    if (argc > 1) {
        pid = atoi(argv[1]);
    } else {
        pid = getpid();
    }
    ret = getpriority(which, pid);
    printf("Process Priority: %d\n", ret);

    int policy;
    policy = sched_getscheduler(pid);

    if (policy == -1) {
        perror("sched_getscheduler");
        exit(1);
    }

    switch (policy) {
        case SCHED_FIFO:
            printf("Scheduling policy: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Scheduling policy: SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("Scheduling policy: SCHED_OTHER\n");
            break;
        default:
            printf("Unknown scheduling policy\n");
            break;
    }

    return 0;
}