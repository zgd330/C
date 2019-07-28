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
    fd_set rdset;
    char buf[1024];
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(socketFd,&rdset);
        ret=select(socketFd+1,&rdset,NULL,NULL,NULL);
        if (ret>0)
        {
            if(FD_ISSET(STDIN_FILENO,&rdset))
            {
                bzero(buf,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf));
                if(ret==0)
                {
                    printf("bybe4\n");
                    break;
                }
                send(socketFd,buf,strlen(buf)-1,0);

            }
            if(FD_ISSET(socketFd,&rdset))
            {
                bzero(buf,sizeof(buf));
                ret=recv(socketFd,buf,sizeof(buf),0);
                if(ret==0)
                {
                    printf("bybe3\n");
                    break;
                }
                printf("%s\n",buf);
            }
        }
    }
    close(socketFd);
}

