#include <fun.h>

int main()
{
    printf("Parent process id: %d\n",getpid());
    int i=fork();
    if (i==0)
    {
        printf("child process id %d\n",getpid());
        while(1);
    }else
    {
        printf("parent process success,child :%d\n",i);
        while(1);
    }
    return 0;
}
