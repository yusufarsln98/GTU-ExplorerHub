/*
    Orphans and Zombies
    - Orphans: A child process that has no parent process
    - Zombies: A child process that has terminated but has not been waited for
               by its parent process

    * A child process becomes an orphan when its parent process terminates
        before the child process terminates.

    * A child process becomes a zombie when its parent process terminates
        before the child process terminates and the child process has not
        been waited for by its parent process.

    The parent of an orphaned process becomes the init process (PID 1).

*/

// Waiting for a Child Process
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();
    if (pid > 0)
    {
        printf("Process ID: %d\n", getpid());
        wait(NULL);
        exit(0);
    }
    else if (pid == 0)
    {
        printf("Child Process ID: %d\n", getpid());
        printf("Parent of Child Process ID: %d\n", getppid());
        exit(0);
    }
    else
    {
        perror("fork");
        exit(1);
    }
    return 0;
}

/*
    output:
    Process ID: 25551
    Child Process ID: 25552
    Parent of Child Process ID: 25551
*/

/*
    // Orphaned Process

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/wait.h>

    int main()
    {
        pid_t pid;

        pid = fork();
        if (pid > 0)
        {
            printf("Process ID: %d\n", getpid());
            exit(0);
        }
        else if (pid == 0)
        {
            sleep(3);
            printf("Child Process ID: %d\n", getpid());
            printf("Parent of Child Process ID: %d\n", getppid());
            exit(0);
        }
        else
        {
            perror("fork");
            exit(1);
        }
        return 0;
    }

    output:
    Process ID: 25647
    (3 saniye bekledikten sonra)
    Child Process ID: 25648
    Parent of Child Process ID: 1670
*/

/*
// Zombie Process
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();
    if (pid > 0)
    {
        printf("Process ID: %d\n", getpid());
        sleep(3);
        wait(NULL);
        printf("Child process terminated\n");
        exit(0);
    }
    else if (pid == 0)
    {
        printf("Child Process ID: %d\n", getpid());
        printf("Parent of Child Process ID: %d\n", getppid());
        printf("Child becomes zombie from now on\n");
        exit(0);
    }
    else
    {
        perror("fork");
        exit(1);
    }
    return 0;
}

output:
    Process ID: 26830
    Child Process ID: 26831
    Parent of Child Process ID: 26830
    Child becomes zombie from now on
    Child process terminated

*/