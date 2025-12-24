#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sfd ,cfd;
    char buf[100];

    sfd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in addr = {
        .sin_family =AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr =INADDR_ANY
    };

    bind(sfd,(struct sockaddr *)&addr,sizeof(addr));
    listen(sfd,1);

    printf("server waiting \n");
    cfd = accept(sfd,NULL,NULL);

    read(cfd,buf,sizeof(buf));
    printf("server got %s\n",buf);

    strcpy(buf,"hello from server");
    write(cfd,buf,strlen(buf)+1);

    close(cfd);
    close(sfd);
    return 0;
}


