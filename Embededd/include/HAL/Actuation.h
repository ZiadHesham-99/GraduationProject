/*
 * Actuation.h
 *
 *  Created on: Jul 4, 2023
 *      Author: Hosam
 */

#ifndef HAL_ACTUATION_H_
#define HAL_ACTUATION_H_

#include "LIB/STD_TYPES.h"
#include "MCAL/GPIO_interface.h"
#include "MCAL/TIMER_interface.h"



typedef enum 
{
    LEFT_MOTOR = (u8)0,
    RIGHT_MOTOR
}tenuMotors;

typedef enum 
{
    FORWARD_ACT = (u8)0,
    BACKWARD_ACT
}tenuMotorDir;

typedef enum
{
	VALVE_OPEN = (u8)0,
	VALVE_CLOSE
}tenuValveState;

void ACT_vidActuateMotor(tenuMotors Copy_enuMotor,tenuMotorDir Copy_enuDirection, u8 Copy_u8SpeedPercentage);
void ACT_vidActuateValve(tenuValveState Copy_enuValveState);

#endif /* HAL_ACTUATION_H_ */
