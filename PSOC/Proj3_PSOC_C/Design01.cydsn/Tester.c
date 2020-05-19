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
#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 

void Tester_Init(Tester *this)
{
    srand(time(0));
    UART_tester_Start();
    this->platCalibrate_=1+rand()%400;
    this->weight_=0.0;
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
void GenPlatSensorInput(Tester *this)
{
    if(--(this->platCalibrate_)==0)
    {
        writeTester(this,"Generating platform sensor input \"High\"\r\n");
        Motor_Calibration_Sensor_Write(1);
    }
}
void GenConSensorInput(Tester *this)
{
    if(rand()%20==0)
    {
        writeTester(this,"Generating container sensor input \"low\"\r\n");
        Pill_Container_Sensor_Write(0);
    }
    else
    {
        Pill_Container_Sensor_Write(1);
    }
}
float GenADCInput(Tester *this)
{
    if(rand()%50)
    {
        this->weight_+=10+(rand()%100)/100;
    }
    else
    {
        writeTester(this,"Generating no pill dispensed input\r\n");
        //tilfældigt tal mellem 0.25 og -0.25
        this->weight_+=((rand()%100)/200)-0.25;
    }
    
    return this->weight_;
}
void GenPillsRemoved(Tester *this)
{
    //delay mellem 5 og 10 sek
    writeTester(this,"Generating pills removed input\r\n");
    CyDelay((rand()%6)*1000+5000);
    
    this->weight_=0.0;
}
        

/* [] END OF FILE */
