/* 
Main File of Sensor Node
*/
//Standard Libraries to be included plus customized sensor header files
#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include "neomote.h"
#include <FS.h>
#include "I2C_1.h"
//Customized libraries
#include "SoilMoisture_Decagon.h"
#include "Ultrasonic_Maxbotix.h"

//Glabal Variable
uint8 Debug_Timer;

#define SENSIRION_ADDR 0b1000000
#define SENSIRION_RH_COMMAND 0b11100101
#define SENSIRION_TEMP_COMMAND 0b11100011

struct{
    
//float temp;
//float rh;    
uint16 temp;
uint16 rh;

}typedef SensirionData;

//==========//==========//==========//==========//==========//==========//==========//==========//==========

//Create a structure Wireless_Packet for data transmission to the manager
struct {
    DecagonGS3 SoilMoisture;
    //Here we need to add strucutre for the ultrasonic reading for consistency and good practice.  
    MaxbotixUltrasonic Depth;
    SensirionData TempRH;
    
    NeoRtcTimeStruct time;
}typedef Wireless_Packet;




//==========//==========//==========//==========//==========//==========//==========//==========//==========

void rtcCallBackReceived(uint8 alarmType);

void Write_To_SD_Card(const char * fileName, const char * pMode, const void * pData, U32 NumBytes);

void TakeReading();

//==========//==========//==========//==========//==========//==========//==========//==========//==========

//Debug shortening fire time t8g
void TakeReading(){
        Wireless_Packet Packet;
        
        //set time information of the packet to the RTC 
        Packet.time = NeoRTC_Read_Time();
        
        //set soilmoisture information of packet to a reading from the Soilmoisture sensor
        Packet.SoilMoisture = SoilMoisture_Decagon_Take_Reading();
        Packet.Depth = Ultrasonic_Maxbotix_Take_Reading();
//        Packet.TempRH = Take_TempRH_Reading();
        
        uint8 x =0;
        Mote_Send_Packet(&Packet,sizeof(Wireless_Packet));
}

//==========//==========//==========//==========//==========//==========//==========//==========//==========


//SD CARD WRITE
void Write_To_SD_Card(const char * fileName, const char * pMode, const void * pData, U32 NumBytes){
    
    NEOMOTE_1_SD_Card_Power_Write(0u); // Power on SD Card
    FS_FILE * pFile;
    
    char sdVolName[10]; // Buffer that will hold SD card volume name.
    
    if(0 != FS_GetVolumeName(0, &sdVolName[0], 9)){
        pFile = FS_FOpen(fileName, pMode);
        if (pFile == 0){ // If the SD card doesn't open.
            FS_DeInit();
            FS_Init();
            pFile = FS_FOpen(fileName, pMode);
        }
        FS_Write(pFile, pData, NumBytes);
        FS_FClose(pFile);
    }
    NEOMOTE_1_SD_Card_Power_Write(1u); // Power off SD Card.
}


//==========//==========//==========//==========//==========//==========//==========//==========//==========


//The function to test whether the PSoC is communicating with the manager.
void moteNotificationReceived(NeoMoteNotification notification){
    
    //If an event happens
    if(notification.type == TYPE_MOTE_EVENT){
        //set variable to be check - payload from notification structure
        uint8 type = notification.payload[0];
        //If the notification return is EVENT_MOTE_OPERATIONAL
        //Statement = True means we have a connection!!!
        if(type == EVENT_MOTE_OPERATIONAL){
            //dummy variable to insert break points
            uint8 x=0;
        }
    }
    
    else if(notification.type == TYPE_MOTE_DATA){
    }
    
}

//==========//==========//==========//==========//==========//==========//==========//==========//==========

