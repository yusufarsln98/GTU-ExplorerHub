/*
    InterProcess Communication (IPC)
    * Pipes
    * FIFOs

    IPC refers to the mechanisms an operating system provides to allow the processes to
    manage shared data.

    IPC facilities are divided into three broad categories:

    1) Communication: exchanging data between processes
    2) Synchronization: synchronizing the actions of processes
    3) Signals: they have various uses; including communication &
    synchronization between processes.

    An overview of communication options:
    1) Shared memory permits processes to communicate by simply
    reading and writing to a shared memory page.
    2) Mapped memory is similar to shared memory, except that it is
    associated With a file in the filesystem.
    3) *Pipes* permit sequential communication from one process to a
    related process.
    4) *FIFOs* are similar to pipes, except that unrelated processes can
    communicate because the pipe is given a name in the filesystem.
    5) Sockets support communication between unrelated processes even
    on different computers.
        and more (message queues, etc)..

    IPC criteria:
    * Whether they restrict communication to related processes (processes
    With a common ancestor), to unrelated processes sharing the same
    filesystem, or to any computer connected to a network
    * Whether a communicating process is limited to only writing data or
    only reading data
    * The number of processes permitted to communicate
    * Whether the communicating processes are synchronized by the IPC;
    for example, a reading process halts until data is available to read
*/

/*
    Pipes
    Pipes are the oldest Unix IPC method.

    A pipe is a communication device that permits undirectional
    communication. Data written to the “write end” of the pipe is read back
    from the “read end.”
    Pipes are serial devices; the data is always read from the pipe in the
    same order it was written.
    Typically, a pipe is used to communicate between two threads in a
    single process or between parent and child processes.

    example:
    $ ls | wc -l

    - Output of 'ls' is written to the pipe, and 'wc' reads the data from the
    pipe.
    It means, output of 'ls' will be input for 'wc'.

    ------------------------------------------------------------

    The pipe() System Call

    #include <unistd.h>
    int pipe(int fd[2]); // returns 0 on success, -1 on error

    Programmer creates a array of size 2, and passes it to pipe() function.

    fd[1] is the file descriptor for the write end of the pipe.
    fd[0] is the file descriptor for the read end of the pipe.

    example:

    int pipe_fds[2];
    int read_fd;
    int write_fd;

    pipe(pipe_fds); // never forget to error control

    read_fd = pipe_fds[0];
    write_fd = pipe_fds[1];


    A process’s file descriptors cannot be passed to unrelated processes;
    however, When the process calls fork, file descriptors are copied to
    the new child process. Thus, pipes can connect only related processes.

    How does pipe() work?
    - In the parent process, fork() operation being called. Thus, we have two
    processes.
    Since the file descriptors are copied to the child process, both processes
    can access the same files.
    By closing the unused file descriptors, we created a pipe.
    After, the parent process writes to the pipe, and the child process reads from the pipe.


    example - steps in creating pipe to transfer data from a parent process to a child process:

    int pipe_fds[2];
    if (pipe(pipe_fds) == -1) // create the pipe
    {
        perror("pipe");
        exit(1);
    }

    switch (fork()) // create a child process
    {
        case -1:
            perror("fork");
            exit(1);
        case 0: // child process
            if (close(pipe_fds[1]) == -1) // close the write end of the pipe
            {
                perror("close");
                exit(1);
            }
            // Child now reads from pipe
            break;
        default: // parent process
            if (close(pipe_fds[0]) == -1) // close the read end of the pipe
            {
                perror("close");
                exit(1);
            }
            // Parent now writes to pipe
            break;
    }
*/

// example - Using a Pipe to Communicate with Child Process

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Write COUNT copies of MESSAGE to STREAM, pausing for 1 second
// between each.

void writer(const char *message, int count, FILE *stream)
{
    for (; count > 0; --count)
    {
        // write the message to the stream and set it off immediately
        fprintf(stream, "%s\n", message);
        fflush(stream); // flush the stream to make sure the message is sent
        // snooze for a second
        sleep(1);
    }
}

// Read random strings from the stream as long as possible.

void reader(FILE *stream)
{
    char buffer[1024];
    // Read until we hit the end of the stream. fgets()
    // reads until either a newline or the end-of-file.
    while (!feof(stream) &&
           !ferror(stream) &&
           fgets(buffer, sizeof(buffer), stream) != NULL)
    {
        fputs(buffer, stdout);
    }
}

int main(int argc, char const *argv[])
{
    int fds[2];
    pid_t pid;

    // create the pipe. file descriptors for the two ends of the pipe are
    // placed in fds.
    pipe(fds);

    // fork a child process
    pid = fork();

    if (pid == (pid_t)0)
    {
        FILE *stream;
        // This is the child process. Close our copy of the
        // write end of the file descriptor.
        close(fds[1]);
        // Convert the read file descriptor to a FILE object,
        // and read from it using the standard I/O functions.
        stream = fdopen(fds[0], "r");
        reader(stream);
        close(fds[0]);
    }
    else
    {
        // This is the parent process.
        FILE *stream;
        // Close our copy of the read end of the file descriptor.
        close(fds[0]);
        // Convert the write file descriptor to a FILE object,
        // and write to it using the standard I/O functions.
        stream = fdopen(fds[1], "w");
        writer("Hello, world!", 5, stream);
        close(fds[1]);
    }
    return 0;
}

/*
    output:
    Hello, world! (after 1 second)
    Hello, world! (after 1 second)
    Hello, world! (after 1 second)
    Hello, world! (after 1 second)
    Hello, world! (after 1 second)
*/