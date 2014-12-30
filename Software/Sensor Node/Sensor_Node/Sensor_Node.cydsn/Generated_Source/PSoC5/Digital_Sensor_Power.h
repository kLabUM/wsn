/*******************************************************************************
* File Name: Digital_Sensor_Power.h  
* Version 2.0
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Digital_Sensor_Power_H) /* Pins Digital_Sensor_Power_H */
#define CY_PINS_Digital_Sensor_Power_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Digital_Sensor_Power_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Digital_Sensor_Power__PORT == 15 && ((Digital_Sensor_Power__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Digital_Sensor_Power_Write(uint8 value) ;
void    Digital_Sensor_Power_SetDriveMode(uint8 mode) ;
uint8   Digital_Sensor_Power_ReadDataReg(void) ;
uint8   Digital_Sensor_Power_Read(void) ;
uint8   Digital_Sensor_Power_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Digital_Sensor_Power_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Digital_Sensor_Power_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Digital_Sensor_Power_DM_RES_UP          PIN_DM_RES_UP
#define Digital_Sensor_Power_DM_RES_DWN         PIN_DM_RES_DWN
#define Digital_Sensor_Power_DM_OD_LO           PIN_DM_OD_LO
#define Digital_Sensor_Power_DM_OD_HI           PIN_DM_OD_HI
#define Digital_Sensor_Power_DM_STRONG          PIN_DM_STRONG
#define Digital_Sensor_Power_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Digital_Sensor_Power_MASK               Digital_Sensor_Power__MASK
#define Digital_Sensor_Power_SHIFT              Digital_Sensor_Power__SHIFT
#define Digital_Sensor_Power_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Digital_Sensor_Power_PS                     (* (reg8 *) Digital_Sensor_Power__PS)
/* Data Register */
#define Digital_Sensor_Power_DR                     (* (reg8 *) Digital_Sensor_Power__DR)
/* Port Number */
#define Digital_Sensor_Power_PRT_NUM                (* (reg8 *) Digital_Sensor_Power__PRT) 
/* Connect to Analog Globals */                                                  
#define Digital_Sensor_Power_AG                     (* (reg8 *) Digital_Sensor_Power__AG)                       
/* Analog MUX bux enable */
#define Digital_Sensor_Power_AMUX                   (* (reg8 *) Digital_Sensor_Power__AMUX) 
/* Bidirectional Enable */                                                        
#define Digital_Sensor_Power_BIE                    (* (reg8 *) Digital_Sensor_Power__BIE)
/* Bit-mask for Aliased Register Access */
#define Digital_Sensor_Power_BIT_MASK               (* (reg8 *) Digital_Sensor_Power__BIT_MASK)
/* Bypass Enable */
#define Digital_Sensor_Power_BYP                    (* (reg8 *) Digital_Sensor_Power__BYP)
/* Port wide control signals */                                                   
#define Digital_Sensor_Power_CTL                    (* (reg8 *) Digital_Sensor_Power__CTL)
/* Drive Modes */
#define Digital_Sensor_Power_DM0                    (* (reg8 *) Digital_Sensor_Power__DM0) 
#define Digital_Sensor_Power_DM1                    (* (reg8 *) Digital_Sensor_Power__DM1)
#define Digital_Sensor_Power_DM2                    (* (reg8 *) Digital_Sensor_Power__DM2) 
/* Input Buffer Disable Override */
#define Digital_Sensor_Power_INP_DIS                (* (reg8 *) Digital_Sensor_Power__INP_DIS)
/* LCD Common or Segment Drive */
#define Digital_Sensor_Power_LCD_COM_SEG            (* (reg8 *) Digital_Sensor_Power__LCD_COM_SEG)
/* Enable Segment LCD */
#define Digital_Sensor_Power_LCD_EN                 (* (reg8 *) Digital_Sensor_Power__LCD_EN)
/* Slew Rate Control */
#define Digital_Sensor_Power_SLW                    (* (reg8 *) Digital_Sensor_Power__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Digital_Sensor_Power_PRTDSI__CAPS_SEL       (* (reg8 *) Digital_Sensor_Power__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Digital_Sensor_Power_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Digital_Sensor_Power__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Digital_Sensor_Power_PRTDSI__OE_SEL0        (* (reg8 *) Digital_Sensor_Power__PRTDSI__OE_SEL0) 
#define Digital_Sensor_Power_PRTDSI__OE_SEL1        (* (reg8 *) Digital_Sensor_Power__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Digital_Sensor_Power_PRTDSI__OUT_SEL0       (* (reg8 *) Digital_Sensor_Power__PRTDSI__OUT_SEL0) 
#define Digital_Sensor_Power_PRTDSI__OUT_SEL1       (* (reg8 *) Digital_Sensor_Power__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Digital_Sensor_Power_PRTDSI__SYNC_OUT       (* (reg8 *) Digital_Sensor_Power__PRTDSI__SYNC_OUT) 


#if defined(Digital_Sensor_Power__INTSTAT)  /* Interrupt Registers */

    #define Digital_Sensor_Power_INTSTAT                (* (reg8 *) Digital_Sensor_Power__INTSTAT)
    #define Digital_Sensor_Power_SNAP                   (* (reg8 *) Digital_Sensor_Power__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Digital_Sensor_Power_H */


/* [] END OF FILE */
