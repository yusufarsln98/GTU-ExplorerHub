/*
    FIFOs

    A FIFO is simply a pipe that has a name in the filesystem.
    * it is unidirectional (has reading and writing ends)
    * unlike the Pipes, in FIFO processes does not need to be related.

    #include <sys/stat.h>
    int mkfifo(const char* pathname, mode_t mode); // returns 0 on success, -1 otherwise

    modes: constants: S_I(R|W|X)(USR|GRP|OTH)
*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define BUF_SIZE 256
#define FIFO_PERM (S_IRUSR | S_IWUSR)

// r_write function
ssize_t r_write(int fd, void *buf, size_t size)
{
    ssize_t retval;
    ssize_t wcnt = 0;

    while (size > 0 && (retval = write(fd, buf, size)) != 0)
    {
        if (retval == -1)
        {
            if (errno == EINTR)
                continue;
            perror("write");
            break;
        }
        size -= retval;
        buf += retval;
        wcnt += retval;
    }

    return wcnt;
}

// r_read function
ssize_t r_read(int fd, void *buf, size_t size)
{
    ssize_t retval;
    ssize_t rcnt = 0;

    while (size > 0 && (retval = read(fd, buf, size)) != 0)
    {
        if (retval == -1)
        {
            if (errno == EINTR)
                continue;
            perror("read");
            break;
        }
        size -= retval;
        buf += retval;
        rcnt += retval;
    }

    return rcnt;
}

int dofifochild(const char *fifoname, const char *idstring);
int dofifoparent(const char *fifoname);

int main(int argc, char const *argv[])
{
    pid_t childpid;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s pipename\n", argv[0]);
        return 1;
    }

    if (mkfifo(argv[1], FIFO_PERM) == -1)
    {
        if (errno != EEXIST)
        {
            fprintf(stderr, "[%ld]: failed to create named pipe %s: %s\n",
                    (long)getpid(), argv[1], strerror(errno));
            return 1;
        }
    }

    if ((childpid = fork()) == -1)
    {
        perror("Failed to fork");
        return 1;
    }

    if (childpid == 0)
    {
        // the child writes
        return dofifochild(argv[1], "this was written by the child");
    }
    else
    {
        return dofifoparent(argv[1]);
    }

    return 0;
}

int dofifochild(const char *fifoname, const char *idstring)
{
    char buf[BUF_SIZE];
    int fd;
    int rval;
    ssize_t strsize;

    fprintf(stderr, "[%ld]: (child) about the open FIFO %s. . .\n",
            (long)getpid(), fifoname);

    while (((fd = open(fifoname, O_WRONLY)) == -1) && (errno == EINTR))
        ;

    if (fd == -1)
    {
        fprintf(stderr, "[%ld]: failed to open named pipe %s for write: %s\n",
                (long)getpid(), fifoname, strerror(errno));
        return 1;
    }

    rval = snprintf(buf, BUF_SIZE, "[%ld]: %s\n", (long)getpid(), idstring);

    if (rval < 0)
    {
        fprintf(stderr, "[%ld]: failed to make the string: %s\n",
                (long)getpid(), strerror(errno));
        return 1;
    }

    strsize = strlen(buf) + 1;

    fprintf(stderr, "[%ld]: about to write...\n", (long)getpid());

    rval = r_write(fd, buf, strsize);

    if (rval != strsize)
    {
        fprintf(stderr, "[%ld]: failed to write to pipe: %s\n",
                (long)getpid(), strerror(errno));
        return 1;
    }

    fprintf(stderr, "[%ld]: write finished\n", (long)getpid());
    return 0;
}

// dofifoparent implementation
int dofifoparent(const char *fifoname)
{
    char buf[BUF_SIZE];
    int fd;
    int rval;

    fprintf(stderr, "[%ld]: (parent) about to open FIFO %s...\n",
            (long)getpid(), fifoname);

    while (((fd = open(fifoname, O_RDONLY)) == -1) && (errno == EINTR))
        ;

    if (fd == -1)
    {
        fprintf(stderr, "[%ld]: failed to open named pipe %s for read: %s\n",
                (long)getpid(), fifoname, strerror(errno));
        return 1;
    }

    fprintf(stderr, "[%ld]: about to read...\n", (long)getpid());

    rval = r_read(fd, buf, BUF_SIZE);

    if (rval == -1)
    {
        fprintf(stderr, "[%ld]: failed to read from pipe: %s\n",
                (long)getpid(), strerror(errno));
        return 1;
    }
    fprintf(stderr, "[%ld]: read %.*s\n", (long)getpid(), rval, buf);

    return 0;
}
