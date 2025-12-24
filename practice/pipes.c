#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    char buffer[100];

    pipe(fd);
    pid_t pid = fork();

    if(pid==0)
    {
        close(fd[1]);
        read(fd[0],buffer,sizeof(buffer));
        printf("child received : %s",buffer);
        close(fd[0]);
    }
    else
    {
        close(fd[0]);
        strcpy(buffer,"hello via pipe");
        write(fd[1],buffer,strlen(buffer)+1);
        close(fd[1]);
        wait(NULL);
    }
}