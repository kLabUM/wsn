//==============================Header File/Global Variable==============================
//Standard String Library
#include <string.h>
//Import the header file that has all the files listed for use in the master file later
#include "SoilMoisture_Decagon.h"
//Global Variable for the number of characters received from the UART reading
#define RAW_SERIAL_DATA_LENGTH_d 100
//How many reading to we want to average by after the reading's been parsed.
#define VALUES_ARRAY_LENGTH 6
//This is where we stored the initial UART reading result
uint8 raw_serial_data_d[RAW_SERIAL_DATA_LENGTH_d];
//counter for interrupt readings
uint8 raw_serial_data_count_d;

//CY_ISR_PROTO(IntUartRx);


//===============================Start Function==============================
void SoilMoisture_Decagon_Start(){

    //Call the UART Start 
    UART_SoilMoisture_Decagon_Start();

}

//===============================Interrupt Function==============================
CY_ISR(IntUartRx_D)
{
   uint8 getchar;
   getchar  = UART_SoilMoisture_Decagon_GetChar();
        
   if(getchar > 0u && raw_serial_data_count_d < RAW_SERIAL_DATA_LENGTH_d){
        raw_serial_data_d[raw_serial_data_count_d] = getchar;
        raw_serial_data_count_d++;
        }   
    
}

//===============================Data Conversion Function==============================
//WATCH IT HERE!!
//Still needs to figure out what to do with the parsing Item
/*
DecagonGS3 SoilMoisture_Decagon_Convert_Raw_Reading(uint8* raw_D){
    DecagonGS3 final_reading;
    final_reading.valid = 0u;
        
    final_reading.valid  = sscanf(raw_D,"\x09%f %f %d\x0d%s",&final_reading.dielectric,
                                &final_reading.temp,&final_reading.conductivity,NULL);
    
    if(final_reading.valid != 4){
        final_reading.valid = 0;
    }
    
    return final_reading;
    
}
*/
//===
DecagonGS3 SoilMoisture_Decagon_Convert_Raw_Reading(uint8* raw_D){
    DecagonGS3 final_reading;
    final_reading.valid = 0u;

    //
    
    final_reading.valid  = sscanf(raw_D,"\x09%f %f %d\r%s",&final_reading.dielectric,
                                &final_reading.temp,&final_reading.conductivity,NULL);

    if(final_reading.valid != 4){
        final_reading.valid = 0;
    }
    
    return final_reading;
    
}
//===


DecagonGS3 SoilMoisture_Decagon_Take_Reading(){

//    uint8 getchar;
    //uint8 arraycount = 0u;
    raw_serial_data_count_d = 0u;
    CyDelay(1000u);
    Decagon_Sensor_Power_Write(0u); 
    isr_SoilMoisture_Decagon_StartEx(IntUartRx_D);
    CyDelay(2000u);
    Decagon_Sensor_Power_Write(1u);
    isr_SoilMoisture_Decagon_Stop();

    DecagonGS3 SoilMoisture;
    SoilMoisture = SoilMoisture_Decagon_Convert_Raw_Reading(raw_serial_data_d);
    return SoilMoisture;
}


/*    while(1){
        getchar  = UART_Maxbotix_GetChar();
        
        if(getchar > 0u){
            raw_serial_data_d[arraycount] = getchar;
            arraycount++;
            if (arraycount == RAW_SERIAL_DATA_LENGTH_d){
                break;
            }
        }   
    }*/