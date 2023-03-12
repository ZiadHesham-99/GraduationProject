/*
 * Display.c
 *
 *  Created on: Dec 18, 2022
 *      Author: Hosam
 */

#include "HAL/Display.h"

void DISPLAY_vidLCDWriteChar(u8 Copy_u8Character);
void DISPLAY_vidLCDWriteString(u8* Copy_String);

void DISPLAY_vidLCDInit(void)
{
	TIM_vidDelayms(TIM_3, 20);

	switch(LCD_MODE)
	{
	case _4BITS_LCD :
	{
		DISPLAY_vidLCDCommand(0x33);
		DISPLAY_vidLCDCommand(0x32);
		DISPLAY_vidLCDCommand(0x28);
	}
	break;
	case _8BITS_LCD :
	{
		DISPLAY_vidLCDCommand(0x38);
	}
	break;
	}

	DISPLAY_vidLCDCommand(0x0C);
	DISPLAY_vidLCDCommand(0x06);
	DISPLAY_vidLCDCommand(0x01);
	DISPLAY_vidLCDCommand(0x80);
}

void DISPLAY_vidLCDWriteChar(u8 Copy_u8Character)
{
	u16 LOC_u16Temp;

	switch(LCD_MODE)
	{
	case _4BITS_LCD:
	{
		LOC_u16Temp = 	(0xFF0F)&((u16)GPIO_u32GetPortValue(LCD_DATA_PORT));
		GPIO_voidSetPortValue(LCD_DATA_PORT, LOC_u16Temp);

		LOC_u16Temp += 	((u16)(Copy_u8Character&0xF0));
		GPIO_voidSetPortValue(LCD_DATA_PORT, LOC_u16Temp);
		GPIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, HIGH);
		GPIO_voidSetPinValue(LCD_EN_PORT, LCD_EN_PIN, HIGH);
		TIM_vidDelayus(TIM_2, 1);
		GPIO_voidSetPinValue(LCD_EN_PORT, LCD_EN_PIN, LOW);
		TIM_vidDelayus(TIM_2, 190);

		LOC_u16Temp &= 	(0xFF0F);
		LOC_u16Temp += 	((u16)(Copy_u8Character<<4));
		GPIO_voidSetPortValue(LCD_DATA_PORT, LOC_u16Temp);
		GPIO_voidSetPinValue(LCD_EN_PORT, LCD_EN_PIN, HIGH);
		TIM_vidDelayus(TIM_2, 1);
		GPIO_voidSetPinValue(LCD_EN_PORT, LCD_EN_PIN, LOW);

		TIM_vidDelayms(TIM_3, 2);
	}
	break;
	case _8BITS_LCD:
	{
		LOC_u16Temp = 	(0xFF00)&((u16)GPIO_u32GetPortValue(LCD_DATA_PORT));
		GPIO_voidSetPortValue(LCD_DATA_PORT, LOC_u16Temp);

		LOC_u16Temp += 	((u16)Copy_u8Character);
		GPIO_voidSetPortValue(LCD_DATA_PORT, LOC_u16Temp);
		GPIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, HIGH);
		GPIO_voidSetPinValue(LCD_RW_PORT, LCD_RW_PIN, LOW);
		GPIO_voidSetPinValue(LCD_EN_PORT, LCD_EN_PIN, HIGH);
		TIM_vidDelayus(TIM_2, 1);
		GPIO_voidSetPinValue(LCD_EN_PORT, LCD_EN_PIN, LOW);

		TIM_vidDelayms(TIM_3, 1);
	}
	break;
	}
}

void DISPLAY_vidLCDWriteString(u8* Copy_String)
{
	u32 LOC_u32Counter;
	for(LOC_u32Counter = 0; Copy_String[LOC_u32Counter]!='\0'; LOC_u32Counter++)
	{
		DISPLAY_vidLCDWriteChar(Copy_String[LOC_u32Counter]);
	}
}

void DISPLAY_vidLCDWriteStringXY(u8 Copy_u8Row, u8 Copy_u8Position, u8* Copy_String)
{
	if(Copy_u8Position < 16)
	{
		switch(Copy_u8Row)
		{
		case 0:
			DISPLAY_vidLCDCommand((Copy_u8Position&0x0F)|0x80);
			break;
		case 1:
			DISPLAY_vidLCDCommand((Copy_u8Position&0x0F)|0xC0);
			break;
		}
		DISPLAY_vidLCDWriteString(Copy_String);
	}
	else
	{
	}
}

