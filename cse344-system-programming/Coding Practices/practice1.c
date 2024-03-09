#include <stdio.h>

// takes arguments from the command line and prints them out
int main(int argc, char *argv[])
{
    // int i;
    // for (i = 0; i < argc; i++) {
    //     printf("argv[%d] = %s\n", i, argv[i]);
    // }

    // alternative way to print out the arguments
    char **p;
    for (p = argv; *p != NULL; p++)
    {
        printf("%s\n", *p);
    }
}