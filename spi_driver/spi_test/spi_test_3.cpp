#include "PSoCIF.hpp"
#include <stdio.h>
#include <string>

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
    int status = p1.startRead();

    switch(status)
    {
        case 65:
            p1.laasBeholderOp('65');
        break;

        case 66:
            p1.laasBeholderOp('66');
        break;

        case 67:
            p1.laasBeholderOp('67');
        break;

        default:
        break;
    }
   
    return 0;
}