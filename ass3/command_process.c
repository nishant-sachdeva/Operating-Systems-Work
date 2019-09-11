#include "main.h"


char * input, *output, *append;
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
		output = malloc(1024*sizeof(char));
		input = malloc(1024*sizeof(char));
		append = malloc(1024*sizeof(char));
		
		int input_redirection = 0, output_redirection = 0, append_output = 0;
		char * argv[100];
		while (parts != NULL)
		{


			// now, the entire string is one command, 
			// identify if it is valid, if yes, do the needful, else, exit with some error message and go on to the next

			if(strcmp(parts, "quit") == 0 || strcmp(parts,"quit\n")== 0)
			{
				exit(0);
			}
			// exit if command is exit
			if(strcmp(parts, "&") == 0 || strcmp(parts, "&\n") == 0)
			{
				background_required = 1;
				parts = strtok_r(NULL, " ", &secondary_2);
				continue; // so we basically ignore the background thing to provide for further commands after the background symbol
			}
			// mark background as 1 if required
			// slight issue, so the thing is that, we don't want all these symbols etc. to be counted

			if(strcmp(parts, ">") == 0 || strcmp(parts , ">\n")== 0)
			{
				output_redirection = 1;
				parts = strtok_r(NULL, " ", &secondary_2);
				if(parts[strlen(parts)-1] =='\n')
					parts[strlen(parts)-1] = '\0';
				strcpy(output , parts);
				parts = strtok_r(NULL, " ", &secondary_2);
				continue;
			}
			if(strcmp(parts, ">>") == 0 || strcmp(parts , ">>\n")== 0)
			{
				append_output = 1;
				parts = strtok_r(NULL, " ", &secondary_2);
				if(parts[strlen(parts)-1] =='\n')
					parts[strlen(parts)-1] = '\0';
				strcpy(append , parts);
				parts = strtok_r(NULL, " ", &secondary_2);
				continue;
			}
			if(strcmp(parts, "<") == 0 || strcmp(parts,"<\n") == 0)
			{
				input_redirection = 1;
				parts = strtok_r(NULL, " ", &secondary_2);
				if(parts[strlen(parts)-1] =='\n')
					parts[strlen(parts)-1] = '\0';
				strcpy(input, parts);
				parts = strtok_r(NULL, " ", &secondary_2);
				continue;
			}

			// so by the time I reach here , we are past the point where there are parameters for the commands
			if(strcmp(parts, "\n") !=0 )
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


		// for (int i = 0; i < arg; i++)
		// {
		// 	printf("%s\n",argv[i]);
		// }

		char * redirect[5];
		if(input_redirection == 1)
		{
			// printf("input is %s\n", input);
			redirect[0] = (char*)malloc((100)*sizeof(char));
			strcpy(redirect[0], input);
		}
		else
		{
			redirect[0] = (char*)malloc((100)*sizeof(char));
			redirect[0] = NULL;
		}
		if(output_redirection == 1)
		{
			// printf("output is %s\n", output);
			redirect[1] = (char*)malloc((100)*sizeof(char));
			strcpy(redirect[1], output);
		}
		else
		{
			redirect[1] = (char*)malloc((100)*sizeof(char));
			redirect[1] = NULL;
		}

		if(append_output == 1)
		{
			// printf("output is %s\n", append);
			redirect[2] = (char*)malloc((100)*sizeof(char));
			strcpy(redirect[2], append);
		}
		else
		{
			redirect[2] = (char*)malloc((100)*sizeof(char));
			redirect[2] = NULL;
		}


		// so I have created a function which is pretty similar in make up to the previous one that was being used		
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

			diversion(input_redirection, output_redirection, append_output, redirect);
			if(arg != 0) // cuz null seh comparison gives us a seg fault
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
					echo_function(copy_of_command);
				}				
				else if(!strcmp(argv[0] , "kjob") || !strcmp(argv[0], "kjob\n"))
				{
					kjobs(argv, arg);
				}
				else if(!strcmp(argv[0] , "jobs") || !strcmp(argv[0], "jobs\n"))
				{
					jobs_list(argv, arg);
				}
				else if(!strcmp(argv[0] , "cd") || !strcmp(argv[0], "cd\n"))
				{
					// we need to work cd on the child process
					exit(0);
				}
				else if(!strcmp(argv[0] , "setenv") || !strcmp(argv[0], "setenv\n"))
				{
					// we need to work setenv on the child process
					exit(0);
				}
				else if(!strcmp(argv[0] , "unsetenv") || !strcmp(argv[0], "unsetenv\n"))
				{
					// we need to work unsetenv on the child process
					exit(0);
				}
				else
				{
					if(background_required == 1)
						setpgid(0,0);
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
			if(arg != 0)
			{
				if(!strcmp(argv[0] , "cd") || !strcmp(argv[0], "cd\n"))
				{
					cd_function(argv, arg, home_path);			
				}
				else if(!strcmp(argv[0] , "setenv") || !strcmp(argv[0], "setenv\n"))
				{
					set_env(argv, arg);
				}
				else if(!strcmp(argv[0] , "unsetenv") || !strcmp(argv[0], "unsetenv\n"))
				{
					// we need to work setenv on the child process
					unset_env(argv, arg);
				}
			}

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
		free(input);
		free(output);
		free(append);
		command = strtok_r(NULL, ";", &secondary);
	}
	return ;
}



