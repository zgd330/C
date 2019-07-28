#include <fun.h>

typedef struct{
    pthread_mutex_t mutex;
}Data_t;
void * threadFunc(void*p)
{
    int ret;
    Data_t*pArg=(Data_t*)p;
    ret=pthread_mutex_lock(&pArg->mutex);
    CHILD_PTHREAD_ERROR_CHECK(ret,"pthread_mutex_lock");
    printf("i am child lock success\n");
    sleep(1);
    pthread_mutex_unlock(&pArg->mutex);
    printf("you can't see me\n");
    pthread_exit(NULL); 
}

int main(int argc,char* argv[])
{
    int ret;
    Data_t threadInfo;
    pthread_t pthid1,pthid2;
    pthread_create(&pthid1,NULL,threadFunc,&threadInfo);
    pthread_create(&pthid2,NULL,threadFunc,&threadInfo);
    ret=pthread_cancel(pthid1);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    ret=pthread_cancel(pthid2);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    long threadret;
    pthread_join(pthid2,(void**)&threadret);
    printf("pthlid1 ret=%ld",threadret);
    pthread_join(pthid1,(void**)&threadret);
    printf("pthlid2 ret=%ld",threadret);
    return 0;
}

