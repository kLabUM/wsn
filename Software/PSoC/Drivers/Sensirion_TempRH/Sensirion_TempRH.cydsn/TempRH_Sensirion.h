#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include "I2C_1.h"


struct{
    float rh;
    float temp;
}typedef Sensirion;

Sensirion Get_SensironValue;
Sensirion Take_TempRH_Reading();


/* [] END OF FILE */
