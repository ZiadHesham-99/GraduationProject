/*
 * GPIO_program.c
 *
 *  Created on: Aug 10, 2022
 *      Author: Hosam
 */
#include "../../01- LIB/01- TYPES/STD_TYPES.h"
#include "../../01- LIB/02- BIT_MATH/BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"

void GPIO_voidSetPinAtomicValue(PORTx Copy_enumPort, PINn Copy_enumPin, PIN_VALUE Copy_enumValue);

void GPIO_voidSetPinsConfig(void)
{
	u8 Local_u8Counter;
	PIN_CONFIG LOC_strPin;
	for(Local_u8Counter = 0; Local_u8Counter < NUMBER_OF_USED_PINS; Local_u8Counter++)
	{
		LOC_strPin = GLOB_prtStrPins[Local_u8Counter];

		CLR_TWO_BITS(LOC_strPin.prtStrPORT->MODER, LOC_strPin.PIN);
		LOC_strPin.prtStrPORT->MODER |= (LOC_strPin.MODE << (LOC_strPin.PIN*2));

		switch(LOC_strPin.MODE)
		{
		case INPUT:
			CLR_TWO_BITS(LOC_strPin.prtStrPORT->PUPDR, LOC_strPin.PIN);
			LOC_strPin.prtStrPORT->PUPDR |= (LOC_strPin.PULL_UP_DOWN << (LOC_strPin.PIN*2));
			break;
		case OUTPUT:
			CLR_TWO_BITS(LOC_strPin.prtStrPORT->OTYPER, LOC_strPin.PIN);
			LOC_strPin.prtStrPORT->OTYPER |= (LOC_strPin.TYPE << LOC_strPin.PIN);
			CLR_TWO_BITS(LOC_strPin.prtStrPORT->OSPEEDR, LOC_strPin.PIN);
			LOC_strPin.prtStrPORT->OSPEEDR |= (LOC_strPin.SPEED << (LOC_strPin.PIN*2));
			break;
		case ALT_FUNC:
			if(LOC_strPin.PIN <= 7)
			{
				CLR_FOUR_BITS(LOC_strPin.prtStrPORT->AFRL, LOC_strPin.PIN);
				LOC_strPin.prtStrPORT->AFRL |= (LOC_strPin.AF << (LOC_strPin.PIN*4));
			}
			else
			{
				u8 LOC_u8Pin = LOC_strPin.PIN - 8;
				CLR_FOUR_BITS(LOC_strPin.prtStrPORT->AFRH, LOC_u8Pin);
				LOC_strPin.prtStrPORT->AFRH |= (LOC_strPin.AF << (LOC_u8Pin*4));
			}
			break;
		}//end of switch

		GLOB_prtStrPins[Local_u8Counter] = LOC_strPin;
	}// end of loop

}


void GPIO_voidSetPinValue(PORTx Copy_enumPort, PINn Copy_enumPin, PIN_VALUE Copy_enumValue)
{
	u32 Local_u32PinValue = (u32)( ((u32)Copy_enumValue) << ((u32)Copy_enumPin) );
	switch(Copy_enumPort)
	{
	case PORT_A:
		CLR_BIT(GPIOA_R->ODR,Copy_enumPin);
		GPIOA_R->ODR |= Local_u32PinValue;
		break;
	case PORT_B:
		CLR_BIT(GPIOB_R->ODR,Copy_enumPin);
		GPIOB_R->ODR |= Local_u32PinValue;
		break;
	case PORT_C:
		CLR_BIT(GPIOC_R->ODR,Copy_enumPin);
		GPIOC_R->ODR |= Local_u32PinValue;
		break;
	}
}

void GPIO_voidSetPinAtomicValue(PORTx Copy_enumPort, PINn Copy_enumPin, PIN_VALUE Copy_enumValue)
{
	u32 Local_u32PinValue = (u32)Copy_enumValue;
	switch(Copy_enumPort)
	{
	case PORT_A:
		GPIOA_R->BSRR = Local_u32PinValue;
		GPIOA_R->BSRR = (TOG_BIT(Local_u32PinValue,Copy_enumPin))<<16;
		break;
	case PORT_B:
		GPIOB_R->BSRR = Local_u32PinValue;
		GPIOB_R->BSRR = (TOG_BIT(Local_u32PinValue,Copy_enumPin))<<16;
		break;
	case PORT_C:
		GPIOC_R->BSRR = Local_u32PinValue;
		GPIOC_R->BSRR = (TOG_BIT(Local_u32PinValue,Copy_enumPin))<<16;
		break;
	}
}

u8   GPIO_u8GetPinValue(PORTx Copy_enumPort, PINn Copy_enumPin)
{
	PIN_VALUE Local_enumPinValue = LOW;
	switch(Copy_enumPort)
	{
	case PORT_A:	Local_enumPinValue = GET_BIT(GPIOA_R->IDR,Copy_enumPin);	break;
	case PORT_B:	Local_enumPinValue = GET_BIT(GPIOB_R->IDR,Copy_enumPin);	break;
	case PORT_C:	Local_enumPinValue = GET_BIT(GPIOC_R->IDR,Copy_enumPin);	break;
	}
	return Local_enumPinValue;
}


void GPIO_voidSetPortValue(PORTx Copy_enumPort, u16 Copy_u16PortValue)
{
	switch(Copy_enumPort)
	{
	case PORT_A:	GPIOA_R->ODR = ((u32)Copy_u16PortValue);	break;
	case PORT_B:	GPIOB_R->ODR = ((u32)Copy_u16PortValue);	break;
	case PORT_C:	GPIOC_R->ODR = ((u32)Copy_u16PortValue);	break;
	}
}

void GPIO_voidSetPortAtomicValue(PORTx Copy_enumPort, u16 Copy_u16PortValue)
{
	u8 Local_u8Counter, Local_u8Value = 0;
	for(Local_u8Counter = 0; Local_u8Counter < 16; Local_u8Counter++)
	{
		Local_u8Value = (u8)GET_BIT(Copy_u16PortValue,Local_u8Counter);
		GPIO_voidSetPinAtomicValue(Copy_enumPort,Local_u8Counter,Local_u8Value);
	}
}

u32  GPIO_u32GetPortValue(PORTx Copy_enumPort)
{
	u32 Local_u32PortValue = 0;
	switch(Copy_enumPort)
	{
	case PORT_A:	Local_u32PortValue = GPIOA_R->IDR;	break;
	case PORT_B:	Local_u32PortValue = GPIOB_R->IDR;	break;
	case PORT_C:	Local_u32PortValue = GPIOC_R->IDR;	break;
	}
	return Local_u32PortValue;
}
