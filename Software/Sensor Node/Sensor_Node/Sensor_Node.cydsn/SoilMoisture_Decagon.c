//==============================Header File/Global Variable==============================
//Standard String Library
#include <string.h>
//Import the header file that has all the files listed for use in the master file later
#include "SoilMoisture_Decagon.h"
//Global Variable for the number of characters received from the UART reading
#define RAW_SERIAL_DATA_LENGTH 100
//How many reading to we want to average by after the reading's been parsed.
#define VALUES_ARRAY_LENGTH 6
//This is where we stored the initial UART reading result
uint8 raw_serial_data[RAW_SERIAL_DATA_LENGTH];
//counter for interrupt readings
uint8 raw_serial_data_count;

CY_ISR_PROTO(IntUartRx);


//===============================Start Function==============================
void SoilMoisture_Decagon_Start(){

    //Call the UART Start 
    UART_SoilMoisture_Decagon_Start();

}

//===============================Interrupt Function==============================
CY_ISR(IntUartRx)
{
   uint8 getchar;
   getchar  = UART_SoilMoisture_Decagon_GetChar();
        
   if(getchar > 0u && raw_serial_data_count < RAW_SERIAL_DATA_LENGTH){
        raw_serial_data[raw_serial_data_count] = getchar;
        raw_serial_data_count++;
        }   
    
}

//===============================Data Conversion Function==============================
//WATCH IT HERE!!
//Still needs to figure out what to do with the parsing Item
DecagonGS3 SoilMoisture_Decagon_Convert_Raw_Reading(uint8* raw){
    DecagonGS3 final_reading;
    final_reading.valid = 0u;
    
    final_reading.valid  = sscanf(raw,"\x09%f %f %d\x0d%s",&final_reading.dielectric,
                                &final_reading.temp,&final_reading.conductivity,NULL);
    
    if(final_reading.valid != 4){
        final_reading.valid = 0;
    }
    
    return final_reading;
    
}

DecagonGS3 SoilMoisture_Decagon_Take_Reading(){

//    uint8 getchar;
    //uint8 arraycount = 0u;
    raw_serial_data_count = 0u;
    CyDelay(1000u);
    Sensor_Power_Write(0u); 
    isr_SoilMoisture_Decagon_StartEx(IntUartRx);
    CyDelay(2000u);
    Sensor_Power_Write(1u);
    isr_SoilMoisture_Decagon_Stop();
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
    DecagonGS3 SoilMoisture;
    SoilMoisture = SoilMoisture_Decagon_Convert_Raw_Reading(raw_serial_data);
    return SoilMoisture;
}