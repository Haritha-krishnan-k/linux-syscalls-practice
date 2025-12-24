file descriptor and permission based:
    -open()
    -close()
    -chmod()

-open()
    -int open(const char *pathname,int flag , mode_t mode)
    -pathname -filename
    -flags - O_CREATE , O_WRONLY , O_RDWR , O_APPEND  , O_TRUNC , O_RDONLY
    -0644 , 0400
    -the success output is always 0
-close()
    -int close(int fd)
-chmod()
    -int chmod(const char *pathname , mode_t mode)