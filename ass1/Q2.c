#include<stdio.h>

/* library files for the function calls open and stat */
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>

#include<unistd.h>

#define CONS 100000


int main(int argc, char* argv[])
{


    /* take input paths as command line arguments,  */

    /* check if the contents actually exist */

    if(argc != 4)
    {
        char error[] = {"There is error in the parameters entered. Please check up with the readme and reapply \n"};
        write(STDOUT_FILENO, &error, sizeof(error));
        return 0;
    }
    // check for old_file;
    long long int old = open(argv[1], O_RDONLY);
    if(old == -1)
    {
        char file_error[] = {"The old-file specified has not been found. Please confirm path and retry\n"};
        write(STDOUT_FILENO, &file_error, sizeof(file_error));
        return 0;
    }

    struct stat folder;
    int is_dir = 1;
    // check for directory
    if(stat(argv[2], &folder) != 0 || !S_ISDIR(folder.st_mode))
    {
        char file_error[] = {"The directory specified has not been found. Please confirm with the readme and retry\n"};
        write(STDOUT_FILENO, &file_error, sizeof(file_error));        
        is_dir = 0;
    }

    
    // check for new file;
    long long int new = open(argv[3], O_RDONLY);
    if(new == -1)
    {
        char file_error[] = {"The new-file specified has not been found. Please confirm path and retry\n"};
        write(STDOUT_FILENO, &file_error, sizeof(file_error));
        return 0;
    }

    struct stat newfile;
    struct stat oldfile;

    
    


    /* section to check if the files are reverse or not */


    // two fds are old and  new

    long long int count = lseek(new, 0, SEEK_END) ;

    // now we know the size of the file: we can start comparing now
    int same = 1;

    long long int blocks = count/CONS;
    long long int off = count%CONS;


    while(blocks--)
    {
        lseek(new, -CONS, SEEK_CUR);
        char c[CONS], d[CONS];
        read(old, c,CONS);
        read(new, d, CONS);

        for(int i = 0 ; i<CONS ; i++)
        {
            if(c[i] != d[CONS-i-1]){
                same = 0;
                break;
            }
        }

        if(same == 0)
        {
            break;
        }
        lseek(new, -CONS , SEEK_CUR);
    }


    if(same == 1)
    {
        lseek(new, -off, SEEK_CUR);
        if(off)
        {
            char c[CONS],d[CONS];
            read(old, &c, off);
            read(new, &d, off);
            for(int i = 0 ; i<off ; i++)
            {   
                if(c[i] != d[off-i-1])
                {
                    same = 0;
                    break;
                }
            }

            // if(same == 0)
            // {
            //     break;
            // }
            lseek(new, -off*2 , SEEK_CUR);
        }
    }







    /* if they do, fill up the data questions accordingly */
    /* as of now all files exist and now we can start printing info out */
    // filling out the 9 data fields for each file

    stat(argv[1], &oldfile);
    stat(argv[3], &newfile);

    // stat operation on the dir has been 

    /* now we start printing */

    if(same == 1)
    {
        char ans[] = {"Are the files reverse of each other : YES\n"};
        write(STDOUT_FILENO, &ans, sizeof(ans));
    }
    else
    {
        
        char ans[] = {"Are the files reverse of each other : NO\n"};
        write(STDOUT_FILENO, &ans, sizeof(ans));
    }
    


    if(is_dir == 0)
    {
    write(STDOUT_FILENO, "Directory exists : NO \n\n" ,24 );
    }
    else
    {
    write(STDOUT_FILENO, "Directory exists : YES \n\n" ,25 );
    }

    char user_per_r[] = {"User  has read permission on "};
    char user_per_w[] = {"User  has write permission on "};
    char user_per_x[] = {"User  has execute permission on "};

    char group_per_r[] = {"Group has read permission on "};
    char group_per_w[] = {"Group has write permission on "};
    char group_per_x[] = {"Group has execute permission on "};

    char other_per_r[] = {"Others have read permission on "};
    char other_per_w[] = {"Others have write permission on "};
    char other_per_x[] = {"Others have execute permission on "};


    
    if(oldfile.st_mode & S_IRUSR )
    {
        write(STDOUT_FILENO, &user_per_r, sizeof(user_per_r));
        write(STDOUT_FILENO, "oldfile : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &user_per_r, sizeof(user_per_r));
        write(STDOUT_FILENO, "oldfile : no\n", 14 );        
    }
    
    if(oldfile.st_mode & S_IWUSR )
    {
        write(STDOUT_FILENO, &user_per_w, sizeof(user_per_w));
        write(STDOUT_FILENO, "oldfile : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &user_per_w, sizeof(user_per_w));
        write(STDOUT_FILENO, "oldfile : no\n", 14 );        
    }
    
    if(oldfile.st_mode & S_IXUSR )
    {
        write(STDOUT_FILENO, &user_per_x, sizeof(user_per_x));
        write(STDOUT_FILENO, "oldfile : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &user_per_x, sizeof(user_per_x));
        write(STDOUT_FILENO, "oldfile : no\n", 14 );        
    }

    write(STDOUT_FILENO, "\n", 1);

    if(oldfile.st_mode & S_IRGRP )
    {
        write(STDOUT_FILENO, &group_per_r, sizeof(group_per_r));
        write(STDOUT_FILENO, "oldfile : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &group_per_r, sizeof(group_per_r));
        write(STDOUT_FILENO, "oldfile : no\n", 14 );        
    }
    
    if(oldfile.st_mode & S_IWGRP )
    {
        write(STDOUT_FILENO, &group_per_w, sizeof(group_per_w));
        write(STDOUT_FILENO, "oldfile : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &group_per_w, sizeof(group_per_w));
        write(STDOUT_FILENO, "oldfile : no\n", 14 );        
    }
    
    if(oldfile.st_mode & S_IXGRP )
    {
        write(STDOUT_FILENO, &group_per_x, sizeof(group_per_x));
        write(STDOUT_FILENO, "oldfile : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &group_per_x, sizeof(group_per_x));
        write(STDOUT_FILENO, "oldfile : no\n", 14 );        
    }


    write(STDOUT_FILENO, "\n", 1);


    if(oldfile.st_mode & S_IROTH )
    {
        write(STDOUT_FILENO, &other_per_r, sizeof(other_per_r));
        write(STDOUT_FILENO, "oldfile : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &other_per_r, sizeof(other_per_r));
        write(STDOUT_FILENO, "oldfile : no\n", 14 );        
    }
    
    if(oldfile.st_mode & S_IWOTH )
    {
        write(STDOUT_FILENO, &other_per_w, sizeof(other_per_w));
        write(STDOUT_FILENO, "oldfile : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &other_per_w, sizeof(other_per_w));
        write(STDOUT_FILENO, "oldfile : no\n", 14 );        
    }
    
    if(oldfile.st_mode & S_IXOTH )
    {
        write(STDOUT_FILENO, &other_per_x, sizeof(other_per_x));
        write(STDOUT_FILENO, "oldfile : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &other_per_x, sizeof(other_per_x));
        write(STDOUT_FILENO, "oldfile : no\n", 14 );        
    }

    write(STDOUT_FILENO, "\n", 1);

    ///////////////////////////////////////////////


    if(newfile.st_mode & S_IRUSR )
    {
        write(STDOUT_FILENO, &user_per_r, sizeof(user_per_r));
        write(STDOUT_FILENO, "newfile : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &user_per_r, sizeof(user_per_r));
        write(STDOUT_FILENO, "newfile : no\n", 14 );        
    }
    
    if(newfile.st_mode & S_IWUSR )
    {
        write(STDOUT_FILENO, &user_per_w, sizeof(user_per_w));
        write(STDOUT_FILENO, "newfile : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &user_per_w, sizeof(user_per_w));
        write(STDOUT_FILENO, "newfile : no\n", 14 );        
    }
    
    if(newfile.st_mode & S_IXUSR )
    {
        write(STDOUT_FILENO, &user_per_x, sizeof(user_per_x));
        write(STDOUT_FILENO, "newfile : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &user_per_x, sizeof(user_per_x));
        write(STDOUT_FILENO, "newfile : no\n", 14 );        
    }

    write(STDOUT_FILENO, "\n", 1);


    if(newfile.st_mode & S_IRGRP )
    {
        write(STDOUT_FILENO, &group_per_r, sizeof(group_per_r));
        write(STDOUT_FILENO, "newfile : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &group_per_r, sizeof(group_per_r));
        write(STDOUT_FILENO, "newfile : no\n", 14 );        
    }
    
    if(newfile.st_mode & S_IWGRP )
    {
        write(STDOUT_FILENO, &group_per_w, sizeof(group_per_w));
        write(STDOUT_FILENO, "newfile : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &group_per_w, sizeof(group_per_w));
        write(STDOUT_FILENO, "newfile : no\n", 14 );        
    }
    
    if(newfile.st_mode & S_IXGRP )
    {
        write(STDOUT_FILENO, &group_per_x, sizeof(group_per_x));
        write(STDOUT_FILENO, "newfile : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &group_per_x, sizeof(group_per_x));
        write(STDOUT_FILENO, "newfile : no\n", 14 );        
    }


    write(STDOUT_FILENO, "\n", 1);


    if(newfile.st_mode & S_IROTH )
    {
        write(STDOUT_FILENO, &other_per_r, sizeof(other_per_r));
        write(STDOUT_FILENO, "newfile : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &other_per_r, sizeof(other_per_r));
        write(STDOUT_FILENO, "newfile : no\n", 14 );        
    }
    
    if(newfile.st_mode & S_IWOTH )
    {
        write(STDOUT_FILENO, &other_per_w, sizeof(other_per_w));
        write(STDOUT_FILENO, "newfile : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &other_per_w, sizeof(other_per_w));
        write(STDOUT_FILENO, "newfile : no\n", 14 );        
    }
    
    if(newfile.st_mode & S_IXOTH )
    {
        write(STDOUT_FILENO, &other_per_x, sizeof(other_per_x));
        write(STDOUT_FILENO, "newfile : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &other_per_x, sizeof(other_per_x));
        write(STDOUT_FILENO, "newfile : no\n", 14 );        
    }

    write(STDOUT_FILENO, "\n", 1);
    
    ///////////////////////////////////////////////

    if(is_dir == 0)
    {
        write(STDOUT_FILENO, "No directory found! can't say anything \n", 40);
        return 0;
    }

    if(folder.st_mode & S_IRUSR )
    {
        write(STDOUT_FILENO, &user_per_r, sizeof(user_per_r));
        write(STDOUT_FILENO, "folder : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &user_per_r, sizeof(user_per_r));
        write(STDOUT_FILENO, "folder : no\n", 14 );        
    }
    
    if(folder.st_mode & S_IWUSR )
    {
        write(STDOUT_FILENO, &user_per_w, sizeof(user_per_w));
        write(STDOUT_FILENO, "folder : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &user_per_w, sizeof(user_per_w));
        write(STDOUT_FILENO, "folder : no\n", 14 );        
    }
    
    if(folder.st_mode & S_IXUSR )
    {
        write(STDOUT_FILENO, &user_per_x, sizeof(user_per_x));
        write(STDOUT_FILENO, "folder : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &user_per_x, sizeof(user_per_x));
        write(STDOUT_FILENO, "folder : no\n", 14 );        
    }


    write(STDOUT_FILENO, "\n", 1);


    if(folder.st_mode & S_IRGRP )
    {
        write(STDOUT_FILENO, &group_per_r, sizeof(group_per_r));
        write(STDOUT_FILENO, "folder : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &group_per_r, sizeof(group_per_r));
        write(STDOUT_FILENO, "folder : no\n", 14 );        
    }
    
    if(folder.st_mode & S_IWGRP )
    {
        write(STDOUT_FILENO, &group_per_w, sizeof(group_per_w));
        write(STDOUT_FILENO, "folder : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &group_per_w, sizeof(group_per_w));
        write(STDOUT_FILENO, "folder : no\n", 14 );        
    }
    
    if(folder.st_mode & S_IXGRP )
    {
        write(STDOUT_FILENO, &group_per_x, sizeof(group_per_x));
        write(STDOUT_FILENO, "folder : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &group_per_x, sizeof(group_per_x));
        write(STDOUT_FILENO, "folder : no\n", 14 );        
    }


    write(STDOUT_FILENO, "\n", 1);


    if(folder.st_mode & S_IROTH )
    {
        write(STDOUT_FILENO, &other_per_r, sizeof(other_per_r));
        write(STDOUT_FILENO, "folder : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &other_per_r, sizeof(other_per_r));
        write(STDOUT_FILENO, "folder : no\n", 14 );        
    }
    
    if(folder.st_mode & S_IWOTH )
    {
        write(STDOUT_FILENO, &other_per_w, sizeof(other_per_w));
        write(STDOUT_FILENO, "folder : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &other_per_w, sizeof(other_per_w));
        write(STDOUT_FILENO, "folder : no\n", 14 );        
    }
    
    if(folder.st_mode & S_IXOTH )
    {
        write(STDOUT_FILENO, &other_per_x, sizeof(other_per_x));
        write(STDOUT_FILENO, "folder : yes\n", 14 );
    }
    else
    {
        write(STDOUT_FILENO, &other_per_x, sizeof(other_per_x));
        write(STDOUT_FILENO, "folder : no\n", 14 );        
    }


    write(STDOUT_FILENO, "\n", 1);
    close(new);
    close(old);


    return 0;
}
