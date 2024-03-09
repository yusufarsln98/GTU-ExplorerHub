/*
    1st Step:
        - Start the simulator
        - Handle SIGINT and SIGTERM:
            If SIGINT or SIGTERM is received, clear the child, recieve the next command and continue.
            If SIGKILL is received, clear the child, close the simulator and exit.
        - Fork a child process
            From child process, create a new process, and execute the command taken from parent.
        - Inside the parent process, create a loop to take a shell command from user.
            Send the command to child process, save the log file with the name of timestamp.
                Log file should contain: pid, command

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_COMMAND_ARGS 20

#define TRUE 1
#define FALSE 0

static int SIG_IGNORED = FALSE; /* flag to prevent parent be able to ignore
                                   SIGINT and SIGTERM signals */
void errExit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void signal_handler(int signum)
{
    switch (signum)
    {
    case SIGINT:
        printf("SIGINT received (child process terminated)\n");
        exit(0);
        break;
    case SIGTERM:
        printf("SIGTERM received (child process terminated)\n");
        exit(0);
        break;
    default:
        break;
    }
}

void signal_ignore(int signum)
{
    switch (signum)
    {
    case SIGINT:
        printf("SIGINT ignored (from parent process)\n");
        SIG_IGNORED = TRUE;
        break;
    case SIGTERM:
        printf("SIGTERM ignored (from parent process)\n");
        SIG_IGNORED = TRUE;
        break;
    default:
        break;
    }
}

int main(int argc, char const *argv[])
{
    pid_t pid;
    char command[MAX_COMMAND_LENGTH]; // for each command, e.g. ls -l
    char *args[MAX_COMMAND_ARGS];     // for each argument, e.g. ls, -l

    while (1)
    {
        // Ignore SIGINT and SIGTERM signals for parent process
        struct sigaction sa;
        sa.sa_handler = signal_ignore;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction(SIGINT, &sa, NULL);
        sigaction(SIGTERM, &sa, NULL);

        // clear command
        memset(command, 0, MAX_COMMAND_LENGTH);

        // Ask command from user
        printf("$ ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);
        command[strlen(command) - 1] = '\0';

        // if command is :q, exit
        if (strcmp(command, ":q") == 0)
        {
            printf("Exiting...\n");
            exit(0);
        }

        if (!SIG_IGNORED)
        {
            int i = 0;
            args[i] = strtok(command, " ");
            while (args[i] != NULL)
            {
                i++;
                args[i] = strtok(NULL, " ");
            }
            // Fork
            switch (pid = fork())
            {
            case -1:
                errExit("fork");
                break;
            case 0:
                // handle SIGINT and SIGTERM signals

                sa.sa_handler = signal_handler;
                sigemptyset(&sa.sa_mask);
                sa.sa_flags = 0;
                sigaction(SIGINT, &sa, NULL);
                sigaction(SIGTERM, &sa, NULL);

                // Child process
                // Create a new process and execute the command
                execvp(args[0], args);
                errExit("execvp");
                break;
            default:
                // Parent process

                wait(NULL);
                // print the log file with the name of timestamp
                // Log file should contain: pid, command
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                char log_file_name[100];
                sprintf(log_file_name, "%d-%d-%d_%d:%d:%d.log",
                        tm.tm_year + 1900,
                        tm.tm_mon + 1,
                        tm.tm_mday,
                        tm.tm_hour,
                        tm.tm_min,
                        tm.tm_sec);
                FILE *log_file = fopen(log_file_name, "w");
                fprintf(log_file, "pid: %d\n", pid);

                fprintf(log_file, "command: ");
                int i = 0;
                while (args[i] != NULL)
                {
                    fprintf(log_file, "%s ", args[i]);
                    i++;
                }

                fclose(log_file);

                break;
            }
        }
        else
        {
            SIG_IGNORED = FALSE;
        }
    }

    return 0;
}
