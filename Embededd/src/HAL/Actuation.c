/*
 * Actuation.c
 *
 *  Created on: Jul 4, 2023
 *      Author: Hosam
 */

#include "HAL/Actuation.h"


void ACT_vidActuateMotor(tenuMotors Copy_enuMotor, tenuMotorDir Copy_enuDirection, u8 Copy_u8SpeedPercentage)
{   
    if(Copy_u8SpeedPercentage > 100)
    {
        Copy_u8SpeedPercentage = 100;
    }
    else
    {
    }

    switch (Copy_enuMotor)
    {
    case LEFT_MOTOR:
        
        TIM_vidPWMStart(TIM_2, TIM_CHANNEL3, 250, Copy_u8SpeedPercentage);
        switch (Copy_enuDirection)
        {
        case FORWARD_ACT:
            GPIO_voidSetPinValue(PORT_A, PIN4, HIGH);
            break;
        
        case BACKWARD_ACT:
            GPIO_voidSetPinValue(PORT_A, PIN4, LOW);
            break;
        }
        break;
    case RIGHT_MOTOR:
         TIM_vidPWMStart(TIM_2, TIM_CHANNEL4, 250, Copy_u8SpeedPercentage);
        switch (Copy_enuDirection)
        {
        case FORWARD_ACT:
            GPIO_voidSetPinValue(PORT_A, PIN5, HIGH);
            break;
        case BACKWARD_ACT:
            GPIO_voidSetPinValue(PORT_A, PIN5, LOW);
            break;
        }
        break;
    }
}

void ACT_vidActuateValve(tenuValveState Copy_enuValveState)
{
	switch(Copy_enuValveState)
	{
	case TRUE:

		GPIO_voidSetPinValue(PORT_B, PIN0, HIGH);

		break;

	case FALSE:

		GPIO_voidSetPinValue(PORT_B, PIN0, LOW);

		break;
	}
}
