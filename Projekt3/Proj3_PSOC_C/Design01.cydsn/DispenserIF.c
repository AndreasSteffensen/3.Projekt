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
#include "DispenserIF.h"

void DispenserIF_Init(DispenserIF *this)
{
    //opsæt og kalibrer stepper-motorer.
}

int dispense(DispenserIF *this,enum PilleType type)
{
    //roter platformen
    
    //detekter pillebeholdning
    
    //hvis pillebeholdning OK
    //{
    //stempel-funktion (skub en pille ud)
    
    //vejefunktion
    
    
    //}
    
    //ellers: fejlhåndtering
    
    //returner succes eller fejlmelding
}
static int rotatePlatform(DispenserIF *this,enum PilleType type)
{
    //roter platform i korrekt position baseret på pilletyppe
    
    //evt. fejlcheck og fejlbesked som returværdi
    return 0;
}
static void pushPill(DispenserIF *this)
{
    
    //få stempel til at køre frem og tilbage igen
}


/* [] END OF FILE */
