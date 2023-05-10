// Implementing System() function

/*
    We need to use fork() to create a child that then does an execl() to
    to implement a command like:

    execl("/bin/sh", "sh", "-c", command, (char *)NULL);

    To collect the status of the child created by system(), we use a waitpid() call that
    specifies the child's process ID.
*/

// Code written with ChatGPT - Similar with the code covered in the lecture
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int my_system(char *command)
{
    pid_t pid;
    int status;

    if (command == NULL)
    {
        return -1;
    }

    pid = fork();

    if (pid == -1)
    {
        return -1;
    }

    if (pid == 0)
    { /* Child process */
        /* Execute the command using execl */
        execl("/bin/sh", "sh", "-c", command, (char *)NULL);

        _exit(127); // not supposed to reach here
    }
    else
    { /* Parent process */
        /* Wait for the child to terminate */
        if (waitpid(pid, &status, 0) == -1)
        {
            return -1;
        }
        /* Return the exit status of the child process */
        return status;
    }
}

int main()
{
    /* Call the my_system() function with the command to execute */
    int result = my_system("ls");

    /* Print the exit status of the command */
    printf("Exit status: %d\n", result);

    return 0;
}

/*
    This my_system() function takes a string argument that contains the
    command to be executed. It uses the fork() system call to create a new process,
    and then uses the execl() system call to replace the child process
    with the specified command.

    The parent process waits for the child process to terminate using
    the waitpid() system call, and then returns the exit status of the child
    process using the WEXITSTATUS() macro.

    Note that this implementation is a simplified version of the system()
    function and does not handle signals or other edge cases that the actual
    system() function would handle.
*/