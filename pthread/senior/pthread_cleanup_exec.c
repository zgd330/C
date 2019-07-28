#include <fun.h>
void cleanup(void *p)
{
    free(p);
    printf("i am cleanup\n");
}
void* threadFunc(void *p)
{
    p=malloc(20);
    pthread_cleanup_push(cleanup,p);
    sleep(3);
    pthread_cleanup_pop(1);//你要提前free用的是pop
    pthread_exit(NULL);
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

