#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <sys/wait.h>
#include <unistd.h>

#define QUEUE "/my_queue"

int main()
{
    mqd_t mq;
    char msg[] = "this is the message from message queue";
    char buffer[100];

    struct mq_attr attr = {
        .mq_maxmsg=10,
        .mq_msgsize=100
    };

    mq = mq_open(QUEUE,O_CREAT|O_RDWR ,0666,&attr);

    pid_t pid =fork();

    if(pid ==0)
    {
        sleep(1);
        mq_receive(mq,buffer,sizeof(buffer),NULL);
        printf("child received %s\n",buffer);
    }

    else
    {
       mq_send(mq,msg,strlen(msg)+1,1);
       wait(NULL);
       mq_close(mq);
       mq_unlink(QUEUE);

    }
    return 0;

}
