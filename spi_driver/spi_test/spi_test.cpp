#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <err.h>
#include <string>

int main(int argc, char *argv[])
{
    
    

    int fd_spi;
    int buffer[3];
    int length = 1;     //<-- number of bytes to write

    std::string f = "/dev/spi_drv";
    f += *argv[1];
    const char *filename = f.c_str();
    std::string fops = argv[2];

    if ((fd_spi = open(filename, O_RDWR)) < 0)
    {
        //ERROR HANDLING
        err(errno, "Failed to open '%s'", filename);buffer[0] = 1;
        buffer[1] = 2;
        buffer[2] = 3;
        if (write(fd_spi, buffer, length) != length)
        {
            //ERROR HANDLING
            err(errno, "Failed to write to spi bus");
        } 

    if (fops == "read")
    {

        if (read(fd_spi, buffer, length) != length)
        {
            //ERROR HANDLING
            err(errno, "Failed to read from spi bus");
        }
        else
        {
            printf("Data read: %d\n", buffer[0]);
        }
    }

    if (fops == "write")
    {  
        buffer[0] = 1;
        buffer[1] = 2;
        buffer[2] = 3;
        if (write(fd_spi, buffer, length) != length)
        {
            //ERROR HANDLING
            err(errno, "Failed to write to spi bus");
        }   
    }

    sleep(1);
    
    return 0;
}