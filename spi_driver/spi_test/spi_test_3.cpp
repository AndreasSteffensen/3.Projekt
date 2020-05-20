#include "PSoCIF.hpp"
#include <stdio.h>
#include <string>
#include <unistd.h>

int main(int argc, char *argv[])
{
    PSoCIF p1;

    if(argc < 3)
    {
        printf("Not enough input arguments\n");
        exit(EXIT_FAILURE);
    }

    // printf("%c, %c, %c\n", *argv[1],*argv[2],*argv[3]);

    p1.dispensPille(*argv[1],*argv[2],*argv[3]);
    int status=0;
    for(;;)//ever
    {
        sleep(1);
        int status = p1.startRead();
        printf("status: %d\n",status);
    
        switch(status)
        {
            case 3:
                p1.laasBeholderOp('1');
                
            break;

            case 4:
                p1.laasBeholderOp('2');
                
            break;

            case 5:
                p1.laasBeholderOp('3');

            break;
            case 6:
                return 0;
            break;
            
            default:
            break;
        }
    }
    return 0;
}