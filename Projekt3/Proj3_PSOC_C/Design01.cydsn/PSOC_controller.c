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
#include "PSOC_controller.h"


/**********************private(static)***********************/




/**************************public***************************/
void dispensPiller(const PSOC_controller *this,uint8_t a,uint8_t b,uint8_t c)
{
//     char buff[100];
//     int n=snprintf(buff,100,"Dosis er: %u af pilletype a, %u af pilletype b og %u af pilletype c.\r\n",a,b,c);
//     writeTester(this->testerPtr,buff);
//    for(uint8_t i=0;i<a;i++)
//    {
//        blinkLED(this->testerPtr);
//    }
//    FiveSecDelay(this->testerPtr);
//    for(uint8_t i=0;i<b;i++)
//    {
//        blinkLED(this->testerPtr);
//    }
//    FiveSecDelay(this->testerPtr);
//    for(uint8_t i=0;i<c;i++)
//    {
//        blinkLED(this->testerPtr);
//    }
//    FiveSecDelay(this->testerPtr);
    
}
void PSOC_controller_Init(PSOC_controller *this, Tester *testPtr)
{
    this->testerPtr=testPtr;
}


/**********************Free-functions***********************/




/* [] END OF FILE */

/* [] END OF FILE */
