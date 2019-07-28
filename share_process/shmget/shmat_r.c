#include <fun.h>

int main(int argc,char*argv[])
{
    int shmid;
    shmid=shmget(1000, 1<<20,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    char* p;
    p=(char*)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(char*)-1,"shmat");
    if (!fork())
    {
        puts(p);
    }else{
        strcpy(p,"how are you");
        wait(NULL);
    }

    shmctl(shmid, IPC_RMID, 0);
    return 0;
}
