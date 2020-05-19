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
#include "DispenserIF.h"

#include "RaspberryIF.h"

#include "project.h"
#include "PSOC_controller.h"

#include "Tester.h"


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    
    Tester TesterObj;
    
    DispenserIF DispenserIFObj;
    PSOC_controller ControllerObj;
    RaspberryIF RaspberryIFObj;
    
    
    Tester_Init(&TesterObj);
    RaspberryIF_init(&RaspberryIFObj);
    DispenserIF_Init(&DispenserIFObj,&TesterObj);
    PSOC_controller_Init(&ControllerObj,&TesterObj,&DispenserIFObj);
    setControllerPtr(&RaspberryIFObj,&ControllerObj);
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    blinkLED(&TesterObj);
    
    for(;;)
    {
        if(ControllerObj.status==0)
        {
            GenPillsRemoved(ControllerObj.testerPtr);
            if(ControllerObj.testerPtr->weight_==0.0)
            {
                ControllerObj.status=PillsRemoved;
                generateInt(&ControllerObj);
            }
        }
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
