#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#define TOT_CMD 8

int main(void)
{
    pid_t   pid;
    int     i;

    i = 0;
    while (i++ < TOT_CMD)
    {
        pid = fork();
        if (pid == 0)
        {
            printf("My pid is %d and I'll exec cmd %d\n", pid, i);
            /* I put a break to simulate the fact that after the exec no line is executed */
            break ;
        }
    }
    wait(NULL);
    /* I print only parents because the children got caught in the exec */
    if (pid > 0)
        printf("Here I am! My pid is %d\n", pid);
}