/*******************************************************************************
* File Name: UART_Ultrasonic_Maxbotix_PM.c
* Version 2.30
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_Ultrasonic_Maxbotix.h"


/***************************************
* Local data allocation
***************************************/

static UART_Ultrasonic_Maxbotix_BACKUP_STRUCT  UART_Ultrasonic_Maxbotix_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: UART_Ultrasonic_Maxbotix_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_Ultrasonic_Maxbotix_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_Ultrasonic_Maxbotix_SaveConfig(void)
{
    #if (CY_UDB_V0)

        #if(UART_Ultrasonic_Maxbotix_CONTROL_REG_REMOVED == 0u)
            UART_Ultrasonic_Maxbotix_backup.cr = UART_Ultrasonic_Maxbotix_CONTROL_REG;
        #endif /* End UART_Ultrasonic_Maxbotix_CONTROL_REG_REMOVED */

        #if( (UART_Ultrasonic_Maxbotix_RX_ENABLED) || (UART_Ultrasonic_Maxbotix_HD_ENABLED) )
            UART_Ultrasonic_Maxbotix_backup.rx_period = UART_Ultrasonic_Maxbotix_RXBITCTR_PERIOD_REG;
            UART_Ultrasonic_Maxbotix_backup.rx_mask = UART_Ultrasonic_Maxbotix_RXSTATUS_MASK_REG;
            #if (UART_Ultrasonic_Maxbotix_RXHW_ADDRESS_ENABLED)
                UART_Ultrasonic_Maxbotix_backup.rx_addr1 = UART_Ultrasonic_Maxbotix_RXADDRESS1_REG;
                UART_Ultrasonic_Maxbotix_backup.rx_addr2 = UART_Ultrasonic_Maxbotix_RXADDRESS2_REG;
            #endif /* End UART_Ultrasonic_Maxbotix_RXHW_ADDRESS_ENABLED */
        #endif /* End UART_Ultrasonic_Maxbotix_RX_ENABLED | UART_Ultrasonic_Maxbotix_HD_ENABLED*/

        #if(UART_Ultrasonic_Maxbotix_TX_ENABLED)
            #if(UART_Ultrasonic_Maxbotix_TXCLKGEN_DP)
                UART_Ultrasonic_Maxbotix_backup.tx_clk_ctr = UART_Ultrasonic_Maxbotix_TXBITCLKGEN_CTR_REG;
                UART_Ultrasonic_Maxbotix_backup.tx_clk_compl = UART_Ultrasonic_Maxbotix_TXBITCLKTX_COMPLETE_REG;
            #else
                UART_Ultrasonic_Maxbotix_backup.tx_period = UART_Ultrasonic_Maxbotix_TXBITCTR_PERIOD_REG;
            #endif /*End UART_Ultrasonic_Maxbotix_TXCLKGEN_DP */
            UART_Ultrasonic_Maxbotix_backup.tx_mask = UART_Ultrasonic_Maxbotix_TXSTATUS_MASK_REG;
        #endif /*End UART_Ultrasonic_Maxbotix_TX_ENABLED */


    #else /* CY_UDB_V1 */

        #if(UART_Ultrasonic_Maxbotix_CONTROL_REG_REMOVED == 0u)
            UART_Ultrasonic_Maxbotix_backup.cr = UART_Ultrasonic_Maxbotix_CONTROL_REG;
        #endif /* End UART_Ultrasonic_Maxbotix_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: UART_Ultrasonic_Maxbotix_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_Ultrasonic_Maxbotix_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_Ultrasonic_Maxbotix_RestoreConfig(void)
{

    #if (CY_UDB_V0)

        #if(UART_Ultrasonic_Maxbotix_CONTROL_REG_REMOVED == 0u)
            UART_Ultrasonic_Maxbotix_CONTROL_REG = UART_Ultrasonic_Maxbotix_backup.cr;
        #endif /* End UART_Ultrasonic_Maxbotix_CONTROL_REG_REMOVED */

        #if( (UART_Ultrasonic_Maxbotix_RX_ENABLED) || (UART_Ultrasonic_Maxbotix_HD_ENABLED) )
            UART_Ultrasonic_Maxbotix_RXBITCTR_PERIOD_REG = UART_Ultrasonic_Maxbotix_backup.rx_period;
            UART_Ultrasonic_Maxbotix_RXSTATUS_MASK_REG = UART_Ultrasonic_Maxbotix_backup.rx_mask;
            #if (UART_Ultrasonic_Maxbotix_RXHW_ADDRESS_ENABLED)
                UART_Ultrasonic_Maxbotix_RXADDRESS1_REG = UART_Ultrasonic_Maxbotix_backup.rx_addr1;
                UART_Ultrasonic_Maxbotix_RXADDRESS2_REG = UART_Ultrasonic_Maxbotix_backup.rx_addr2;
            #endif /* End UART_Ultrasonic_Maxbotix_RXHW_ADDRESS_ENABLED */
        #endif  /* End (UART_Ultrasonic_Maxbotix_RX_ENABLED) || (UART_Ultrasonic_Maxbotix_HD_ENABLED) */

        #if(UART_Ultrasonic_Maxbotix_TX_ENABLED)
            #if(UART_Ultrasonic_Maxbotix_TXCLKGEN_DP)
                UART_Ultrasonic_Maxbotix_TXBITCLKGEN_CTR_REG = UART_Ultrasonic_Maxbotix_backup.tx_clk_ctr;
                UART_Ultrasonic_Maxbotix_TXBITCLKTX_COMPLETE_REG = UART_Ultrasonic_Maxbotix_backup.tx_clk_compl;
            #else
                UART_Ultrasonic_Maxbotix_TXBITCTR_PERIOD_REG = UART_Ultrasonic_Maxbotix_backup.tx_period;
            #endif /*End UART_Ultrasonic_Maxbotix_TXCLKGEN_DP */
            UART_Ultrasonic_Maxbotix_TXSTATUS_MASK_REG = UART_Ultrasonic_Maxbotix_backup.tx_mask;
        #endif /*End UART_Ultrasonic_Maxbotix_TX_ENABLED */

    #else /* CY_UDB_V1 */

        #if(UART_Ultrasonic_Maxbotix_CONTROL_REG_REMOVED == 0u)
            UART_Ultrasonic_Maxbotix_CONTROL_REG = UART_Ultrasonic_Maxbotix_backup.cr;
        #endif /* End UART_Ultrasonic_Maxbotix_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: UART_Ultrasonic_Maxbotix_Sleep
********************************************************************************
*
* Summary:
*  Stops and saves the user configuration. Should be called
*  just prior to entering sleep.
*
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_Ultrasonic_Maxbotix_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_Ultrasonic_Maxbotix_Sleep(void)
{

    #if(UART_Ultrasonic_Maxbotix_RX_ENABLED || UART_Ultrasonic_Maxbotix_HD_ENABLED)
        if((UART_Ultrasonic_Maxbotix_RXSTATUS_ACTL_REG  & UART_Ultrasonic_Maxbotix_INT_ENABLE) != 0u)
        {
            UART_Ultrasonic_Maxbotix_backup.enableState = 1u;
        }
        else
        {
            UART_Ultrasonic_Maxbotix_backup.enableState = 0u;
        }
    #else
        if((UART_Ultrasonic_Maxbotix_TXSTATUS_ACTL_REG  & UART_Ultrasonic_Maxbotix_INT_ENABLE) !=0u)
        {
            UART_Ultrasonic_Maxbotix_backup.enableState = 1u;
        }
        else
        {
            UART_Ultrasonic_Maxbotix_backup.enableState = 0u;
        }
    #endif /* End UART_Ultrasonic_Maxbotix_RX_ENABLED || UART_Ultrasonic_Maxbotix_HD_ENABLED*/

    UART_Ultrasonic_Maxbotix_Stop();
    UART_Ultrasonic_Maxbotix_SaveConfig();
}


/*******************************************************************************
* Function Name: UART_Ultrasonic_Maxbotix_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_Ultrasonic_Maxbotix_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_Ultrasonic_Maxbotix_Wakeup(void)
{
    UART_Ultrasonic_Maxbotix_RestoreConfig();
    #if( (UART_Ultrasonic_Maxbotix_RX_ENABLED) || (UART_Ultrasonic_Maxbotix_HD_ENABLED) )
        UART_Ultrasonic_Maxbotix_ClearRxBuffer();
    #endif /* End (UART_Ultrasonic_Maxbotix_RX_ENABLED) || (UART_Ultrasonic_Maxbotix_HD_ENABLED) */
    #if(UART_Ultrasonic_Maxbotix_TX_ENABLED || UART_Ultrasonic_Maxbotix_HD_ENABLED)
        UART_Ultrasonic_Maxbotix_ClearTxBuffer();
    #endif /* End UART_Ultrasonic_Maxbotix_TX_ENABLED || UART_Ultrasonic_Maxbotix_HD_ENABLED */

    if(UART_Ultrasonic_Maxbotix_backup.enableState != 0u)
    {
        UART_Ultrasonic_Maxbotix_Enable();
    }
}


/* [] END OF FILE */
