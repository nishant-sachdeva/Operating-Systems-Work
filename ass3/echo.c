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
            command[strlen(command)-1] = '\0';
            // this is to remove the last line out of the input string
            char * tokenn =  strtok(command, " ");
            while(tokenn  != NULL)
            {
                tokenn =  strtok(NULL, " ");
                if(tokenn)
                    printf("%s ",tokenn);
            }
            printf("\b");
            printf("\n");
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
    }
    
    return;
}