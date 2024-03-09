// Using a pipe to connect ls and wc
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/*
    int pfds[2];

    pfds[0] is the read end of the pipe
    pfds[1] is the write end of the pipe
*/

void errExit(const char *call)
{
    perror(call);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int pfd[2];          /* Pipe file descriptors */
    if (pipe(pfd) == -1) /* Create pipe */
    {
        errExit("pipe");
    }
    switch (fork())
    {
    case -1:
        errExit("fork");
    case 0:                      /* First child: exec 'ls' to write to pipe */
        if (close(pfd[0]) == -1) /* Read end is unused */
        {
            errExit("close 1");
        }
        /* Duplicate stdout on write end of pipe; close duplicated descriptor */
        if (pfd[1] != STDOUT_FILENO)
        { /* Defensive check */
            if (dup2(pfd[1], STDOUT_FILENO) == -1)
            {
                errExit("dup2 1");
            }
            if (close(pfd[1]) == -1)
            {
                errExit("close 2");
            }
        }
        execlp("ls", "ls", (char *)NULL); /* Writes to pipe */

        errExit("execlp ls");

    default: /* Parent falls through to create next child */
        break;
    }

    switch (fork())
    {
    case -1:
    {
        errExit("fork");
    }
    case 0:                      /* Second child: exec 'wc' to read from pipe */
        if (close(pfd[1]) == -1) /* Write end is unused */
        {
            errExit("close 3");
        }
        /* Duplicate stdin on read end of pipe; close duplicated descriptor */
        if (pfd[0] != STDIN_FILENO)
        { /* Defensive check */
            if (dup2(pfd[0], STDIN_FILENO) == -1)
            {
                errExit("dup2 2");
            }
            if (close(pfd[0]) == -1)
            {
                errExit("close 4");
            }
        }
        execlp("wc", "wc", "-l", (char *)NULL); /* Reads from pipe */

        errExit("execlp wc");

    default: /* Parent falls through */
        break;
    }
    /* Parent closes unused file descriptors for pipe, and waits for children */
    if (close(pfd[0]) == -1)
    {
        errExit("close 5");
    }
    if (close(pfd[1]) == -1)
    {
        errExit("close 6");
    }
    if (wait(NULL) == -1)
    {
        errExit("wait 1");
    }
    if (wait(NULL) == -1)
    {
        errExit("wait 2");
    }
    exit(EXIT_SUCCESS);
}