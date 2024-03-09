// ioctl practice
#include <fcntl.h>
#include <linux/cdrom.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// int ioctl(int d, int request, ...);
/*
    d: file descriptor
    request: request code
    ...: optional arguments
*/

// ioctl function is for manipulating underlying device parameters of special files.
// It requires detailed knowledge of the device represented by the fd (file descriptor).

// !-- It is beyond the scope of the course --!

int main(int argc, char *argv[])
{
    // open a file descriptor to the device specified on the command line
    int fd = open(argv[1], O_RDONLY);

    // eject the CD-ROM
    ioctl(fd, CDROMEJECT);

    // close the file descriptor
    close(fd);

    return 0;
}

// to compile:
// gcc -o practice practice10.c
// to run:
// ./practice /dev/cdrom