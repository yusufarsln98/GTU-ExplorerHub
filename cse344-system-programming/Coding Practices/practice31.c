/*
    The waitid() System Call

    #include <sys/wait.h>
    int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);

    Like waitpid(), waitid() returns the status of a child process. However,
    waitid() provides extra functionality that is not available in waitpid().

    parameters:
        idtype:     Specifies the type of the id parameter
        id:         Specifies the child process whose status is to be returned
        infop:      Pointer to a siginfo_t structure that will be filled with
                    information about the child process
        options:    Specifies the options that affect the behavior of waitid()

    waitid() returns 0 on success, or -1 on error or WNOHANG was specified and
    no child process was found.
*/