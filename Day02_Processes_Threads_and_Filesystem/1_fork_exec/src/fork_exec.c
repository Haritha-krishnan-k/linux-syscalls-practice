#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int i;

    char *task[][3] = {{"ls","-l",NULL},{"pwd",NULL},{"date",NULL}};
    for(i=0;i<3;i++)
    {
    pid = fork();
    if(pid<0)
    {
        perror("fork failed");
    }

    else if (pid == 0)
    {
     printf("child %d PID=%d PPID=%d , executing %s\n",i+1 , getpid(), getppid() , task[i][0]);
    //   printf(" the tasks %s\n",task[i][0]);
    //   printf("child no %d whose PID=%d parentid=%d \n",i+1,getpid(),getppid());
    execvp(task[i][0], task[i]);
    perror("execvp failed");
     _exit(1);   

}
    }

    for (i = 0; i < 3; i++)
    {
        wait(NULL);
    }

}