#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "proc_stat.h"


int main(int argc, char const *argv[])
{
	//printf(1,"Yo sup machass!! Ima give you the details of the processes\n");

	// here we will declare the two guys
	struct proc_stat p;
	// printf(1,"we are trying to find the details of pid %s\n" , argv[1]);
	int pid  = atoi(argv[1]);
	// printf(1 , "%d\n", atoi(argv[1]) );

	getpinfo(&p , pid);

	exit();
}