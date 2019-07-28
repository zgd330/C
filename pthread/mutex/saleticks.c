#include <fun.h>

typedef struct{
    int tickets;
    pthread_mutex_t mutex;
}Data_t;
void * salewindows1(void*p)
{
    int i=0;
    Data_t*pArg=(Data_t*)p;
    while(1)
    {
        pthread_mutex_lock(&pArg->mutex);
        if(pArg->tickets>0)
        {
            //printf("i am salewindows1 start sale,%d\n",pArg->tickets);
            pArg->tickets--;
            i++;
            //printf("i am salewindows1 finish sale,%d\n",pArg->tickets);
            pthread_mutex_unlock(&pArg->mutex);
        }else{            
            pthread_mutex_unlock(&pArg->mutex);
            printf("total=%d\n",i);
            break;
        }
    }
    return NULL;
}
void * salewindows2(void*p)
{
    int j=0;
    Data_t*pArg=(Data_t*)p;
    while(1)
    {
        pthread_mutex_lock(&pArg->mutex);
        if(pArg->tickets>0)
        {
            //printf("i am salewindows2 start sale,%d\n",pArg->tickets);
            pArg->tickets--;
            j++;
            //printf("i am salewindows2 finish sale,%d\n",pArg->tickets);

            pthread_mutex_unlock(&pArg->mutex);

        }else{            
            pthread_mutex_unlock(&pArg->mutex);
            printf("total=%d\n",j);
            break;
        }
    }
    return NULL;
}

int main(int argc,char* argv[])
{
    Data_t threadInfo;
    threadInfo.tickets=20000000;
    pthread_t pthid1,pthid2;
    pthread_mutex_init(&threadInfo.mutex,NULL);
    pthread_create(&pthid1,NULL,salewindows1,&threadInfo);
    pthread_create(&pthid2,NULL,salewindows2,&threadInfo);
    long threadret;
    int ret;
    ret=pthread_join(pthid1,(void**)&threadret);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    ret=pthread_join(pthid2,(void**)&threadret);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("sale over\n");
    return 0;
}
