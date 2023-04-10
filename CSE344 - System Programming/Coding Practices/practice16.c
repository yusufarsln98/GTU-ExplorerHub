#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
// int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
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

void sigint_handler(int sig)
{
    printf("Received SIGINT signal.\n");
}

int main()
{
    sigset_t mask;                       // create a signal set
    sigemptyset(&mask);                  // initialize the signal set
    sigaddset(&mask, SIGINT);            // add SIGINT to the signal set
    sigaddset(&mask, SIGTSTP);           // add SIGTSTP to the signal set
    sigprocmask(SIG_BLOCK, &mask, NULL); // block the signals in the signal set
    signal(SIGINT, sigint_handler);      // install the signal handler for SIGINT (see after critical_operation() is done)

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