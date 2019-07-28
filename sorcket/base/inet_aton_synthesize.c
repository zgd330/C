#include <fun.h>



int main()
{
    char ip[]="192.168.5.175";
    struct in_addr myaddr;
    int ret;
    ret =inet_aton(ip,&myaddr);
    printf("%x\n",myaddr.s_addr);
    printf("%x\n",inet_addr(ip));
    return 0;
}

