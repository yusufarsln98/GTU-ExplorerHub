// files practice with timestap
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char *get_timestamp()
{
    time_t now = time(NULL);
    return asctime(localtime(&now));
}

int main(int argc, char *argv[])
{
    // the file for appending
    char *path = argv[1];

    char *s = get_timestamp();

    // print the timestamp to the console
    printf("%s", s);

    // open the file for appending
    // 0666 permission for all users
    int fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0666);

    size_t length = strlen(s);

    // write the timestamp to the file
    write(fd, s, length);

    // close the file
    close(fd);

    // open the file for reading
    fd = open(path, O_RDONLY);

    // read the file
    char buf[1000];
    read(fd, buf, 1000);

    // print the file to the console
    printf("Reading the file: \n");
    printf("%s", buf);
    printf("\n");

    // try to write to the file
    if (write(fd, "hello", 5) == -1)
    {
        // since the file is opened for reading only, this will fail
        printf("Error: cannot write to the file\n");
    }
    // close the file
    close(fd);

    return 0;
}

// to compile: gcc practice6.c -o p6
// to run: ./p6 test.txt