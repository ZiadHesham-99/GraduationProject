
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/SYSTICK_interface.h"
#include "MCAL/SYSTICK_config.h"
#include "MCAL/SYSTICK_private.h"

f64 Global_f64SysTickFreq;
void (*Global_ptrToFuncISR)(void);

void SYSTICK_voidInit (void)
{
	SYSTICK_R->CTRL.REGISTER = 0;
	SYSTICK_R->CTRL.BIT.CLKSRC = SYSTICK_CLK_SELECTION;
	switch (SYSTICK_CLK_SELECTION) {
	case AHB:
		Global_f64SysTickFreq = (f64)AHB_CLK_IN_MHZ;
		break;
	case AHB_DIVIDED_BY_8:
		Global_f64SysTickFreq = AHB_CLK_IN_MHZ/8.0;
		break;
	}
}

void SYSTICK_voidDelayTicksSync(u32 Copy_u32NumberOfTicks){
	SYSTICK_R->VAL.BIT.CURRENT = 0;
	SYSTICK_R->LOAD.BIT.RELOAD = Copy_u32NumberOfTicks - 1 ;
	SYSTICK_R->CTRL.BIT.ENABLE = 1;
	while(!SYSTICK_R->CTRL.BIT.COUNTFLAG);
	SYSTICK_R->CTRL.BIT.COUNTFLAG = 0;
}

void SYSTICK_voidDelayTicksAsync(u32 Copy_u32NumberOfTicks, void (*Copy_ptrToFunc)(void)){
	SYSTICK_R->VAL.BIT.CURRENT = 0;
	SYSTICK_R->LOAD.BIT.RELOAD = Copy_u32NumberOfTicks - 1 ;
	Global_ptrToFuncISR = Copy_ptrToFunc;
	SYSTICK_R->CTRL.BIT.TICKINT = 1;
	SYSTICK_R->CTRL.BIT.ENABLE = 1;
}

void SYSTICK_voidDelayMicroSec(u16 Copy_u16MicroSeconds){
	u16 Copy_u16Counter;
	if((Global_f64SysTickFreq*1)>16777215){
		Global_f64SysTickFreq = AHB_CLK_IN_MHZ/8.0;
		SYSTICK_R->CTRL.BIT.CLKSRC = AHB_DIVIDED_BY_8;
	}
	u32 Copy_u32NumberOfTicks = 1*Global_f64SysTickFreq;
	SYSTICK_R->VAL.REGISTER = 0;
	for(Copy_u16Counter = 0; Copy_u16Counter < Copy_u16MicroSeconds; Copy_u16Counter++){
		SYSTICK_R->LOAD.REGISTER = Copy_u32NumberOfTicks-1;
		SYSTICK_R->CTRL.BIT.ENABLE = 1;
		while(!SYSTICK_R->CTRL.BIT.COUNTFLAG);
		SYSTICK_R->CTRL.BIT.COUNTFLAG = 0;
	}
}

void SYSTICK_voidDelayMilliSec(u16 Copy_u16MilliSeconds){
	u16 Copy_u16Counter;
	if((Global_f64SysTickFreq*1000)>16777215){
		Global_f64SysTickFreq = AHB_CLK_IN_MHZ/8.0;
		SYSTICK_R->CTRL.BIT.CLKSRC = AHB_DIVIDED_BY_8;
	}
	u32 Copy_u32NumberOfTicks = 1000*Global_f64SysTickFreq;
	SYSTICK_R->VAL.REGISTER = 0;
	for(Copy_u16Counter = 0; Copy_u16Counter < Copy_u16MilliSeconds; Copy_u16Counter++){
		SYSTICK_R->LOAD.REGISTER = Copy_u32NumberOfTicks-1;
		SYSTICK_R->CTRL.BIT.ENABLE = 1;
		while(!SYSTICK_R->CTRL.BIT.COUNTFLAG);
		SYSTICK_R->CTRL.BIT.COUNTFLAG = 0;
	}
}

void SYSTICK_voidDelaySeconds(u8 Copy_u8Seconds){
	u8 Local_u8SecondsCounter;
	if((Global_f64SysTickFreq*1000000)>16777215){
		Global_f64SysTickFreq = AHB_CLK_IN_MHZ/8.0;
		SYSTICK_R->CTRL.BIT.CLKSRC = AHB_DIVIDED_BY_8;
	}
	u32 Copy_u32NumberOfTicks = 1000000*Global_f64SysTickFreq;
	SYSTICK_R -> VAL.REGISTER = 0;
	for(Local_u8SecondsCounter = 0; Local_u8SecondsCounter < Copy_u8Seconds; Local_u8SecondsCounter++){
		SYSTICK_R -> LOAD.REGISTER = Copy_u32NumberOfTicks-1;
		SYSTICK_R -> CTRL.BIT.ENABLE = 1;
		while(SYSTICK_R -> CTRL.BIT.COUNTFLAG == 0);
		SYSTICK_R -> CTRL.BIT.COUNTFLAG = 0;
	}
}

void SYSTICK_voidStopSysTick(void){
	SYSTICK_R->LOAD.BIT.RELOAD = 0;
	SYSTICK_R->CTRL.BIT.ENABLE = 0;
}

void SysTick_Handler(void){
	Global_ptrToFuncISR();
}

