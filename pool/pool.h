#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <sys/select.h>
#include <sys/time.h> 
#include <sys/wait.h>
#include <sys/sem.h> 
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <sys/msg.h> 
#include <pthread.h>
#include <signal.h>
#include <errno.h>
typedef struct{
    pid_t pid;//子进程的pid
    int fd;//管道的一端
    short busy;//代表子进程是否忙碌，0代表非忙碌，1代表忙碌
}process_data;
#define ARGS_CHECK(argc,val) {if(argc!=val)  {printf("error args\n");return -1;}}
#define ERROR_CHECK(ret,retVal,funcName) {if(ret==retVal) {perror(funcName);return -1;}}
#define THREAD_ERROR_CHECK(ret,funcName){if (ret!=0){printf("%s:%s\n",uncName,strerror(ret));return -1;}}
