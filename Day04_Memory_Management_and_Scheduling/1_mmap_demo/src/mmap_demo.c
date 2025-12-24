#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    struct stat sb;
    char *mapped;

    fd = open("example.txt",O_RDWR);
    if(fd == -1)
    {
        perror("open");
        return 1;
    }

    // if (stat("example.txt", &sb) == -1) {
    //     perror("stat");
    //     close(fd);
    //     return 1;
    // }


        if (fstat(fd, &sb) == -1) {
        perror("fstat");
        close(fd);
        return 1;
    }

    mapped = mmap(NULL,sb.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(mapped ==MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        return 1;
    }

    printf("Original content:\n%s\n", mapped);
    strcpy(mapped, "Memory mapped file updated!\n");
    msync(mapped, sb.st_size, MS_SYNC);
    printf("changes content:\n%s\n", mapped);
    munmap(mapped, sb.st_size);

    printf("Inode: %ld\n", sb.st_ino);
    printf("Size: %ld bytes\n", sb.st_size);
    printf("Links: %ld\n", sb.st_nlink);
    printf("UID: %d\n", sb.st_uid);
    printf("GID: %d\n", sb.st_gid);

}