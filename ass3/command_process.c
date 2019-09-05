#include "main.h"

void do_work(char inp[], char home_path[])
{
	// printf("do work mein aa gya\n");
	add_to_history(inp, home_path);

	char *secondary;
	char *command = strtok_r(inp, ";", &secondary);

	while (command != NULL)
	{
		// command has been read
		char *secondary_2, *copy_of_command;
		copy_of_command = (char *)malloc((1000)*sizeof(char));
		strcpy(copy_of_command, command);
		// created a copy of command because aageh jaake this is gonna be lost in strtok

		char *parts = strtok_r(command, " ", &secondary_2);
		int arg = 0, background_required = 0;

		char * argv[100];
		while (parts != NULL)
		{

			// now, the entire string is one command, 
			// identify if it is valid, if yes, do the needful, else, exit with some error message and go on to the next

			if(strcmp(parts, "exit") == 0 || strcmp(parts,"exit\n")== 0)
			{
				exit(0);
			}
			// exit if command is exit
			if(strcmp(parts, "&") == 0 || strcmp(parts, "&\n") == 0)
			{
				background_required = 1;
			}
			// mark background as 1 if required

			if(strcmp(parts, "\n") !=0 && background_required == 0 )
			{
				argv[arg]=(char *)malloc((100)*sizeof(char));
				if(parts[strlen(parts)-1] =='\n')
					parts[strlen(parts)-1] = '\0';
				strcpy(argv[arg], parts);
				arg++;
			}

			parts = strtok_r(NULL, " ", &secondary_2);
		}
		argv[arg]=(char *)malloc((100)*sizeof(char));
		argv[arg]  = NULL;

		// so here is the deal, the data 2d array already has the command input, and now for every commmand we are busy trying to get it into one big 2d array, and honestly, I don't think we are doing a very great job !
		pid_t pid;
		int status;
		pid = fork();
		if(pid < 0)
		{
			printf("forking failed\n");
		}
		// yhaan fork  ho gya hai, right, now we will execute all the commands;

		if(pid == 0)
		{
			if(argv[0] != NULL) // cuz null seh comparison gives us a seg fault
			{
				if(!strcmp(argv[0] , "ls") || !strcmp(argv[0], "ls\n"))
				{
					ls_function(argv, arg, home_path);				
				}
				else if(!strcmp(argv[0] , "pwd") || !strcmp(argv[0], "pwd\n"))
				{
					pwd_function(background_required, home_path);
				}


				else if(!strcmp(argv[0] ,"pinfo") || !strcmp(argv[0],"pinfo\n"))
				{
					pinfo_function(argv, arg);				
				}
				else if(!strcmp(argv[0] ,"history")||!strcmp(argv[0], "history\n"))
				{
					history_function(argv, home_path , arg);
				}
				else if(!strcmp(argv[0] , "echo") || !strcmp(argv[0], "echo\n"))
				{
					echo_function(copy_of_command, background_required);
				}
                else if(!strcmp(argv[0] , "cd") || !strcmp(argv[0], "cd\n"))
			    {
				    // cd_function(argv, arg, home_path);			
                    exit(0);
                }
				else
				{
					// we are in the extra command section now
					if( execvp(*argv, argv) < 0)
					{
						printf("Error : %s  failed!\n", argv[0]);
					}
				}

			}

			exit(0);
		}
		else
		{
            if(!strcmp(argv[0] , "cd") || !strcmp(argv[0], "cd\n"))
			{
				cd_function(argv, arg, home_path);			
            }
            // cd command is not supposed to be executed in a forked process, hence this exception


			if(background_required == 0)
				(void)waitpid(pid, &status, 0);
			if(background_required == 1)
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
		// now go to the next command
		// this step will take us to the next command 
		command = strtok_r(NULL, ";", &secondary);
	}
	return ;
}
