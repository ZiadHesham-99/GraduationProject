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

#include "HAL/Sensing.h"

#include "APP/DataAcquisition.h"
#include "APP/RobotMotion.h"

void main(void)
{

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

	SEN_vidInit();

	DAQ_vidInit();
	RMO_vidInit();

	//volatile u8 counter = 25, counter1[9] = {55,66,99,77,88,11,22,33,44};
	while(1)
	{
		DAQ_vidCollectData();
		RMO_vidMotionHandler();
		//I2C_vidMasterRX(I2C_2, 0x16, counter1, 9);
		//counter = 0;

	}
}

