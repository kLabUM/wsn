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
#include "isr_Ultrasonic_Maxbotix.h"

void Ultrasonic_Maxbotix_Start();

//uint32 Ultrasonic_Maxbotix_Take_Reading();
//uint32 Ultrasonic_Maxbotix_Convert_Raw_Reading(uint8* raw);


struct {
    uint32 depth;
    uint8 valid;
}typedef MaxbotixUltrasonic;

MaxbotixUltrasonic Ultrasonic_Maxbotix_Take_Reading();
MaxbotixUltrasonic Ultrasonic_Maxbotix_Convert_Raw_Reading(uint8* raw_M);




