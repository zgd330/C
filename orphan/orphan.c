#include <fun.h>

int main(int argc,char* argv[])

{
    if(!fork())
    {

        printf("i am child\n");
        while(1);
    }
    else{

        return 0;
    }
}

