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
#include "Tester.h"

#ifdef __cplusplus
extern "C" {
#endif

    // PSoC include, this has to be wrapped
    #include "project.h"

#ifdef __cplusplus
}
#endif

    Tester::Tester()
    {
        UART_tester_Start();
        Pin_1_Write(1);
        UART_tester_PutString("Hello there, i am your debugger today \r\n");
    }
    void Tester::writeTester(const char* buff)
    {
        UART_tester_PutString(buff);
        
       
        
    }
    void Tester::blinkLed()
    {
        Pin_1_Write(1);
        CyDelay(500);
        Pin_1_Write(0);
        CyDelay(500);
        
    }
/* [] END OF FILE */
