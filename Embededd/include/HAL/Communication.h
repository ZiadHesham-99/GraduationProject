/*
 * Communication.c
 *
 *  Created on: March 1, 2022
 *      Author: Hosam
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_


typedef enum
{
	SENSORS_COMM = (u8)0,
	MOTION_COMM
}tenuMsgType;

typedef struct
{
	u8 u8GasPercentage;
	s8 s8GyroX;
	s8 s8GyroY;
	s8 s8GyroZ;
	s16 s16AccelX;
	s16 s16AccelY;
	s16 s16AccelZ;
	u16 u8Temperatue;

	s16 s16LeftMotorRPM;
	s16 s16RightMotorRPM;

}tstrRaspberryPiMsg;

typedef struct
{
	s16 s16LeftMotorSpeed;
	s16 s16RightMotorSpeed;
	u8 u8Valve;
}tstrStmMsg;

void COM_vidSendToRaspBerryPi(tstrRaspberryPiMsg Copy_strMsg, tenuMsgType Copy_enuMsgType);
void COM_vidRecFromRaspBerryPi(tstrStmMsg *Copy_pstrMsg);

static void vidToString(s32 Copy_s32Num, u8 Copy_u8DigitsNum, u8 * Copy_pu8Bffr);
static s32  s32ToInteger(u8 * Copy_pu8Bffr, u8 Copy_u8DigitsNum);

#endif  
