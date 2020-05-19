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




    #ifndef PSOC_CONTROLLER_H
    #define PSOC_CONTROLLER_H
//Class <Controller> PSOC Controller
#include <stdint.h>
#include "Tester.h"
#include "DispenserIF.h"
//private:

    //forward declaration of PSOC_Controller Pointer?
   
    
    //Class struct
    typedef struct PSOC_Controller_Type
    {
        Tester *testerPtr;
        DispenserIF *dispenserPtr;
    }PSOC_controller;
//public:

void PSOC_controller_Init(PSOC_controller *this, Tester* testPtr, DispenserIF *dispenserPtr);
void dispensPiller(const PSOC_controller *this,uint8_t a,uint8_t b,uint8_t c);





//end Class <Controller> PSOC Controller
/* [] END OF FILE */
#endif