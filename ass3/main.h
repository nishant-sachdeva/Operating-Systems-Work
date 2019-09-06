#include<stdio.h>
#include<unistd.h>
#include<stdlib.h> 
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <error.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>
#include<sys/wait.h>
#include <fcntl.h>  

#include<dirent.h>
#include<time.h>


extern char home_path[1024];



void get_path(char arr[]);
void displayPrompt(char home_path[]);
void take_commands(char input[]);
void do_work(char inp[], char home_path[]);
void fill_path(char path[], char home_path[]);
void parse(char *line, char **argv);
int substring(char arr1[], char arr2[]);


void pwd_function(int background,  char home_path[]);

void echo_function(char *command, int background);

void cd_function(char **argv, int arg, char arr[]);

void pinfo_function(char ** argv, int args);

void ls_function(char **argv , int args, char home_path[]);

void history_function(char **argv, char home_path[], int arg);

void add_to_history(char *  arr, char home_path[]);

void update(char home_path[]);

void file_diversions(int input, int output, int append, char ** argv);

int main();