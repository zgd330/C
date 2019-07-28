#include <fun.h>

typedef struct{
    pthread_mutex_t mutex;
}Data_t;
void * threadFunc(void*p)
{
    int ret;
    Data_t*pArg=(Data_t*)p;
    ret=pthread_mutex_unlock(&pArg->mutex);
    CHILD_PTHREAD_ERROR_CHECK(ret,"pthread_mutex_unlock");
    pthread_mutex_lock(&pArg->mutex);
    printf("i am child lock success\n"); 
    pthread_exit(NULL); 
}

int main(int argc,char* argv[])
{
    int ret;
    Data_t threadInfo;
    pthread_t pthid;
    pthread_mutex_init(&threadInfo.mutex,NULL);
    ret=pthread_create(&pthid,NULL,threadFunc,&threadInfo);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    pthread_mutex_lock(&threadInfo.mutex);
    printf("main thread lock success\n");
    pthread_join(pthid,NULL);
    return 0;
}

