#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int sig)
{
    printf("Received SIGINT signal.\n");
    if (signal(SIGINT, SIG_DFL) == SIG_ERR)
    {
        printf("Error setting signal handler for SIGINT.\n");
        exit(1);
    }
}

int main()
{
    // Install the signal handler for SIGINT
    signal(SIGINT, sigint_handler);

    printf("Press Ctrl+C to send a SIGINT signal.\n");

    // Loop forever
    while (1)
    {
        // Do some work
    }
    return 0;
}