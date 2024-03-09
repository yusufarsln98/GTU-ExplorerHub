// dup and dup2 implementation with fcntl

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int dup(int oldfd)
{
    int newfd;
    newfd = fcntl(oldfd, F_DUPFD, 0);
    if (newfd == -1)
    {
        errno = EBADF;
        return -1;
    }

    return newfd;
}

int dup2(int oldfd, int newfd)
{
    int flag;
    int result;

    // if oldfd is not a valid file descriptor
    flag = fcntl(oldfd, F_GETFL);
    if (flag == -1)
    {
        errno = EBADF;
        return -1;
    }

    if (oldfd == newfd)
    {
        return newfd;
    }
    else
    {
        // if newfd is a valid file descriptor
        // close it first
        flag = fcntl(newfd, F_GETFL);
        if (flag != -1)
        {
            close(newfd);
        }

        result = fcntl(oldfd, F_DUPFD, newfd);
        if (result == -1)
        {
            errno = EBADF;
            return -1;
        }
        else
        {
            return newfd;
        }
    }
}

int main(int argc, char *argv[])
{
    int fd1, fd2, fd3;
    fd1 = open("test1.txt", O_RDWR | O_CREAT, 0644);
    fd2 = open("test2.txt", O_RDWR | O_CREAT, 0644);

    if (fd1 == -1 || fd2 == -1)
    {
        perror("open");
        exit(1);
    }

    printf("\n -------- duplication.c -------- \n\n");

    printf(" -- Two file descriptors created: %d (test1.txt) and %d (test2.txt) \n", fd1, fd2);

    // write to fd1
    write(fd1, "Hello!", 6);
    printf(" -- \"Hello!\" written to fd1 (check the test1.txt to see results) \n");

    // test the dup2 function
    printf(" -- Test the dup2 function: \n");
    // dup fd1 to fd2
    dup2(fd1, fd2);

    printf(" -- After dup2(fd1, fd2), fd2 is %d\n", fd2);

    // compare cursor positions
    printf(" -- Compare cursor positions: \n");
    printf(" -- fd1: %ld, fd2: %ld \n", lseek(fd1, 0, SEEK_CUR), lseek(fd2, 0, SEEK_CUR));

    // write to fd2
    write(fd2, "Hello World!", 12);

    printf(" -- \"Hello World!\" written to fd2 (check the test1.txt to see results) \n");

    printf(" -- Error when invalid file descriptor is passed to dup2: \n");
    dup2(100, 101);
    // print error message
    perror("dup2");
    printf("\n");

    printf(" -- Error when oldfd and newfd are the same but not a valid file descriptor: \n");
    perror("dup2");
    dup2(100, 100);

    // test the dup function
    printf(" \n\n-- Test the dup function: \n");

    // open a new file descriptor
    fd3 = open("test3.txt", O_RDWR | O_CREAT, 0644);
    printf(" -- A new file descriptor created: %d (test3.txt) \n", fd3);
    printf(" -- stdout duped to fd3 (check the test3.txt to see results) \n");
    // dup stdout to fd3
    dup2(fd3, 1);
    printf(" -- After dup2(1, fd3), fd3 is %d\n", fd3);

    // invalid file descriptor for dup
    fprintf(stderr, " -- Error when invalid file descriptor (100) is passed to dup: \n");
    perror("dup");
    dup(100);

    // close all file descriptors
    close(fd1);
    close(fd2);
    close(fd3);

    printf(" -- All file descriptors closed (check test3.txt to see result) \n");

    return 0;
}