#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <err.h>
#include <pthread.h>
#include <string>

void* read(void *arg)
{
    int fd_spi;
    int buffer[3];
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
        err(errno, "Failed to read from i2c bus");
    }
    else
    {
        printf("Data read: %d\n", buffer[0]);
    }

    switch(buffer[0])
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
            printf("Ikke flere piller af typen: %s\n", buffer[1]);
            break;

        case 33:
            printf("Dispensering afsluttet\n");
            break;

        case 63:
            printf("Dispensered piller ikke taget inden for 4 timer\n");
            break;

        default:
            break;
    }

    return NULL;
}

int main()
{
    pthread_t spiRead;
    pthread_create(&spiRead, NULL, read, NULL);
    pthread_join(spiRead, NULL);
	
    return 0;
}