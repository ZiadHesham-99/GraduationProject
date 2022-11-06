/*********************************
Author	:	Hosam Magdy
Date	:	22 July 2022
Version	:	1.0
*********************************/
#ifndef	RCC_INTERFACE_H
#define	RCC_INTERFACE_H

#include "../../01- LIB/01- TYPES/STD_TYPES.h"
//#include "STD_TYPES.h"

typedef enum{
	GPIOA			= 0x00,
	GPIOB 			= 0x01,
	GPIOC 			= 0x02,
	CRC1			= 0x0C,
	DMA1 			= 0x15,
	DMA2 			= 0x16,
	OTGFS 			= 0x47,
	TIMER2 			= 0x80,
	TIMER3 			= 0x81,
	TIMER4 			= 0x82,
	TIMER5 			= 0x83,
	WATCHDOG 		= 0x8B,
	SPI2_RCC 		= 0x8E,
	SPI3_RCC 		= 0x8F,
	USART2 			= 0x91,
	I2C1 			= 0x95,
	I2C2 			= 0x96,
	I2C3 			= 0x97,
	POWER_INTERFACE = 0x9C,
	TIMER1 			= 0xC0,
	USART1 			= 0xC4,
	USART6 			= 0xC5,
	ADC1 			= 0xC8,
	SDIO 			= 0xCB,
	SPI1_RCC 		= 0xCC,
	SPI4_RCC		= 0xCD,
	SYSCFG 			= 0xCE,
	TIMER9 			= 0xD0,
	TIMER10 		= 0xD1,
	TIMER11 		= 0xD2
}PERIPHERAL_ID;

typedef enum{
	HSI								= (0x00000001),
	HSE_CRYSTAL						= (0x40010000),
	HSE_CRYSTAL_WITH_CLK_SECURITY	= (0x40090000),
	HSE_RC							= (0x40050000),
	HSE_RC_WITH_CLK_SECURITY		= (0x400D0000),
	PLL								= (0x81000000)
}SYSCLOCK;

typedef enum{
	PLL_HSI = 0x00,
	PLL_HSE
}PLL_SOURCE;

typedef enum{
	SYSCLK_NO_PRESCALER	= (0x0),
	SYSCLK_DIVIDED_BY_2	= (0x8),
	SYSCLK_DIVIDED_BY_4,
	SYSCLK_DIVIDED_BY_8,
	SYSCLK_DIVIDED_BY_16,
	SYSCLK_DIVIDED_BY_64,
	SYSCLK_DIVIDED_BY_128,
	SYSCLK_DIVIDED_BY_256,
	SYSCLK_DIVIDED_BY_512
}SYSCLK_PRESCALER_AHB;

typedef enum{
	AHB1_NO_PRESCALER = 0b000,
	AHB1_DIVIDED_BY_2 = 0b100,
	AHB1_DIVIDED_BY_4,
	AHB1_DIVIDED_BY_8,
	AHB1_DIVIDED_BY_16
}AHB_PRESCALER_APB;

typedef enum{
	INVALID_CLK_SRC					= (u8)0,
	INVALID_PERIPHERAL_ID
}RCC_ERROR_ID;

typedef enum{
	RCC_voidInit_ID			= (u8)0,
	RCC_voidEnablePeripheralClock_ID,
	RCC_voidDisablePeripheralClock_ID
}RCC_FUNC_ID;

void RCC_voidInit(void);
void RCC_voidEnablePeripheralClock(PERIPHERAL_ID Copy_enumPeripheralID);
void RCC_voidDisablePeripheralClock(PERIPHERAL_ID Copy_enumPeripheralID);

#endif
