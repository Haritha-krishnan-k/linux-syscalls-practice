#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

#define NUM_THREADS 5
#define INCREMENTS 100000

atomic_int counter = 0;

void* increment_counter(void *arg)
{
    for(int i=0;i<INCREMENTS;i++)
    {
        atomic_fetch_add(&counter,1);
    }

}

int main()
{
    pthread_t threads[NUM_THREADS];

    for(int i=0;i<NUM_THREADS;i++)
    {
        pthread_create(&threads[i],NULL,increment_counter,NULL);
    }

    for(int i=0;i<NUM_THREADS;i++)
    {
         pthread_join(threads[i],NULL);
    }

    printf("Final counter value : %d\n",counter);
}
