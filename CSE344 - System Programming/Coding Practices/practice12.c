// redirection

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

// dup2 - duplicate a file descriptor
/*
    int dup2(int oldfd, int newfd);

    - dup2() makes a duplicate of the file descriptor (fd) `oldfd`
    using the descriptor number `newfd`.
    ** If the file descriptor `newfd` was already open, it closes it first.

    example:
    dup2(1, 2) --> 2 > &1
    first closes stderr (2), then replaces it with a copy of stdout (1)


    !-- Or, we can use fcntl to do the same thing:

    newfd = fcntl(oldfd, F_DUPFD, startfd);
    - F_DUPFD - duplicate the file descriptor
    - startfd - the lowest-numbered file descriptor to use (lowest unused file descriptor)
*/

/*
    Bourne-style shell redirection

    $ ./myscript > results.log 2>&1
    i.e. redirect stdout to results.log, and redirect stderr to
    whereever stdout points to (which is results.log)
    So, both stdout and stderr are redirected to results.log

    $ ./myscript 2>&1 | less
    Both stdout and stderr of 'myscript' become stdin (input) of 'less'

*/

int main(int argc, char *argv[])
{
    int fd;
    char *file = argv[1];

    // open the file
    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // redirect stdout to the file
    dup2(fd, 1);

    // redirect stderr to the file
    dup2(fd, 2);

    // close the file
    close(fd);

    // print some output
    printf("This is stdout, redirected to %s\n", file);
}