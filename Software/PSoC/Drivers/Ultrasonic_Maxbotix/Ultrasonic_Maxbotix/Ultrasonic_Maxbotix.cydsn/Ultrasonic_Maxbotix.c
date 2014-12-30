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
#include "Ultrasonic_Maxbotix.h"
#define RAW_SERIAL_DATA_LENGTH_m 30
#define VALUES_ARRAY_LENGTH 5
uint8 raw_serial_data_m[RAW_SERIAL_DATA_LENGTH_m];
uint8 raw_serial_data_count_m;

CY_ISR_PROTO(IntUartRx_M);

void Ultrasonic_Maxbotix_Start(){
    
    UART_Ultrasonic_Maxbotix_Start();

}

CY_ISR(IntUartRx_M)
{
   uint8 getchar;
   getchar  = UART_Ultrasonic_Maxbotix_GetChar();
        
   if(getchar > 0u && raw_serial_data_count_m < RAW_SERIAL_DATA_LENGTH_m){
        raw_serial_data_m[raw_serial_data_count_m] = getchar;
        raw_serial_data_count_m++;
        }   
    
}

MaxbotixUltrasonic Ultrasonic_Maxbotix_Convert_Raw_Reading(uint8* raw_M){
    uint32 values[VALUES_ARRAY_LENGTH];
    char* token;
    uint8 value_count = 0u;
    token = strtok(raw_M,"\r");
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
    //uint32 final_value = 0u;
    
    MaxbotixUltrasonic final_value;
    final_value.valid = 0u;    
    
    
    int i = 0;
    for(i = 0; i < VALUES_ARRAY_LENGTH+1; i++){
        final_value.depth = final_value.depth + values[i];
    }
    final_value.depth = final_value.depth/VALUES_ARRAY_LENGTH;

    return final_value;
    

    
}

MaxbotixUltrasonic Ultrasonic_Maxbotix_Take_Reading(){

//    uint8 getchar;
    //uint8 arraycount = 0u;
    raw_serial_data_count_m = 0u;
    isr_Ultrasonic_Maxbotix_StartEx(IntUartRx_M);
    CyDelay(1000u);
    isr_Ultrasonic_Maxbotix_Stop();
/*    while(1){
        getchar  = UART_Maxbotix_GetChar();
        
        if(getchar > 0u){
            raw_serial_data_m[arraycount] = getchar;
            arraycount++;
            if (arraycount == RAW_SERIAL_DATA_LENGTH_m){
                break;
            }
        }   
    }*/
    MaxbotixUltrasonic depth;
    depth = Ultrasonic_Maxbotix_Convert_Raw_Reading(raw_serial_data_m);
    return depth;
}

