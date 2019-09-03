#include "main.h"


void cd_function(char ** argv, int arg, char home_path[])
{
    char *paath, *path;
    if(arg == 1)
    {
        path = home_path;
        path[strlen(path)+1] = '\0';
    }
    else
    {
        if(argv[1][0] == '~')
        {
            paath = malloc(1024*sizeof(char));
            strcpy(paath, home_path);
            strcpy(paath + strlen(paath), argv[1]+1);
            paath[strlen(paath)+1] = '\0';
            argv[1] = paath;
            path = argv[1];
        }
        else
        {
            path = argv[1];
            path[strlen(path) + 1] = '\0';
        }
    }

    if(chdir(path) != 0)
        perror("");
    char arr[1024];
     get_path(arr);

    return;
}