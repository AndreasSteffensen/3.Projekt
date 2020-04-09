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

//private:

    //forward declaration of PSOC_Controller Pointer?
   
    
    //Class struct
    typedef struct Raspberry_IF_Type
    {
        uint8_t readBuf[8];
        uint8_t writeBuf[8];
        PSOC_controller *PSOC_controllerPtr;
    }RaspberryIF;
//public:

void RaspberryIF_init(RaspberryIF* const this);
void I2C_DosisReceived(RaspberryIF* const this);
void outOfPill(RaspberryIF* const this);
void pillsTaken(RaspberryIF* const this);
void PillsNotTaken(RaspberryIF* const this);
void dispenseDone(RaspberryIF* const this);
void setControllerPtr(RaspberryIF* const this,PSOC_controller *ptr);
PSOC_controller* getControllerPtr(RaspberryIF* const this);
void I2C_1_ISR_ExitCallback();




//end Class <Boundary> Raspberry IF
/* [] END OF FILE */
#endif