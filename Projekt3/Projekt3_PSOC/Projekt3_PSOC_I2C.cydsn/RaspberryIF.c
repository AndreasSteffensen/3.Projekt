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

    
#ifdef __cplusplus
extern "C" {
#endif

    // PSoC include, this has to be wrapped
    #include "project.h"

#ifdef __cplusplus
}
#endif
#include <cstddef>
#include "RaspberryIF.h"
#include "PSOC_controller.h"
    RaspberryIF::RaspberryIF()
    {
        RaspberryPtr=this;
        
        I2C_1_SlaveInitReadBuf(readBuf,8);
        I2C_1_SlaveInitWriteBuf(writeBuf,8);
        I2C_1_Start();
        PSOC_controller_Ptr=nullptr;       
    }

    void RaspberryIF::outOfPill()
    {
    }
    void RaspberryIF::pillsTaken()
    {
    }
    void RaspberryIF::pillsNotTaken()
    {
    }
    void RaspberryIF::dispenseDone()
    {
    }
   //i2C CALLBACK
    void RaspberryIF::I2C_1_ISR_ExitCallback()
    {
        
        if(I2C_1_SlaveGetWriteBufSize()>=3)
        {
            RaspberryPtr->I2C_DosisReceived();
           
        }
        
        
    }
    
    void RaspberryIF::I2C_DosisReceived()
    {
         //dispensdosis med de tre bytes fra writebufsize.
            uint8_t PillA=writeBuf[0];
            uint8_t PillB=writeBuf[1];
            uint8_t PillC=writeBuf[2];
            I2C_1_SlaveClearWriteBuf();
            PSOC_controller_Ptr->dispensPiller(PillA,PillB,PillC);
    }
    
   

/* [] END OF FILE */
