/*******************************************************************************
* File Name: sda.h  
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

#if !defined(CY_PINS_sda_H) /* Pins sda_H */
#define CY_PINS_sda_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sda_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sda__PORT == 15 && ((sda__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sda_Write(uint8 value);
void    sda_SetDriveMode(uint8 mode);
uint8   sda_ReadDataReg(void);
uint8   sda_Read(void);
void    sda_SetInterruptMode(uint16 position, uint16 mode);
uint8   sda_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sda_SetDriveMode() function.
     *  @{
     */
        #define sda_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sda_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sda_DM_RES_UP          PIN_DM_RES_UP
        #define sda_DM_RES_DWN         PIN_DM_RES_DWN
        #define sda_DM_OD_LO           PIN_DM_OD_LO
        #define sda_DM_OD_HI           PIN_DM_OD_HI
        #define sda_DM_STRONG          PIN_DM_STRONG
        #define sda_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sda_MASK               sda__MASK
#define sda_SHIFT              sda__SHIFT
#define sda_WIDTH              1u

/* Interrupt constants */
#if defined(sda__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sda_SetInterruptMode() function.
     *  @{
     */
        #define sda_INTR_NONE      (uint16)(0x0000u)
        #define sda_INTR_RISING    (uint16)(0x0001u)
        #define sda_INTR_FALLING   (uint16)(0x0002u)
        #define sda_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sda_INTR_MASK      (0x01u) 
#endif /* (sda__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sda_PS                     (* (reg8 *) sda__PS)
/* Data Register */
#define sda_DR                     (* (reg8 *) sda__DR)
/* Port Number */
#define sda_PRT_NUM                (* (reg8 *) sda__PRT) 
/* Connect to Analog Globals */                                                  
#define sda_AG                     (* (reg8 *) sda__AG)                       
/* Analog MUX bux enable */
#define sda_AMUX                   (* (reg8 *) sda__AMUX) 
/* Bidirectional Enable */                                                        
#define sda_BIE                    (* (reg8 *) sda__BIE)
/* Bit-mask for Aliased Register Access */
#define sda_BIT_MASK               (* (reg8 *) sda__BIT_MASK)
/* Bypass Enable */
#define sda_BYP                    (* (reg8 *) sda__BYP)
/* Port wide control signals */                                                   
#define sda_CTL                    (* (reg8 *) sda__CTL)
/* Drive Modes */
#define sda_DM0                    (* (reg8 *) sda__DM0) 
#define sda_DM1                    (* (reg8 *) sda__DM1)
#define sda_DM2                    (* (reg8 *) sda__DM2) 
/* Input Buffer Disable Override */
#define sda_INP_DIS                (* (reg8 *) sda__INP_DIS)
/* LCD Common or Segment Drive */
#define sda_LCD_COM_SEG            (* (reg8 *) sda__LCD_COM_SEG)
/* Enable Segment LCD */
#define sda_LCD_EN                 (* (reg8 *) sda__LCD_EN)
/* Slew Rate Control */
#define sda_SLW                    (* (reg8 *) sda__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sda_PRTDSI__CAPS_SEL       (* (reg8 *) sda__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sda_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sda__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sda_PRTDSI__OE_SEL0        (* (reg8 *) sda__PRTDSI__OE_SEL0) 
#define sda_PRTDSI__OE_SEL1        (* (reg8 *) sda__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sda_PRTDSI__OUT_SEL0       (* (reg8 *) sda__PRTDSI__OUT_SEL0) 
#define sda_PRTDSI__OUT_SEL1       (* (reg8 *) sda__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sda_PRTDSI__SYNC_OUT       (* (reg8 *) sda__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sda__SIO_CFG)
    #define sda_SIO_HYST_EN        (* (reg8 *) sda__SIO_HYST_EN)
    #define sda_SIO_REG_HIFREQ     (* (reg8 *) sda__SIO_REG_HIFREQ)
    #define sda_SIO_CFG            (* (reg8 *) sda__SIO_CFG)
    #define sda_SIO_DIFF           (* (reg8 *) sda__SIO_DIFF)
#endif /* (sda__SIO_CFG) */

/* Interrupt Registers */
#if defined(sda__INTSTAT)
    #define sda_INTSTAT            (* (reg8 *) sda__INTSTAT)
    #define sda_SNAP               (* (reg8 *) sda__SNAP)
    
	#define sda_0_INTTYPE_REG 		(* (reg8 *) sda__0__INTTYPE)
#endif /* (sda__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sda_H */


/* [] END OF FILE */
