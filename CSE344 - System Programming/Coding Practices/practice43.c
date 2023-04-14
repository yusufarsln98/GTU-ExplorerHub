/*
    Simulate IO redirection
    > ./a.out < input.txt > output.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 10
#define MAX_CMD_LENGTH 100

int main()
{
    char cmd[MAX_CMD_LENGTH];
    char *args[MAX_ARGS];
    char *input_file, *output_file;
    int i, pid, status, input_fd, output_fd;

    while (1)
    {
        // Prompt for command
        printf("$ ");
        fgets(cmd, MAX_CMD_LENGTH, stdin);
        cmd[strcspn(cmd, "\n")] = '\0'; // Remove newline character

        // Parse command into arguments
        i = 0;
        args[i] = strtok(cmd, " ");
        while (args[i] != NULL && i < MAX_ARGS - 1)
        {
            i++;
            args[i] = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Check for input and output redirections
        input_file = NULL;
        output_file = NULL;
        i = 0;
        while (args[i] != NULL)
        {
            if (strcmp(args[i], "<") == 0)
            {
                input_file = args[i + 1];
                args[i] = NULL;
            }
            else if (strcmp(args[i], ">") == 0)
            {
                output_file = args[i + 1];
                args[i] = NULL;
            }
            i++;
        }

        // Open input file if specified
        if (input_file != NULL)
        {
            input_fd = open(input_file, O_RDONLY);
            if (input_fd == -1)
            {
                perror("open");
                continue;
            }
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }

        // Open output file if specified
        if (output_file != NULL)
        {
            output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (output_fd == -1)
            {
                perror("open");
                continue;
            }
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        // Execute command
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            continue;
        }
        else if (pid == 0)
        {
            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        else
        {
            waitpid(pid, &status, 0);
        }

        // Reset input and output streams
        dup2(STDIN_FILENO, 0);
        dup2(STDOUT_FILENO, 1);
    }

    return 0;
}
