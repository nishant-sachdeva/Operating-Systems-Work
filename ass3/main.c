#include "main.h"

char homepath[1024];


char home_path[1024];

int main()
{
	get_path(home_path);

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