#include <fun.h>


int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd;
    int ret;
    socketFd=socket(AF_INET,SOCK_DGRAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in saddr;
    bzero(&saddr,sizeof(saddr));
    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(atoi(argv[2]));
    saddr.sin_addr.s_addr=inet_addr(argv[1]);
    ret=bind(socketFd,(struct sockaddr*)&saddr,sizeof(saddr));//一旦bind,端口就激活
    ERROR_CHECK(ret,-1,"bind");
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    socklen_t fromlen=sizeof(struct sockaddr);
    char buf[1024]={0};
    recvfrom(socketFd,buf,sizeof(buf),0,(struct sockaddr*)&client,&fromlen);
    printf("client ip=%s,client port=%d",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    sendto(socketFd,"i hen niu",9,0,(struct sockaddr*)&client, sizeof(client));
    close(socketFd);
    return 0;

}

