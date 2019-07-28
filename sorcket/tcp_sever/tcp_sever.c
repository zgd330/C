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
    ret=bind(socketFd,(struct sockaddr*)&sockAddr,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(socketFd,10);
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    socklen_t clientlen=sizeof(client);
    int newFd=accept(socketFd,(struct sockaddr*)&client,&clientlen);
    printf("client_ip=%s,client_port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    char buf[1024]={0};
    recv(newFd,buf,sizeof(buf),0);
    printf("server get %s\n",buf);
    send(newFd,"i hen niu",9,0);
    close(socketFd);
    return 0;
}

