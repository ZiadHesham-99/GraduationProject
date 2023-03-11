/*
 * Display.h
 *
 *  Created on: Dec 18, 2022
 *      Author: Hosam
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/GPIO_interface.h"
#include "MCAL/TIMER_interface.h"

/*
 * Configuration of LCD :
 */

/*
 * Select from :
 * 	_4BITS_LCD
 * 	_8BITS_LCD
 */

#define	LCD_EN_PORT		PORT_A
#define	LCD_EN_PIN		PIN4


#define	LCD_RS_PORT		PORT_A
#define	LCD_RS_PIN		PIN2

#define	LCD_RW_PORT		PORT_A
#define	LCD_RW_PIN		PIN3

#define	LCD_DATA_PORT	PORT_B




typedef enum
{
	_4BITS_LCD = (u8)1,
	_8BITS_LCD
}LCD_BIT_MODE;

#define	LCD_MODE		_4BITS_LCD

void DISPLAY_vidLCDInit(void);
void DISPLAY_vidLCDWriteChar(u8 Copy_u8Character);
void DISPLAY_vidLCDWriteString(u8* Copy_String);
void DISPLAY_vidLCDWriteInteger(u32 Copy_u32Integer);
void DISPLAY_vidLCDWriteStringXY(u8 Copy_u8Row, u8 Copy_u8Position, u8* Copy_String);

static void DISPLAY_vidLCDCommand(u8 Copy_u8Command);
static void DISPLAY_vidLCDWriteSingleInteger(u8 Copy_u8Integer);
#endif
