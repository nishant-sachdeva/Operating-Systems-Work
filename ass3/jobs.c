#include "main.h"
#define decimal 10

int foreground_process_id = 0;

int background_processes_array[2048];

int background_counter = 0;


void add_to_foreground(int process_id)
{
    foreground_process_id = process_id;
    return;
}

void send_to_Zhandler(int signal)
{
    if(kill(foreground_process_id, SIGTSTP) == -1);
    return;
}

void add_to_background(int process_id)
{
    background_processes_array[background_counter++] = process_id;
    return ;
}

void print_info(int process_id, int job_number)
{
    char* name = (char*)calloc(1024,sizeof(char));
    if(name)
    {
        sprintf(name, "/proc/%d/comm",process_id);
        FILE* f = fopen(name,"r");
        if(f)
        {
            size_t size;
            size = fread(name, sizeof(char), 1024, f);
            if(size>0)
            {
                if('\n'==name[size-1])
                    name[size-1]='\0';
            }
            fclose(f);
        }
    }

    char *arr =  malloc(1024*sizeof(char));    
    char *id =  malloc(1024*sizeof(char));    
    char *status =  malloc(1024*sizeof(char));    
    size_t size = 1024;

    char* stat_file = (char*)calloc(1024,sizeof(char));
    sprintf(stat_file, "/proc/%d/status", process_id);
    if(stat_file)
    {
        FILE * data = fopen(stat_file, "r");
        if(data)
        {
            int field = 0;
            while(field < 4)
            { 
                if(getline(&arr, &size, data) == -1)
                {
                    perror("Oops! Error occurred! Please check\n");
                    break;
                }
                if(field == 0)
                {
                    strcpy(id, arr);
                }
                else if(field == 2)
                {
                    strcpy(status, arr);
                    // okay, i will try to fix this \n thingy
                    char * secondary;
                    char *parts = strtok_r(status, "\n", &secondary);
                    strcpy(status, parts);
                    char * secondary2;
                    parts = strtok_r(status," ", &secondary2);
                    parts = strtok_r(NULL, " ", &secondary2);
                    strcpy(status, parts);
                }
                field++;
            }
        }
        fclose(data);        
    }
    char proc_id[100];
    sprintf(proc_id, "%d", process_id);
    printf("[%d] : %s %s [%s]\n",job_number, status , name, proc_id);

    return;

}

void jobs_list(char ** argv , int arg)
{
    // okay so the idea is that I have the list of all jobs , and the idea is that the latest one are at the current counter
    // so I'll take the list of all jobs and print out their info side by side
    // then in the end, I'll take the foreground one and put out it's data too
    for(int i = 0 ; i < (background_counter); i++)
    {
        print_info(background_processes_array[i], i+1); // this is the oldest -> newest order
    }
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

void overkill_func()
{
    for (int i = 0; i < background_counter; i++)
    {
        if(kill(background_processes_array[i], 9) == -1)
        {
            printf("Couldn't kill %d\n", background_processes_array[background_counter]);
        }
    }
    return;
}
void fg_function(char ** argv, int arg)
{
    printf("in the fg functio now\n");
    // argv[1] is the pid
    int job_number = atoi(argv[1]) -1;
    if(job_number > background_counter)
    {
        printf("Error: job dosen't exist\n");
        return;
    }
    int signal = 0;
    int job = background_processes_array[job_number];
    if(kill(job, signal) == -1)
    {
        printf("Error: couldn't access job with pid %d\n", job);
        return;
    }
    else
    {
        printf("about to send signal \n");
        kill(job, SIGCONT);
        tcsetpgrp(0, job);
        // signal(SIGTTOU, SIG_IGN);
        tcsetpgrp(0, getpid());
        // signal(SIGTTOU, SIG_DFL);
        // so now we know that this job exists
    }
    

    return ;
}

void bg_function(char ** argv, int arg)
{

    return;
}