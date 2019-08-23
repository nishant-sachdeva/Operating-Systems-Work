#include "main.h"

char command[100][100];


int get_count(){
    FILE * lines = fopen("/home/nishu/nishant/sem3/Operating-Systems-Work/ass2/.history", "r");
    //read file into array
    int count = 0;
    char c;
    for(c = getc(lines); c!= EOF ; c = getc(lines))
    {
        if(c == '\n')
            count++;
    }
    return count;
}


void history_function(char *argv)
{
    FILE *myFile, *lines;
    myFile = fopen("/home/nishu/nishant/sem3/Operating-Systems-Work/ass2/.history", "r");
    // printf("file open hui\n");
    int count = get_count()/2;
    // printf("count is : %d\n", count);
    for (int i = 0; i < count ; i++)
    {
        fscanf(myFile, "%s", command[i]);
        printf("%d : %s\n",i+1, command[i]);
    }
    fclose(myFile);
    fclose(lines);
}



void add_to_history(char * command)
{
    FILE * file = fopen("/home/nishu/nishant/sem3/Operating-Systems-Work/ass2/.history", "a");
    int count  = get_count();
    strcat(command,  "\n");
    if((count) <= 38)
    {
        // printf("%d\n", count);
        FILE * f = fopen("/home/nishu/nishant/sem3/Operating-Systems-Work/ass2/.history", "a");
        // printf("command to be appended is %s", command);
        fprintf(f, "%s", command);
        fclose(f);
        // append command in file
    }
    else
    {
        // printf("%d\n", count);
        // printf("count has reached 20, we are deleting 2 \n");


        FILE * f = fopen("/home/nishu/nishant/sem3/Operating-Systems-Work/ass2/.history", "a");
        // printf("command to be appended is %s", command);
        fprintf(f, "%s", command);
        fclose(f);

                FILE *  file1 = fopen("/home/nishu/nishant/sem3/Operating-Systems-Work/ass2/.history", "r");
        FILE * file2  = fopen("/home/nishu/nishant/sem3/Operating-Systems-Work/ass2/.replica", "w");
        // append command in file, and then move everything up by one step;
        int temp =  1;
        for(char c = getc(file1); c!= EOF ; c = getc(file1))
        {
            if(temp != 1 && temp != 2)
            {
                putc(c, file2);
            }
            if(c == '\n')
                temp++;
        }
        fclose(file1);
        fclose(file2);
        

        remove("/home/nishu/nishant/sem3/Operating-Systems-Work/ass2/.history");
        rename("/home/nishu/nishant/sem3/Operating-Systems-Work/ass2/.replica", "/home/nishu/nishant/sem3/Operating-Systems-Work/ass2/.history");
        return ;
    }
    

}