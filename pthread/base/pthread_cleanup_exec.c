#include <fun.h>
void cleanup1()
{
    printf("i am cleanup1\n");
}
void cleanup2()
{
    printf("i am cleanup2\n");
}
void* threadFunc(void *p)
{
    pthread_cleanup_push(cleanup1,NULL);
    pthread_cleanup_push(cleanup2,NULL);
    pthread_exit(NULL);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    pthread_create(&pthid,NULL,threadFunc,NULL);
    long threadRet;
    int ret;
    ret=pthread_join(pthid,(void**)&threadRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("threadRet=%ld\n",threadRet);
    printf("Hello world\n");
    return 0;
}

