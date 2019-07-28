#include <fun.h>
typedef struct{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}Data_t,*pData_t;

void *threadFunc(void*p)
{
    pData_t pAry=(pData_t)p;
    struct timespec t;
    t.tv_sec=time(NULL)+3;
    t.tv_nsec=0;
    int ret;
    pthread_mutex_lock(&pAry->mutex);
    ret=pthread_cond_timedwait(&pAry->cond,&pAry->mutex,&t);
   // pthread_cond_wait(&pAry->cond,&pAry->mutex);
    pthread_mutex_unlock(&pAry->mutex);
    printf("i am child thread wake up=%d\n",ret);
    pthread_exit(NULL);
}

int main(int argc,char*argv[])
{
    pthread_t pthid;
    Data_t threadInfo;
    pthread_mutex_init(&threadInfo.mutex,NULL);
    pthread_cond_init(&threadInfo.cond,NULL);
    pthread_create(&pthid,NULL,threadFunc,&threadInfo);
    pthread_cond_signal(&threadInfo.cond);
    pthread_join(pthid,NULL);
    printf("I am main thread\n");
    return 0;
}