void DISPLAY_vidLCDWriteInteger(u32 Copy_u32Integer)
{
	switch(Copy_u32Integer)
	{
	case 0 :	DISPLAY_vidLCDWriteSingleInteger(0);	break;
	default:
	{
		s8 	LOC_s8Counter 	= 0;
		u32 LOC_u32Temp 	= 1;
		u32 LOC_u32Tens		= 1;
		BOOL LOC_bFirstTime = TRUE;
		while(0 != LOC_u32Temp)
		{
			LOC_u32Temp = (Copy_u32Integer/LOC_u32Tens)%10;
			if(0 != LOC_u32Temp)
			{
				LOC_u32Tens *= 10;
				LOC_s8Counter++;
			}
			else
			{
			}
		}
		LOC_u32Tens /= 10;
		for(; LOC_s8Counter>1; )
		{
			if(TRUE == LOC_bFirstTime)
			{
				LOC_bFirstTime = FALSE;
				LOC_s8Counter--;
				LOC_u32Temp = (Copy_u32Integer/LOC_u32Tens);
				LOC_u32Tens /= 10;
				DISPLAY_vidLCDWriteSingleInteger((u8)LOC_u32Temp);
			}
			else
			{
				LOC_s8Counter--;
				LOC_u32Tens /= 10;
				LOC_u32Temp = (Copy_u32Integer/(LOC_s8Counter*10))%10;
				DISPLAY_vidLCDWriteSingleInteger((u8)LOC_u32Temp);
			}
		}
		LOC_u32Temp = Copy_u32Integer%10;
		DISPLAY_vidLCDWriteSingleInteger((u8)LOC_u32Temp);
	}
	break;
	}
}

void DISPLAY_vidClearLCD(void)
{
	DISPLAY_vidLCDCommand(0x01);
	DISPLAY_vidLCDCommand(0x80);
}

static void DISPLAY_vidLCDCommand(u8 Copy_u8Command)
{
	u16 LOC_u16Command;

	switch(LCD_MODE)
	{
	case _4BITS_LCD :
	{
		LOC_u16Command = 	(0xFF0F)&((u16)GPIO_u32GetPortValue(LCD_DATA_PORT));
		GPIO_voidSetPortValue(LCD_DATA_PORT, LOC_u16Command);

		LOC_u16Command += 	((u16)(Copy_u8Command&0xF0));

		GPIO_voidSetPortValue(LCD_DATA_PORT, LOC_u16Command);

		GPIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, LOW);

		GPIO_voidSetPinValue(LCD_EN_PORT, LCD_EN_PIN, HIGH);
		TIM_vidDelayus(TIM_2, 1);
		GPIO_voidSetPinValue(LCD_EN_PORT, LCD_EN_PIN, LOW);
		TIM_vidDelayus(TIM_2, 190);

		LOC_u16Command &= 	(0xFF0F);
		LOC_u16Command += 	((u16)(Copy_u8Command<<4));
		GPIO_voidSetPortValue(LCD_DATA_PORT, LOC_u16Command);

		GPIO_voidSetPinValue(LCD_EN_PORT, LCD_EN_PIN, HIGH);
		TIM_vidDelayus(TIM_2, 1);
		GPIO_voidSetPinValue(LCD_EN_PORT, LCD_EN_PIN, LOW);
		TIM_vidDelayms(TIM_3, 2);
	}
	break;
	case _8BITS_LCD :
	{
		LOC_u16Command = 	(0xFF00)&((u16)GPIO_u32GetPortValue(LCD_DATA_PORT));
		GPIO_voidSetPortValue(LCD_DATA_PORT, LOC_u16Command);

		LOC_u16Command += 	((u16)Copy_u8Command);
		GPIO_voidSetPortValue(LCD_DATA_PORT, LOC_u16Command);

		GPIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, LOW);
		GPIO_voidSetPinValue(LCD_RW_PORT, LCD_RW_PIN, LOW);
		GPIO_voidSetPinValue(LCD_EN_PORT, LCD_EN_PIN, HIGH);
		TIM_vidDelayus(TIM_2, 1);
		GPIO_voidSetPinValue(LCD_EN_PORT, LCD_EN_PIN, LOW);
		TIM_vidDelayms(TIM_3, 3);
	}
	break;
	}
}

static void DISPLAY_vidLCDWriteSingleInteger(u8 Copy_u8Integer)
{
	u8 LOC_u8IntASCII = Copy_u8Integer + 0x30;
	DISPLAY_vidLCDWriteChar(LOC_u8IntASCII);
}
