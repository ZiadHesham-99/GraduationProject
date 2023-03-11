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


#include "HAL/Sensing.h"

void main(void)
{


	RCC_voidInit();

	RCC_voidEnablePeripheralClock(GPIOA);
	RCC_voidEnablePeripheralClock(GPIOB);
	RCC_voidEnablePeripheralClock(ADC1);
	RCC_voidEnablePeripheralClock(I2C1);
	RCC_voidEnablePeripheralClock(USART1);

	GPIO_voidSetPinsConfig();

	//ADC_vidInit();
	I2C_vidInit();
	UART_vidInit();

	//u8 counter = 0;
	u8 buffer[2] = {0};
	I2C_vidSlaveRX(I2C_1,buffer,2);

	UART_vidTransmitChar((buffer[0]+0x30));
	UART_vidTransmitChar((buffer[1]+0x30));

	while(1)
	{
		//SEN_vidUpdateSensorsData();


	}
}

