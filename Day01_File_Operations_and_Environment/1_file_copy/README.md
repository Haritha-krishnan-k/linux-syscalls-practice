file descriptor based 
    -open()
    -close()
    -read()
    -write()



-open()
    -int open(const char *pathname,int flag , mode_t mode)
    -pathname -filename
    -flags - O_CREATE , O_WRONLY , O_RDWR , O_APPEND  , O_TRUNC , O_RDONLY
    -0644 , 0400
    -the success output is always 0
-close()
    -int close(int fd)
-read()
    -ssize_t read(int fd , void *buf , size_t count)
    -fd -file descriptor
    -buf- buffer to store data
    -count- maximum no of bytes to read 
-write()
    -ssize_t write(int fd , const void *buf , ssize_t count)
    -fd - file descriptor
    -buf -buffer to store data
    -size_t - number of bytes write

