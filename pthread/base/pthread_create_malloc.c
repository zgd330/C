#include <fun.h>
void* threadFunc(void* p)//线程函数
{
    printf("i am child thread %d\n",*(int*)p);
}
int main(int argc,char *argv[])
{
    pthread_t pthid1,pthid2;
    int ret;
    int val=10;
    
    ret=pthread_create(&pthid1,NULL,threadFunc,&val);
    THREAD_ERROR_CHECK(ret,"pthread_create");//创建线程封装到THREAD_ERROR_CHECK
    val=2;

    ret=pthread_create(&pthid2,NULL,threadFunc,&val);
    pthread_join(pthid1,NULL);//等待子线程 
    pthread_join(pthid2,NULL);//等待子线程 
    printf("i am main thread\n");
    return 0;
}

