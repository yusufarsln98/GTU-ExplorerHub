// different memory allocation practices
// (malloc, calloc, realloc, brk, sbrk, alloca)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    // malloc (allocates memory on the heap)
    char *p = malloc(100);
    strcpy(p, "hello");
    printf("%s\n", p);

    // calloc (allocates memory on the heap)
    // calloc() initializes the allocated memory to 0
    char *q = calloc(100, sizeof(char));
    strcpy(q, "world");
    printf("%s\n", q);

    // realloc (reallocates memory on the heap)
    q = realloc(q, 200);
    strcpy(q, "hello world");
    printf("%s\n", q);

    // sbrk (allocates memory on the heap)
    char *s = sbrk(100);
    strcpy(s, "hello");
    printf("%s\n", s);

    // alloca (allocates memory on the stack)
    // we must not call free() to deallocate memory allocated with alloca()
    char *t = alloca(100);
    strcpy(t, "world");
    printf("%s\n", t);

    // free
    free(p);
    free(q);

    return 0;
}
