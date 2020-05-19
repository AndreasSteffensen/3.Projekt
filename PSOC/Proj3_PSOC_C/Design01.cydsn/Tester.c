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
#include "project.h"

void Tester_Init(const Tester *this)
{
    UART_tester_Start();
    UART_tester_PutString("Hello there, i am your debugger today \r\n");
}
void writeTester(const Tester *this, const char* buff)
{
    UART_tester_PutString(buff);
}
void blinkLED(const Tester *this)
{
    LED_Write(1);
    CyDelay(1000);
    LED_Write(0);
    CyDelay(1000);
}
void FiveSecDelay(const Tester *this)
{
    CyDelay(5000);
}
        
        

/* [] END OF FILE */
