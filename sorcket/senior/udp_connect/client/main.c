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
   // int ret;
    char buf[1024];
    sendto(socketFd,"shide",5,0,(struct sockaddr*)&sockAddr,sizeof(struct sockaddr));
    recvfrom(socketFd,buf,sizeof(buf),0,NULL,NULL);
    printf("client gets the buf %s\n",buf);
    close(socketFd);
    return 0;
}
