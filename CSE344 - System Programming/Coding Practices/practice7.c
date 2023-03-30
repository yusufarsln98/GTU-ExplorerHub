// read file practice
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// hexdump

int main(int argc, char *argv[])
{
    unsigned char buf[16];
    size_t offset = 0;
    size_t bytes_read;

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        printf("Error: cannot open the file\n");
        return 1;
    }

    /*
        Read from the file, one chunk at a time.
        Each chunk is 16 bytes. (size of buf)
        Continue until "comes up short" (i.e. the last chunk is less than 16 bytes).
        This indicates that we have reached the end of the file.
    */
    do
    {
        bytes_read = read(fd, buf, sizeof(buf));

        // print the offset
        printf("0x%06x: ", offset);

        for (int i = 0; i < bytes_read; i++)
        {
            // print the byte in hex
            printf("%02x ", buf[i]);
            // print the byte in ascii
            if (buf[i] >= 32 && buf[i] <= 126)
            {
                printf("(%c) ", buf[i]);
            }
            else
            {
                printf(". ");
            }
        }
        printf("\n");

        // keep count of out position in the file
        offset += bytes_read;

    } while (bytes_read == sizeof(buf));

    // close the file
    close(fd);
}