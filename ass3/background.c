#include "main.h"

void deal_with_background()
{
	signal(SIGCHLD, signal_handler);
	return;
}


void signal_handler(int signal_number)
{
	int status;
	pid_t pid = waitpid(-1, &status, WNOHANG);
	if(pid > 0)
	{
		printf("pid = %d exited, status = %d\n",pid, status);
	}
	// else if(WIFCONTINUED(status))
	// {
	// 	printf("continued\n");
	// }
	// else if (WIFSIGNALED(status))
	// {
	// 	printf("pid = %d killed by %d\n", pid, WTERMSIG(status));
	// }
	// else if(WIFSTOPPED(status))
	// {
	// 	printf("pid = %d stopped by %d\n",pid, WTERMSIG(status));
	// }

	return;
}
