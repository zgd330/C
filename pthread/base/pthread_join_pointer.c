#include <fun.h>
void* threadFunc(void* p)//线程函数
{
    p=malloc(20);
    strcpy((char*)p,"i hen niu");
    printf("i am child thread %s\n",(char*)p);
    pthread_exit(p);
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    int ret;
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");//创建线程封装到THREAD_ERROR_CHECK
    char *pRet;
    ret=pthread_join(pthid,(void**)&pRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");//创建线程封装到THREAD_ERROR_CHECK
    printf("i am main thread %s\n",pRet);
    return 0;
}

