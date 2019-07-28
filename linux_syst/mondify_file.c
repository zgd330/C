#include <fun.h>

int main(int argc,char* argv[])
{
    int fd=open("file",O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    write(fd,"hello\n",5);
    printf("pid=%d,ppid=%d\n",getpid(),getppid());
    printf("uid=%d,gid=%d,euid=%d,egid=%d\n",getuid(),getgid(),geteuid(),getegid());
    close(fd); 
    return 0;
}

