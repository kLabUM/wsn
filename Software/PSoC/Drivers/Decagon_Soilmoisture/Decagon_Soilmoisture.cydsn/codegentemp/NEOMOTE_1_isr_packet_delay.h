/*******************************************************************************
* File Name: NEOMOTE_1_isr_packet_delay.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_NEOMOTE_1_isr_packet_delay_H)
#define CY_ISR_NEOMOTE_1_isr_packet_delay_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void NEOMOTE_1_isr_packet_delay_Start(void);
void NEOMOTE_1_isr_packet_delay_StartEx(cyisraddress address);
void NEOMOTE_1_isr_packet_delay_Stop(void);

CY_ISR_PROTO(NEOMOTE_1_isr_packet_delay_Interrupt);

void NEOMOTE_1_isr_packet_delay_SetVector(cyisraddress address);
cyisraddress NEOMOTE_1_isr_packet_delay_GetVector(void);

void NEOMOTE_1_isr_packet_delay_SetPriority(uint8 priority);
uint8 NEOMOTE_1_isr_packet_delay_GetPriority(void);

void NEOMOTE_1_isr_packet_delay_Enable(void);
uint8 NEOMOTE_1_isr_packet_delay_GetState(void);
void NEOMOTE_1_isr_packet_delay_Disable(void);

void NEOMOTE_1_isr_packet_delay_SetPending(void);
void NEOMOTE_1_isr_packet_delay_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the NEOMOTE_1_isr_packet_delay ISR. */
#define NEOMOTE_1_isr_packet_delay_INTC_VECTOR            ((reg32 *) NEOMOTE_1_isr_packet_delay__INTC_VECT)

/* Address of the NEOMOTE_1_isr_packet_delay ISR priority. */
#define NEOMOTE_1_isr_packet_delay_INTC_PRIOR             ((reg8 *) NEOMOTE_1_isr_packet_delay__INTC_PRIOR_REG)

/* Priority of the NEOMOTE_1_isr_packet_delay interrupt. */
#define NEOMOTE_1_isr_packet_delay_INTC_PRIOR_NUMBER      NEOMOTE_1_isr_packet_delay__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable NEOMOTE_1_isr_packet_delay interrupt. */
#define NEOMOTE_1_isr_packet_delay_INTC_SET_EN            ((reg32 *) NEOMOTE_1_isr_packet_delay__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the NEOMOTE_1_isr_packet_delay interrupt. */
#define NEOMOTE_1_isr_packet_delay_INTC_CLR_EN            ((reg32 *) NEOMOTE_1_isr_packet_delay__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the NEOMOTE_1_isr_packet_delay interrupt state to pending. */
#define NEOMOTE_1_isr_packet_delay_INTC_SET_PD            ((reg32 *) NEOMOTE_1_isr_packet_delay__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the NEOMOTE_1_isr_packet_delay interrupt. */
#define NEOMOTE_1_isr_packet_delay_INTC_CLR_PD            ((reg32 *) NEOMOTE_1_isr_packet_delay__INTC_CLR_PD_REG)


#endif /* CY_ISR_NEOMOTE_1_isr_packet_delay_H */


/* [] END OF FILE */
