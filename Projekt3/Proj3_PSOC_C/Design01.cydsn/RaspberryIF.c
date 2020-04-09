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
#include "project.h"
#include "RaspberryIF.h"
#include "PSOC_controller.h"
//Static pointer to RaspberryIF obj. used in Cy Api callback
static RaspberryIF *callbackPtr;
/**********************private(static)***********************/




/**************************public***************************/
void RaspberryIF_init(RaspberryIF* const this)
{
        callbackPtr=this;
        
        I2C_1_SlaveInitReadBuf(this->readBuf,8);
        I2C_1_SlaveInitWriteBuf(this->writeBuf,8);
        I2C_1_SlaveSetAddress(0x42);
        I2C_1_Start();
        this->PSOC_controllerPtr=_NULL; 
}

void I2C_DosisReceived(RaspberryIF* const this)
{
    //dispensdosis med de tre bytes fra writebufsize.
            uint8_t PillA=this->writeBuf[0];
            uint8_t PillB=this->writeBuf[1];
            uint8_t PillC=this->writeBuf[2];
            I2C_1_SlaveClearWriteBuf();
            dispensPiller(this->PSOC_controllerPtr,PillA,PillB,PillC);
            
}

void setControllerPtr(RaspberryIF* const this,PSOC_controller *ptr)
{
    this->PSOC_controllerPtr=ptr;
}
/**********************Free-functions***********************/

//Cy Api callback function:
void I2C_1_ISR_ExitCallback()
{
        
        if(I2C_1_SlaveGetWriteBufSize()>=3)
        {
            I2C_DosisReceived(callbackPtr);           
        }
       
}
/* [] END OF FILE */
