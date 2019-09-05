#include "main.h"

void displayPrompt(char home_path[])
{
	char username[100];
	char sysname[100];

	char path[1024];
	get_path(path);

	fill_path(path, home_path);

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


void fill_path(char path[], char home_path[])
{
	if(strcmp(home_path, path) == 0)
	{
		char arr[] = "~";
		strcpy(path, arr);
	}
	else
	{
		if(strlen(path) > strlen(home_path))
			if(substring(path, home_path)==1)
			{
				// printf("substring hai\n");
				char tilda[1024] = "~/";
				strncat(tilda, (path + strlen(home_path)+1), strlen(path) - strlen(home_path) - 1);
				strcpy(path, tilda);
			}
	}
	return ;
}


int substring(char arr1[], char arr2[])
{
	// to check if arr2 is a substring of another arr1
	int i, j=0, k;
	for(i=0; arr1[i]; i++)
	{
		if(arr1[i] == arr2[j])
		{
			for(k=i, j=0; arr1[k] && arr2[j]; j++, k++)
				if(arr1[k]!=arr2[j])
					break;
			if(!arr2[j])
				return 1;
		}
	}
	return 0;
}
