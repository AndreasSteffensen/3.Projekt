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
#include "PSOC_controller.h"
#include "RaspberryIF.h"
#include "Tester.h"
#include "DispenserIF.h"
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    
    Tester TesterObj;
    RaspberryIF RaspberryIFObj;
    DispenserIF DispenserIFObj;
    PSOC_controller ControllerObj;
    Tester_Init(&TesterObj);
    RaspberryIF_init(&RaspberryIFObj);
    PSOC_controller_Init(&ControllerObj,&TesterObj);
    setControllerPtr(&RaspberryIFObj,&ControllerObj);
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    blinkLED(&TesterObj);
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
