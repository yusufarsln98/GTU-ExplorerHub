// sonuc: 35 puan

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>

#define MAX_LINE_LENGTH 1024 /* maximum length of line, e.g. "ls -l -a | grep .c" */
#define MAX_COMMANDS 20      /* maximum number of commands, \
                                e.g. "ls -l -a | grep .c" has 2 commands, "ls -l -a" and "grep .c" */
#define MAX_COMMAND_ARGS 20  /* maximum number of arguments for a command ,e.g. ls, -l, -a */

#define TRUE 1
#define FALSE 0

static int SIG_IGNORED = FALSE; /* flag to prevent parent be able to ignore
                                   SIGINT and SIGTERM signals */

// Utility functions
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
        printf("\nSIGINT received (child process terminated)\n");
        exit(0);
        break;
    case SIGTERM:
        printf("\nSIGTERM received (child process terminated)\n");
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
        printf("\nSIGINT ignored (from parent process)\n");
        SIG_IGNORED = TRUE;
        break;
    case SIGTERM:
        printf("\nSIGTERM ignored (from parent process)\n");
        SIG_IGNORED = TRUE;
        break;
    default:
        break;
    }
}

int main(int argc, char const *argv[])
{
    struct sigaction sa;

    char line[MAX_LINE_LENGTH];                   // line = "ls -l -a | grep .c"
    char commands[MAX_COMMANDS][MAX_LINE_LENGTH]; // commands[0] = "ls -l -a", commands[1] = "grep .c"
    char *args[MAX_COMMAND_ARGS];                 // args[0] = "ls", args[1] = "-l", args[2] = "-a"

    int i, j, k, status, command_count, command_index, args_count;
    pid_t pid; // process id

    char *token;

    while (1)
    {
        // Ignore SIGINT and SIGTERM signals for parent process
        sa.sa_handler = signal_ignore;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction(SIGINT, &sa, NULL);
        sigaction(SIGTERM, &sa, NULL);

        // clear line
        memset(line, 0, MAX_LINE_LENGTH);
        // clear commands
        for (i = 0; i < MAX_COMMANDS; i++)
        {
            memset(commands[i], 0, MAX_LINE_LENGTH);
        }

        // Ask line from user
        printf("$ ");
        fgets(line, MAX_LINE_LENGTH, stdin);
        line[strlen(line) - 1] = '\0';

        command_index = 0;
        command_count = 0;

        // if line is :q, exit
        if (strcmp(line, ":q") == 0)
        {
            printf("Exiting...\n");
            exit(0);
        }
        if (!SIG_IGNORED)
        {
            // parse line to commands by `|` character for piped commands
            for (i = 0, command_count = 0; i < strlen(line); i++)
            {
                if (line[i] == ' ')
                {
                    // ignore leading spaces
                    continue;
                }
                else
                {
                    // copy command to commands array
                    for (j = i; j < strlen(line); j++)
                    {
                        if (line[j] == '|')
                        {
                            // copy command to commands array
                            strncpy(commands[command_count], &line[i], j - i);
                            commands[command_count][j - i] = '\0';
                            command_count++;
                            i = j;
                            break;
                        }
                        else if (j == strlen(line) - 1)
                        {
                            // copy command to commands array
                            strncpy(commands[command_count], &line[i], j - i + 1);
                            commands[command_count][j - i + 1] = '\0';
                            command_count++;
                            i = j;
                            break;
                        }
                    }
                }
            }

            if (command_count == 0)
            {
                continue;
            }
            // if there is only one command, execute it
            if (command_count == 1)
            {
                // parse command to args by ` ` character with strtok
                args_count = 0;
                token = strtok(commands[0], " ");
                while (token != NULL)
                {
                    args[args_count] = token;
                    args_count++;
                    token = strtok(NULL, " ");
                }

                // add NULL to args array
                args[args_count] = NULL;

                char redirect_STDIN[100] = "";
                char redirect_STDOUT[100] = "";

                // check if there is STDIN redirection
                for (i = 0; i < args_count; i++)
                {
                    if (strcmp(args[i], "<") == 0)
                    {
                        // copy file name to redirect_STDIN
                        strcpy(redirect_STDIN, args[i + 1]);
                        // remove < and file name from args
                        for (j = i; j < args_count - 2; j++)
                        {
                            args[j] = args[j + 2];
                        }
                        args_count -= 2;
                        args[args_count] = NULL;
                        break;
                    }
                }

                // check if there is STDOUT redirection
                for (i = 0; i < args_count; i++)
                {
                    if (strcmp(args[i], ">") == 0)
                    {
                        // copy file name to redirect_STDOUT
                        strcpy(redirect_STDOUT, args[i + 1]);
                        // remove > and file name from args
                        for (j = i; j < args_count - 2; j++)
                        {
                            args[j] = args[j + 2];
                        }
                        args_count -= 2;
                        args[args_count] = NULL;
                        break;
                    }
                }
                // add NULL to args array
                args[args_count] = NULL;

                // fork a child process
                pid = fork();
                if (pid == -1)
                {
                    errExit("fork");
                }
                else if (pid == 0)
                {
                    // child process

                    // Ignore SIGINT and SIGTERM signals for child process
                    sa.sa_handler = signal_handler;
                    sigemptyset(&sa.sa_mask);
                    sa.sa_flags = 0;
                    sigaction(SIGINT, &sa, NULL);
                    sigaction(SIGTERM, &sa, NULL);

                    // if there is STDIN redirection, redirect STDIN
                    if (strlen(redirect_STDIN) > 0)
                    {
                        int fd = open(redirect_STDIN, O_RDONLY);
                        if (fd == -1)
                        {
                            errExit("open");
                        }
                        if (dup2(fd, STDIN_FILENO) == -1)
                        {
                            errExit("dup2");
                        }
                        close(fd);
                    }

                    // if there is STDOUT redirection, redirect STDOUT
                    if (strlen(redirect_STDOUT) > 0)
                    {
                        int fd = open(redirect_STDOUT, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                        if (fd == -1)
                        {
                            errExit("open");
                        }
                        if (dup2(fd, STDOUT_FILENO) == -1)
                        {
                            errExit("dup2");
                        }
                        close(fd);
                    }

                    // execute command
                    execvp(args[0], args);
                    errExit("execvp");
                }
                else
                {
                    // parent process

                    // wait for child process to finish
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
                }
            }
            else
            {
                // if there are more than one command, then we need to create pipes
                int pipes_count = command_count - 1;
                int pipes[pipes_count][2];

                // create pipes
                for (i = 0; i < pipes_count; i++)
                {
                    if (pipe(pipes[i]) == -1)
                    {
                        errExit("pipe");
                    }
                }

                // fork child processes
                for (i = 0; i < command_count; i++)
                {
                    // get args for command
                    args_count = 0;
                    token = strtok(commands[i], " ");
                    while (token != NULL)
                    {
                        args[args_count] = token;
                        args_count++;
                        token = strtok(NULL, " ");
                    }

                    // add NULL to args array
                    args[args_count] = NULL;

                    // Get STDIN and STDOUT redirection
                    char redirect_STDIN[100] = "";
                    char redirect_STDOUT[100] = "";

                    // check if there is STDIN redirection
                    for (j = 0; j < args_count; j++)
                    {
                        if (strcmp(args[j], "<") == 0)
                        {
                            // copy file name to redirect_STDIN
                            strcpy(redirect_STDIN, args[j + 1]);
                            // remove < and file name from args
                            for (k = j; k < args_count - 2; k++)
                            {
                                args[k] = args[k + 2];
                            }
                            args_count -= 2;
                            args[args_count] = NULL;
                            break;
                        }
                    }

                    // check if there is STDOUT redirection
                    for (j = 0; j < args_count; j++)
                    {
                        if (strcmp(args[j], ">") == 0)
                        {
                            // copy file name to redirect_STDOUT
                            strcpy(redirect_STDOUT, args[j + 1]);
                            // remove > and file name from args
                            for (k = j; k < args_count - 2; k++)
                            {
                                args[k] = args[k + 2];
                            }
                            args_count -= 2;
                            args[args_count] = NULL;
                            break;
                        }
                    }
                    args[args_count] = NULL;

                    // fork a child process
                    pid = fork();
                    if (pid == -1)
                    {
                        errExit("fork");
                    }
                    else if (pid == 0)
                    {
                        if (i != 0)
                        {
                            // if REDIRECT_STDIN is not empty, then redirect STDIN
                            // otherwise, redirect the input of the previous command
                            if (strlen(redirect_STDIN) > 0)
                            {
                                int fd = open(redirect_STDIN, O_RDONLY);
                                if (fd == -1)
                                {
                                    errExit("open");
                                }
                                if (dup2(fd, STDIN_FILENO) == -1)
                                {
                                    errExit("dup2");
                                }
                                close(fd);
                            }
                            else
                            {
                                // redirect input to the previous command's output
                                if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
                                {
                                    errExit("dup2");
                                }
                                close(pipes[i - 1][0]);
                            }

                            // if REDIRECT_STDOUT is not empty, then redirect STDOUT
                            // otherwise, redirect the output to the next command
                            if (strlen(redirect_STDOUT) > 0)
                            {
                                int fd = open(redirect_STDOUT, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                                if (fd == -1)
                                {
                                    errExit("open");
                                }
                                if (dup2(fd, STDOUT_FILENO) == -1)
                                {
                                    errExit("dup2");
                                }
                                close(fd);
                            }
                        }

                        if (i != command_count - 1)
                        {
                            // if REDIRECT_STDOUT is not empty, then redirect STDOUT
                            // otherwise, redirect the output to the next command
                            if (strlen(redirect_STDOUT) > 0)
                            {
                                int fd = open(redirect_STDOUT, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                                if (fd == -1)
                                {
                                    errExit("open");
                                }
                                if (dup2(fd, STDOUT_FILENO) == -1)
                                {
                                    errExit("dup2");
                                }
                                close(fd);
                            }
                            else
                            {
                                // redirect output to the next command's input
                                if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
                                {
                                    errExit("dup2");
                                }
                                close(pipes[i][1]);
                            }

                            // if REDIRECT_STDIN is not empty, then redirect STDIN
                            // otherwise, redirect the input of the previous command
                            if (strlen(redirect_STDIN) > 0)
                            {
                                int fd = open(redirect_STDIN, O_RDONLY);
                                if (fd == -1)
                                {
                                    errExit("open");
                                }
                                if (dup2(fd, STDIN_FILENO) == -1)
                                {
                                    errExit("dup2");
                                }
                                close(fd);
                            }
                        }

                        // execute command
                        execvp(args[0], args);
                        errExit("execvp");
                    }
                    else
                    {
                        // parent process

                        // close unused pipes
                        if (i != 0)
                        {
                            close(pipes[i - 1][0]);
                        }
                        if (i != command_count - 1)
                        {
                            close(pipes[i][1]);
                        }

                        // wait for child process to finish
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
                    }
                }
            }
        }
        else
        {
            SIG_IGNORED = FALSE;
        }
    }

    return 0;
}
