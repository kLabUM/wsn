#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include "SoilMoisture_Decagon.h"

#include "neomote.h"

//================================================== Wireless Section ==================================================

struct {
    NeoRtcTimeStruct time;
    DecagonGS3 SoilMoisture;
    
}typedef Wireless_Packet;



void rtcCallBackReceived(uint8 alarmType);

void moteNotificationReceived(NeoMoteNotification notification){
        
    if(notification.type == TYPE_MOTE_EVENT){
        uint8 type = notification.payload[0];
        if(type == EVENT_MOTE_OPERATIONAL){
           uint8 x=0;
        }
    }
    else if(notification.type == TYPE_MOTE_DATA){
       
    }
    
}







//================================================== Main Section ==================================================

int main()
{

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    CYGlobalIntEnable;
    
    SoilMoisture_Decagon_Start();
    
    
    //=======================Real Time Clock Section=======================
    NeoRTC_Start(rtcCallBackReceived); // Start and enable the RTC.
    NeoRTC_Set_Repeating_Minute_Alarm(1u);
    NeoRTC_Enable_Second_Interrupt();
        Mote_Start(moteNotificationReceived);
    for(;;){
        NeoRTC_Process_Tasks();
        Mote_Process_Tasks();
    }
    //==============================================
    

}
    
//================================================== Real Time Clock Section ==================================================
 
void rtcCallBackReceived(uint8 alarmType){ // RTC Event Handler.
    if(alarmType == RTC_SECOND_ALARM){
        
    }else if(alarmType == RTC_MINUTE_ALARM){
        Wireless_Packet Packet;
        Packet.time = NeoRTC_Read_Time();
        
        Packet.SoilMoisture = SoilMoisture_Decagon_Take_Reading();
        uint8 x =0;
        //Mote_Send_Packet(Packet,sizeof(Wireless_Packet))
    
    }

}



//================================================== Wireless Section ==================================================
    

    
//================================================== Wireless Section ==================================================
    
  

