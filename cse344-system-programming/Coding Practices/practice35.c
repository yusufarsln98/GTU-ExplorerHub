// Example of fork+exec from lecture

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int spawn(char *program, char **arg_list)
{
    pid_t child_pid;

    // duplicate this process
    child_pid = fork();

    if (child_pid != 0)
    {
        // this is the parent process
        return child_pid;
    }
    else
    {
        // now execute PROGRAM, searching for it in the path
        execvp(program, arg_list);
        // the execvp function returns only if an error occurs
        fprintf(stderr, "an error occurred in execvp\n");
        abort(); // terminate the program
    }
}

int main(int argc, char const *argv[])
{
    // the argument list to pass to the "ls" command
    char *arg_list[] = {
        "ls", // argv[0], the name of the program
        "-l",
        "/",
        NULL // the argument list must end with a NULL
    };

    // spawn a child process running the "ls" command. Ignore the returned
    // child process ID

    spawn("ls", arg_list);
    printf("done with main program\n");

    return 0;
}
