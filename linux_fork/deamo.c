#include <fun.h>

int main()
{
    if(!fork())
    {
        printf("i am child,uid=%d,gid=%d,pgid=%d,sid=%d",getuid(),getgid(),getpgid(),getsid());        
    }else
    {
        exit(0);

        return 0;
    }
}

