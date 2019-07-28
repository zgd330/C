#include <fun.h>

#define N 10000000
void* threadFunc(void* p)//线程函数
{
    for(int i=0;i<N;i++)
    {
        *(int*)p+=1;
    }
    printf("i am child thread %d\n",*(int*)p);
}
int main(int argc,char *argv[])
{
    pthread_t pthid1;
    int ret;
    int val=0;
    
    ret=pthread_create(&pthid1,NULL,threadFunc,&val);
    THREAD_ERROR_CHECK(ret,"pthread_create");//创建线程封装到THREAD_ERROR_CHECK
    for (int i=0;i<N;i++)
    {
        val+=1;
    }
    pthread_join(pthid1,NULL);//等待子线程 
    printf("i am main thread %d \n",val);
    return 0;
}

