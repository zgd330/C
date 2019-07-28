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
    char buf[128]={0};
    recvfrom(socketFd,buf,sizeof(buf),0,(struct sockaddr*)&client,&fromlen);
    printf("gets %s , client ip=%s,client port=%d",buf,inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    fd_set rdset;
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(socketFd,&rdset);
        ret=select(socketFd+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset))
        {
            bzero(buf,sizeof(buf));
            read(STDIN_FILENO,buf,sizeof(buf)-1);
            sendto(socketFd,buf,strlen(buf)-1,0,(struct sockaddr*)&client,sizeof(client));
        }
        if(FD_ISSET(socketFd,&rdset))
        {
            bzero(buf,sizeof(buf));
            recvfrom(socketFd,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&fromlen);
            printf("%s\n",buf);
        }
    }
    close(socketFd);
    return 0;
}

