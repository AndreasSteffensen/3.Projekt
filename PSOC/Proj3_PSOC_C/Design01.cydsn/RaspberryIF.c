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

#include "RaspberryIF.h"
#include "PSOC_controller.h"
#include "project.h"
#include <stdlib.h>
//Static pointer to RaspberryIF obj. used in interrupts
static RaspberryIF *callbackPtr;
CY_ISR_PROTO(SPI_rx_handler);
/**********************private(static)***********************/




/**************************public***************************/
void RaspberryIF_init(RaspberryIF* const this)
{
        callbackPtr=this;
        SPIS_1_Start();
        this->PSOC_controllerPtr=_NULL;
        this->readBuf=(uint8_t *)calloc(sizeof(uint8_t)*8,sizeof(uint8_t));
        this->readBufLen=0;
        this->spi_status=NONE;
        isr_1_StartEx(&SPI_rx_handler);
        
}

void SPI_DosisReceived(RaspberryIF* const this)
{
    //dispensdosis med de tre bytes fra writebufsize.
            uint8_t PillA=this->readBuf[0];
            uint8_t PillB=this->readBuf[1];
            uint8_t PillC=this->readBuf[2];
            
            dispensPiller(this->PSOC_controllerPtr,PillA,PillB,PillC);
            
}

void setControllerPtr(RaspberryIF* const this,PSOC_controller *ptr)
{
    this->PSOC_controllerPtr=ptr;
}
/**********************Free-functions***********************/

//Cy

CY_ISR(SPI_rx_handler)
{
    
    callbackPtr->readBuf[callbackPtr->readBufLen++]=SPIS_1_ReadRxData();
    if(callbackPtr->spi_status==NONE)
    {
          
        if(callbackPtr->readBufLen==1)
        {
            switch(callbackPtr->readBuf[0])
            {
                case 0xAA:
                    callbackPtr->spi_status=RECEIVING;
                    callbackPtr->readBufLen=0;
                break;
                
                case 0xA0:
                    callbackPtr->spi_status=STATUSREQ;
                    callbackPtr->readBufLen=0;
                    SPIS_1_WriteTxData(callbackPtr->PSOC_controllerPtr->status);
                    if(callbackPtr->PSOC_controllerPtr->status==PillsRemoved)
                    {
                        callbackPtr->PSOC_controllerPtr->status=Idle;
                    }
                default:
                break;
            }
        }
        else
        {
            callbackPtr->readBufLen=0;
            
        }
            
    
    }
    else if(callbackPtr->spi_status==STATUSREQ)
    {
        callbackPtr->readBufLen=0;
        callbackPtr->spi_status=NONE;
        
    }
    
    else if((callbackPtr->spi_status==RECEIVING)&&(callbackPtr->readBufLen==3))
    {
        SPI_DosisReceived(callbackPtr);
        callbackPtr->readBufLen=0;
        callbackPtr->spi_status=NONE;
        
    }
    
}

/* [] END OF FILE */
