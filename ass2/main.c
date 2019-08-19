    #include "main.h"

    char homepath[1024];


    char home_path[1024];


    int main()
    {
        get_path(home_path);

        while(1)
        {
            displayPrompt();
            char inp[1024];
            take_commands(inp);
            fflush(stdin);

            // if(strlen(inp) == 0){
            //     continue;
            // }

            
            // okay, now we have the command, now we will remove all the empty spaces
            char input[1024];
            int c = 0, d = 0;
    
            while (inp[c] != '\0' && inp[c] != '\n')
            {
                if (!(inp[c] == ' ' && inp[c+1] == ' '))   
                {
                    input[d] = inp[c];
                    d++;
                }
                c++;
            }
    
            input[d] = '\0';

            // printf("the command received is %s\n", input);

            // now we will use strtok to get all the commands:

            
            char * command = strtok(inp, ";");
            while(command != NULL)
            {
                char input[1024];
                int c = 0, d = 0;
    
                while (command[c] != '\0')
                {
                    if (!(command[c] == ' ' && command[c+1] == ' '))   
                    {
                        input[d] = command[c];
                        d++;
                    }
                    c++;
                }
                input[d] = '\0';
    
                // printf("command read is %s", input);
                char a[] = "exit\n";
                if(strcmp(input, a) == 0){
                    return 0;
                }

                command = strtok (NULL, "; ");
            }
        }
        return 0;
    }


    void displayPrompt()
    {
        char username[100];
        char sysname[100];

        char path[1024];
        get_path(path);

        // we will check what the path is
        if(strcmp(home_path, path) == 0)
        {
            char arr[] = "~";
            strcpy(path, arr);
        }
        else
        {
            // now we will give the relative path
            if(strlen(path) > strlen(home_path))
            {
                // now we construct the relative path
                char tilda[] = "~";
                char * rel;
                rel = strtok(path, home_path);
                strncat(tilda, rel, strlen(path) - strlen(home_path));
                strcpy(path, tilda);

            }
            else
            {
                char rev[1024];
                int len = strlen(path);
                for(int i = len; i>= 0 ; i--)
                {
                    rev[i] = path[len - 1 - i];
                }
                char * p = strtok(rev, "/");
                strcpy(path, p);
            }
        }

        getlogin_r(username, sizeof(username));
        gethostname(sysname, sizeof(sysname)); 

        printf("<%s @ %s: %s > ", username, sysname,path);

        return;
    }

    void take_commands(char inp[])
    {
        fgets(inp, 1024, stdin);
        return;
    }

    void get_path(char arr[])
    {
        getcwd(arr, 1024);
    }