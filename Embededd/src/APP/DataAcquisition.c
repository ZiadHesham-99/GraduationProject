/*
 * DataAcquisition.c
 *
 *  Created on: March 11, 2022
 *      Author: Hosam
 */

#include "LIB/STD_TYPES.h"
#include "SERVICES/Delay.h"

#include "HAL/Sensing.h"
#include "HAL/Communication.h"
#include "HAL/Display.h"

#include "APP/DataAcquisition.h"

static tstrRaspberryPiMsg LOC_strMsg;

void DAQ_vidInit(void)
{
    LOC_strMsg.s8GyroX = 0;
    LOC_strMsg.s8GyroY = 0;
    LOC_strMsg.s8GyroZ = 0;
    LOC_strMsg.s16AccelX = 0;
    LOC_strMsg.s16AccelY = 0;
    LOC_strMsg.s16AccelZ = 0;
	LOC_strMsg.u8Temperatue = 0;
    LOC_strMsg.u8GasPercentage = 0;
}

void DAQ_vidCollectData(void)
{
    f32 af32MPU[6] ={0};
    u16	u16Temperature = 0;

    SEN_vidUpdateSensorsData();

    u16Temperature = SEN_u16GetTemperature();
    u16Temperature = (((f32)u16Temperature)* 0.05);
    
    LOC_strMsg.u8GasPercentage = SEN_u8GetGasPercentage();
    LOC_strMsg.u8Temperatue = (u8)u16Temperature;
    SEN_vidGetGyroAccel(af32MPU);
    
    //LOC_strMsg.u8GasPercentage = 45;
    LOC_strMsg.s8GyroX = ((s8)af32MPU[3]);
    LOC_strMsg.s8GyroY = ((s8)af32MPU[4]);
    LOC_strMsg.s8GyroZ = ((s8)af32MPU[5]);
    LOC_strMsg.s16AccelX = ((s16)(af32MPU[0]*1000));
    LOC_strMsg.s16AccelY = ((s16)(af32MPU[1]*1000));
    LOC_strMsg.s16AccelZ = ((s16)(af32MPU[2]*1000));

    if(LOW == SEN_enmGetPushButton())
    {

		COM_vidSendToRaspBerryPi(LOC_strMsg);
    }
    else
    {
    }
}
