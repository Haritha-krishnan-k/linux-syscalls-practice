#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define SHM_NAME "/my_shm"
#define COUNT 10

int main()
{
    int fd;
    int *shared_mem;

    fd = shm_open(SHM_NAME,O_CREAT|O_RDWR,0666);
    if(fd == -1)
    {
        perror("shm_open");
        return 1;
    }

    if(ftruncate(fd,COUNT*sizeof(int)) == -1)
    {
        perror("ftrucate");
        return 1;
    }

    shared_mem = mmap(NULL,COUNT*sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(shared_mem == MAP_FAILED)
    {
        perror("mmap");
        return 1;
    }

    pid_t pid = fork();

    if(pid==0)
    {
        for(int i=0;i<COUNT;i++)
        {
            shared_mem[i] = i*1;
            printf("child wrote :%d\n",shared_mem[i]);
            sleep(1);
        }
        exit(0);
    }
    else{
        wait(NULL);
        printf("parent reading shared memory");
        for(int i=0;i<COUNT;i++)
        {
            printf("%d",shared_mem[i]);
        }
        printf("\n");
    }

    munmap(shared_mem, COUNT * sizeof(int));
    close(fd);
    shm_unlink(SHM_NAME);

    return 0;
}