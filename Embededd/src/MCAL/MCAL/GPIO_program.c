/*
 * GPIO_program.c
 *
 *  Created on: Aug 10, 2022
 *      Author: Hosam
 */

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/GPIO_interface.h"
#include "MCAL/GPIO_config.h"
#include "MCAL/GPIO_private.h"

void GPIO_voidSetPinAtomicValue(PORT_x Copy_enuPORT_x, PINn Copy_enuPINn, PIN_VALUE Copy_enumValue);

void GPIO_voidSetPinsConfig(void)
{
	u8 Local_u8Counter;
	PIN_CONFIG LOC_strPin;
	for (Local_u8Counter = 0; Local_u8Counter < NUMBER_OF_USED_PINS; Local_u8Counter++)
	{
		LOC_strPin = GLOB_prtStrPins[Local_u8Counter];
		switch (LOC_strPin.PORT)
		{
		case PORT_A:
		{
			CLR_TWO_BITS(GPIOA_R->MODER, LOC_strPin.PIN);
			GPIOA_R->MODER |= (LOC_strPin.MODE << (LOC_strPin.PIN * 2));

			switch (LOC_strPin.MODE)
			{
			case INPUT:
				CLR_TWO_BITS(GPIOA_R->PUPDR, LOC_strPin.PIN);
				GPIOA_R->PUPDR |= (LOC_strPin.PULL_UP_DOWN << (LOC_strPin.PIN * 2));
				break;
			case OUTPUT:
				CLR_BIT(GPIOA_R->OTYPER, LOC_strPin.PIN);
				GPIOA_R->OTYPER |= (LOC_strPin.TYPE << LOC_strPin.PIN);
				CLR_TWO_BITS(GPIOA_R->OSPEEDR, LOC_strPin.PIN);
				GPIOA_R->OSPEEDR |= (LOC_strPin.SPEED << (LOC_strPin.PIN * 2));
				break;
			case ALT_FUNC:
				if(GPIO_NOT_USED != LOC_strPin.PULL_UP_DOWN)
				{
					CLR_TWO_BITS(GPIOA_R->PUPDR, LOC_strPin.PIN);
					GPIOA_R->PUPDR |= (LOC_strPin.PULL_UP_DOWN << (LOC_strPin.PIN * 2));
				}
				else{}

				if(GPIO_NOT_USED != LOC_strPin.TYPE)
				{
					CLR_BIT(GPIOA_R->OTYPER, LOC_strPin.PIN);
					GPIOA_R->OTYPER |= (LOC_strPin.TYPE << LOC_strPin.PIN);
				}
				else{}

				if(GPIO_NOT_USED != LOC_strPin.SPEED)
				{
					CLR_TWO_BITS(GPIOA_R->OSPEEDR, LOC_strPin.PIN);
					GPIOA_R->OSPEEDR |= (LOC_strPin.SPEED << (LOC_strPin.PIN * 2));
				}
				else{}

				if (LOC_strPin.PIN <= 7)
				{
					CLR_FOUR_BITS(GPIOA_R->AFRL, LOC_strPin.PIN);
					GPIOA_R->AFRL |= (LOC_strPin.AF << (LOC_strPin.PIN * 4));
				}
				else
				{
					u8 LOC_u8Pin = LOC_strPin.PIN - 8;
					CLR_FOUR_BITS(GPIOA_R->AFRH, LOC_u8Pin);
					GPIOA_R->AFRH |= (LOC_strPin.AF << (LOC_u8Pin * 4));
				}
				break;
			case ANALOG :
				//Do nothing
				break;
			} // end of switch
		}
		break;
		case PORT_B:
		{
			CLR_TWO_BITS(GPIOB_R->MODER, LOC_strPin.PIN);
			GPIOB_R->MODER |= (LOC_strPin.MODE << (LOC_strPin.PIN * 2));

			switch (LOC_strPin.MODE)
			{
			case INPUT:
				CLR_TWO_BITS(GPIOB_R->PUPDR, LOC_strPin.PIN);
				GPIOB_R->PUPDR |= (LOC_strPin.PULL_UP_DOWN << (LOC_strPin.PIN * 2));
				break;
			case OUTPUT:
				CLR_BIT(GPIOB_R->OTYPER, LOC_strPin.PIN);
				GPIOB_R->OTYPER |= (LOC_strPin.TYPE << LOC_strPin.PIN);
				CLR_TWO_BITS(GPIOB_R->OSPEEDR, LOC_strPin.PIN);
				GPIOB_R->OSPEEDR |= (LOC_strPin.SPEED << (LOC_strPin.PIN * 2));
				break;
			case ALT_FUNC:
				if(GPIO_NOT_USED != LOC_strPin.PULL_UP_DOWN)
				{
					CLR_TWO_BITS(GPIOB_R->PUPDR, LOC_strPin.PIN);
					GPIOB_R->PUPDR |= (LOC_strPin.PULL_UP_DOWN << (LOC_strPin.PIN * 2));
				}
				else{}

				if(GPIO_NOT_USED != LOC_strPin.TYPE)
				{
					CLR_BIT(GPIOB_R->OTYPER, LOC_strPin.PIN);
					GPIOB_R->OTYPER |= (LOC_strPin.TYPE << LOC_strPin.PIN);
				}
				else{}

				if(GPIO_NOT_USED != LOC_strPin.SPEED)
				{
					CLR_TWO_BITS(GPIOB_R->OSPEEDR, LOC_strPin.PIN);
					GPIOB_R->OSPEEDR |= (LOC_strPin.SPEED << (LOC_strPin.PIN * 2));
				}
				else{}

				if (LOC_strPin.PIN <= 7)
				{
					CLR_FOUR_BITS(GPIOB_R->AFRL, LOC_strPin.PIN);
					GPIOB_R->AFRL |= (LOC_strPin.AF << (LOC_strPin.PIN * 4));
				}
				else
				{
					u8 LOC_u8Pin = LOC_strPin.PIN - 8;
					CLR_FOUR_BITS(GPIOB_R->AFRH, LOC_u8Pin);
					GPIOB_R->AFRH |= (LOC_strPin.AF << (LOC_u8Pin * 4));
				}
				break;
			case ANALOG :
				//Do nothing
				break;
			} // end of switch
		}
		break;
		case PORT_C:
		{
			CLR_TWO_BITS(GPIOC_R->MODER, LOC_strPin.PIN);
			GPIOC_R->MODER |= (LOC_strPin.MODE << (LOC_strPin.PIN * 2));

			switch (LOC_strPin.MODE)
			{
			case INPUT:
				CLR_TWO_BITS(GPIOC_R->PUPDR, LOC_strPin.PIN);
				GPIOC_R->PUPDR |= (LOC_strPin.PULL_UP_DOWN << (LOC_strPin.PIN * 2));
				break;
			case OUTPUT:
				CLR_BIT(GPIOC_R->OTYPER, LOC_strPin.PIN);
				GPIOC_R->OTYPER |= (LOC_strPin.TYPE << LOC_strPin.PIN);
				CLR_TWO_BITS(GPIOC_R->OSPEEDR, LOC_strPin.PIN);
				GPIOC_R->OSPEEDR |= (LOC_strPin.SPEED << (LOC_strPin.PIN * 2));
				break;
			case ALT_FUNC:
				if(GPIO_NOT_USED != LOC_strPin.PULL_UP_DOWN)
				{
					CLR_TWO_BITS(GPIOC_R->PUPDR, LOC_strPin.PIN);
					GPIOC_R->PUPDR |= (LOC_strPin.PULL_UP_DOWN << (LOC_strPin.PIN * 2));
				}
				else{}

				if(GPIO_NOT_USED != LOC_strPin.TYPE)
				{
					CLR_BIT(GPIOC_R->OTYPER, LOC_strPin.PIN);
					GPIOC_R->OTYPER |= (LOC_strPin.TYPE << LOC_strPin.PIN);
				}
				else{}

				if(GPIO_NOT_USED != LOC_strPin.SPEED)
				{
					CLR_TWO_BITS(GPIOC_R->OSPEEDR, LOC_strPin.PIN);
					GPIOC_R->OSPEEDR |= (LOC_strPin.SPEED << (LOC_strPin.PIN * 2));
				}
				else{}

				if (LOC_strPin.PIN <= 7)
				{
					CLR_FOUR_BITS(GPIOC_R->AFRL, LOC_strPin.PIN);
					GPIOC_R->AFRL |= (LOC_strPin.AF << (LOC_strPin.PIN * 4));
				}
				else
				{
					u8 LOC_u8Pin = LOC_strPin.PIN - 8;
					CLR_FOUR_BITS(GPIOC_R->AFRH, LOC_u8Pin);
					GPIOC_R->AFRH |= (LOC_strPin.AF << (LOC_u8Pin * 4));
				}
				break;
			case ANALOG :
				//Do nothing
				break;
			} // end of switch
		}
		break;
		default:
			break;
		} // end of switch

	} // end of loop
}

