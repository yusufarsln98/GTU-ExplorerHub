#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// First signals will be handled by the signal handlers
// after that, the default signal handlers will be called

void sigint_handler(int sig)
{
    printf("Received SIGINT signal.\n");
    if (signal(SIGINT, SIG_DFL) == SIG_ERR)
    {
        printf("Error setting signal handler for SIGINT.\n");
        exit(1);
    }
}

void sigterm_handler(int sig)
{
    printf("Received SIGTERM signal.\n");
    if (signal(SIGTERM, SIG_DFL) == SIG_ERR)
    {
        printf("Error setting signal handler for SIGTERM.\n");
        exit(1);
    }
}

void sigkill_handler(int sig)
{
    // Handling SIGKILL is not possible, so this function will never be called
    printf("Received SIGKILL signal.\n");
    if (signal(SIGKILL, SIG_DFL) == SIG_ERR)
    {
        printf("Error setting signal handler for SIGKILL.\n");
        exit(1);
    }
}

int main()
{
    // Install the signal handlers
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigterm_handler);
    signal(SIGKILL, sigkill_handler); // SIGKILL cannot be caught or ignored

    printf("Press Ctrl+C to send a SIGINT signal.\n");
    printf("To kill this process by SIGTERM, use the following command: kill -SIGTERM %d\n", getpid());
    printf("To kill this process by SIGKILL, use the following command: kill -9 %d\n", getpid());

    // Loop forever
    while (1)
    {
        // Do some work
    }

    return 0;
}