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
//C includes
#ifdef cplusplus
extern "C" {
#endif

    // PSoC include, this has to be wrapped
    #include "project.h"

#ifdef cplusplus
}
#endif


int main(void)
{
CyGlobalIntEnable; /* Enable global interrupts. */
RaspberryIF RaspberryIFObj();



    for(;;)
    {
        
    }



}


/* [] END OF FILE */
