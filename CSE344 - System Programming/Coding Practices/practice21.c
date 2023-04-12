// waiting for signals...
// ! Important !
/*
    Busy waiting is a method of waiting for a signal to occur.

    Using busy waiting is easy, however,
    CPU usage will be 100%.
    When this happens, other processes will not be able to run.

    ! Do not use busy waiting !

    -- from slides --
    busy waiting: testing continuously (within a loop) whether
    a certain event occurred by using CPU cycles.

    The alternative is to suspend the process until a signal arrives
    notifying it that the event occurred (hence the CPU is free).

    POSIX system calls for suspending process until a signal occurs:
    - sleep (NO) x
    - nanosleep (NO) x
    - pause (NO) x
    - sigsuspend (YES) v

*/

/*
    sleep() and nanosleep() (BAD PRACTICE)

    Returns 0 on normal completion, or number of unslept seconds if
    prematurely terminated.

    #include <unistd.h>
    --> unsigned int sleep(unsigned int seconds);

    nanosleep is a more powerful version of sleep that operates at higher
    resolution.
*/

/*
    pause() (BAD PRACTICE)

    Suspends the process until a signal is received. (or an unhandled signal terminates the process)

    Always returns -1 and sets errno to EINTR.

    #include <unistd.h>
    --> int pause(void);

    for (;;)        // infinite loop
        pause();    // wait for a signal
*/

// Why pause() is insufficient?

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int sig)
{
    printf("Ouch!\n");
}

int main()
{
    sigset_t prevMask, intMask;
    struct sigaction sa; // action to be taken when a signal is received

    // add SIGINT to the mask set
    sigemptyset(&intMask);
    sigaddset(&intMask, SIGINT);

    // Handle SIGINT (action)
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = &handler;

    // sig num, action, old action
    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    /* Block SIGINT prior to execut ing critical section. (At this
        point we assume that SIGINT is not already blocked.) */
    if (sigprocmask(SIG_BLOCK, &intMask, &prevMask) == -1)
    {
        perror("sigprocmask - SIG_BLOCK");
        exit(EXIT_FAILURE);
    }

    /* Critical section : do some work here that must not be
       interrupted by the SIGINT handler */
    printf("Critical section time starts now...\n");
    sleep(3);
    printf("Critical section time ends now...\n");

    /* End of critical section - restore old mask to unblock SIGINT */
    if (sigprocmask(SIG_SETMASK, &prevMask, NULL) == -1)
    {
        perror("sigprocmask - SIG_SETMASK");
        exit(EXIT_FAILURE);
    }

    /* BUG:
       what if SIGINT arrives now... (BURADA GELIRSE SICTIK) */

    pause(); // Wait for SIGINT
}