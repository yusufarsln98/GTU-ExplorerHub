// signal handler for SININT to mysighand

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void mysighand(int signum)
{
    printf("I got signal %d\n", signum);
}

// This is how to set a signal handling should be for a signal with sigaction()
int main()
{
    struct sigaction newact;
    newact.sa_handler = &mysighand; // set the handler
    newact.sa_flags = 0;            // no special flags

    // No special options
    if ((sigemptyset(&newact.sa_mask) == -1) ||
        (sigaction(SIGINT, &newact, NULL) == -1))
    {
        perror("Failed to set SIGINT handler");
    }

    while (1)
    {
        printf("Hello World!\n");
        sleep(1);
    }
}