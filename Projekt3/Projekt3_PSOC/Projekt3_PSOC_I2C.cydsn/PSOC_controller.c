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
#include <stdio.h>
#ifdef cplusplus
extern "C" {
#endif

    // PSoC include, this has to be wrapped
    #include "project.h"

#ifdef cplusplus
}
#endif

#include "PSOC_controller.h"

    PSOC_controller::PSOC_controller(Tester* tester)
    :tester_(tester)
    {
        
    }
    void PSOC_controller::dispensPiller(uint8_t a,uint8_t b, uint8_t c)
    {
       char buff[100];
       snprintf(buff,100,"Dosis er: %u af pilletype a, %u af pilletype b og %u af pilletype c.\r\n",a,b,c);
       
       tester_->writeTester(buff);
        
    }
/* [] END OF FILE */
