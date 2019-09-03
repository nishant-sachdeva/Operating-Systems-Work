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

#include<dirent.h>
#include<time.h>





void get_path(char arr[]);
void displayPrompt();
void take_commands(char input[]);
void do_work(char inp[]);
void fill_path(char path[]);
void  parse(char *line, char **argv);
int substring(char arr1[], char arr2[]);


void pwd_function();

void echo_function(char *command, int background);

void cd_function(char **argv, int arg, char arr[]);

void pinfo_function(char ** argv, int args);

void ls_function(char **argv , int args, char home_path[]);

void history_function(char **argv, char home_path[], int arg);

void add_to_history(char *  arr, char home_path[]);

void update(char home_path[]);

int main();