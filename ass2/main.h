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




int main();