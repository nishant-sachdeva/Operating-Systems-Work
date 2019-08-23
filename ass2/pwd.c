#include "main.h"

void pwd_function(int background)
{
    int id = fork();
    int status;
    
    // okay process yhaan separate hain
    if(id == 0)
    {
        // maane child process hai
        char paath[1024];
        long int i = (long int)getcwd(paath, 1024);
        fill_path(paath);
        // here we will get path relative to our path
        if(!i)
        {
            perror("");
        }
        else
        {
            printf("%s\n" , paath);
        }
        exit(0);
    }
    else
    {
        // ab hum parent mein hain
        (void)waitpid(id, &status, 0);
        if(background == 1)
				{
					if(WIFEXITED(status))
					{
						printf("pid = %d exited, status = %d\n",pid, WEXITSTATUS(status));
					}
					else if(WIFCONTINUED(status))
					{
						printf("continued\n");
					}
					else if (WIFSIGNALED(status))
					{
						printf("pid = %d killed by %d\n", pid, WTERMSIG(status));
					}
					else if(WIFSTOPPED(status))
					{
						printf("pid = %d stopped by %d\n",pid, WTERMSIG(status));
					}
				}
    }

    return ;
}