// waitpid() system call
/*
    #include <sys/wait.h>
    pid_t waitpid(pid_t pid, int *status, int options);

    - parameters:
        - pid: the process ID of the child process
        - status: the termination status of the child process
        - options: the options to be used
    - returns:
        - the process ID of the child process
        - -1 on error

    * waitpid() system call suspends the execution of the parent process until
    the given child process terminates.

    !! By using wait(), we can only find out about children that have terminated.
    It is NOT possible to be notified when a child is stopped by a signal (e.g., SIGSTOP, SIGTTIN) or
    when a stopped child is resumed by a signal (e.g., SIGCONT).
*/