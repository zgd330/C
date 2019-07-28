#include <fun.h>

void *pthreadFunc(void*p)
{
    time_t now;
    time(&now);
    char*q=ctime(&now);
    printf("i am child thread p=%s\n",q);
    sleep(3);
    printf("i am child thread p=%s\n",q);
}

int main(int argc,char *argv[])
{

    pthread_t pthid;
    pthread_create(&pthid,NULL,pthreadFunc,NULL);
    sleep(1);
    time_t now;
    time(&now);
    char*q=ctime(&now);
    printf("i am main thread p=%s\n",q);
    pthread_join(pthid,NULL);
    return 0;
}

