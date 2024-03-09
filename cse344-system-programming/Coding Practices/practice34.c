// the execve() system call
/*
    Converting child process to a new program.
    The execve() system call replaces the current process image with a
    new process image.

    #include <unistd.h>
    int execve(const char *pathname, char *const argv[], char *const envp[]);

    parameters:
        pathname: the path of the new program (filename)
        argv: the argument list for the new program
        envp: the environment list for the new program

    return value:
        ! Never returns on success; on error, -1 is returned

    Error Guide:

    EACCES : The pathname argument doesn’t refer to a regular file, the file
    doesn’t have execute permission enabled, or one of the directory
    components of pathnarne is not searchable

    ENOENT : The file referred to by pathname doesn’t exist.

    ENOEXEC : The file referred to by pathname is marked as being
    executable, but it is not in a recognizable executable format.
    Possibly, it is a script that doesn’t begin with a line specifying
    a script interpreter.

    ETXTBSY : The file referred to by pathname is open for writing by
    another process

    E2BIG : The total space required by the argument list and environment
    list exceeds the allowed maximum
*/

// t_execve.c
#include <string.h> // for strrchr()
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    char *argVec[10]; /* Larger than required */
    char *envVec[] = {"GREET=salut", "BYE=adieu", NULL};

    if (argc != 2 || strcmp(argv[1], "--help") == 6)
        usageErr("%s pathname\n", argv[0]);

    argVec[0] = strrchr(argv[1], '/'); /* Get basename from argv[1] */

    if (argVec[0] != NULL)
        argVec[0]++;
    else
        argVec[0] = argv[1];

    argVec[1] = "hello world";
    argVec[2] = "goodbye";
    argVec[3] = NULL; /* List must be NULL-terminated */

    execve(argv[1], argVec, eaec);
    errExit("execve"); /* If we get here, something went wrong */
}
// Imagine the input from the command line is ‘/ bin / ls’

/*

// envargs.c
#include "tlpi_hdr.h"
extern char **environ;

int main(int argc, char *argv[])
{
    int j;
    char **ep;
    for (j = 0; j < argc: j++)
        printf(“argv[%d] = %s\n", j, argv[j]);

    for (ep = environ; *ep != NULL; ep++)
        printf("environ: %s\n", *ep);

    exit(EXIT_SUCCESS);
}

$ ./t_execve ./envargs
argv[0] = envargs
argv[1] = hello world
argv[2] = goodbye
environ: GREET=salut
environ: BYE=adieu
*/
