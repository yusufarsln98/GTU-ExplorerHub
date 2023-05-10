// More precise system() implementation from the lecture
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>

// add mask to the signal set

int my_system(char *command)
{
    sigset_t block_mask, orig_mask;
    struct sigaction sa_ignore, sa_orig_quit, sa_orig_int, sa_default;
    pid_t child_pit;
    int status, saved_errno;

    if (command == NULL) // Is a shell available?
    {
        return my_system(":") == 0;
    }

    sigemptyset(&block_mask); // Block SIGCHLD
    sigaddset(&block_mask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &block_mask, &orig_mask);

    sa_ignore.sa_handler = SIG_IGN; // Ignore SIGINT and SIGQUIT
    sa_ignore.sa_flags = 0;
    sigemptyset(&sa_ignore.sa_mask);
    sigaction(SIGINT, &sa_ignore, &sa_orig_int);
    sigaction(SIGQUIT, &sa_ignore, &sa_orig_quit);

    switch (child_pit = fork())
    {
    case -1: // fork() failed
        status = -1;
        break;
    case 0:
        sa_default.sa_handler = SIG_DFL;
        sa_default.sa_flags = 0;
        sigemptyset(&sa_default.sa_mask);

        if (sa_orig_int.sa_handler != SIG_IGN)
        {
            sigaction(SIGINT, &sa_default, NULL);
        }

        if (sa_orig_quit.sa_handler != SIG_IGN)
        {
            sigaction(SIGQUIT, &sa_default, NULL);
        }

        sigprocmask(SIG_SETMASK, &orig_mask, NULL); // Restore signal mask
        execl("/bin/sh", "sh", "-c", command, (char *)NULL);
        _exit(127);
    default:
        while (waitpid(child_pit, &status, 0) == -1)
        {
            if (errno != EINTR)
            {
                status = -1;
                break;
            }
        }
        break;
    }

    // unblock SIGCHLD, restore dispositions of SIGINT and SIGQUIT

    saved_errno = errno; // the following may change 'errno'
    sigprocmask(SIG_SETMASK, &orig_mask, NULL);
    sigaction(SIGINT, &sa_orig_int, NULL);
    sigaction(SIGQUIT, &sa_orig_quit, NULL);
    errno = saved_errno;

    return status;
}

int main()
{
    /* Call the my_system() function with the command to execute */
    int result = my_system("ls");

    /* Print the exit status of the command */
    printf("Exit status: %d\n", result);

    return 0;
}