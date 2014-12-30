/*******************************************************************************
* File Name: NEOMOTE_1_DELAY_COUNTER_PM.c  
* Version 2.40
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "NEOMOTE_1_DELAY_COUNTER.h"

static NEOMOTE_1_DELAY_COUNTER_backupStruct NEOMOTE_1_DELAY_COUNTER_backup;


/*******************************************************************************
* Function Name: NEOMOTE_1_DELAY_COUNTER_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  NEOMOTE_1_DELAY_COUNTER_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void NEOMOTE_1_DELAY_COUNTER_SaveConfig(void) 
{
    #if (!NEOMOTE_1_DELAY_COUNTER_UsingFixedFunction)

        NEOMOTE_1_DELAY_COUNTER_backup.CounterUdb = NEOMOTE_1_DELAY_COUNTER_ReadCounter();

        #if (CY_UDB_V0)
            NEOMOTE_1_DELAY_COUNTER_backup.CounterPeriod = NEOMOTE_1_DELAY_COUNTER_ReadPeriod();
            NEOMOTE_1_DELAY_COUNTER_backup.CompareValue = NEOMOTE_1_DELAY_COUNTER_ReadCompare();
            NEOMOTE_1_DELAY_COUNTER_backup.InterruptMaskValue = NEOMOTE_1_DELAY_COUNTER_STATUS_MASK;
        #endif /* CY_UDB_V0 */

        #if(!NEOMOTE_1_DELAY_COUNTER_ControlRegRemoved)
            NEOMOTE_1_DELAY_COUNTER_backup.CounterControlRegister = NEOMOTE_1_DELAY_COUNTER_ReadControlRegister();
        #endif /* (!NEOMOTE_1_DELAY_COUNTER_ControlRegRemoved) */

    #endif /* (!NEOMOTE_1_DELAY_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: NEOMOTE_1_DELAY_COUNTER_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  NEOMOTE_1_DELAY_COUNTER_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void NEOMOTE_1_DELAY_COUNTER_RestoreConfig(void) 
{      
    #if (!NEOMOTE_1_DELAY_COUNTER_UsingFixedFunction)

        #if (CY_UDB_V0)
            uint8 NEOMOTE_1_DELAY_COUNTER_interruptState;
        #endif  /* (CY_UDB_V0) */

       NEOMOTE_1_DELAY_COUNTER_WriteCounter(NEOMOTE_1_DELAY_COUNTER_backup.CounterUdb);

        #if (CY_UDB_V0)
            NEOMOTE_1_DELAY_COUNTER_WritePeriod(NEOMOTE_1_DELAY_COUNTER_backup.CounterPeriod);
            NEOMOTE_1_DELAY_COUNTER_WriteCompare(NEOMOTE_1_DELAY_COUNTER_backup.CompareValue);

            NEOMOTE_1_DELAY_COUNTER_interruptState = CyEnterCriticalSection();
            NEOMOTE_1_DELAY_COUNTER_STATUS_AUX_CTRL |= NEOMOTE_1_DELAY_COUNTER_STATUS_ACTL_INT_EN_MASK;
            CyExitCriticalSection(NEOMOTE_1_DELAY_COUNTER_interruptState);

            NEOMOTE_1_DELAY_COUNTER_STATUS_MASK = NEOMOTE_1_DELAY_COUNTER_backup.InterruptMaskValue;
        #endif  /* (CY_UDB_V0) */

        #if(!NEOMOTE_1_DELAY_COUNTER_ControlRegRemoved)
            NEOMOTE_1_DELAY_COUNTER_WriteControlRegister(NEOMOTE_1_DELAY_COUNTER_backup.CounterControlRegister);
        #endif /* (!NEOMOTE_1_DELAY_COUNTER_ControlRegRemoved) */

    #endif /* (!NEOMOTE_1_DELAY_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: NEOMOTE_1_DELAY_COUNTER_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  NEOMOTE_1_DELAY_COUNTER_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void NEOMOTE_1_DELAY_COUNTER_Sleep(void) 
{
    #if(!NEOMOTE_1_DELAY_COUNTER_ControlRegRemoved)
        /* Save Counter's enable state */
        if(NEOMOTE_1_DELAY_COUNTER_CTRL_ENABLE == (NEOMOTE_1_DELAY_COUNTER_CONTROL & NEOMOTE_1_DELAY_COUNTER_CTRL_ENABLE))
        {
            /* Counter is enabled */
            NEOMOTE_1_DELAY_COUNTER_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            NEOMOTE_1_DELAY_COUNTER_backup.CounterEnableState = 0u;
        }
    #else
        NEOMOTE_1_DELAY_COUNTER_backup.CounterEnableState = 1u;
        if(NEOMOTE_1_DELAY_COUNTER_backup.CounterEnableState != 0u)
        {
            NEOMOTE_1_DELAY_COUNTER_backup.CounterEnableState = 0u;
        }
    #endif /* (!NEOMOTE_1_DELAY_COUNTER_ControlRegRemoved) */
    
    NEOMOTE_1_DELAY_COUNTER_Stop();
    NEOMOTE_1_DELAY_COUNTER_SaveConfig();
}


/*******************************************************************************
* Function Name: NEOMOTE_1_DELAY_COUNTER_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  NEOMOTE_1_DELAY_COUNTER_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void NEOMOTE_1_DELAY_COUNTER_Wakeup(void) 
{
    NEOMOTE_1_DELAY_COUNTER_RestoreConfig();
    #if(!NEOMOTE_1_DELAY_COUNTER_ControlRegRemoved)
        if(NEOMOTE_1_DELAY_COUNTER_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            NEOMOTE_1_DELAY_COUNTER_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!NEOMOTE_1_DELAY_COUNTER_ControlRegRemoved) */
    
}


/* [] END OF FILE */
