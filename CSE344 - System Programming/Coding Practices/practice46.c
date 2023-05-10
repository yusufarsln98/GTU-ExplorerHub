/*
    popen and pclose functions:
    #include <stdio.h>

    FILE *popen(const char* command, const char* mode); // returns file stream
                                                        // or NULL on error

    int pclose(FILE *stream);                           // Returns termination
                                                        // status of child process
                                                        // or -1 on error
    since popen creates a shell and executes it, it is risky to use it
    as system() function
*/

#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    FILE *stream = popen("sort", "w");
    fprintf(stream, "This is a test.\n");
    fprintf(stream, "Hello, world.\n");
    fprintf(stream, "My dog has fleas.\n");
    fprintf(stream, "This program is great.\n");
    fprintf(stream, "One fish, two fish.\n");
    return pclose(stream);
}
