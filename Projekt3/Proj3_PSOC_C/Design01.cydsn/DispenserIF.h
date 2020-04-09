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
#ifndef RASPBERRYIF_H
#define RASPBERRYIF_H
//Class <Boundary> Raspberry IF
#include <stdint.h>
#include "PSOC_controller.h"



     
    
    //Class struct
    typedef struct Dispenser_IF_Type
    {
        float weight;        
    }DispenserIF;
    
    enum PilleType
    {
        A=0,B=1,C=2
    };
//public:
int dispense(DispenserIF *this,enum PilleType type);
void DispenserIF_Init(DispenserIF *this);

//private:
static int rotatePlatform(enum PilleType type);
//end Class <Boundary> Dispenser IF
/* [] END OF FILE */
#endif