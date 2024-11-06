/**********************************
* CPE 2600 121 Lab 9: System Calls
* Filename: pmod.c
* Description: Program changes the priority of the called process then nanosleeps and prints a goodbye message using system calls
*
* Author: Holden Truman
* Date 11/5/2024
***********************************/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h> 
#include <time.h>

int main(int argc, char* argv[])
{
    int which = PRIO_PROCESS;
    id_t pid = getpid();
    int ret;

    ret = getpriority(which, pid);
    printf("Initial Process Priority: %d\n", ret);

    int increment = 10;  // positive increment nice reduces priority

    int new_nice_value = nice(increment);

    if (new_nice_value == -1 && errno != 0) {
        perror("nice");
        return EXIT_FAILURE;
    }

    ret = getpriority(which, pid);
    printf("Final Process Priority: %d\n", ret);


    struct timespec req, rem;

    // Set the duration for sleep (1.837272638 seconds)
    req.tv_sec = 1;          // 1 second
    req.tv_nsec = 837272638; // 837272638 nanoseconds (0.837272638 seconds)

    nanosleep(&req, &rem);
    printf("Goodbye, closing program\n");

    return 0;
}