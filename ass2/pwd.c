#include "main.h"

void pwd_function()
{
    // okay, so now I fork the process, and start my work with the new thread
    char paath[1024];
    //  means that it's the child process
    int i = (long int)getcwd(paath, 1024);
    if(!i)
    {
        perror("");
    }
    printf("%s\n", paath);
    exit(0);
}