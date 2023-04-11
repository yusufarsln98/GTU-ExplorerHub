// pending signals
/*
    The set of pending signals is only a mask; indicates
    whether or not a signal has occured, but not how many
    times it has occured.
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// int sigpending (sigset_t *set); // returns 0 on success, -1 on error

// handle sigint
void sigint_handler(int signum)
{
    printf("SIGINT is handled\n");
}

// handle sigtstp
void sigtstp_handler(int signum)
{
    printf("SIGTSTP is handled\n");
}

int main()
{
    // block SIGINT and print pending signals
    sigset_t set, pending_set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTSTP);
    sigprocmask(SIG_BLOCK, &set, NULL);

    // register signal handlers
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);

    printf("Press any key to continue...\n");
    getchar();
    sigpending(&pending_set);

    // if user sends SIGINT, it will be pending
    if (sigismember(&pending_set, SIGINT))
        printf("SIGINT is pending\n");
    else
        printf("SIGINT is not pending\n");

    // if user sends SIGTSTP, it will be pending
    if (sigismember(&pending_set, SIGTSTP))
        printf("SIGTSTP is pending\n");
    else
        printf("SIGTSTP is not pending\n");

    // unblock SIGINT
    sigprocmask(SIG_UNBLOCK, &set, NULL);
    printf("handle pending signals...\n");
    sleep(2);

    // get pending signals
    sigpending(&pending_set);

    // check after unblocking SIGINT and SIGTSTP if they are pending
    if (sigismember(&pending_set, SIGINT))
        printf("SIGINT is pending\n");
    else
        printf("SIGINT is not pending\n");

    if (sigismember(&pending_set, SIGTSTP))
        printf("SIGTSTP is pending\n");
    else
        printf("SIGTSTP is not pending\n");

    return 0;
}