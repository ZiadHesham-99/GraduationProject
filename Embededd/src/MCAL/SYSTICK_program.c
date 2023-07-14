
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/SYSTICK_interface.h"
#include "MCAL/SYSTICK_config.h"
#include "MCAL/SYSTICK_private.h"

static f64 LOC_f64SysTickFreq;
void (*Global_ptrToFuncISR)(void);

void SYSTICK_vidInit(void)
{
	LOC_f64SysTickFreq = 0;
	SYSTICK_R->CTRL.REGISTER = 0;
	SYSTICK_R->CTRL.BIT.CLKSRC = SYSTICK_CLK_SELECTION;
	switch (SYSTICK_CLK_SELECTION)
	{
	case AHB:
		LOC_f64SysTickFreq = (f64)AHB_CLK_IN_MHZ;
		break;
	case AHB_DIVIDED_BY_8:
		LOC_f64SysTickFreq = AHB_CLK_IN_MHZ/8.0;
		break;
	}
}

void SYSTICK_vidDelayTicksSync(u32 Copy_u32NumberOfTicks)
{
	SYSTICK_R->VAL.BIT.CURRENT = 0;
	SYSTICK_R->LOAD.BIT.RELOAD = Copy_u32NumberOfTicks;
	SYSTICK_R->CTRL.BIT.ENABLE = 1;
	while(FALSE == SYSTICK_R->CTRL.BIT.COUNTFLAG);
	SYSTICK_R->CTRL.BIT.COUNTFLAG = 0;
}

void SYSTICK_vidStartAsync(u32 Copy_u32NumberOfTicks, void (*Copy_ptrToFunc)(void))
{

	Global_ptrToFuncISR = Copy_ptrToFunc;
	SYSTICK_R->LOAD.REGISTER = Copy_u32NumberOfTicks - 1;
	SYSTICK_R->CTRL.BIT.TICKINT = 1;
	SYSTICK_R->CTRL.BIT.ENABLE = 1;
}

void SYSTICK_vidDelayMicroSec(u16 Copy_u16MicroSeconds)
{
	u16 LOC_u16Counter;

	if( (LOC_f64SysTickFreq) > 16777215 )
	{
		LOC_f64SysTickFreq = AHB_CLK_IN_MHZ/8.0;
		SYSTICK_R->CTRL.BIT.CLKSRC = AHB_DIVIDED_BY_8;
	}

	SYSTICK_R->VAL.REGISTER = 0;

	for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16MicroSeconds; LOC_u16Counter++)
	{
		SYSTICK_R->LOAD.REGISTER = (u32)(LOC_f64SysTickFreq - 1);
		SYSTICK_R->CTRL.BIT.ENABLE = 1;
		while(!SYSTICK_R->CTRL.BIT.COUNTFLAG);
		SYSTICK_R->CTRL.BIT.COUNTFLAG = 0;
	}
}

void SYSTICK_vidDelayMilliSec(u16 Copy_u16MilliSeconds)
{
	u16 LOC_u16Counter;

	if( (LOC_f64SysTickFreq*1000) > 16777215)
	{
		LOC_f64SysTickFreq = AHB_CLK_IN_MHZ/8.0;
		SYSTICK_R->CTRL.BIT.CLKSRC = AHB_DIVIDED_BY_8;
	}

	LOC_f64SysTickFreq *= 1000;
	SYSTICK_R->VAL.REGISTER = 0;

	for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16MilliSeconds; LOC_u16Counter++)
	{
		SYSTICK_R->LOAD.REGISTER = (u32)(LOC_f64SysTickFreq - 1);
		SYSTICK_R->CTRL.BIT.ENABLE = 1;
		while(!SYSTICK_R->CTRL.BIT.COUNTFLAG);
		SYSTICK_R->CTRL.BIT.COUNTFLAG = 0;
	}
}

void SYSTICK_vidDelaySeconds(u8 Copy_u8Seconds)
{
	u8 LOC_u8Counter;

	if( (LOC_f64SysTickFreq*1000000) > 16777215)
	{
		LOC_f64SysTickFreq = AHB_CLK_IN_MHZ/8.0;
		SYSTICK_R->CTRL.BIT.CLKSRC = AHB_DIVIDED_BY_8;
	}

	LOC_f64SysTickFreq *= 1000000;
	SYSTICK_R -> VAL.REGISTER = 0;

	for(LOC_u8Counter = 0; LOC_u8Counter < Copy_u8Seconds; LOC_u8Counter++)
	{
		SYSTICK_R -> LOAD.REGISTER = (u32)(LOC_f64SysTickFreq - 1);
		SYSTICK_R -> CTRL.BIT.ENABLE = 1;
		while(SYSTICK_R -> CTRL.BIT.COUNTFLAG == 0);
		SYSTICK_R -> CTRL.BIT.COUNTFLAG = 0;
	}
}

void SYSTICK_vidStartSysTick(void)
{
	SYSTICK_R->VAL.BIT.CURRENT = 0;
	SYSTICK_R->LOAD.BIT.RELOAD = 0xFFFFFF;
	SYSTICK_R->CTRL.BIT.ENABLE = 1;
}

void SYSTICK_vidStopSysTick(void)
{
	SYSTICK_R->CTRL.BIT.ENABLE = 0;
}

u32 SYSTICK_u32GetTime(void)
{
	u32 LOC_u32Time = 0;

	LOC_u32Time = SYSTICK_R->LOAD.BIT.RELOAD;
	LOC_u32Time -= SYSTICK_R->VAL.BIT.CURRENT;

	return LOC_u32Time;
}

SysTick_Handler()
{
	Global_ptrToFuncISR();
}

