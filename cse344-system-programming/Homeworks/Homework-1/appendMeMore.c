// Sonuc: 70 puan

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h> // for strlen()

/*
    usage: ./appendMeMore <filename> num-bytes [x](optional)

    if x is specified, for each append operation,
    the file offset is set to the end of the file by lseek() before writing

    otherwise, the file will be opened with O_APPEND and bytes will be appended one by one

*/

#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[])
{
    int fd, num_bytes, i;
    char *filename;
    off_t offset;
    int use_lseek = FALSE;

    // check for correct number of arguments
    if (argc < 3 || argc > 4)
    {
        fprintf(stderr, "usage: %s <filename> num-bytes [x]\n", argv[0]);
        return 1;
    }

    filename = argv[1];
    num_bytes = atoi(argv[2]);

    // check if x was specified
    if (argc == 4)
    {
        if (strlen(argv[3]) == 1 && argv[3][0] == 'x')
        {
            use_lseek = TRUE;
        }
        else
        {
            fprintf(stderr, "usage: %s <filename> num-bytes [x]\n", argv[0]);
            return 1;
        }
    }

    // if x was specified, open the file without O_APPEND, otherwise open with O_APPEND
    fd = open(filename, O_WRONLY | O_CREAT | (use_lseek ? 0 : O_APPEND), 0666);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    if (use_lseek)
    {
        for (i = 0; i < num_bytes; i++)
        {
            offset = lseek(fd, 0, SEEK_END); // set file offset to end of file
            write(fd, "#", 1);               // write a single byte
        }
    }
    else
    {
        for (i = 0; i < num_bytes; i++)
        {
            write(fd, "#", 1); // write a single byte (O_APPEND will set file offset to end of file)
        }
    }

    close(fd);

    return 0;
}
