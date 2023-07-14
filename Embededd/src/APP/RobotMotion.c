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
	LOC_strRaspMsg.s8LeftMotorRPM = 0;
	LOC_strRaspMsg.s8RightMotorRPM = 0;

	LOC_strStmMsg.s8LeftMotorSpeed = 0;
	LOC_strStmMsg.s8RightMotorSpeed = 0;
}

void RMO_vidMotionHandler(void)
{
	tenuMotorDir enuLeftMotorDir, enuRightMotorDir;

	COM_vidRecFromRaspBerryPi(&LOC_strStmMsg);

	if ( LOC_strStmMsg.s8LeftMotorSpeed < 0)
	{
		LOC_strStmMsg.s8LeftMotorSpeed  *= -1;
		enuLeftMotorDir = BACKWARD_ACT;
	}
	else
	{
		enuLeftMotorDir = FORWARD_ACT;
	}
	if ( LOC_strStmMsg.s8RightMotorSpeed < 0)
	{
		LOC_strStmMsg.s8RightMotorSpeed  *= -1;
		enuRightMotorDir = BACKWARD_ACT;
	}
	else
	{
		enuRightMotorDir = FORWARD_ACT;
	}


	ACT_vidActuateValve(LOC_strStmMsg.u8Valve);
	ACT_vidActuateMotor(LEFT_MOTOR, enuLeftMotorDir, LOC_strStmMsg.s8LeftMotorSpeed);
	ACT_vidActuateMotor(RIGHT_MOTOR, enuRightMotorDir, LOC_strStmMsg.s8RightMotorSpeed);
	
	SEN_vidUpdateEncoders();
	LOC_strRaspMsg.s8LeftMotorRPM = SEN_u8GetLeftMotorRPM();
	LOC_strRaspMsg.s8RightMotorRPM = SEN_u8GetRightMotorRPM();
	
	if(enuLeftMotorDir == BACKWARD_ACT)
	{
		LOC_strRaspMsg.s8LeftMotorRPM *= -1;
	}
	else
	{
	}

	if(enuRightMotorDir == BACKWARD_ACT)
	{
		LOC_strRaspMsg.s8RightMotorRPM *= -1;
	}
	else
	{
	}
	
	COM_vidSendToRaspBerryPi(LOC_strRaspMsg, MOTION_COMM);
}


