// Copy file example
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

// Buffer size (copyfile)
#define BLKSIZE 1024

// Flags and permisions (main)
#define READ_FLAGS O_RDONLY
#define WRITE_FLAGS (O_WRONLY | O_CREAT | O_EXCL)
#define WRITE_PERMS (S_IRUSR | S_IWUSR)

int copyfile(int fromfd, int tofd)
{
    char *bp; // buffer pointer
    char buf[BLKSIZE];
    int bytesread;
    int byteswritten = 0;
    int totalbytes = 0;

    for (;;)
    {
        while ((bytesread = read(fromfd, buf, BLKSIZE)) == -1 &&
               (errno == EINTR)) // Handle interrupted by signal
            ;
        if (bytesread <= 0) // real error or EOF
        {
            break;
        }

        bp = buf;
        while (bytesread > 0)
        {
            while ((byteswritten = write(tofd, bp, bytesread)) == -1 &&
                   (errno == EINTR)) // Handle interrupted by signal
                ;
            if (byteswritten < 0) // real error
            {
                break;
            }
            bytesread -= byteswritten;
            totalbytes += byteswritten;
            bp += byteswritten;
        }

        if (byteswritten == -1) // real error on tofd
        {
            break;
        }
    }

    return totalbytes;
}

int main(int argc, char *argv[])
{
    int bytes;
    int fromfd, tofd;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s fromfile tofile\n", argv[0]);
        return 1;
    }

    if ((fromfd = open(argv[1], READ_FLAGS)) == -1)
    {
        perror(argv[1]);
        return 1;
    }

    if ((tofd = open(argv[2], WRITE_FLAGS, WRITE_PERMS)) == -1)
    {
        perror(argv[2]);
        return 1;
    }

    bytes = copyfile(fromfd, tofd);

    // print fromfd and tofd
    printf("fromfd: %d, tofd: %d \n", fromfd, tofd);

    printf("Copied %d bytes from %s to %s\n", bytes, argv[1], argv[2]);

    close(fromfd);
    close(tofd);

    return 0;
}