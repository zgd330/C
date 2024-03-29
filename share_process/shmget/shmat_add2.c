#include <fun.h>

int main(int argc,char*argv[])
{
    int semArrId=semget(1000,1,IPC_CREAT|0600);
    ERROR_CHECK(semArrId,-1,"semget");
    int shmid;
    shmid=shmget(1000, 1<<20,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    int* p;
    p=(int*)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(int*)-1,"shmat");
   struct sembuf sopp,sopv;
   sopp.sem_num=0;
   sopp.sem_op=-1;
   sopp.sem_flg=SEM_UNDO;
   sopv.sem_num=0;
   sopv.sem_op=1;
   sopv.sem_flg=SEM_UNDO;
    if (!fork())
    {
        for(int i=0;i<100000000;i++)
        {
            semop(semArrId,&sopp,1);
            p[0]=p[0]+1;
            semop(semArrId,&sopv,1);
        }
    }else{
        for(int i=0;i<100000000;i++)
        {

            semop(semArrId,&sopp,1);
            p[0]=p[0]+1;
            semop(semArrId,&sopv,1);
        }
        wait(NULL);
        printf("result=%d\n",*p);
    }
    return 0;
}
