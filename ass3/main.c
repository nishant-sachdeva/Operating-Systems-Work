#include "main.h"

char homepath[1024];


char home_path[1024];
char prev_directory[1024];

int main()
{
	get_path(home_path);
	strcpy(prev_directory, home_path); // now we have recorded the prev directory option, so we will be fine now as this has been initialised
	while(1)
	{
		displayPrompt(home_path);
		char inp[1024];
		take_commands(inp);
		fflush(stdin);
		do_work(inp, home_path);
	}
	return 0;
}