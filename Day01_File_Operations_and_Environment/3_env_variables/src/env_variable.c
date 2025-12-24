#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *path_value , *value;
    path_value = getenv("HOME");
    // printf("pathvalue %s\n",path_value);
    if(path_value != NULL)
    {
        printf("PATH=%s\n",path_value);
    }
    else
    {
        printf("PATH variable not found\n");
    }

    if(setenv("MY_VAR","linux_system_programming",1)!=0)
    {
      perror("setenv failed");
      return EXIT_FAILURE;
    }
    value = getenv("MY_VAR");
    printf("SETENV Value= %s\n",value);
}
