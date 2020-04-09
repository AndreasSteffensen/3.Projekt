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
#include <stdint.h>
#include "Tester.h"
/* [] END OF FILE */


    
class PSOC_controller
{
    public:
        PSOC_controller(Tester* tester);
        void dispensPiller(uint8_t a,uint8_t b, uint8_t c);
    private:
        Tester* tester_;
        
       
};
#endif
