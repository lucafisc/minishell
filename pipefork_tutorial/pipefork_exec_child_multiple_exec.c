#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#define TOT_CMD 8

int main(void)
{
    pid_t   pid;
    int     i;

    char *cmd[] = {"/usr/bin/printf", "Exec\n", NULL};
    i = 0;
    while (i++ < TOT_CMD)
    {
        pid = fork();
        if (pid == 0)
            execv(cmd[0], cmd);
    }
    wait(NULL);
    printf("Here I am! My pid is %d\n", pid);
}