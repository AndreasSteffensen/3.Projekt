#ifndef TESTER_H
#define TESTER_H
//Class <Test> Tester
#include <stdint.h>


//private:

    //Class struct
    typedef struct Tester_TYPE
    {
        float weight_;
        int platCalibrate_;
       
    }Tester;
//public:
void Tester_Init(Tester *this);
void writeTester(const Tester *this, const char* buff);
void blinkLED(const Tester *this);
void FiveSecDelay(const Tester *this);
void GenPlatSensorInput(Tester *this);
void GenConSensorInput(Tester *this);
float GenADCInput(Tester *this);
void GenPillsRemoved(Tester *this);


//end Class <Test> Tester
/* [] END OF FILE */
#endif