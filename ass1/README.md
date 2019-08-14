ques 1:

==>>
The input is suppossed to be given in the form of command line arguments in the order:

-->
The order for paths to be entered is as given :
Path for input file ( any variation in this order could lead to unintended consequences for which the coder cannot be held accountable  :P)

->
STEPS TO RUN THE CODE:
1. gcc ques1.c
2. ./a.out (path for source file) (Path for dest file)

NOTE : The directory name has been specified in the assignment pdf hence that will be created irrespective of the dest path. Please give the output file path accordingly.

==> DESCRIPTION:
The code uses various system calls like open, read, write, close etc. to perform the functions as required. To know more about them, look up the man 2 pages by using the command -> man 2 "sys call name" .

In case the man 2 pages are not installed, use the following command to install them -> sudo apt-get install build-essential manpages manpages-dev manpages-posix manpages-posix-dev

This should set up the man pages which can then be used for reference :) 

Ques 2:

The input  is suppossed to be given in the form of command line arguments:

The order for the files to be entered is as given: 
Oldfile path - directory name - newfile path ( any variation in this order could lead to unintended consequences for which the coder cannot be held accountable  :P)

==>  STEPS TO RUN THE CODE:
1. gcc ques2.c
2. ./a.out (path for newfile) (directory name) (path for oldfile)

NOTE: The directory name has been asked to check for the directory individually. The newfile path may or may not be include it. 

==> DESCRIPTION:
The code uses various system calls like open, read, write, close etc. to perform the functions as required. To know more about them, look up the man 2 pages by using the command -> man 2 "sys call name" .

In case the man 2 pages are not installed, use the following command to install them -> sudo apt-get install build-essential manpages manpages-dev manpages-posix manpages-posix-dev

This should set up the man pages which can then be used for reference :) 