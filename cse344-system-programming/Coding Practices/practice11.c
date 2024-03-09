// fcntl practice
/*
    - it can manipulate the flags associated with a file descriptor (same ones used during opening)
    - it can duplicate a file descriptor
    - it can lock and unlock a file - very useful for inter process communication (IPC)

*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *file = argv[1];
    int fd;
    struct flock lock;

    printf("Opening file %s\n", file);
    // open the file
    fd = open(file, O_WRONLY);

    printf("Setting lock\n");
    //  initialize the flock structure
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;
    // place a write lock on the file
    fcntl(fd, F_SETLKW, &lock);

    printf("Press enter to unlock\n");
    getchar();

    printf("Unlocking\n");
    // release the lock
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);

    printf("Closing file\n");
    // close the file
}