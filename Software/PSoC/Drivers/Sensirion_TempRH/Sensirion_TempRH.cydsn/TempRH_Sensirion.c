#include <string.h>
#include "TempRH_Sensirion.h"

#define SENSIRION_ADDR 0b1000000
#define SENSIRION_RH_COMMAND 0b11100101
#define SENSIRION_TEMP_COMMAND 0b11100011

//uint16 Get_SensironValue(uint8 sensorCommand){
Sensirion Get_SensironValue(uint8 sensorCommand){
    
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
Sensirion Take_TempRH_Reading(){
    
    //delay 15ms based on data sheet
    CyDelay(15u);
    
    //turn power on to sensor
    Digital_Sensor_Power_Write(1u);
    Sensirion returnValue;
    
    float RH = (float) Get_SensironValue(SENSIRION_RH_COMMAND);
    returnValue.rh = -6 + 125*(RH/65532);
    
    float TEMP = (float) Get_SensironValue(SENSIRION_TEMP_COMMAND);
    returnValue.temp = -46.85 + 175.72*(TEMP/65532);
    
    //turn sensor off
    Digital_Sensor_Power_Write(0u);
    return returnValue;


}

/* [] END OF FILE */