//Main function of the sesor nodes.
int main()
{
    Debug_Timer = 0;
    //Enable Global Interrupt
    CYGlobalIntEnable;

   
    
    //Startup the SoilMoisture UART
    //SoilMoisture_Decagon_Start();
    UART_SoilMoisture_Decagon_Start();
    
    //Startup the Maxbotix UART
    //Ultrasonic_Maxbotix_Start();
    UART_Ultrasonic_Maxbotix_Start();
    
    
    //=======================Real Time Clock Section=======================
    NeoRTC_Start(rtcCallBackReceived); // Start and enable the RTC.
    NeoRTC_Set_Repeating_Minute_Alarm(1u);
    NeoRTC_Enable_Second_Interrupt();
    
    Mote_Start(moteNotificationReceived);
  
    FS_Init(); // Start the File Systm.
    
//    File Location Lookup
    FS_Init(); // Start the File System.
    uint8 x1=0;
    
    for(;;){
        NeoRTC_Process_Tasks();
        Mote_Process_Tasks();

    }
    //==============================================

}


//==========//==========//==========//==========//==========//==========//==========//==========//==========

void rtcCallBackReceived(uint8 alarmType){ // RTC Event Handler.
    if(alarmType == RTC_SECOND_ALARM){
        Debug_Timer = Debug_Timer + 1;
        uint8 xx = 0;
        if (Debug_Timer == 5){
            TakeReading();
            Debug_Timer = 0;
        }

        
    }else if(alarmType == RTC_MINUTE_ALARM){
        Wireless_Packet Packet;
        
        //set time information of the packet to the RTC 
        Packet.time = NeoRTC_Read_Time();
        
        //set soilmoisture information of packet to a reading from the Soilmoisture sensor
        Packet.SoilMoisture = SoilMoisture_Decagon_Take_Reading();
        Packet.Depth = Ultrasonic_Maxbotix_Take_Reading();
//        Packet.TempRH = Take_TempRH_Reading();
        
        uint8 x =0;
        Mote_Send_Packet(&Packet,sizeof(Wireless_Packet));

        
        //Write to SD card
        //Write_To_SD_Card("myData.txt","a",sendBuffer,strlen(sendBuffer));
    }

}

//==========//==========//==========//==========//==========//==========//==========//==========//==========


/*

uint16 Get_SensironValue(uint8 sensorCommand){
    //send command to sensor to take reading
    I2C_1_MasterClearStatus();
    I2C_1_MasterWriteBuf(SENSIRION_ADDR, &sensorCommand,1,
    I2C_1_MODE_COMPLETE_XFER);
    
    //wait until sensor responds
    while(0u == (I2C_1_MasterStatus() & I2C_1_MSTAT_WR_CMPLT));
    
    //read value from sensor
    uint8 i2cBufferRead[2];
    I2C_1_MasterClearStatus();
    I2C_1_MasterReadBuf(SENSIRION_ADDR, i2cBufferRead, 2,
    I2C_1_MODE_COMPLETE_XFER);
    
    //wait until sensor responds
    while(0u == (I2C_1_MasterStatus() & I2C_1_MSTAT_RD_CMPLT));
    
    //convert two bytes into 16-bit integer
    uint16 returnValue = (i2cBufferRead[0] <<8) + i2cBufferRead[1];
    return returnValue;
}
SensirionData Take_TempRH_Reading(){

    //delay 15ms based on data sheet
    CyDelay(15u);
    
    //turn power on to sensor
    SensirionData returnValue;
    Digital_Sensor_Power_Write(1u);
    uint16 RH;
    uint16 TEMP;
    
    
    RH = Get_SensironValue(SENSIRION_RH_COMMAND);
    //Calibration
    returnValue.rh = -6 + 125*(RH/65532);
    
    TEMP = Get_SensironValue(SENSIRION_TEMP_COMMAND);
    //Calibration
    returnValue.temp = -46.85 + 175.72*(TEMP/65532);
    
  
    float RH = (float) Get_SensironValue(SENSIRION_RH_COMMAND);
    returnValue.rh = -6 + 125*(RH/65532);
    
    float TEMP = (float) Get_SensironValue(SENSIRION_TEMP_COMMAND);
    returnValue.temp = -46.85 + 175.72*(TEMP/65532);
  
    
    //turn sensor off
    Digital_Sensor_Power_Write(0u);
    
    return returnValue;
}

*/

