#include <fun.h>

#define N 20000000

typedef struct{
    int val;
    pthread_mutex_t mutex;
}Data_t;

void* threadFunc(void* p)//线程函数
{
    int i;
    Data_t *pVal=(Data_t*)p;
    for(i=0;i<N;i++)
    {
        pthread_mutex_lock(&pVal->mutex);
        pVal->val+=1;
        pthread_mutex_unlock(&pVal->mutex);
    }
    printf("i am child thread %d\n",pVal->val);
}

int main(int argc,char *argv[])
{
    pthread_t pthid1;
    int ret;
    Data_t threadInfo;
    threadInfo.val=0;
    ret=pthread_mutex_init(&threadInfo.mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    struct timeval start,end;
    gettimeofday(&start,NULL);
    ret=pthread_create(&pthid1,NULL,threadFunc,&threadInfo);
    THREAD_ERROR_CHECK(ret,"pthread_create");//创建线程封装到THREAD_ERROR_CHECK
    for (int i=0;i<N;i++)
    {
        pthread_mutex_lock(&threadInfo.mutex);
        threadInfo.val+=1;
        pthread_mutex_unlock(&threadInfo.mutex);
    }
    pthread_join(pthid1,NULL);//等待子线程 
    gettimeofday(&end,NULL);
    printf("i am main thread %d,usetime=%ld \n",threadInfo.val,(end.tv_sec-start.tv_sec)*1000000+end.tv_sec-start.tv_sec);
    return 0;
}

