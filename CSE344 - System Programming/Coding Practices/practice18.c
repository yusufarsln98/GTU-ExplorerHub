//  --- --- SIGNAL HANDLING --- ---
// sigaction() (DO NOT USE signal() system call)

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

// int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
// signum: signal number
// act: new action for signal signum (the action to take)
// oldact: old action for signal signum (recieves the previous action towards signum)

/*
!
    Don't use signal().
    signal() does not guarantee blocking a signal during the
    handler's execution, etc.

    Instead, use sigaction()
!
*/

/*
    struct sigaction
    {
        // SIG_DFL (default action), SIG_IGN (ignore),
        // or a pointer to a function
        void (*sa_handler)(int);

        // additional signals to be blocked during execution of handler
        sigset_t sa_mask;

        // special flags and options
        int sa_flags;

        // obsolete, do not use
        void (*sa_restorer)(void);
    }

*/
sig_atomic_t sigusr1_count = 0;

// it has only one parameter, which is the signal number
void handler(int signal_number)
{
    ++sigusr1_count;
}

// counter for interrupt signal
sig_atomic_t int_count = 0;

void int_handler(int signal_number)
{
    ++int_count;

    if (int_count == 3)
    {
        printf("interrupted 3 times, exiting...\n");
        exit(0);
    }
}

int main()
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &handler;
    // SIGUSR1 -> user defined signal 1
    // to send SIGUSR1 to a process, use kill(pid, SIGUSR1)
    sigaction(SIGUSR1, &sa, NULL);

    // interrupt signal
    struct sigaction sa_int;
    memset(&sa_int, 0, sizeof(sa_int));
    sa_int.sa_handler = &int_handler;
    sigaction(SIGINT, &sa_int, NULL);

    // do some lengthy stuff here
    while (1)
    {
        printf("sigusr1_count = %d\n", sigusr1_count);
        kill(getpid(), SIGUSR1);
        printf("int_count = %d\n", int_count);
        sleep(1);
    }

    return 0;
}