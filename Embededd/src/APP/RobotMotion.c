/*
 * RobotMotion.c
 *
 *  Created on: Jul 2, 2023
 *      Author: Hosam
 */

#include "LIB/STD_TYPES.h"
#include "SERVICES/Delay.h"

#include "HAL/Sensing.h"
#include "HAL/Communication.h"
#include "HAL/Actuation.h"

#include "APP/RobotMotion.h"

static tstrRaspberryPiMsg LOC_strRaspMsg;
static tstrStmMsg LOC_strStmMsg;

void RMO_vidInit(void)
{
	LOC_strRaspMsg.s16LeftMotorRPM = 0;
	LOC_strRaspMsg.s16RightMotorRPM = 0;

	LOC_strStmMsg.s16LeftMotorSpeed = 0;
	LOC_strStmMsg.s16RightMotorSpeed = 0;
}

void RMO_vidMotionHandler(void)
{
	tenuMotorDir enuLeftMotorDir, enuRightMotorDir;

	COM_vidRecFromRaspBerryPi(&LOC_strStmMsg);

	if ( LOC_strStmMsg.s16LeftMotorSpeed < 0)
	{
		LOC_strStmMsg.s16LeftMotorSpeed  *= -1;
		enuLeftMotorDir = BACKWARD_ACT;
	}
	else
	{
		enuLeftMotorDir = FORWARD_ACT;
	}
	if ( LOC_strStmMsg.s16RightMotorSpeed < 0)
	{
		LOC_strStmMsg.s16RightMotorSpeed  *= -1;
		enuRightMotorDir = BACKWARD_ACT;
	}
	else
	{
		enuRightMotorDir = FORWARD_ACT;
	}


	ACT_vidActuateValve(LOC_strStmMsg.u8Valve);
	ACT_vidActuateMotor(LEFT_MOTOR, enuLeftMotorDir, (u8)LOC_strStmMsg.s16LeftMotorSpeed);
	ACT_vidActuateMotor(RIGHT_MOTOR, enuRightMotorDir, (u8)LOC_strStmMsg.s16RightMotorSpeed);
	
	SEN_vidUpdateEncoders();
	LOC_strRaspMsg.s16LeftMotorRPM = SEN_u8GetLeftMotorRPM();
	LOC_strRaspMsg.s16RightMotorRPM = SEN_u8GetRightMotorRPM();
	
	if(enuLeftMotorDir == BACKWARD_ACT)
	{
		LOC_strRaspMsg.s16LeftMotorRPM *= -1;
	}
	else
	{
	}

	if(enuRightMotorDir == BACKWARD_ACT)
	{
		LOC_strRaspMsg.s16RightMotorRPM *= -1;
	}
	else
	{
	}
	
	COM_vidSendToRaspBerryPi(LOC_strRaspMsg, MOTION_COMM);
}


