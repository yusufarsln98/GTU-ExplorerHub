/*
    Daemons

    A daemon is a process With the following characteristics:
    * It is long-lived. Often, a daemon is created at system
    startup and runs until the system is shut down.

    * It runs in the background and has no controlling
    terminal. The lack of a controlling terminal ensures that
    the kernel never automatically generates any job-control or
    terminal-related signals (such as SIGINT, SIGTSTP, and SIGHUP) for a daemon.

    * It is a convention (not universally observed) that
    daemons have names ending with the letter `d`.

*/

/*
    To become a daemon, a program performs the following steps:
    * Perform a fork(), after which the parent exits and the child continues
    (the shell returns to its prompt)

    * The child process calls setsidO to start a new session and free itself of
    any association with a controlling terminal
    (otherwise Closing the terminal will kill the daemon)

    * If the daemon might later open a terminal device,
    then we must take steps to ensure that the device does not become
    the controlling terminal.

    * Clear the process umask to ensure that, when the daemon creates files and
    directories, they have the requested permissions.

    * Change the process’s current working directory, typically to the root directory

    * Close all open file descriptors that the daemon has inherited from its parent

    * After having closed file descriptors O, 1, and 2, a daemon normally
    opens /dev/null and uses dup2() (or similar) to make all those descriptors
    refer to this device; this way neither the daemon nor its children write to
    the terminal when running + detach from tty

    session ID —> process group ID —» process ID

*/

// become_daemon.h
#ifndef BECOME_DAEMON_H /* Prevent double inclusion */
#define BECOME_DAEMON_H

/* Bit-mask values for 'flags' argument of becomeDaemon() */
#define BD_NO_CHDIR 01          /* Don't chdir("/") */
#define BD_NO_CLOSE_FILES 02    /* Don't close all open files */
#define BD_NO_REOPEN_STD_FDS 04 /* Don't reopen stdin, stdout, and stderr to \
                                 * /dev/null */
#define BD_NO_UMASK0 010        /* Don't do a umask(0) */
#define BD_MAX_CLOSE 8192       /* Maximum file descriptors to close if \
                                 * sysconf(_sc_0PEN_MAX) is indeterminate */
int becomeDaemon(int flaqs);
#endif

// becomeDaemon.c
#include <sys/stat.h>
#include <fcntl.h>
#include "become_daemon.h"
#include "tlpi_hdr.h"

int becomeDaemon(int flags) /* Returns 0 on success, -1 on error */
{
    int maxfd, fd;
    switch (fork())
    { /* Become background process */
    case -1:
        return -1;
    case 0:
        break; /* Child falls through; adopted by init */
    default:
        _exit(EXIT_SUCCESS); /* parent terminates and shell prompt is back*/
    }

    if (setsid() == -1) /* Become leader of new session, dissociate from tty */
        return -1;      /* can still acquire a controlling terminal */

    switch (fork())
    { /* Ensure we are not session leader */
    case -1:
        return -1; /* thanks to 2nd fork, there is no way of acquiring a tty */
    case 0:
        break;
    default:
        _exit(EXIT_SUCCESS);
    }
    if (!(flags & BD_NO_UMASK0))
    {
        umask(0); /* Clear file mode creation mask */
    }

    if (!(flags & BD_NO_CHDIR))
    {
        chdir("/"); /* Change to root directory */
    }

    if (!(flags & BD_NO_CLOSE_FILES))
    { /* Close all open files */
        maxfd = sysconf(_SC_OPEN_MAX);
        if (maxfd == -1) /* Limit is indeterminate... */
        {
            maxfd = BD_MAX_CLOSE; /* so take a guess */
        }
        for (fd = 0; fd < maxfd; fd++)
        {
            close(fd);
        }
    }

    if (!(flags & BD_NO_REOPEN_STD_FDS))
    {
        close(STDIN_FILENO); /* Reopen standard fd's to /dev/null */
        fd = open("/dev/null", O_RDWR);
        if (fd != STDIN_FILENO) /* 'fd' should be 0 */
        {
            return -1;
        }
        if (dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO)
        {
            return -1;
        }
        if (dup2(STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO)
        {
            return -1;
        }
    }
    return 0;
}
