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

#define PORTA			GPIOA_R
#define PORTB          	GPIOB_R
#define PORTC          	GPIOC_R

#define FULL_HIGH		0xFFFF
#define FULL_LOW		0x0000
#define GPIO_NOT_USED	0xFF

typedef enum{
	PORT_A			= (u8)0,
	PORT_B,
	PORT_C
}PORTx;

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
	AF0  			= (u8)0,
	AF1,
    AF2,
    AF3,
    AF4,
    AF5,
    AF6,
    AF7,
    AF8,
    AF9,
    AF10,
    AF11,
    AF12,
    AF13,
    AF14,
    AF15,
}ALT_FUNC_SLCTION;

typedef struct{
	GPIOx_REGISTERS*	prtStrPORT;
	PINn 				PIN;
	MODE_OF_PIN			MODE;
	OUTPUT_TYPE			TYPE;
	OUTPUT_SPEED		SPEED;
	INPUT_PULL_UP_DOWN	PULL_UP_DOWN;
	ALT_FUNC_SLCTION	AF;
}PIN_CONFIG;

PIN_CONFIG	GLOB_prtStrPins[NUMBER_OF_USED_PINS];

void GPIO_voidSetPinsConfig(void);

void GPIO_voidSetPinValue(PORTx Copy_enumPort, PINn Copy_enumPin, PIN_VALUE Copy_enumValue);
void GPIO_voidSetPinAtomicValue(PORTx Copy_enumPort, PINn Copy_enumPin, PIN_VALUE Copy_enumValue);
u8   GPIO_u8GetPinValue(PORTx Copy_enumPort, PINn Copy_enumPin);

void GPIO_voidSetPortValue(PORTx Copy_enumPort, u16 Copy_u16PortValue);
void GPIO_voidSetPortAtomicValue(PORTx Copy_enumPort, u16 Copy_u16PortValue);
u32  GPIO_u32GetPortValue(PORTx Copy_enumPort);



#endif
