#include <fun.h>

//typedef struct{
//    pthread_mutex_t mutex;
//}Data_t;

//void * threadFunc(void *p)
//{
    //printf("i am child thread\n");
//}

int main(int argc,char* argvp[])
{
    int ret;
    //pthread_t pthid;
    pthread_mutex_t threadRet;
    pthread_mutexattr_t mutexattr;
    pthread_mutexattr_init(&mutexattr);
    pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_ERRORCHECK);//只允许同一个线程对同一把锁加锁多次
    pthread_mutex_init(&threadRet,&mutexattr);
    pthread_mutex_lock(&threadRet);
    ret=pthread_mutex_lock(&threadRet);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_lock");


    // pthread_create(&pthid,NULL,threadFunc,NULL);
    printf("YOU CAN'T SEE ME\n");
    return 0;
}

