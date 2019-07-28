#include <fun.h>

int main(int argc,char*argv[])
{
    int shmid;
    shmid=shmget(1000, 1<<20,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    char* p;
    p=(char*)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(char*)-1,"shmat");
    strcpy(p,"hello");
    printf("Hello world\n");
    while(1);
    return 0;
}
