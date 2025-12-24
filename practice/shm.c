#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define SHM_NAME "/my_shm"

int main()
{
    int fd;

    fd = shm_open(SHM_NAME,O_CREAT|O_RDWR,0666);
    if(fd == -1)
    {
        perror("shm_open");
        return 1;
    }

    if(ftruncate(fd,sizeof(int)) == -1)
    {
        perror("ftrucate");
        return 1;
    }

    printf("shared memory created and size set\n");
    close(fd);
}