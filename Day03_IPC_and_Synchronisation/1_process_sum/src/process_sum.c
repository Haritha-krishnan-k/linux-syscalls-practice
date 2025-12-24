#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <semaphore.h>

#define SHM_NAME "/my_shm"
#define MAX_NUMBERS 10

typedef struct 
{
    int number[MAX_NUMBERS];
    int index;
    int sum;
    sem_t sem;
}shm_data_t;

int main()
{
    int fd;
    shm_data_t *shm;

    fd = shm_open(SHM_NAME , O_CREAT|O_RDWR,0666);
    if(fd == -1)
    {
        perror("shm_open");
        exit(1);
    }
    if(ftruncate(fd,sizeof(shm_data_t))==-1)
    if(fd ==-1)
    {
       perror("ftruncate");
       exit(1);
    }

    shm = mmap(NULL , sizeof(shm_data_t),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(shm == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }
    shm->index = 0;
    shm->sum = 0;

    sem_init(&shm->sem,1,0);

    pid_t pid = fork();

    if(pid == 0)
    {
        for(int i=0;i<MAX_NUMBERS;i++)
        {
            shm->index = i;
            shm->number[i] = i+1;
            printf("the count : %d and Child wrote: %d\n", shm->index,shm->number[i]);
            sem_post(&shm->sem);
            sleep(1);
        }

        exit(0);
    }
    else
    {
      printf("the parent is printing the value\n");
      for(int i=0;i<MAX_NUMBERS;i++)
      {
        sem_wait(&shm->sem);
        shm->sum += shm->number[i];
        printf("the sum is %d for the read %d\n",shm->sum,shm->number[i]);
      }
      wait(NULL);
      printf("\nFinal Sum = %d\n", shm->sum);
    //   printf("\n");
    }

    sem_destroy(&shm->sem);
    munmap(shm, sizeof(shm_data_t));
    close(fd);
    shm_unlink(SHM_NAME);

    return 0;

}
