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
        do_work(inp);
	}
	return 0;
}

void do_work(char inp[])
{

	char *secondary;
	char *command = strtok_r(inp, ";", &secondary);

	while (command != NULL)
	{
		char *secondary_2, *copy_of_command;
		copy_of_command = (char *)malloc((1000)*sizeof(char));
		strcpy(copy_of_command, command);
		
		char *parts = strtok_r(command, " ", &secondary_2);
		int arg = 0, background_required = 0;
		// printf("this is a new command coming \n");
		char data[100][10];
		while (parts != NULL)
		{
            // now, the entire string is one command, 
            // identify if it is valid, if yes, do the needful, else, exit with some error message and go on to the next

            char arr[] = "exit\n";

            if(strcmp(parts, "exit") == 0 || strcmp(parts,"exit\n")== 0)
            {
                exit(0);
            }
			if(strcmp(parts, "&") == 0 || strcmp(parts, "&\n") == 0)
			{
				background_required = 1;
			}
			if(strcmp(parts, "\n")!=0)
				{strcpy(data[arg],  parts);
				arg++;}

			parts = strtok_r(NULL, " ", &secondary_2);
		}

		if(!strcmp(data[0] , "ls") || !strcmp(data[0], "ls\n"))
		{
			// continue;
		}
		else if(!strcmp(data[0] , "pwd") || !strcmp(data[0], "pwd\n"))
		{
			pwd_function(background_required);
		}
		else if(!strcmp(data[0] , "cd") || !strcmp(data[0], "cd\n"))
		{
			// continue;
		}
		else if(!strcmp(data[0] , "pinfo") || !strcmp(data[0], "pinfo\n"))
		{
			// continue;
		}
		else if(!strcmp(data[0] , "history") || !strcmp(data[0], "history\n"))
		{
			// continue;
		}
		else if(!strcmp(data[0] , "echo") || !strcmp(data[0], "echo\n"))
		{
			echo_function(copy_of_command, background_required); // that's the entire command that we got, so that whatever spaces are there, they can be accounted there and then
		}
		else
		{
			// printf("here for execvp\n");
			char *argv[100];
			for(int i = 0 ; i<arg ; i++)
			{
				argv[i]=(char *)malloc((100)*sizeof(char));
				if(data[i][strlen(data[i])-1] =='\n')
					data[i][strlen(data[i])-1] = '\0';
				strcpy(argv[i], data[i]);
				// printf("hi\n");
			}
			argv[arg]=(char *)malloc((100)*sizeof(char));
			argv[arg]  = NULL;
			// printf("copy ho gya\n");
			// I mean I still have a command right?
			/* below code is for executing this weird command*/
			pid_t pid;
			int status;
			if((pid = fork()) < 0)
			{
				printf("forking failed\n");
			}
			else if(pid == 0)
			{
				if( execvp(*argv, argv) < 0)
				{
					printf("Error : %s  failed!\n", data[0]);
					exit(1);
				}
			}
			else
			{
				while(wait(&status) != pid);
			}
		}

		// now go to the next command
		command = strtok_r(NULL, ";", &secondary);
	}
    return ;
}

void displayPrompt()
{
	char username[100];
	char sysname[100];

	char path[1024];
	get_path(path);

	fill_path(path);

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


void fill_path(char path[])
{
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
		// else
		// {
		// 	char rev[1024];
		// 	int len = strlen(path);
		// 	for(int i = len; i>= 0 ; i--)
		// 	{
		// 		rev[i] = path[len - 1 - i];
		// 	}
		// 	char * p = strtok(rev, "/");
		// 	strcpy(path, p);
		// }
	}
	return ;
}