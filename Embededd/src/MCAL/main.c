/*
 * main.c
 *
 *  Created on: Dec 16, 2022
 *      Author: Hosam
 */
#include "LIB/STD_TYPES.h"

#include "MCAL/RCC_interface.h"
#include "MCAL/GPIO_interface.h"
#include "MCAL/ADC_interface.h"
#include "MCAL/I2C_interface.h"
#include "MCAL/UART_interface.h"
#include "MCAL/TIMER_interface.h"


#include "HAL/Sensing.h"

#include "APP/DataAcquisition.h"

void main(void)
{

	RCC_voidInit();

	RCC_voidEnablePeripheralClock(GPIOA);
	RCC_voidEnablePeripheralClock(GPIOB);
	RCC_voidEnablePeripheralClock(ADC1);
	RCC_voidEnablePeripheralClock(I2C1);
	RCC_voidEnablePeripheralClock(I2C2);
	//RCC_voidEnablePeripheralClock(USART1);

	GPIO_voidSetPinsConfig();

	TIM_vidInit();
	I2C_vidInit();
	UART_vidInit();

	SEN_vidInit();

	DAQ_vidInit();


	while(1)
	{

		DAQ_vidCollectData();

	}
}

