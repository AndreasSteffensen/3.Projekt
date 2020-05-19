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

void PSoCIF::dispenseResten(char A)
{
    char buffer[1] = {A};
    int length = 1;
    int fd_spi;

    const char *filename = "/dev/spi_drv2";
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
    char buffer[1];
    int readlength = 1;     //<-- number of bytes to read

    const char* filename = "/dev/spi_drv0";


    //----- OPEN SPI BUS -----
    if ((fd_spi = open(filename, O_RDWR)) < 0)
    {
        //ERROR HANDLING
        err(errno, "Failed to open '%s'", filename);
        return nullptr;
    }

    //----- READ BYTES -----
    if (read(fd_spi, buffer, readlength) != readlength)
    {
        //ERROR HANDLING
        err(errno, "Failed to read from spi bus");
    }
    else
    {
        printf("Data read: %d\n", buffer[0]);
    }

    switch((unsigned int)buffer[0])
    {
        case 255:
            printf("Korrekt vægt af dispenserede piller\n");
            break;

        case 0:
            printf("Forkert vægt af dispenserede piller\n");
            break;

        case 204:
            printf("Dispenserede piller er fjernet fra vægten\n");
            break;

        case 129:
            printf("Ikke flere piller af typen: %d\n", buffer[1]);
            break;

        case 33:
            printf("Dispensering afsluttet\n");
            break;

        case 63:
            printf("Dispenserede piller ikke taget inden for 4 timer\n");
            break;

        default:
            break;
    }

    return NULL;
}

void PSoCIF::startRead()
{
    pthread_t spiRead;
    pthread_create(&spiRead, NULL, read, NULL);
    pthread_join(spiRead, NULL);
}