/*
    Semaphores
    2 type of semaphores exist
        1- Named Semaphores
        2- Unnamed Semaphores


    1- Named Semaphores

    #inlcude <fcntl.h>      // Define o_* constants
    #include <sys/stat.h>   // Define mode constants
    #include <semaphore.h>

    sem_t *sem_open(const char* name, int oflag, ...
                    /* mode_t mode, unsigned int value * / );
        returns pointer to semphore on success, or SEM_FAILED on error and errno is set

    #define SEM_FAILED ((semt_t*)0)

    notes
    -----

    - never copy a semaphore
    - when a child is created via fork(), it inherits references to *all the
    named semaphores* that are open in its parent.



    #include <semaphore.h>
    int sem_close(sem_t *sem)
        returns 0 on success, or -1 on error

    ** closing a semaphore does not delete it.
    To delete it from the system, we should use sem_unlink().


    #include <semaphore.h>
    int sem_unlink(const char* name)
        returns 0 on success, or -1 on error


    // Methods of WAITING a semaphore

    #define _XOPEN_SOURCE 600
    #include <semaphore.h>

    int sem_wait(sem_t *sem);
    int sem_trywait(sem_t *sem);

    int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
        // !!! not available on all UNIX implementations !!!


    sem_wait() and sem_trywait() decrease sem by one
    sem_wait() returns 0 if sem already 1, however if it was 0, it waits to return
    until unblock.
    sem_trywait() otherwise, returns immediately (returns the EAGAIN error in liue of blocking)



    // POSTING a semaphore

    #include <semaphore.h>
    int sem_post(sem_t *sem);
        // increments the value of the semaphore by one

    int sem_getvalue(sem_t *sem, int *sval);
        // returns the current value of the semaphore in sval




    2- Unnamed Semaphores

    #include <semaphores.h>
    int sem_init(const *sem, int pshared, unisgend int value);

    int sem_destroy(sem_t *sem);

*/

#include <semaphore.h>
#include <pthread.h>
#include "tlpi_hdr.h"
static int glob = 0;
static sem_t sem;
static void *threadFunc(void *arg) /* Loop 'arg' times incrementing 'glob' */
{
    int loops = *((int *)arg);
    int loc, j;
    for (j = 0; j < loops; j++)
    {
        if (sem_wait(&sem) == -1)
            errExit("sem_wait");
        loc = glob;
        loc++;
        glob = loc;
        if (sem_post(&sem) == -1)
            errExit("sem_post");
    }
    return NULL;
}
{
    pthread_t t1, t2;
    int loops, s;
    loops = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-loops") : 10000000;

    /* Initialize a thread-shared mutex with the value 1 */
    if (sem_init(&sem, 0, 1) == -1)
        errExit("sem_init");
    /* Create two threads that increment 'glob' */
    s = pthread_create(&t1, NULL, threadFunc, &loops);
    if (s != 0)
        errExitEN(s, "pthread_create");
    s = pthread_create(&t2, NULL, threadFunc, &loops);
    if (s != 0)
        errExitEN(s, "pthread_create");
    /* Wait for threads to terminate */
    s = pthread_join(t1, NULL);
    if (s != 0)
        errExitEN(s, "pthread_join");
    s = pthread_join(t2, NULL);
    if (s != 0)
        errExitEN(s, "pthread_join");
    printf("glob = %d\n", glob);
    exit(EXIT_SUCCESS);
}