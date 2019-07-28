#include <fun.h>

int main(int argc,char*argv[])
{
    int shmid;
    shmid=shmget(1000, 1<<20,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    int* p;
    p=(int*)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(int*)-1,"shmat");
    if (!fork())
    {
        for(int i=0;i<100000000;i++)
        {
            p[0]=p[0]+1;
        }
    }else{
        for(int i=0;i<100000000;i++)
        {
            p[0]=p[0]+1;
        }
        wait(NULL);
        printf("result=%d\n",*p);
    }
    return 0;
}
