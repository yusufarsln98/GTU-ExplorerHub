// practice for files

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

/*
    flags: (in the library <fcntl.h>)
    O_RDONLY - open for reading only
    O_RDWR - open for reading and writing
    O_CREAT - create file if it does not exist
    O_APPEND - append on each write
    O_TRUNC - truncate file to 0 length
    O_EXCL - used with O_CREAT, file must not exist
    O_NONBLOCK - open in non-blocking mode
    ...

    modes: (in the library <sys/stat.h>)
    S_IRUSR - read by owner
    S_IWGRP - write by group
    S_IXOTH - execute by others
    ...


*/

int main(int argc, char *argv[])
{
    // create a file
    int fd = open("test.txt", O_CREAT | O_WRONLY, 0644);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }
    // close the file
    close(fd);

    // open the test.txt file in read and write mode
    fd = open("test.txt", O_RDWR);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // write to the file
    char *s = "hello world";
    int n = write(fd, s, strlen(s));
    if (n == -1)
    {
        perror("write");
        return 1;
    }
    // close the file
    close(fd);
}