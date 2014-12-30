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
#include "isr_SoilMoisture_Decagon.h"

struct {
    float dielectric;
    float temp;
    float soilMoisture;
    uint16 conductivity;
    uint8 valid;
}typedef DecagonGS3;




void SoilMoisture_Decagon_Start();
DecagonGS3 SoilMoisture_Decagon_Take_Reading();
DecagonGS3 SoilMoisture_Decagon_Convert_Raw_Reading(uint8* raw_D);






/* [] END OF FILE */
