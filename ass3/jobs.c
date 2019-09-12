#include "main.h"


void jobs_list(char ** argv , int arg)
{
    // now we are here, we now have to list all the jobs and their pids and states, and all that in order of their times, recent ones at the bottom and the oldests ones at the top so
    // the list goes like <number> <job type foreground:background> <job name > < pid>


    return ;
}

void kjobs(char ** argv, int arg)
{
    // so argv[1] is the job number in string form
    // argv[2] is the signal number in string form
    int job = atoi(argv[1]);
    int signal = atoi(argv[2]);

    if(kill(job,signal) == -1)
    {
        perror("");
    }
    else
    {
        // we are good to go, keep going
    }
    
    return ;

}

void fg(char ** argv, int arg)
{

    return ;
}

void bg(char ** argv, int arg)
{

    return;
}