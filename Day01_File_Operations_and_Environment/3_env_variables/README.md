environment variable based
    -getenv()
    -setenv()

-getenv()
    -char *getenv(const char *name)
    -name - name of the environment variable
-setenv()
    -int setenv(const char *name , const char *value , int overwrite)
    -name - name of the environment variable to set
    -value - value to assign
    -overwrite - 1 -overwrite if exists 0 - do not overwrite