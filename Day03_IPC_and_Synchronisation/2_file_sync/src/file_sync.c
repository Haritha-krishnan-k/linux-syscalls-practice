#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define PATH_MAX_LEN 1024
#define BUFFER_SIZE 4096

int copy_file(const char *src, const char *dst) {
    FILE *fs = fopen(src, "rb");
    if (!fs) {
        perror("fopen src");
        return -1;
    }
    FILE *fd = fopen(dst, "wb");
    if (!fd) {
        perror("fopen dst");
        fclose(fs);
        return -1;
    }

    char buffer[BUFFER_SIZE];
    size_t n;
    while ((n = fread(buffer, 1, BUFFER_SIZE, fs)) > 0) {
        fwrite(buffer, 1, n, fd);
    }

    fclose(fs);
    fclose(fd);
    return 0;
}

int files_are_same(const char *f1, const char *f2) {
    FILE *file1 = fopen(f1, "rb");
    FILE *file2 = fopen(f2, "rb");

    if (!file1 || !file2) {
        if(file1) fclose(file1);
        if(file2) fclose(file2);
        return 0; 
    }

    int result = 1; 
    char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
    size_t n1, n2;

    while (1) {
        n1 = fread(buf1, 1, BUFFER_SIZE, file1);
        n2 = fread(buf2, 1, BUFFER_SIZE, file2);

        if (n1 != n2 || memcmp(buf1, buf2, n1) != 0) {
            result = 0; 
            break;
        }
        if (n1 == 0) break; 
    }

    fclose(file1);
    fclose(file2);
    return result;
}

void sync_directories(const char *src_dir , const char *dst_dir)
{
    DIR *src = opendir(src_dir);
    if (!src) {
        perror("opendir source");
        return;
    }
    mkdir(dst_dir, 0755);

    struct dirent *entry;

    while (((entry = readdir(src)) )!= NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue; 
}

        char src_path[PATH_MAX_LEN];
        char dst_path[PATH_MAX_LEN];

        snprintf(src_path, PATH_MAX_LEN, "%s/%s", src_dir, entry->d_name);
        snprintf(dst_path, PATH_MAX_LEN, "%s/%s", dst_dir, entry->d_name);
        
        struct stat st;
        
        if (stat(src_path, &st) == -1) {
            perror("stat");
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
           
            sync_directories(src_path, dst_path);
        } else if (S_ISREG(st.st_mode)) {
           
            if (access(dst_path, F_OK) != 0 || !files_are_same(src_path, dst_path)) {
                printf("Copying %s -> %s\n", src_path, dst_path);
                copy_file(src_path, dst_path);
            }
        }

    closedir(src);
}


int main(int argc , char *argv[])
{
    if(argc != 3)
    {
        printf("source , destination error");
        return 1;
    }
    sync_directories(argv[1],argv[2]);
    printf("synchronisation completed\n");
    return 0;
}