/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef RASPBERRYIF_H
#define RASPBERRYIF_H
//Class <Boundary> Raspberry IF
#include <stdint.h>
#include "PSOC_controller.h"
#include "project.h"
    

//private:

    //forward declaration of PSOC_Controller Pointer?
    
    
    //Class struct
    typedef struct Raspberry_IF_Type
    {
         uint8_t *readBuf;
        uint8_t readBufLen;
        PSOC_controller *PSOC_controllerPtr;
        enum SpiState {RECEIVING=0,STATUSREQ=1,NONE=2}spi_status;
    }RaspberryIF;
//public:

void RaspberryIF_init(RaspberryIF* const this);
void SPI_DosisReceived(RaspberryIF* const this);
void setControllerPtr(RaspberryIF* const this,PSOC_controller *ptr);
PSOC_controller* getControllerPtr(RaspberryIF* const this);






//end Class <Boundary> Raspberry IF
/* [] END OF FILE */
#endif