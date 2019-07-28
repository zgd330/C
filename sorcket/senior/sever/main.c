#include <fun.h>

int tcpInit(int *,char*,char*);
int main(int argc,char*argv[])
{
    int socketFd;
    ARGS_CHECK(argc,3);
    tcpInit(&socketFd,argv[1],argv[2]);
    int newFd=accept(socketFd,NULL,NULL);
    fd_set rdset;
    int ret;
    char buf[1024];
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(newFd,&rdset);
        ret=select(newFd+1,&rdset,NULL,NULL,NULL);
        if (ret>0)
        {
            if(FD_ISSET(STDIN_FILENO,&rdset))
            {
                bzero(buf,sizeof(buf));
               ret=read(STDIN_FILENO,buf,sizeof(buf)-1);
               if(ret==0)
               {
                   printf("bybe2\n");
                   break;
               }
                send(newFd,buf,strlen(buf)-1,0);
            }
            if(FD_ISSET(newFd,&rdset))
            {
                bzero(buf,sizeof(buf));
                ret=recv(newFd,buf,strlen(buf)-1,0);
                if(ret==0)
                {
                    printf("bybe1\n");
                    break;
                }
                printf("%s\n",buf);
            }
        }
    }
    return 0;
}

