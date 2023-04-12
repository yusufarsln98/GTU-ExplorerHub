// child gets offset from the parent example

/*
    ! new file descriptors will not be inherited by the child
    process, however, file operations (read, write, offset, etc.)
    will be inherited by the child process.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t child_pid;
    FILE *fp = NULL;
    fp = fopen("test.txt", "w");

    child_pid = fork();
    if (child_pid != 0)
    {
        if (fp == NULL)
        {
            printf("error opening file\n");
            return 1;
        }
        fprintf(fp, "hi world from parent\n"); // only this will be written to the file
        // set offset to the beginning of the file
        fseek(fp, 3, SEEK_SET);
    }
    else
    {
        if (fp == NULL)
        {
            printf("error opening file\n");
            return 1;
        }
        fprintf(fp, "hello world from child\n");
    }
    return 0;
}

// output: hi hello world from child