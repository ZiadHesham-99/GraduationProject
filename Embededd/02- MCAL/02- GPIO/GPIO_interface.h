/*
 * GPIO_interface.h
 *
 *  Created on: Aug 10, 2022
 *      Author: Hosam
 */

#ifndef	GPIO_INTERFACE_H
#define	GPIO_INTERFACE_H

#include "../../01- LIB/01- TYPES/STD_TYPES.h"
#include "GPIO_config.h"
#include "GPIO_private.h"

#define FULL_HIGH		0xFFFF
#define FULL_LOW		0x0000
#define GPIO_NOT_USED	0xFF

typedef enum{
	PORT_A			= (u8)0,
	PORT_B,
	PORT_C
}PORT_x;

typedef enum{
	PIN0 			= (u8)0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
}PINn;

typedef enum{
	INPUT			= (u32)0,
	OUTPUT,
	ALT_FUNC,
	ANALOG
}MODE_OF_PIN;

typedef enum{
	PUSH_PULL		= (u32)0,
	OPEN_DRAIN
}OUTPUT_TYPE;

typedef enum{
	NORMAL			= (u32)0,
	MEDIUM,
	HIGH_SPEED,
	VERY_HIGH
}OUTPUT_SPEED;

typedef enum{
	NO_PULL_UP_DOWN	= (u32)0,
	PULL_UP,
	PULL_DOWN,
}INPUT_PULL_UP_DOWN;

typedef enum{
	LOW				= (u8)0,
	HIGH
}PIN_VALUE;

typedef enum
{
	AF_SYSTEM= 0 ,
	AF_TIM1_2= 1 ,
	AF_TIM3_5= 2 ,
	AF_TIM9_11= 3 ,
	AF_I2C1_3= 4 ,
	AF_SPI1_4= 5 ,
	AF_SPI3= 6 ,
	AF_USART1_2= 7 ,
	AF_USAART6= 8 ,
	AF_I2C2_3= 9 ,
	AF_OTG_FS =10,
	AF_NF1 =11,
	AF_SDIO =12,
	AF_NF2 =13,
	AF_NF3=14,
	AF_EVENTOUT =15,
}ALT_FUNC_SLCTION;

typedef struct{
	PORT_x				PORT;
	PINn 				PIN;
	MODE_OF_PIN			MODE;
	OUTPUT_TYPE			TYPE;
	OUTPUT_SPEED		SPEED;
	INPUT_PULL_UP_DOWN	PULL_UP_DOWN;
	ALT_FUNC_SLCTION	AF;
}PIN_CONFIG;

PIN_CONFIG	GLOB_prtStrPins[NUMBER_OF_USED_PINS];

void GPIO_voidSetPinsConfig(void);

void GPIO_voidSetPinValue(PORT_x Copy_enuPORT_x, PINn Copy_enuPINn, PIN_VALUE Copy_enumValue);
void GPIO_voidSetPinAtomicValue(PORT_x Copy_enuPORT_x, PINn Copy_enuPINn, PIN_VALUE Copy_enumValue);
u8   GPIO_u8GetPinValue(PORT_x Copy_enuPORT_x, PINn Copy_enuPINn);

void GPIO_voidSetPortValue(PORT_x Copy_enuPORT_x, u16 Copy_u16PortValue);
void GPIO_voidSetPortAtomicValue(PORT_x Copy_enuPORT_x, u16 Copy_u16PortValue);
u32  GPIO_u32GetPortValue(PORT_x Copy_enuPORT_x);



#endif
