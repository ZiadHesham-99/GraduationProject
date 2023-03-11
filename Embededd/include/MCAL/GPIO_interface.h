/*
 * GPIO_interface.h
 *
 *  Created on: Aug 10, 2022
 *      Author: Hosam
 */

#ifndef	GPIO_INTERFACE_H
#define	GPIO_INTERFACE_H

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "GPIO_config.h"
#include "GPIO_private.h"

#define FULL_HIGH		0xFFFF
#define FULL_LOW		0x0000
#define GPIO_NOT_USED	0xFF

typedef enum
{
	PORT_A			= (u8)0,
	PORT_B,
	PORT_C
}PORT_x;

typedef enum
{
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

typedef enum
{
	INPUT			= (u32)0,
	OUTPUT,
	ALT_FUNC,
	ANALOG
}MODE_OF_PIN;

typedef enum
{
	PUSH_PULL		= (u32)0,
	OPEN_DRAIN
}OUTPUT_TYPE;

typedef enum
{
	NORMAL			= (u32)0,
	MEDIUM,
	HIGH_SPEED,
	VERY_HIGH
}OUTPUT_SPEED;

typedef enum
{
	NO_PULL_UP_DOWN	= (u32)0,
	PULL_UP,
	PULL_DOWN,
}INPUT_PULL_UP_DOWN;

typedef enum
{
	LOW				= (u8)0,
	HIGH
}PIN_VALUE;

typedef enum
{
	AF_0	= (u8)0,
	AF_1,
	AF_2,
	AF_3,
	AF_4,
	AF_5,
	AF_6,
	AF_7,
	AF_8,
	AF_9,
	AF_10,
	AF_11,
	AF_12,
	AF_13,
	AF_14,
	AF_15,
}ALT_FUNC_SLCTION;

typedef struct
{
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

void GPIO_vidSetPinDirection(PORT_x Copy_enuPORT_x, PINn Copy_enuPINn, MODE_OF_PIN Copy_enuMode);

#endif
