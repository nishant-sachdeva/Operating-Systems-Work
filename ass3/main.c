#include "main.h"

char homepath[1024];


char home_path[1024];
char prev_directory[1024];

int main()
{
	get_path(home_path);
	strcpy(prev_directory, home_path);
	int saved_stdin = dup(STDIN_FILENO);
	int saved_stdout = dup(STDIN_FILENO); // now we have recorded the prev directory option, so we will be fine now as this has been initialised
	while(1)
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDIN_FILENO);
		displayPrompt(home_path);
		char inp[1024];
		take_commands(inp);
		fflush(stdin);
		do_work(inp, home_path);

		dup2(saved_stdout, 1);
		close(saved_stdout);

		dup2(saved_stdin, 0);
		close(saved_stdin);
	}
	return 0;
}