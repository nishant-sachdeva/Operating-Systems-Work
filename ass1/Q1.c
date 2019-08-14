#include<stdio.h>

/* libraries for open, mkdir, lseek sys calls */
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

// #include<time.h>
// #include<sys/time.h>

/* libraries for write,lseek,close, read sys calls */
#include<unistd.h>

#define CONS (1024*1024*2)


/* funtion to convert  integer to string */

void integer_to_string(char arr[], int size, int percent)
{
    if(percent == 0)
    {
        arr[0] =  0 +  '0';
        arr[1] = '\0';
        return;
    }
    int len  = 1;
    if(percent == 100)
    {
        len = 2;
        arr[3] = '\0';
    }
    else{
        arr[2] = '\0';
    }
    int i = 0;
    while(percent)
    {
        arr[len--] = percent%10 + '0';
        percent /= 10;
    }
    arr[3] = '\0' ;
    // the percent  (which is at max a 3 digit number
    // has been made into a string)
    return; 

}

int main(int argc, char* argv[])
{
    // time_t begin  = time(NULL);
    if(argc != 2)
    {
        char arr[] = {"Wrong argument format. Please consult the readme file for details on proper input format"};
        write(STDOUT_FILENO, &arr, sizeof(arr));
        write(STDOUT_FILENO, "\n", 1);
        return  0;
    }

    

    // printf("arguments confirmed\n");


    /* create the new directory using mkdir sys call */
    long long int make_new_folder = mkdir ("./Assignment", 0700);

    long long int source, dest; // file descriptors for source and destination
    
    // printf("folder made\n");

    source = open(argv[1], O_RDONLY); // txt file only for reading
    if(source < 0)
    {
        char e[] = {"The source file could not be opened. Please recheck source and consult readme and try again.\n"};
        write(STDOUT_FILENO, &e, sizeof(e));
        return 0;
    }
    // now we will take argv[1] and extract the input name out of it
    char tempp[1000];
    int l = strlen(argv[1]);
    for(int i = 0; i < l ; i++)
    {
        tempp[i] = argv[1][l - i - 1];
    }

    // printf("file name is %s\n", argv[1]);
    // printf("reverse file name is %s\n", tempp);

    // now  we have the reversed string

    char * token = strtok(tempp, "/");

    char path[10000];
    strcpy(path, "Assignment/");
    // printf("%s\n", token);

    char tokenn[1000];
    l =  strlen(token);
    for(int i = 0 ; i < l ; i++)
    {
        tokenn[i] = token[l - i - 1];
    }
    // printf("final file name is %s \n", tokenn);

    int is_same = strcmp(tokenn, argv[1]);

    // printf("extracted name is %s\n", tokenn);
    // printf("org  name is %s\n", argv[1]);
    // printf("strcmp gave ans as %d\n", is_same);
    if(!is_same) // means they are same names
    {
        strcat(path , argv[1]);
        // printf("so final path is %s\n", path);

    }
    else
    {
        // printf("say hi\n");

        strcat(path, tokenn);
        // printf("so final path is %s\n", path);
    }

    // that gives us the proper file name;

    dest = open(path, O_RDWR | O_CREAT, 0700);

    // this should create the new file;

    long long int size = lseek(source, 0 , SEEK_END);
    // this takes source to the end of the file, and returns the
    // size of the file into the variable "size"

    long long int total = size; // for displayin percentages;
    char per[3];

    /////////////////////////////////////////////////////////
    /* THIS IS THE SECTION THAT REVERSES THE FILE */

    // my constant is 1000

    long long int blocks = size/CONS;
    long long int off = size%CONS;
    // this gives me the number of blocks of size 1000 bytes, and the
    // remaining number of bytes

    // now it is in the abs last
    while(blocks)
    {
        lseek(source, -CONS, SEEK_CUR);

        char c[CONS], d[CONS];
        

        read(source, c, CONS);
        
        // now we have some characters in the buffer

        for(int i = 0; i<CONS ; i++)
        {
            d[i] = c[CONS-i-1];
        }
        // this reversed the array

        // printf("%s\n", d);

        write(dest, d, CONS);

        // this has written the content as required
        
        lseek(source, -CONS, SEEK_CUR);

        blocks--;

        size -= CONS;

        /* section for the progress bar */

        int percent = ((total - size)*100)/total ;

        integer_to_string(per, sizeof(per), percent);


        write(STDOUT_FILENO, "\r The current progress is : ", 29);
        write(STDOUT_FILENO, per, sizeof(per));
        write(STDOUT_FILENO, " %", 2);


        // time_t end = time(NULL);

        // printf("\r %ld  ", end - begin);
    }

    lseek(source, -off, SEEK_CUR);

    if(off)
    {

        char c[CONS], d[CONS];
        

        read(source, c, off);
        
        // now we have some characters in the buffer

        for(int i = 0; i<off ; i++)
        {
            d[i] = c[off-i-1];
        }
        // this reversed the array

        // printf("%s\n", d);

        write(dest, d, off);

        // this has written the content as required
        
        lseek(source, -2*off, SEEK_CUR);


        size -= off;

        /* section for the progress bar */

        int percent = ((total - size)*100)/total ;

        integer_to_string(per, sizeof(per), percent);


        write(STDOUT_FILENO, "\r The current progress is : ", 29);
        write(STDOUT_FILENO, per, sizeof(per));
        write(STDOUT_FILENO, " %", 2);

        
        
    }


    /* REVERSING COMPLETE */
    char final_ans[] = {"The process has finished :) , you may go at the specified output dest and check it out"};
    write(STDOUT_FILENO, "\r", 1);
    write(STDOUT_FILENO, &final_ans, sizeof(final_ans));
    write(STDOUT_FILENO, "\n", 1);

    close(source);
    close(dest);
    return 0;    
}
