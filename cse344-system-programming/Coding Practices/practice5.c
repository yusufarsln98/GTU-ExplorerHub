#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    // the path to the file
    char *path = argv[1];

    // the permissions for the file
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    // create the file
    // O_WRONLY - open for writing only
    // O_EXCL - used with O_CREAT, file must not exist
    int fd = open(path, O_WRONLY | O_EXCL | O_CREAT, mode);

    // check if the file was created
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // write to the file
    char *s = "hello world";
    size_t n = write(fd, s, strlen(s));
    if (n == -1)
    {
        perror("write");
        return 1;
    }

    printf("wrote %ld bytes to %s", n, path);

    return 0;
}

// to run the program:
// gcc -o practice5 p5.c && ./practice5 test.txt
// if test.txt already exists, the program will not create a new file