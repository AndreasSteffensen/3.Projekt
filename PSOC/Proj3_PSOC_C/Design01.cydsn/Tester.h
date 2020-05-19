#ifndef TESTER_H
#define TESTER_H
//Class <Test> Tester
#include <stdint.h>


//private:

    //Class struct
    typedef struct Tester_TYPE
    {
       
    }Tester;
//public:
void Tester_Init(const Tester *this);
void writeTester(const Tester *this, const char* buff);
void blinkLED(const Tester *this);
void FiveSecDelay(const Tester *this);



//end Class <Test> Tester
/* [] END OF FILE */
#endif