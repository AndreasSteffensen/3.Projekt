#include "PSoCIF.hpp"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <errno.h>
#include <err.h>
#include <string>

PSoCIF::PSoCIF()
{

}

void PSoCIF::dispensPille(char A, char B, char C)
{
    char buffer[3] = {A, B, C};
    int length = 3;
    int fd_spi;

    const char *filename = "/dev/spi_drv0";
    if ((fd_spi = open(filename, O_RDWR)) < 0)
    {
        //ERROR HANDLING
        err(errno, "Failed to open '%s'", filename);
        return;
    }

    if (write(fd_spi, buffer, length) != length)
    {
        //ERROR HANDLING
        err(errno, "Failed to write to spi bus");
    }

    close(fd_spi);
}

void PSoCIF::laasBeholderOp(char A)
{
    char buffer[1] = {A};
    int length = 1;
    int fd_spi;

    const char *filename = "/dev/spi_drv1";
    if ((fd_spi = open(filename, O_RDWR)) < 0)
    {
        //ERROR HANDLING
        err(errno, "Failed to open '%s'", filename);
        return;
    }

    if (write(fd_spi, buffer, length) != length)
    {
        //ERROR HANDLING
        err(errno, "Failed to write to spi bus");
    }

    close(fd_spi);
}

void* read(void *arg)
{
    int fd_spi;
    char buffer[4];
    int readlength = 4;     //<-- number of bytes to read

    const char* filename = "/dev/spi_drv0";


    //----- OPEN SPI BUS -----
    if ((fd_spi = open(filename, O_RDWR)) < 0)
    {
        //ERROR HANDLING
        err(errno, "Failed to open '%s'", filename);
        return nullptr;
    }

    //----- READ BYTES -----
    if (read(fd_spi, buffer, readlength) > readlength)
    {   
        
        //ERROR HANDLING
        err(errno, "Failed to read from spi bus");
    }
    else
    {

        printf("Data read: %s\n", buffer);
    }


    switch(atoi(buffer))
    {
        case 255:
            printf("Korrekt vægt af dispenserede piller\n");
            return (void*) 1;

        case 0:
            printf("Forkert vægt af dispenserede piller\n");
            return (void*) 0;

        case 204:
            printf("Dispenserede piller er fjernet fra vægten\n");
            return (void*) 2;

        case 65:
            printf("Ikke flere piller af typen: A\n");
            return (void*) 3;

        case 66:
            printf("Ikke flere piller af typen: B\n");
            return (void*) 4;

        case 67:
            printf("Ikke flere piller af typen: C\n");
            return (void*) 5;

        case 33:
            printf("Dispensering afsluttet\n");
            return (void*) 6;

        default:
            break;
    }

    return NULL;
}

/*Returnerer:
0 - Forkert vægt af dispenserede piller
1 - Korrekt vægt af dispenserede piller
2 - Dispenserede piller er fjernet fra vægten
3 - Ikke flere piller af typen: A
4 - Ikke flere piller af typen: B
5 - Ikke flere piller af typen: C
6 - Dispensering afsluttet */
int PSoCIF::startRead()
{
    void* status;
    pthread_t spiRead;
    pthread_create(&spiRead, NULL, read, NULL);
    pthread_join(spiRead, &status);

    return *(int*)status;
}