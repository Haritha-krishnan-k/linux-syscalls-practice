#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

int main()
{
    int fd;
    fd = open("permission_demo.txt",O_CREAT|O_RDONLY,0400);
    if(fd<0)
    {
        perror("file creation failed\n");
        return EXIT_FAILURE;
    }
    close(fd);
    printf("file created with read-only permission for owner\n");
    if(chmod("permission_demo.txt",0600)<0)
    {
        perror("chmod failed");
        return EXIT_FAILURE;
    }

    printf("file permission changed to read-write for owner\n");
    return EXIT_SUCCESS;
}