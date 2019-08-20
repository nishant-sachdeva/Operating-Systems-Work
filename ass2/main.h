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



void get_path(char arr[]);
void displayPrompt();
void take_commands(char input[]);
void do_work(char inp[]);


char list_of_commands[10][10]={

 "ls",
 "cd",
 "pwd",
 "pinfo",
 "echo", 
 "history"
 };



int main();