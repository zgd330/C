#include <fun.h>

int tcpInit(int *,char*,char*);
int main(int argc,char*argv[])
{
    int newFd;
    int socketFd;
    int ret;
    ARGS_CHECK(argc,3);
    ret=tcpInit(&socketFd,argv[1],argv[2]);
    if(-1==ret)
    {
        return -1;
    }
    fd_set rdset;
    fd_set needMoniterFd;//始终记录要监控的描述符
    char buf[1024];
    FD_ZERO(&needMoniterFd);
    FD_SET(STDIN_FILENO,&needMoniterFd);
    FD_SET(socketFd,&needMoniterFd);

    while(1)
    {
        memcpy(&rdset,&needMoniterFd,sizeof(fd_set));
        ret=select(14,&rdset,NULL,NULL,NULL);
        if (ret>0)
        {
            if(FD_ISSET(socketFd,&rdset))
            {
                newFd=accept(socketFd,NULL,NULL);
                ERROR_CHECK(newFd,-1,"accept");
                FD_SET(newFd,&needMoniterFd);
            }
            if(FD_ISSET(STDIN_FILENO,&rdset))
            {
                bzero(buf,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf));
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
                ret=recv(newFd,buf,sizeof(buf),0);
                if(ret==0)
                {
                    printf("bybe1\n");
                    FD_CLR(newFd,&needMoniterFd);
                    close(newFd);
                }else{
                    printf("%s\n",buf);
                }
            }
        }
    }
    return 0;
}

