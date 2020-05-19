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
    p1.startRead();
   
    return 0;
}