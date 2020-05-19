/*******************************************************************************
* File Name: scl.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_scl_H) /* Pins scl_H */
#define CY_PINS_scl_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "scl_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 scl__PORT == 15 && ((scl__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    scl_Write(uint8 value);
void    scl_SetDriveMode(uint8 mode);
uint8   scl_ReadDataReg(void);
uint8   scl_Read(void);
void    scl_SetInterruptMode(uint16 position, uint16 mode);
uint8   scl_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the scl_SetDriveMode() function.
     *  @{
     */
        #define scl_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define scl_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define scl_DM_RES_UP          PIN_DM_RES_UP
        #define scl_DM_RES_DWN         PIN_DM_RES_DWN
        #define scl_DM_OD_LO           PIN_DM_OD_LO
        #define scl_DM_OD_HI           PIN_DM_OD_HI
        #define scl_DM_STRONG          PIN_DM_STRONG
        #define scl_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define scl_MASK               scl__MASK
#define scl_SHIFT              scl__SHIFT
#define scl_WIDTH              1u

/* Interrupt constants */
#if defined(scl__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in scl_SetInterruptMode() function.
     *  @{
     */
        #define scl_INTR_NONE      (uint16)(0x0000u)
        #define scl_INTR_RISING    (uint16)(0x0001u)
        #define scl_INTR_FALLING   (uint16)(0x0002u)
        #define scl_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define scl_INTR_MASK      (0x01u) 
#endif /* (scl__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define scl_PS                     (* (reg8 *) scl__PS)
/* Data Register */
#define scl_DR                     (* (reg8 *) scl__DR)
/* Port Number */
#define scl_PRT_NUM                (* (reg8 *) scl__PRT) 
/* Connect to Analog Globals */                                                  
#define scl_AG                     (* (reg8 *) scl__AG)                       
/* Analog MUX bux enable */
#define scl_AMUX                   (* (reg8 *) scl__AMUX) 
/* Bidirectional Enable */                                                        
#define scl_BIE                    (* (reg8 *) scl__BIE)
/* Bit-mask for Aliased Register Access */
#define scl_BIT_MASK               (* (reg8 *) scl__BIT_MASK)
/* Bypass Enable */
#define scl_BYP                    (* (reg8 *) scl__BYP)
/* Port wide control signals */                                                   
#define scl_CTL                    (* (reg8 *) scl__CTL)
/* Drive Modes */
#define scl_DM0                    (* (reg8 *) scl__DM0) 
#define scl_DM1                    (* (reg8 *) scl__DM1)
#define scl_DM2                    (* (reg8 *) scl__DM2) 
/* Input Buffer Disable Override */
#define scl_INP_DIS                (* (reg8 *) scl__INP_DIS)
/* LCD Common or Segment Drive */
#define scl_LCD_COM_SEG            (* (reg8 *) scl__LCD_COM_SEG)
/* Enable Segment LCD */
#define scl_LCD_EN                 (* (reg8 *) scl__LCD_EN)
/* Slew Rate Control */
#define scl_SLW                    (* (reg8 *) scl__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define scl_PRTDSI__CAPS_SEL       (* (reg8 *) scl__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define scl_PRTDSI__DBL_SYNC_IN    (* (reg8 *) scl__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define scl_PRTDSI__OE_SEL0        (* (reg8 *) scl__PRTDSI__OE_SEL0) 
#define scl_PRTDSI__OE_SEL1        (* (reg8 *) scl__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define scl_PRTDSI__OUT_SEL0       (* (reg8 *) scl__PRTDSI__OUT_SEL0) 
#define scl_PRTDSI__OUT_SEL1       (* (reg8 *) scl__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define scl_PRTDSI__SYNC_OUT       (* (reg8 *) scl__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(scl__SIO_CFG)
    #define scl_SIO_HYST_EN        (* (reg8 *) scl__SIO_HYST_EN)
    #define scl_SIO_REG_HIFREQ     (* (reg8 *) scl__SIO_REG_HIFREQ)
    #define scl_SIO_CFG            (* (reg8 *) scl__SIO_CFG)
    #define scl_SIO_DIFF           (* (reg8 *) scl__SIO_DIFF)
#endif /* (scl__SIO_CFG) */

/* Interrupt Registers */
#if defined(scl__INTSTAT)
    #define scl_INTSTAT            (* (reg8 *) scl__INTSTAT)
    #define scl_SNAP               (* (reg8 *) scl__SNAP)
    
	#define scl_0_INTTYPE_REG 		(* (reg8 *) scl__0__INTTYPE)
#endif /* (scl__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_scl_H */


/* [] END OF FILE */
