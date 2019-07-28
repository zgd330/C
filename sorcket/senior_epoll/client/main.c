#include <fun.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in sockAddr;
    bzero(&sockAddr,sizeof(sockAddr));
    sockAddr.sin_family=AF_INET;
    sockAddr.sin_port=htons(atoi(argv[2]));
    sockAddr.sin_addr.s_addr=inet_addr(argv[1]);
    int ret;
    ret=connect(socketFd,(struct sockaddr*)&sockAddr,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"connect");
    char buf[1024];
    int epfd=epoll_create(1);
    struct epoll_event event,evs[2];
    event.events=EPOLLIN;//监听读事件
    event.data.fd=STDIN_FILENO;
    event.data.fd=socketFd;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int readyFdcount,i;
    while(1)
    {
        readyFdcount=epoll_wait(epfd,evs,2,-1);
        for (i=0;i<readyFdcount;i++)
        {
            if(evs[i].data.fd==STDIN_FILENO)
            {
                bzero(buf,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf)-1);
                if(ret==0)
                {
                    printf("bybe4\n");
                }
                send(socketFd,buf,strlen(buf)-1,0);

            }
            if(evs[i].data.fd==socketFd)
            {
                bzero(buf,sizeof(buf));
                ret=recv(socketFd,buf,sizeof(buf)-1,0);
                if(ret==0)
                {
                    printf("bybe3\n");
                    goto end;
                }
                printf("%s\n",buf);
            }
        }
    }
end:
    close(socketFd);
}

