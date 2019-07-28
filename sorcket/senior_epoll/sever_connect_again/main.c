#include <fun.h>

int tcpInit(int *,char*,char*);
int main(int argc,char*argv[])
{
    int socketFd;
    ARGS_CHECK(argc,3);
    tcpInit(&socketFd,argv[1],argv[2]);
    int newFd;
    int ret;
    char buf[1024];
    int epfd=epoll_create(1);
    struct epoll_event event,evs[2];
    event.events=EPOLLIN;
    event.data.fd=STDIN_FILENO;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    event.data.fd=socketFd;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int readyFdCount,i;
    while(1)
    {

        readyFdCount=epoll_wait(epfd,evs,3,-1);
        for(i=0;i<readyFdCount;i++)
        {
            if (evs[i].data.fd==socketFd)
            {
                newFd=accept(socketFd,NULL,NULL);
                event.data.fd=newFd;
                ret=epoll_ctl(epfd,EPOLL_CTL_ADD,newFd,&event);
                ERROR_CHECK(ret,-1,"epoll_ctl");
            }
            if(evs[i].data.fd==STDIN_FILENO)
            {
                bzero(buf,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf)-1);
                if(ret==0)
                {
                    printf("bybe2\n");
                    goto end;
                }
                send(newFd,buf,strlen(buf)-1,0);
            }
            if(evs[i].data.fd==newFd)
            {
                bzero(buf,sizeof(buf));
                ret=recv(newFd,buf,sizeof(buf)-1,0);
                if(ret==0)
                {
                    printf("bybe1\n");
                    event.data.fd=newFd;
                    ret=epoll_ctl(epfd,EPOLL_CTL_DEL,newFd,&event);
                    ERROR_CHECK(ret,-1,"epoll_ctl");
                    close(newFd);
                    break;
                }
                printf("%s\n",buf);
            }
        }
    }
end:
    close(socketFd);
    return 0;
}

