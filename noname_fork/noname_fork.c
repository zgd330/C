#include <fun.h>
int main()
{
    int fds[2]={0};
    pipe(fds);
    char buf[128]={0};

    if(!fork())
    {
        close(fds[0]);
        write(fds[1],"hello",6);
        // printf("I am child \n");
        // while(1);
        close(fds[1]);
        return 0;
    }else
    {
        close(fds[1]);
        //printf("I am parent \n");
        if (read(fds[0],buf,sizeof(buf))>0)
        {
            printf("%s",buf);
        }
        waitpid(-1,NULL,0);
        close(fds[0]);
        return 0;
    }
}

