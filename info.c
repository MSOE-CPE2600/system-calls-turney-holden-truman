/**********************************
* CPE 2600 121 Lab 9: System Calls
* Filename: info.c
* Description: Program prints information about the system using system calls
*
* Author: Holden Truman
* Date 11/5/2024
***********************************/

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>

int main(int argc, char* argv[])
{
    //time of day
    struct timespec currentTime;
    if (clock_gettime(CLOCK_REALTIME, &currentTime) != 0) {
        perror("clock_gettime");
    }

    struct tm *localTime = localtime(&currentTime.tv_sec);
    if (localTime == NULL) {
        perror("localtime");
        return 1;
    } else {
        printf("Current time of day in ns: %lld\n", (((localTime->tm_hour * 60L * 60L) + (localTime->tm_min * 60L) + localTime->tm_sec) * 1000000000LL + currentTime.tv_nsec));
    }

    //network name
    char hostname[256];
    if (gethostname(hostname, 256) != 0) {
        perror("gethostname");
    } else {
        printf("Network name: %s\n", hostname);
    }

    //operating system name, release, and version
    struct utsname buffer;
    // Call uname and check if it succeeded
    if (uname(&buffer) != 0) {
        perror("uname");
    } else {
        printf("Operating system name: %s\n", buffer.sysname);
        printf("OS release: %s\n", buffer.release);
        printf("OS version: %s\n", buffer.version);
        printf("Hardware type: %s\n", buffer.machine);
    }   

    //num CPUS
    long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
    if (nprocs == -1) {
        perror("sysconf");
        return 1;
    } else {
        printf("Number of CPUs: %ld\n", nprocs);
    }


    //memory
    long page_size = getpagesize();
    long num_pages = sysconf(_SC_PHYS_PAGES);
    long num_avail_pages = sysconf(_SC_AVPHYS_PAGES);

    if (num_pages == -1 || num_avail_pages == -1) {
        perror("sysconf");
        return 1;
    } else {
        long total_mem = page_size * num_pages;
        long avail_mem = page_size * num_avail_pages;

        printf("Total Memory: %ld in Bytes\n", total_mem);
        printf("Available Memory: %ld in Bytes\n", avail_mem);
    }
    
    return 0;
}