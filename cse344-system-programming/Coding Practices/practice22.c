// sigsuspend (WAITING FOR SIGNALS) example

/*
    #include <signal.h>
    int sigsuspend(const sigset_t *mask);
    // returns -1 with errno set to EINTR

    !! Main Idea !!
    block the process efficiently until a certain signal arrives and is handled.


    Atomically unblocks a signal and suspends the process.

    [Atomically: the process is blocked from receiving signals until
    the process is suspended. -Copilot]

    Equivalent to (atomic):
        // Assign new mask and get old mask
        sigprocmask(SIG_SETMASK, mask, &oldMask);

        pause();

        // Restore old mask
        sigprocmask(SIG_SETMASK, &oldMask, NULL);

    sigsuspend() does these 3 operations atomically.
        - block the process from receiving signals
        - suspend the process
        - restore the old mask automatically after an unmasked signal
          is received.

    Thanks to sigsuspend(),
        - we can avoid busy waiting
        - two processes can synchronize themselves where one process
          waits for a signal from the other process.
*/

// --- Issues Can Be Encountered ---
/*
    1- Handling Errors

    // take a backup of errno
    void my_handler(int sig)
    {
        int esaved = errno; // save errno
        // do something
        errno = esaved; // restore errno
    }
*/

/*
    2- System Calls Interrupted by a Signal

    while((cnt = read(fd, buf, BUF_SIZE)) == -1 && errno == EINTR)
        continue; // Do nothing loop body

    if (cnt == -1)
        perror("read")

    -- Create a macro to handle this issue --
    #define NO_EINTR(stmt) while ((stmt) == -1 && errno == EINTR);

    NO_EINTR(cnt = read(fd, buf, BUF_SIZE));
    if (cnt == -1)
        perror("read");
*/

/*
    3- Signal Handler Function Risks

    - Do not call any function that is not async-signal-safe
      from a signal handler function.
      (e.g. printf, malloc, free, etc.)

    - Do not use global variables in a signal handler function.

    What to do?
    Try to use as few instructions as possible in a signal handler function.
    Do not use C library functions.
    * Keep function short

    If you need to use a C library function do them in the main program

    pseduo code:

    signal_handler:
        sets a flag variable to indicate that a signal has been received

    main:
        loop:
            do lengthy work
            if (flag variable is set)
                do something (for example: exit)
        end loop

*/