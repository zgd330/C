#include <fun.h>
typedef struct{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}Data_t,*pData_t;

void cleanup(void*p)
{
    pthread_mutex_unlock((pthread_mutex_t *)p);
    printf("unlock ok\n");
}


void *threadFunc(void*p)
{
    pData_t pAry=(pData_t)p;
    pthread_mutex_lock(&pAry->mutex);
    pthread_cleanup_push(cleanup,&pAry->mutex);
    printf("start wait\n");
    pthread_cond_wait(&pAry->cond,&pAry->mutex);
    printf("wait return\n");
    pthread_cleanup_pop(1);
    printf("i am child thread wake up\n");
    pthread_exit(NULL);
}

#define N 2

int main(int argc,char*argv[])
{
    int i,j;
    pthread_t pthid[N];
    Data_t threadInfo;
    pthread_mutex_init(&threadInfo.mutex,NULL);
    pthread_cond_init(&threadInfo.cond,NULL);
    for(i=0;i<N;i++)
    {
        pthread_create(pthid+i,NULL,threadFunc,&threadInfo);
    }
    int ret;
    usleep(5000);
    for(i=0;i<N;i++)
    {
       ret=pthread_cond_signal(&threadInfo.cond);
       THREAD_ERROR_CHECK(ret,"pthread_cond_signal");
    }   

    for(i=0;i<N;i++)
    {
        pthread_join(pthid[i],NULL);
    }
    printf("I am main thread\n");
    return 0;
}

