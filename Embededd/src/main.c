/*
 * main.c
 *
 *  Created on: Dec 16, 2022
 *      Author: Hosam
 */
#include "LIB/STD_TYPES.h"
#include "SERVICES/Delay.h"

#include "MCAL/RCC_interface.h"
#include "MCAL/GPIO_interface.h"
#include "MCAL/ADC_interface.h"
#include "MCAL/I2C_interface.h"
#include "MCAL/UART_interface.h"
#include "MCAL/TIMER_interface.h"
#include "MCAL/SYSTICK_interface.h"
#include "MCAL/NVIC_interface.h"

#include "HAL/Sensing.h"
#include "HAL/Actuation.h"

#include "APP/DataAcquisition.h"
#include "APP/RobotMotion.h"

#include "OS/OS_interface.h"

void main(void)
{

	/* *********************** MCAL LAYER INITIALIZATION *********************** */
	RCC_voidInit();

	RCC_voidEnablePeripheralClock(ADC1);
	RCC_voidEnablePeripheralClock(GPIOA);
	RCC_voidEnablePeripheralClock(GPIOB);
	RCC_voidEnablePeripheralClock(TIMER2);
	RCC_voidEnablePeripheralClock(TIMER3);
	RCC_voidEnablePeripheralClock(TIMER10);
	RCC_voidEnablePeripheralClock(TIMER11);
	RCC_voidEnablePeripheralClock(I2C1);
	RCC_voidEnablePeripheralClock(I2C2);

	GPIO_voidSetPinsConfig();

	TIM_vidInit();
	I2C_vidInit();
	SYSTICK_vidInit();
	/* ************************************************************************* */



	/* *********************** HAL LAYER INITIALIZATION ************************ */
	SEN_vidInit();
	/* ************************************************************************* */


	/* *********************** APP LAYER INITIALIZATION ************************ */
	DAQ_vidInit();
	RMO_vidInit();
	/* ************************************************************************* */


	/* *********************** OS LAYER INITIALIZATION ************************* */
	OS_vidInit();
	/* ************************************************************************* */

	while(1)
	{
		OS_vidScheduler();
	}
}

