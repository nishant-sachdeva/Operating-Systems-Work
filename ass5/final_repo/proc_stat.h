// here we will declare the material regarding the struct proc stat

struct proc_stat
{
	int pid;
	int num_run;
	int runtime;
	int time_in_queues;
	
	// int current_queue;
	// int ticks[5];

};