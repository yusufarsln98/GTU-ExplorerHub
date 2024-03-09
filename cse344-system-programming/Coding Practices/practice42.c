// #include "curr_time.h" /* Declaration of currTime() */
// #include "tlpi_hdr.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>
#include <stdarg.h>

#define GN_NONNEG 01 /* Value must be >= 0 */
#define GN_GT_0 02   /* Value must be > 0 */
#define BUF_SIZE 1000

void errExit(const char *format, ...) // function from tlpi_hdr.h
{
    va_list argList;
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);
    exit(EXIT_FAILURE);
}

void usageErr(const char *format, ...) // function from tlpi_hdr.h
{
    va_list argList;
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);
    exit(EXIT_FAILURE);
}

void fatal(const char *format, ...) // function from tlpi_hdr.h
{
    va_list argList;
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);
    exit(EXIT_FAILURE);
}

int getInt(const char *arg, int flags, const char *name) // function from tlpi_hdr.h
{
    long res;
    char *endptr;
    if (arg == NULL || *arg == '\0')
        fatal("null or empty string");
    errno = 0;
    res = strtol(arg, &endptr, 0);
    if (errno != 0)
        errExit("strtol");
    if (*endptr != '\0')
        fatal("nonnumeric characters");
    if ((flags & GN_NONNEG) && res < 0)
        fatal("negative value not allowed");
    if ((flags & GN_GT_0) && res <= 0)
        fatal("value must be > 0");
    return (int)res;
}

char *currTime(const char *format) // function from curr_time.h
{
    static char buf[BUF_SIZE]; /* Nonreentrant */
    time_t t;
    size_t s;
    struct tm *tm;
    t = time(NULL);
    tm = localtime(&t);
    if (tm == NULL)
        return NULL;
    s = strftime(buf, BUF_SIZE, (format != NULL) ? format : "%c", tm);
    return (s == 0) ? NULL : buf;
}

int main(int argc, char *argv[])
{
    int pfd[2]; /* Process synchronization pipe */
    int j, dummy;
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s sleep-time...\n", argv[0]);

    setbuf(stdout, NULL); /* Make stdout unbuffered, since we
                             terminate child with _exit() */
    printf("%s Parent started\n", currTime("%T"));

    if (pipe(pfd) == -1)
        errExit("pipe");
    for (j = 1; j < argc; j++)
    {
        switch (fork())
        {
        case -1:
            errExit("fork %d", j);
        case 0:                      /* Child */
            if (close(pfd[0]) == -1) /* Read end is unused */
                errExit("close");
            /* Child does some work, and lets parent know it's done */
            sleep(getInt(argv[j], GN_NONNEG, "sleep-time"));
            /* Simulate processing */
            printf("%s Child %d (PID=%ld) closing pipe\n",
                   currTime("%T"), j, (long)getpid());
            if (close(pfd[1]) == -1)
                errExit("close");
            /* Child now carries on to do other things... */
            _exit(EXIT_SUCCESS);
        default: /* Parent loops to create next child */
            break;
        }
    }
    /* Parent comes here; close write end of pipe so we can see EOF */
    if (close(pfd[1]) == -1) /* Write end is unused */
        errExit("close");
    /* Parent may do other work, then synchronizes with children */
    if (read(pfd[0], &dummy, 1) != 0)
        fatal("parent didn't get EOF");
    printf("%s Parent ready to go\n", currTime("%T"));
    /* Parent can now carry on to do other things... */
    exit(EXIT_SUCCESS);
}

/*
    16:14:36 Parent started
    16:14:38 Child 2 (PID=62036) closing pipe
    16:14:40 Child 1 (PID=62035) closing pipe
    16:14:41 Child 3 (PID=62037) closing pipe
    16:14:41 Parent ready to go

*/