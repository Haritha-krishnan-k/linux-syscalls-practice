#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>

int main()
{
      mkdir("mydir", 0755);

    // 2. Create a file inside directory
    int fd = open("mydir/file.txt", O_CREAT | O_WRONLY, 0644);
    int res= write(fd, "Embedded Linux\n", 16);
    // printf("%d\n",res);
    close(fd);

    DIR *dir = opendir("mydir");
    struct dirent *entry;
    // printf("Directory content");
    while((entry = readdir(dir))!=NULL)
    {
        printf("%s\n",entry->d_name);
    }

    closedir(dir);

    unlink("mydir/file.txt");
    return 0;

}
