// Executing a Shell Command: system()

/*
    #include <stdlib.h>
    int system(const char *command);

    ! Do not use this function.
    Why?
    - It creates two processes, first creates a shell process, then
    the shell process creates a child process to execute the command.

    advantages:
    - It is simple to use.
    - Helps to use shell features

    disadvantages:
    - It is inefficient (two processes are created)
    - It is not secure (if shell has a security hole, then the program
                        using system() is also vulnerable)

*/

// example from lecture
#include <sys/wait.h>
#include "print_wait_status.h"
#include "tlpi_hdr.h"
#define MAX_CMD_LEN 200

int main(int argc, char const *argv[])
{
    char str[MAX_CMD_LEN]; // Command to be executed by system()
    int status;            // Status returned by system()

    for (;;)
    {
        printf("Command: ");
        fflush(stdout);
        if (fgets(str, MAX_CMD_LEN, stdin) == NULL)
        {
            // End of file
            break;
        }

        status = system(str);
        printf("system() returned: status=0x%04x (%d,%d)\n",
               (unsigned int)status, status >> 8, status & 0xff);

        if (status == -1)
        {
            errExit("system");
        }
        else
        {
            // WIFEXITED() and WEXITSTATUS() are macros that used
            // to extract the exit status of the child process
            if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
            {
                printf("(Probably) could not invoke shell\n");
            }
            else
            {
                printWaitStatus(NULL, status);
            }
        }
    }
    exit(EXIT_SUCCESS);
}

/*
    $ ./t_system
    Command: whoami
    yusuf
    system() returned: status=0x0000 (0,0)
    child exited, status=0
    Command: ls | grep XYZ                     `Shell terminates with the status of...
    system() returned: status=0x0100 (1,0)      its last command (grep), which...
    child exited, status=1                      found no match, and so did an. exit(1)`
    Command: exit 127
    system() returned: status=0x7f00 (127,0)
    (Probably) could not invoke shell           `Actually, not true in this case`
    Command: sleep 100
    `Type Control-Z to suspen.dforeground process group`
    [1]+ Stopped        ./t_system
    $ ps | grep sleep                           `Find PID of sleep`
    29361 pts/6 00:00:00 sleep
    $ kill 29361                                `And send a. signal to terminate it
    $ fg                                         Bring t_system back intoforeground`
    ./t_system
    system() returned: status=0x000f (0,15)
    child killed by signal 15 (Terminated)
    Command: ^D$                                `Type Control-D to send EOF to t_system`


*/
