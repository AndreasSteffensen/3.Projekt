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

//C includes
#ifdef __cplusplus
extern "C" {
#endif

    // PSoC include, this has to be wrapped
    #include "project.h"
    

#ifdef __cplusplus
}
#endif

#include "RaspberryIF.h"
#include "PSOC_controller.h"
#include "Tester.h"

int main(void)
{
UART_tester_Start();

CyGlobalIntEnable; /* Enable global interrupts. */
//RaspberryIF RaspberryIFObj;
Tester TesterObj;


UART_tester_PutString("Hello from main \r\n");

//PSOC_controller ControllerObj(&TesterObj);


    for(;;)
    {
        
        
    }



}


/* [] END OF FILE */
