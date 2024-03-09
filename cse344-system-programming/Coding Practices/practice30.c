// Process Termination From Signal Handler

/*
    * Avoid high number of statements in signal handler

    * Avoid calling functions that are not async-signal-safe
        - printf, malloc, free, etc.

    * Avoid using global variables

    ! If the child needs to inform parent that it terminated because of a
    signal, then the child's signal handler should first disestablish
    itself, and then raise the same signal once more. The signal handler would
    contain code such as following:

    void handler(int sig)
    {
        // Perform cleanup steps
        // e.g. close file descriptors, remove temporary files, etc.

        sigaction(. . .); // Disestablish signal handler
        raise(. . .); // Raise the signal again.
    }

    steps:
        1. Catch the signal in the child process
        2. Use sigaction() to disestablish the signal handler
        3. Use raise() to raise the signal again

*/
