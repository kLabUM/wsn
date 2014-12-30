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
#include <string.h>
#include "UART_Maxbotix.h"
#define RAW_SERIAL_DATA_LENGTH 30
#define VALUES_ARRAY_LENGTH 5
uint8 raw_serial_data[RAW_SERIAL_DATA_LENGTH];
uint8 raw_serial_data_count;
CY_ISR_PROTO(IntUartRx);

void Ultrasonic_Maxbotix_Start(){
    
    UART_Maxbotix_Start();

}

CY_ISR(IntUartRx)
{
   uint8 getchar;
   getchar  = UART_Maxbotix_GetChar();
        
   if(getchar > 0u && raw_serial_data_count < RAW_SERIAL_DATA_LENGTH){
        raw_serial_data[raw_serial_data_count] = getchar;
        raw_serial_data_count++;
        }   
    
}

uint32 Ultrasonic_Maxbotix_Convert_Raw_Reading(uint8* raw){
    uint32 values[VALUES_ARRAY_LENGTH];
    char* token;
    uint8 value_count = 0u;
    token = strtok(raw,"\r");
    while(token != NULL){
        uint32 value;
        uint32 scan_valid;
        scan_valid = sscanf(token,"R%d",&value);
        if (scan_valid != 0){
            values[value_count] = value;
            value_count++;
            if (value_count == VALUES_ARRAY_LENGTH){
                break;
            }
        
        }
        token = strtok(NULL,"\r");
        
    }
    uint32 final_value = 0u;
    
    int i = 0;
    for(i = 0; i < VALUES_ARRAY_LENGTH+1; i++){
        final_value = final_value + values[i];
    }
    final_value = final_value/VALUES_ARRAY_LENGTH;

    return final_value;
    

    
}

uint32 Ultrasonic_Maxbotix_Take_Reading(){

//    uint8 getchar;
    //uint8 arraycount = 0u;
    raw_serial_data_count = 0u;
    isr_Ultrasonic_Maxbotix_StartEx(IntUartRx);
    CyDelay(1000u);
    isr_Ultrasonic_Maxbotix_Stop();
/*    while(1){
        getchar  = UART_Maxbotix_GetChar();
        
        if(getchar > 0u){
            raw_serial_data[arraycount] = getchar;
            arraycount++;
            if (arraycount == RAW_SERIAL_DATA_LENGTH){
                break;
            }
        }   
    }*/
    uint32 depth;
    depth = Ultrasonic_Maxbotix_Convert_Raw_Reading(raw_serial_data);
    return depth;
}

