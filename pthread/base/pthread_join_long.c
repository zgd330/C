#include <fun.h>
void* threadFunc(void* p)//线程函数
{
    printf("i am child thread\n");
    pthread_exit((void*)10);
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    int ret;
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");//创建线程封装到THREAD_ERROR_CHECK
    long threadRet;
    ret=pthread_join(pthid,(void**)&threadRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");//创建线程封装到THREAD_ERROR_CHECK
    printf("i am main thread %ld\n",threadRet);
    return 0;
}

