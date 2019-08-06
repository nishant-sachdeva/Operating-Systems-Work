#include<stdio.h>

/* libraries for open, mkdir, lseek sys calls */
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>


/* libraries for write,lseek,close, read sys calls */
#include<unistd.h>


/* funtion to convert  integer to string */

void integer_to_string(char arr[], int size, int percent)
{
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

int main()
{
    /* create the new directory using mkdir sys call */
    long long int make_new_folder = mkdir ("./Assignment", 0700);

    long long int source, dest; // file descriptors for source and destination
    
    source = open("test.txt", O_RDONLY); // txt file only for reading
    dest = open("./Assignment/ans.txt", O_RDWR | O_CREAT, 0700);

    // this should create the new file;

    long long int size = lseek(source, -1 , SEEK_END);
    // this takes source to the end of the file, and returns the
    // size of the file into the variable "size"

    long long int total = size; // for displayin percentages;
    char per[3];
    while(size+1)
    {
        char c;
        read(source, &c,1);
        write(dest, &c, 1);

        int off = lseek(source, -2, SEEK_CUR);
        // as per manual 2 entry in lseek, the  current is incremented
        // while reading operation, hence it needs to be brought back 2 bytes;

        /* section for the progress bar */

        int percent = ((total - size)*100)/total ;

        integer_to_string(per, sizeof(per), percent);

        write(STDOUT_FILENO, "\r The current progress is : ", 29);
        write(STDOUT_FILENO, per, sizeof(per));
        write(STDOUT_FILENO, " %", 2);
        // if (off  <= 0)
            // break;
        size--;
    }
    write(STDOUT_FILENO, "\n", 1);

    close(source);
    close(dest);
    return 0;    
}
