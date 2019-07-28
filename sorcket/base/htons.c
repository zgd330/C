#include <fun.h>



int main(int argc,char*argv[])
{
    ARGS_CHECK(argc,2);
    short port=atoi(argv[1]);
    short nport=htons(port);
    printf("nport=%x\n",nport);
    port=0;
    port =htons(nport);
    printf("port=%x\n",port);
    return 0;
}

