#include <fun.h>

int main(int argc,char* argv[])

{
    if(!fork())
    {

        printf("i am child %d\n",getpid());
    }
    else{
        //wait(NULL);
        while(1);
        return 0;
    }
}

