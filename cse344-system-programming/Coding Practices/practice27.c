// Creating Process with exec() System Call
/*
    In many applications, parent process wants to know how the child process
    terminated.

    There are two techniques to monitor the child process:
        1- wait() system call
        2- SIGCHLD signal

    #include <sys/wait.h>
    pid_t wait(int *status); // returns the process ID of the child process, -1 on error

    * wait() system call suspends the execution of the parent process until
    the child process terminates.
    it returns the termination status of the child process in buffer pointed by
    `status`.
*/

// example

// Example from: A Linux and UNIX® System Programming Handbook - Michael Kerrisk

#include <sys/wait.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int numDead;    /* Number of children so far waited for */
    pid_t childPid; /* PID of waited for child */
    int j;
    time_t t;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        printf("%s sleep-time...\n", argv[0]);

    setbuf(stdout, NULL); /* Disable buffering of stdout */
    /*
        CHATGPT
        The code setbuf(stdout, NULL); disables buffering of the
        standard output stream (stdout) in C.

        By default, the stdout stream is line-buffered, which means that
        the output is stored in a buffer until a newline character is
        encountered, at which point the buffer is flushed and the output
        is written to the screen. This behavior is intended to improve
        performance by reducing the number of write operations to the screen.

        However, in some cases, it may be necessary to disable buffering
        of the stdout stream.
        For example, if you are writing a program that generates a lot of
        output, you may want to disable buffering to ensure that the output
        is written to the screen immediately, rather than being held in a
        buffer until a newline character is encountered.

        Disabling buffering can be done using the setbuf() function in C,
        as shown in the code. The second argument of NULL specifies that
        no buffer should be used for stdout. When buffering is disabled,
        each call to printf() or other output function results in an immediate
        write to the screen.

        It's important to note that disabling buffering can decrease
        performance, especially if your program generates a lot of output.
        Therefore, it's generally a good idea to use buffering unless there
        is a specific reason not to.
    */
    // get current time
    t = time(NULL);
    for (j = 1; j < argc; j++)
    { /* Create one child for each argument */
        switch (fork())
        {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
        case 0: /* Child sleeps for a while then exits */
            printf("%s child %d started with PID %ld, sleeping %s seconds\n",
                   ctime(&t), j, (long)getpid(), argv[j]);
            sleep(atoi(argv[j]));
            _exit(EXIT_SUCCESS); // _exit() is used to terminate the child
                                 // process without calling any of the
                                 // functions registered with atexit() or
                                 // on_exit()

        default: /* Parent just continues around loop */
            break;
        }
    }
    numDead = 0;
    for (;;)
    { /* Parent waits for each child to exit */
        childPid = wait(NULL);
        if (childPid == -1)
        {
            if (errno == ECHILD)
            {
                printf("No more children - bye!\n");
                exit(EXIT_SUCCESS);
            }
            else
            { /* Some other (unexpected) error */
                perror("wait");
                exit(EXIT_FAILURE);
            }
        }
        numDead++;
        // get current time
        t = time(NULL);
        printf("%s wait() returned child PID %ld (numDead=%d)\n",
               ctime(&t), (long)childPid, numDead);
    }
}

/*
    $ ./multi 7 1 4
    [13:41:00] child 1 started with PID 21835, sleeping 7 seconds
    [13:41:00] child 2 started with PID 21836, sleeping 1 seconds
    [13:41:00] child 3 started with PID 21837, sleeping 4 seconds
    [13:41:01] wait() returned child PID 21836 (numDead=1)
    [13:41:04] wait() returned child PID 21837 (numDead=2)
    [13:41:07] wait() returned child PID 21835 (numDead=3)
    No more children- bye!
*/