#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

/* Little program to show the forking only of the child */
int main(void)
{
    pid_t   pid;

    pid = fork();
    /* After the first fork we should have 2 processes
    one with pid 0 and one with >0    
    */
    printf("Here I am! My pid is %d\n", pid);
    if (pid == 0)   // child process
    {
        /* Adding an empty line and forking only the child */
        printf("\n");
        fork();
    }
    /* The command wait imposes to the parent to wait until 
    the child finished execution forcing the empty line to
    appear in the right place */
    wait(NULL);
    /* This should print 3 statements, two with pid 0 and one >0 */
    printf("Here I am! My pid is %d\n", pid);
}