#include <fun.h>
int tcpInit(int *sfd,char*ip,char*port)
{      
    int socketFd=socket(AF_INET,SOCK_STREAM,0); 
    struct sockaddr_in sockAddr;
    bzero(&sockAddr,sizeof(sockAddr));
    sockAddr.sin_family=AF_INET;
    sockAddr.sin_port=htons(atoi(port));
    sockAddr.sin_addr.s_addr=inet_addr(ip);
    int ret;
    ret=bind(socketFd,(struct sockaddr*)&sockAddr,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(socketFd,10);
    *sfd=socketFd;
    return 0;
}

