#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

#define BUFFER_SIZE 0124


int main(int argc , char* argv[])
{
 
    int src_fd , dest_fd;
    char *src_file;
    char *dest_file;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read , bytes_written;

    if(argc !=3 )
    {
        fprintf(stderr,"Use <source_file> <destinaton_file>\n");
        return EXIT_FAILURE ;
    }
    
    src_file = argv[1];
    dest_file = argv[2];

    src_fd = open(src_file,O_WRONLY|O_CREAT,0644);
    if(src_fd <0)
    {
        perror("error creating source file");
        return EXIT_FAILURE ;
    }
    write(src_fd, "This is a sample file created programmatically.\n", 50);
    close(src_fd);

    src_fd = open(src_file,O_RDONLY);
    if(src_fd < 0)
    {
        perror("error opening source file");
        return EXIT_FAILURE;
    }

    dest_fd = open(dest_file , O_WRONLY|O_CREAT, 0644);
    if(dest_fd <0)
    {
        perror("error opening destination file");
        close(src_fd);
        return EXIT_FAILURE ;
    }

     while((bytes_read = read(src_fd , buffer , BUFFER_SIZE))>0)
     {
       printf("source data");
       bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read)
        {
            perror("Write error");
            close(src_fd);
            close(dest_fd);
            return EXIT_FAILURE;
        }
     }
    
    src_fd = open(src_file, O_RDONLY);
    printf("Contents of source file (%s):\n", src_file);
    while((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0)   
    {    
    write(1, buffer, bytes_read);
    }
    
    close(src_fd);
    printf("\n\n");

    dest_fd = open(dest_file, O_RDONLY);
    printf("Contents of destination file (%s):\n", dest_file);
    while((bytes_read = read(dest_fd, buffer, BUFFER_SIZE)) > 0)
    {   
    write(1, buffer, bytes_read);
    }
    close(dest_fd);
    printf("\n");



    return EXIT_SUCCESS;


}