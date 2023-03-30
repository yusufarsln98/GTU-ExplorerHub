// lseek practice
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// the third argument determines how to interpret the offset
// returns the new offset from the beginning of the file
// off_t lseek(int fd, off_t offset, int whence);

/*
    SEEK_SET
        number of bytes from the beginning of the file (only positive values)
    SEEK_CUR
        number of bytes from the current position (positive or negative)
    SEEK_END
        number of bytes from the end of the file (positive or negative)
*/

// some examples
/*
    lseek(fd, 0, SEEK_SET); // beginning of file
    lseek(fd, 0, SEEK_END); // end of file
    lseek(fd, -1, SEEK_END); // last byte of file
    lseek(fd, -10, SEEK_CUR); // 10 bytes prior to current position
    lseek(fd, 10000, SEEK_END); // 10000 bytes past the end of the file
*/

int main(int argc, char *argv[])
{
    int zero = 0;
    const int megabyte = 1024 * 1024;
    char *filename = argv[1];

    size_t length = (size_t)atoi(argv[2]) * megabyte;

    // create a new file
    int fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0666);

    // jump 1 byte short of where we want the file to end
    lseek(fd, length - 1, SEEK_SET);

    write(fd, &zero, 1);

    close(fd);

    return 0;
}

// to compile:
// gcc -o practice practice9.c
// to run:
// ./practice practice9.txt 10