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
   
        //status enum
        typedef enum{
            AEmpty=65,
            BEmpty=66,
            CEmpty=67,
            Done=33,
            PillsRemoved=204,
            Dispensing=0,
            Idle=5,
            
        }STATUS;
            
    
    //Class struct
    typedef struct PSOC_Controller_Type
    {
        DispenserIF *dispenserPtr;
        Tester *testerPtr;
        STATUS status;
        
    }PSOC_controller;
//public:

void PSOC_controller_Init(PSOC_controller *this, Tester* testPtr, DispenserIF* dispPtr);
void dispensPiller(PSOC_controller *this,uint8_t a,uint8_t b,uint8_t c);
void generateInt(PSOC_controller* const this);




//end Class <Controller> PSOC Controller
/* [] END OF FILE */
#endif