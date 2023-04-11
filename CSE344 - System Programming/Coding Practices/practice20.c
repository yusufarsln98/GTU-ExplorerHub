// another example for sigaction usage

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    struct sigaction act;

    // find the current SIGINT handler
    if (sigaction(SIGINT, NULL, &act) == -1)
    {
        perror("Failed to get old SIGINT handler");
    }
    else if (act.sa_handler == SIG_DFL)
    {
        printf("SIGINT handler is default\n");

        // If you comment the line below,
        // sa_handler will remain SIG_DFL and not
        // print the "SIGINT handler is ignore" message
        act.sa_handler = SIG_IGN;
    }

    if (act.sa_handler == SIG_IGN)
    {
        printf("SIGINT handler is ignore\n");
    }
}