void GPIO_voidSetPinValue(PORT_x Copy_enuPORT_x, PINn Copy_enuPINn, PIN_VALUE Copy_enumValue)
{
	u32 Local_u32PinValue = (u32)(((u32)Copy_enumValue) << ((u32)Copy_enuPINn));
	switch (Copy_enuPORT_x)
	{
	case PORT_A:
		CLR_BIT(GPIOA_R->ODR, Copy_enuPINn);
		GPIOA_R->ODR |= Local_u32PinValue;
		break;
	case PORT_B:
		CLR_BIT(GPIOB_R->ODR, Copy_enuPINn);
		GPIOB_R->ODR |= Local_u32PinValue;
		break;
	case PORT_C:
		CLR_BIT(GPIOC_R->ODR, Copy_enuPINn);
		GPIOC_R->ODR |= Local_u32PinValue;
		break;
	}
}

void GPIO_voidSetPinAtomicValue(PORT_x Copy_enuPORT_x, PINn Copy_enuPINn, PIN_VALUE Copy_enumValue)
{
	u32 Local_u32PinValue = (u32)Copy_enumValue;
	switch (Copy_enuPORT_x)
	{
	case PORT_A:
		GPIOA_R->BSRR = Local_u32PinValue;
		GPIOA_R->BSRR = (TOG_BIT(Local_u32PinValue, Copy_enuPINn)) << 16;
		break;
	case PORT_B:
		GPIOB_R->BSRR = Local_u32PinValue;
		GPIOB_R->BSRR = (TOG_BIT(Local_u32PinValue, Copy_enuPINn)) << 16;
		break;
	case PORT_C:
		GPIOC_R->BSRR = Local_u32PinValue;
		GPIOC_R->BSRR = (TOG_BIT(Local_u32PinValue, Copy_enuPINn)) << 16;
		break;
	}
}

