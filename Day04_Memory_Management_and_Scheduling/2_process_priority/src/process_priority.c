#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>


void cpu_task(const char *name)
{
    for (long i = 0; i < 500; i++) {
        if (i % 10000 == 0) {
            printf("Process %s (PID=%d) running\n", name, getpid());
        }
    }
}
int main()
{
    pid_t pid1,pid2,pid3;

    pid1 = fork();
    if(pid1==0)
    {
        setpriority(PRIO_PROCESS,0,-10);
        cpu_task("HIGH");
    }
    pid2 = fork();
     if(pid2==0)
    {
        setpriority(PRIO_PROCESS,0,0);
        cpu_task("MEDIUM");
    }
    pid3 = fork();
     if(pid3==0)
    {
        setpriority(PRIO_PROCESS,0,10);
        cpu_task("LOW");
    }

   wait(NULL);
   wait(NULL);
   wait(NULL);
   
   return 0;

}