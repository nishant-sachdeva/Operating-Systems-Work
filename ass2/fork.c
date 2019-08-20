#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main()
{

    if(fork() == 0)
    {
        printf("hi\n");
    }
    else
    {
        printf("hiiii\n");
    }

    return 0;
}