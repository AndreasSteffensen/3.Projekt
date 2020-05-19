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
#include <stdio.h>
#include "project.h"
/**********************private(static)***********************/




/**************************public***************************/
void dispensPiller(PSOC_controller *this,uint8_t a,uint8_t b,uint8_t c)
{
     this->status=Dispensing;
     char buff[100];
     snprintf(buff,100,"Dosis er: %u af pilletype a, %u af pilletype b og %u af pilletype c.\r\n",a,b,c);
     writeTester(this->testerPtr,buff);
    
    //dispens piller
    while(a--&&(this->status==Dispensing))
    {
        int err=dispense(this->dispenserPtr,A);
        if(err==1)
        {
            //ved fejl, antag at der stadig er piller, men blot ikke blev dispenset en
            ++a;
           
        }
        else if(err==-1)
        {
            writeTester(this->testerPtr,"Container A empty\r\n");
            this->status=AEmpty;
            break;
        }
    }
    while(b--&&(this->status==Dispensing))
    {
        int err=dispense(this->dispenserPtr,B);
        if(err==1)
        {
            //ved fejl, antag at der stadig er piller, men blot ikke blev dispenset en
            ++b;
           
        }
        else if(err==-1)
        {
            //beholder er tom.
            //set status til 2
            writeTester(this->testerPtr,"Container B empty\r\n");
            this->status=BEmpty;
            break;
        }
    }
    while(c--&&(this->status==Dispensing))
    {
        int err=dispense(this->dispenserPtr,C);
        if(err==1)
        {
            
            //ved fejl, antag at der stadig er piller, men blot ikke blev dispenset en
            ++c;
            
        }
        else if(err==-1)
        {
            //beholder er tom.
            //set status til 3
            writeTester(this->testerPtr,"Container C empty\r\n");
            this->status=CEmpty;
            break;
        }
    }
    //sæt status til complete
    //hvis en pillebeholder ikke er løbt tør, sæt til succes.
    if(this->status==Dispensing)
    {
        writeTester(this->testerPtr,"Dispense succesfull\r\n");
        
        this->status=Done;
    }
    //lav interrupt på rpi
    generateInt(this);
    
}
void PSOC_controller_Init(PSOC_controller *this, Tester *testPtr, DispenserIF* dispPtr)
{
    this->dispenserPtr=dispPtr;
    this->testerPtr=testPtr;
    this->status=Idle;
}

void generateInt(PSOC_controller* const this)
{
    writeTester(this->testerPtr,"Generating interrupt\r\n");
    RPI_INT_Write(1);
    CyDelay(1);
    RPI_INT_Write(0);
      
}
/**********************Free-functions***********************/




/* [] END OF FILE */

/* [] END OF FILE */
