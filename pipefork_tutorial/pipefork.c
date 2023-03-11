#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd_pipe[2];
    /* Setup the commands */
    char    *arg1[] = {"/bin/cat", "-e", NULL};
    char    *arg2[] = {"/usr/bin/grep", "more", NULL};
    /* Open input and output files */
    int fd_in1 = open("infile", O_RDONLY);
    int fd_out2 = open("outfile", O_WRONLY | O_CREAT | O_APPEND, 0644);
    /* Create the pipe */
    pipe(fd_pipe);
    /* The output of command1 writes into the pipe's write end */
    int fd_out1 = fd_pipe[1];
    /* The input of command2 reads from the pipe's read end */
    int fd_in2 = fd_pipe[0];
    /* Fork and catch the process id */
    pid_t pid = fork();
    if (pid == 0) // Child process
    {
        /* The child executes command 1 so it will use just the write end */
        /* Close the read end */
        close(fd_pipe[0]);
        /* Redirecting stdin and stdout to in and out of command 1 */
        dup2(fd_in1, 0);
        dup2(fd_out1, 1);
        /* Execute command 1. This process will be substituted by the process */
        /* started with exec. Any code below exec can't be reached unless exec fails */
        execv(arg1[0], arg1);
    }
    else        // Parent process
    {
        /* The parent executes command 2. Same reasoning as the child, just */
        /* opposite loose ends of the pipe */
        close(fd_pipe[1]);
        dup2(fd_in2, 0);
        dup2(fd_out2, 1);
        execv(arg2[0], arg2);
    }
}