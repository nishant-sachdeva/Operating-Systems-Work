#include "main.h"


void echo_function(char *command  , int background)
{
    int id = fork();
    int status;
    if(id == 0)
    {

        char * first_part = strdup(command);
        char * token = strsep(&first_part, "\"");

        if(first_part == NULL)
        {
            // means no semi colon do simple strtok printing
            char * tokenn =  strtok(command, " ");
            while(tokenn  != NULL)
            {
                tokenn =  strtok(NULL, " ");
                if(tokenn)
                    printf("%s ",tokenn);
            }
            printf("\b");
        }
        else
        {
            // printf("%s %s\n", first_part, token);
            // means that semi colon hain
            char * lin = strdup(first_part);
            char * tokenn = strsep(&lin, "\"");
            printf("%s\n", tokenn);            
        }
        
        exit(0);
    }
    else
    {
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
    
    return;
}