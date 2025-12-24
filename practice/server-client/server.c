#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sock;
    char buf[100];

    sock = socket(AF_INET , SOCK_STREAM , 0);

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = inet_addr("127.0.0.1")
    };

    connect(sock,(struct sockaddr *)&addr,sizeof(addr));

    strcpy(buf,"hello from client");
    write(sock,buf,strlen(buf)+1);

    read(sock,buf,sizeof(buf));
    printf("client got : %s\n",buf);

    close(sock);

}