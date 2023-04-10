// Create a process and kill it by using kill() system call.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int status;

    // kill(getpid(), SIGKILL); // kills itself

    // parent process created first, then child process
    // after 5 second delay, parent process being killed
    // so the child process never gets a chance to terminate

    pid = fork();
    if (pid == 0)
    {
        printf("Child process is created. PID: %d\n", getpid());
        sleep(10);
        printf("Child process is terminated.\n");
    }
    else if (pid > 0)
    {
        printf("Parent process is created. PID: %d\n", getpid());
        sleep(5);
        kill(pid, SIGKILL);
        wait(&status);
        printf("Parent process is terminated.\n");
        // print pid
    }
    else
    {
        perror("fork");
        exit(1);
    }

    return 0;
}
