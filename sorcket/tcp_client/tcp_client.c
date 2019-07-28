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
    send(socketFd,"i hen mei",9,0);
    char buf[1024]={0};
    recv(socketFd,buf,sizeof(buf),0);
    printf("client gets %s\n",buf);
    close(socketFd);
    return 0;
}