u8 GPIO_u8GetPinValue(PORT_x Copy_enuPORT_x, PINn Copy_enuPINn)
{
	PIN_VALUE Local_enuPinValue = LOW;
	switch (Copy_enuPORT_x)
	{
	case PORT_A:
		Local_enuPinValue = GET_BIT(GPIOA_R->IDR, Copy_enuPINn);
		break;
	case PORT_B:
		Local_enuPinValue = GET_BIT(GPIOB_R->IDR, Copy_enuPINn);
		break;
	case PORT_C:
		Local_enuPinValue = GET_BIT(GPIOC_R->IDR, Copy_enuPINn);
		break;
	}
	return Local_enuPinValue;
}

void GPIO_voidSetPortValue(PORT_x Copy_enuPORT_x, u16 Copy_u16PortValue)
{
	switch (Copy_enuPORT_x)
	{
	case PORT_A:
		GPIOA_R->ODR = ((u32)Copy_u16PortValue);
		break;
	case PORT_B:
		GPIOB_R->ODR = ((u32)Copy_u16PortValue);
		break;
	case PORT_C:
		GPIOC_R->ODR = ((u32)Copy_u16PortValue);
		break;
	}
}

void GPIO_voidSetPortAtomicValue(PORT_x Copy_enuPORT_x, u16 Copy_u16PortValue)
{
	u8 Local_u8Counter, Local_u8Value = 0;
	for (Local_u8Counter = 0; Local_u8Counter < 16; Local_u8Counter++)
	{
		Local_u8Value = (u8)GET_BIT(Copy_u16PortValue, Local_u8Counter);
		GPIO_voidSetPinAtomicValue(Copy_enuPORT_x, Local_u8Counter, Local_u8Value);
	}
}

