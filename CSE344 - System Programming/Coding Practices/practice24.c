/*
    #include <stdio.h>

    pid_t fork(void);

    returns:
        -1: error
        0: child process
        >0: parent process

    ! using fork() with the aim of creating multiple processes is expensive.
    because of this, it is better to use threads instead of processes.

    -- fork() returns different values within the parent and child processes.
    * the parent process returns the process id of the child process if successful.
    * the child process returns 0 if successful.


    The child process is an exact copy of the parent process,
    except for its process ID.
    It copies, data, heap, stack, and, global/static variables... everything.

    ! Which process runs first?
    There is no guarantee that the parent process will run first or the
    child process will run first.
    So, do not code your program depending on which process
    runs first.

    --- Terminating a process ---
    * exit() function from stdlib.h

    void exit(int status);

    status:
        0: successful
        < 0: failure
        > 0: their meaning is application specific.

*/

// example of fork() usage
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t child_pid;

    printf("the main program process ID is %d\n", (int)getpid());

    child_pid = fork();
    if (child_pid != 0)
    {
        printf("this is the parent process, with id %d\n", (int)getpid());
        printf("the child's process ID is %d\n", (int)child_pid);
    }
    else
    {
        printf("this is the child process, with id %d\n", (int)getpid());
    }
    return 0;
}
