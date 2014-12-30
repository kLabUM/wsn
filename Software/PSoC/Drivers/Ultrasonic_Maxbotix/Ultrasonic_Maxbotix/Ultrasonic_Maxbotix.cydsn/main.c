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
#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include "Ultrasonic_Maxbotix.h"


int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    CYGlobalIntEnable;
    
    Ultrasonic_Maxbotix_Start();
    
    

    
    for(;;)
    {
        
        uint32 Maxbotix_reading;
        /* Place your application code here. */
        LED_Red_Write(1u);
        LED_White_Write(1u);
        
        Maxbotix_reading = Ultrasonic_Maxbotix_Take_Reading();
        
        LED_Red_Write(0u);
        LED_White_Write(0u);
        CyDelay(200u);
    }
}

/* [] END OF FILE */