u32 GPIO_u32GetPortValue(PORT_x Copy_enuPORT_x)
{
	u32 Local_u32PortValue = 0;
	switch (Copy_enuPORT_x)
	{
	case PORT_A:
		Local_u32PortValue = GPIOA_R->IDR;
		break;
	case PORT_B:
		Local_u32PortValue = GPIOB_R->IDR;
		break;
	case PORT_C:
		Local_u32PortValue = GPIOC_R->IDR;
		break;
	}
	return Local_u32PortValue;
}


void GPIO_vidSetPinDirection(PORT_x Copy_enuPORT_x, PINn Copy_enuPINn, MODE_OF_PIN Copy_enuMode)
{
	switch(Copy_enuPORT_x)
	{
	case PORT_A:
	{
		CLR_TWO_BITS(GPIOA_R->MODER, Copy_enuPINn);
		GPIOA_R->MODER |= (Copy_enuMode<< (Copy_enuPINn * 2));
		switch(Copy_enuMode)
		{
		case INPUT:
		{
			CLR_TWO_BITS(GPIOA_R->PUPDR, Copy_enuPINn);
			GPIOA_R->PUPDR |= (PULL_UP << (Copy_enuPINn * 2));
		}
		break;
		case OUTPUT:
		{
			CLR_BIT(GPIOA_R->OTYPER, Copy_enuPINn);
			GPIOA_R->OTYPER |= (PUSH_PULL << Copy_enuPINn);
			CLR_TWO_BITS(GPIOA_R->OSPEEDR, Copy_enuPINn);
			GPIOA_R->OSPEEDR |= (NORMAL << (Copy_enuPINn * 2));
		}
		break;
		default : break;
		}//end of switch
	}
	break;
	case PORT_B:
	{
		CLR_TWO_BITS(GPIOB_R->MODER, Copy_enuPINn);
		GPIOB_R->MODER |= (Copy_enuMode << (Copy_enuPINn * 2));
		switch(Copy_enuMode)
		{
		case INPUT:
		{
			CLR_TWO_BITS(GPIOB_R->PUPDR, Copy_enuPINn);
			GPIOB_R->PUPDR |= (PULL_UP << (Copy_enuPINn * 2));
		}
		break;
		case OUTPUT:
		{
			CLR_BIT(GPIOB_R->OTYPER, Copy_enuPINn);
			GPIOB_R->OTYPER |= (PUSH_PULL << Copy_enuPINn);
			CLR_TWO_BITS(GPIOB_R->OSPEEDR, Copy_enuPINn);
			GPIOB_R->OSPEEDR |= (NORMAL << (Copy_enuPINn * 2));
		}
		break;
		default : break;
		}//end of switch
	}
	break;
	case PORT_C:
	{
		CLR_TWO_BITS(GPIOC_R->MODER, Copy_enuPINn);
		GPIOC_R->MODER |= (Copy_enuMode << (Copy_enuPINn * 2));
		switch(Copy_enuMode)
		{
		case INPUT:
		{
			CLR_TWO_BITS(GPIOC_R->PUPDR, Copy_enuPINn);
			GPIOC_R->PUPDR |= (PULL_UP << (Copy_enuPINn * 2));
		}
		break;
		case OUTPUT:
		{
			CLR_BIT(GPIOC_R->OTYPER, Copy_enuPINn);
			GPIOC_R->OTYPER |= (PUSH_PULL << Copy_enuPINn);
			CLR_TWO_BITS(GPIOC_R->OSPEEDR, Copy_enuPINn);
			GPIOC_R->OSPEEDR |= (NORMAL << (Copy_enuPINn * 2));
		}
		break;
		default : break;
		}//end of switch
	}
	break;
	default : break;
	}//end of switch case
}
