/*
 * SYSTICK_interface.h
 *
 *  Created on: Aug 23, 2022
 *      Author: Hosam
 */

#ifndef	SYSTIC_INTERFACE_H
#define	SYSTIC_INTERFACE_H

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/SYSTICK_config.h"
#include "MCAL/SYSTICK_private.h"

typedef enum
{
	AHB_DIVIDED_BY_8,
	AHB
}CLK_SELECTION;

void SYSTICK_vidInit(void);
u32  SYSTICK_u32GetTime(void);
void SYSTICK_vidDelaySec(u8 Copy_u8Seconds);
void SYSTICK_vidDelayTicksSync(u32 Copy_u32NumberOfTicks);
void SYSTICK_vidStartAsync(u32 Copy_u32NumberOfTicks, void (*Copy_ptrToFunc)(void));
void SYSTICK_vidDelayMicroSec(u16 Copy_u16MicroSeconds);
void SYSTICK_vidDelayMilliSec(u16 Copy_u16MilliSeconds);
void SYSTICK_vidDelaySeconds(u8 Copy_u8Seconds);

void SYSTICK_vidStartSysTick(void);
void SYSTICK_vidStopSysTick(void);

#endif
