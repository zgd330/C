#include <fun.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    struct hostent *ptr;
    ptr=gethostbyname(argv[1]);
    if(ptr==0)
    {
        printf("ptr error\n");
        return -1;
    }
    printf("name=%s\n",ptr->h_name);
    printf("length=%d\n",ptr->h_length);
    printf("addrtype=%d\n",ptr->h_addrtype);
    for(int i=0;ptr->h_aliases[i]!=NULL;i++)
    {
        puts(ptr->h_aliases[i]);
    }
    char ip[16]={0};
    for(int i=0;ptr->h_addr_list[i]!=NULL;i++)
    {
        bzero(ip,sizeof(ip));
        inet_ntop(ptr->h_addrtype,ptr->h_addr_list[i],ip,sizeof(ip));
        puts(ip);

    }
    return 0;
}

