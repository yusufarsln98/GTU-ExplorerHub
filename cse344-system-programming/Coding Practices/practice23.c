// How to create a process

// system() (not a system call)

/*
    #include <stdlib.h>
    --> int system(const char *command);

    1- runs the shell
    2- executes the command

    so, it creates 2 processes.
    Therefore, it is not efficient.

    It is not secure beacuse,
    since it uses the shell,
    it is as secure as the shell.
*/

// !! Unsafe !!
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int return_value;

    return_value = system("ls");

    return return_value;
}

// What to use instead
/*
    Creating process by system calls has 2 steps:
    1- fork()
    2- exec()

    `fork`: that creates a child process that is an exact copy of its parent process.

    `exec`: causees a particular process to cease (terminate) being an instance
    of one program to installed become instance of a program

*/
