#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main()
{
    int sock;
    struct sockaddr_in addr;
    char message[BUF_SIZE];
    char buffer[BUF_SIZE];

    sock =socket(AF_INET,SOCK_STREAM,0);
    if(sock<0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family=AF_INET;
    addr.sin_port=htons(PORT);
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(connect(sock,(struct sockaddr *)&addr,sizeof(addr))<0)
    {
        perror("connect");
        exit(1);
    }

    printf("enter message");
    fgets(message,BUF_SIZE,stdin);
    message[strcspn(message,'\n')]='\0';

    write(sock,buffer,BUF_SIZE);

    read(sock,buffer,BUF_SIZE);
    printf("reversed from server:%s\n",buffer);

    close(sock);
    return 0;
}
