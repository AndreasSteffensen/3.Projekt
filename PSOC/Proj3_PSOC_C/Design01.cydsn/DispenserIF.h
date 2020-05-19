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
#ifndef DISPENSERIF_H
#define DISPENSERIF_H
//Class <Boundary> Dispenser IF
#include <stdint.h>

#include "Tester.h"

//motorcontrol enums
    enum DIRECTION
{
    LEFT,
    RIGHT
};
typedef enum
{
    FIRST,
    SECOND,
    THIRD,
    UNKNOWN
}PLATPOS;
    
    //Class struct
    typedef struct Dispenser_IF_Type
    {
        Tester* testPtr;
        PLATPOS platpos;
        float weight;        
    }DispenserIF;
    
    enum PilleType
    {
        A=0,B=1,C=2
    };
//public:
int dispense(DispenserIF *this,enum PilleType type);
void DispenserIF_Init(DispenserIF *this, Tester* testPtr);


//end Class <Boundary> Dispenser IF
/* [] END OF FILE */
#endif