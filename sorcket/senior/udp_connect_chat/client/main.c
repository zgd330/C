#include <fun.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in sockAddr;
    bzero(&sockAddr,sizeof(sockAddr));
    sockAddr.sin_family=AF_INET;
    sockAddr.sin_port=htons(atoi(argv[2]));
    sockAddr.sin_addr.s_addr=inet_addr(argv[1]);
    char buf[128]={0};
    sendto(socketFd,"1",1,0,(struct sockaddr*)&sockAddr,sizeof(struct sockaddr));
    fd_set rdset;
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(socketFd,&rdset);
        select(socketFd+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset))
        {
            bzero(buf,sizeof(buf));
            read(STDIN_FILENO,buf,sizeof(buf));
            sendto(socketFd,buf,strlen(buf)-1,0,(struct sockaddr*)&sockAddr,sizeof(sockAddr));
        }
        if(FD_ISSET(socketFd,&rdset))
        {
            bzero(buf,sizeof(buf));
            recvfrom(socketFd,buf,sizeof(buf),0,NULL,NULL);
            printf("%s\n",buf);
        }

    }
    close(socketFd);
    return 0;
}
