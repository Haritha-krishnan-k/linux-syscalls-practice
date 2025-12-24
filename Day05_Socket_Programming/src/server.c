#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

void reverse_string(char *str)
{

    int i,j;
    char temp;
    for(i=0,j=strlen(str)-1;i<j;i++,j--)
    {
        temp=str[i];
        str[i]=str[j];
        str[j]=temp;
    }
}

int main()
{
    int sfd, cfd;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];

    sfd = socket(AF_INET , SOCK_STREAM,0);
    if(sfd<0)
    {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr =  INADDR_ANY;
    
    if(bind(sfd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        perror("bind");
        exit(1);
    }

    listen(sfd,5);

    printf("Server listening on port %d\n",PORT);
    cfd = accept(sfd,NULL,NULL);
    if(cfd<0)
    {
        perror("accept");
        exit(1);
    }
    
    read(cfd,buffer,BUF_SIZE);
    
    printf("server received %s\n",buffer);
    reverse_string(buffer);
    write(cfd,buffer,strlen(buffer)+1);

    close(cfd);
    close(sfd);
    return 0;

}