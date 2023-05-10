#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
// int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
/*
    how: SIG_BLOCK, SIG_UNBLOCK, SIG_SETMASK
    set: the signal set to be added, removed, or set
    oldset: the previous signal mask
*/
#include <unistd.h>

void critical_operation()
{
    printf("Performing critical operation... ('enter' to continue)\n");
    // Do some work
    while (1)
    {
        if (getchar() == '\n')
        {
            break;
        }
    }
    printf("Critical operation complete.\n");
}
/*
    Signal for segmentation violation (SIGSEGV) cannot be masked or handled.
    Also, SIGSTOP and SIGKILL cannot be blocked or handled.
*/

/*
    Functions related to signal masks:
    int sigemptyset(sigset_t *set); // initialize the signal set
    int sigfillset(sigset_t *set); // add all signals to the signal set
    int sigaddset(sigset_t *set, int signum); // add a signal to the signal set
    int sigdelset(sigset_t *set, int signum); // remove a signal from the signal set
    int sigismember(const sigset_t *set, int signum); // check if a signal is in the signal set
    int sigprocmask(int how, const sigset_t *set, sigset_t *oldset); // change the signal mask
*/

int main()
{
    sigset_t mask;                       // create a signal set
    sigemptyset(&mask);                  // initialize the signal set
    sigaddset(&mask, SIGINT);            // add SIGINT to the signal set
    sigaddset(&mask, SIGTSTP);           // add SIGTSTP to the signal set
    sigprocmask(SIG_BLOCK, &mask, NULL); // block the signals in the signal set
    // Pressing Ctrl+C will not interrupt the program
    printf("Press Ctrl+C to interrupt the program...\n");

    // Pressing Ctrl+Z will not interrupt the program
    printf("Press Ctrl+Z to send a SIGTSTP signal...\n");

    // to SIGKILL the program, use the following command: kill -9 <pid> from another terminal
    printf("To kill this process by SIGKILL, use the following command: kill -9 %d\n", getpid());

    // Perform a critical operation that must not be interrupted
    critical_operation();
    // Unblock the SIGINT signal
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    printf("Program complete.\n");

    return 0;
}