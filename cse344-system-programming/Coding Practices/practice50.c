/*
    Shared Memory

    - Shared memory is a memory that can be shared between processes.
    - It is the fastest form of IPC.

    shm_open() creates and opens a new shared memory object or opens an existing
    object.

    #inlucde <fctnl.h>      // Define O_* constants
    #include <sys/stat.h>   // Define mode constants
    #include <sys/mman.h>

    int shm_open(const char *name, int oflag, mode_t mode);
        // returns a file descriptor on success, or -1 on error

    When a new shared memory object is created, it initially has zero
    length. This means that, after creating a new shared memory object, we
    normally call ftruncate() to set the size of the object before calling
    mmap(). Following the mmap() call, we may also use ftruncate () to
    expand or shrink the shared memory object as desired.



    Remove a Shared Memory

    - removing shared memory will not effect existing mappings of the object
    (which will remain in effect until the corresponding process call munmap() or terminate)

    #include <sys/man.h>

    int shm_unlink(const char *name);

    --- Overall ---

    • Shared Memory provides fast IPC, and applications typically must
    use a semaphore (or other synchronization primitive) to synchronize
    access to the shared region.
    • Once the shared memory region has been mapped into the process's
    virtual address space, it looks just like any other part of the
    process's memory space.
    • The system places the shared memory regions within the process
    virtual address space.
    • Assuming that we don't attempt to map a shared memory region at
    a fixed address, we should ensure that all references to locations in
    the region are calculated as offsets (rather than pointers), since the
    region may be located at different virtual addresses within different
    processes.

    !! Do not use pointers inside the shared memory.


*/

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "tlpi_hdr.h"

static void usageError(const char *progName)
{
    fprintf(stderr, "Usage: %s [-cx] name size [octal-perms]\n", progName);
    fprintf(stderr, " -c Create shared memory (O_CREAT)\n");
    fprintf(stderr, "-x Create exclusively (O_EXCL)\n");
    exit(EXIT_FAILURE);
}
int main(int argc, char *argv[])
{
    int flags, opt, fd;
    mode_t perms;
    size_t size;
    void *addr;

    flags = O_RDWR;
    while ((opt = getopt(argc, argv, "cx")) != -1)
    {
        switch (opt)
        {
        case 'c':
            flags |= O_CREAT;
            break;
        case 'x':
            flags |= O_EXCL;
            break;
        default:
            usageError(argv[0]);
        }
    }
    if (optind + 1 >= argc)
        usageError(argv[0]);
    size = getLong(argv[optind + 1], GN_ANY_BASE, "size");
    perms = (argc <= optind + 2) ? (S_IRUSR | S_IWUSR) : getLong(argv[optind + 2], GN_BASE_8, "octal-perms");
    /* Create shared memory object and set its size */
    fd = shm_open(argv[optind], flags, perms);
    if (fd == -1)
        errExit("shm_open");
    if (ftruncate(fd, size) == -1)
        errExit("ftruncate");
    /* Map shared memory object */
    addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
        errExit("mmap");
    exit(EXIT_SUCCESS);
}
