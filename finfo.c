/**********************************
* Filename: finfo.c
* Description: Program prints information about a file inputted via command line using system calls
*
* Author: Holden Truman
* Date 11/5/2024
***********************************/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void print_permissions(mode_t mode);

int main(int argc, char* argv[])
{
    struct stat statbuf;

    if (argc < 2) {
        printf("Provide a file path as an argument\n");
        exit(-1);
    }

    if (stat(argv[1], &statbuf) == -1) {
        perror("stat");
        return -1;
    }

    if (S_ISREG(statbuf.st_mode)) {
        printf("Regular file\n");
    } else if (S_ISDIR(statbuf.st_mode)) {
        printf("Directory\n");
    } else if (S_ISCHR(statbuf.st_mode)) {
        printf("Character device\n");
    } else if (S_ISBLK(statbuf.st_mode)) {
        printf("Block device\n");
    } else if (S_ISFIFO(statbuf.st_mode)) {
        printf("FIFO/pipe\n");
    } else if (S_ISLNK(statbuf.st_mode)) {
        printf("Symbolic link\n");
    } else if (S_ISSOCK(statbuf.st_mode)) {
        printf("Socket\n");
    } else {
        printf("Unknown file type\n");
    }

    printf("Permissions:");
    print_permissions(statbuf.st_mode);

    printf("Owner: UID=%d\n", statbuf.st_uid);
    printf("Size: %ld bytes\n", statbuf.st_size);
    printf("Last modified: %s", ctime(&statbuf.st_mtime));

    return 0;
}

void print_permissions(mode_t mode) {
    printf("Permissions: ");
    
    // User permissions
    printf("%c", (mode & S_IRUSR) ? 'r' : '-'); // User read
    printf("%c", (mode & S_IWUSR) ? 'w' : '-'); // User write
    printf("%c", (mode & S_IXUSR) ? 'x' : '-'); // User execute

    // Group permissions
    printf("%c", (mode & S_IRGRP) ? 'r' : '-'); // Group read
    printf("%c", (mode & S_IWGRP) ? 'w' : '-'); // Group write
    printf("%c", (mode & S_IXGRP) ? 'x' : '-'); // Group execute

    // Other permissions
    printf("%c", (mode & S_IROTH) ? 'r' : '-'); // Other read
    printf("%c", (mode & S_IWOTH) ? 'w' : '-'); // Other write
    printf("%c", (mode & S_IXOTH) ? 'x' : '-'); // Other execute
    
    printf("\n");
}
