#include <fun.h>

int main(int argc,char*argv[])
{
    int shmid;
    shmid=shmget(1000,1<<20,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    printf("Hello world\n");
    return 0;
}
