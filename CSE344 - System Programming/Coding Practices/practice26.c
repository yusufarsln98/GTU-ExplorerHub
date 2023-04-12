// process termination
/*
   --- Terminating a process ---
    * exit() function from stdlib.h

    void exit(int status);

    status:
        0: successful
        < 0: failure
        > 0: their meaning is application specific.

    int atexit(void (*function)(void));

    whenever function is terminated, atexit() will be called.

    Abnormal Terminations:
    The process can be terminated by signals like:
    SIGSEGV, SIGBUS, SIGINT, SIGTERM and SIGABRT.

    SIGKILL ends a process immediately and cannot be blocked or handled by any
    program.
*/

// This example replaces the signal mask and then suspends execution.
#define _POSIX_SOURCE
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

void catcher(int signum)
{
    switch (signum)
    {
    case SIGUSR1:
        puts("catcher caught SIGUSR1");
        break;
    case SIGUSR2:
        puts("catcher caught SIGUSR2");
        break;
    default:
        printf("catcher caught unexpected signal %d\n", signum); // bad idea to call printf in handler
    }
}

int main()
{
    sigset_t sigset;
    struct sigaction sact;
    time_t t;

    if (fork() == 0)
    {
        sleep(3);
        puts("child is sending SIGUSR2 signal which should be blocked");
        kill(getppid(), SIGUSR2);
        sleep(3);
        puts("child is sending SIGUSR1 signal which should be caught");
        kill(getppid(), SIGUSR1);
        exit(0);
    }

    sigemptyset(&sact.sa_mask);
    sact.sa_flags = 0;
    sact.sa_handler = catcher;

    if (sigaction(SIGUSR1, &sact, NULL) != 0)
    {
        perror("1st sigaction() error");
    }

    if (sigaction(SIGUSR2, &sact, NULL) != 0)
    {
        perror("2nd sigaction() error");
    }

    sigfillset(&sigset);         // fills the set with all signals
    sigdelset(&sigset, SIGUSR1); // deletes SIGUSR1 from the set

    time(&t); // gets the current time
    printf("parent waiting for child to send SIGUSR1 at %s", ctime(&t));
    if (sigsuspend(&sigset) == -1) // blocks all except for SIGUSR1
    {
        perror("sigsuspend () returned -1 as expected");
    }
    time(&t);
    printf("sigsuspend is over at %s", ctime(&t));
}

/*
    Output:
    parent waiting for child to send SIGUSR1 at Wed Apr 12 13:20:08 2023
    child is sending SIGUSR2 signal which should be blocked
    child is sending SIGUSR1 signal which should be caught
    catcher caught SIGUSR1 [!! orders depends on the kernel]
    catcher caught SIGUSR2 [!! orders depends on the kernel]
    sigsuspend () returned -1 as expected: Interrupted system call
    sigsuspend is over at Wed Apr 12 13:20:14 2023

    steps:
        1. process is forked
        2. child sleeps for 3 seconds
        3. parents makes sigaction operations
        4. child sends SIGUSR2 signal which should be blocked
        5. sigsuspend suspends the SIGUSR2 signal
        6. child sleeps for 3 seconds
        7. child sends SIGUSR1 signal which should be caught
        8. sigsuspend is over
        9. catcher catches SIGUSR1 signal
        10. catcher catches SIGUSR2 signal
        11. sigsuspend returns -1 as expected since it is interrupted by SIGUSR1
        12. sigsuspend is over
*/