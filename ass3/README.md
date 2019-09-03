Shell in C

This is an implementation of a basic interactive shell done in C as an assignment for our Operating Systems course.
Running the code

    Download the repository as a zip, or clone it. cd into directory
    Run ./makefile . Ignore any warnings shown.

    run ./a.out

In order to exit the shell, type exit

Requirements as specified
Minimum requirements to be met:

    Display requirement < username@systemname:path/to/whereever>

    Builtins: ls, echo, cd, pwd. Don't use execvp.

    Make an ls functionality to enable: -l, -a, -al/la

    Option to execute system command, like the ones in /bin/. Implement foreground, background processes. Should have arguments.

    pinfo. Prints information related to the running shell program process.

    pinfo pid should print the process related information about the process with pid.

    Print correct information about the background process exiting safely.

Stuff to note:

    Usage of system is strictly prohibited.
    Get error handling right
    rollnum_assgn2.tar.gz
