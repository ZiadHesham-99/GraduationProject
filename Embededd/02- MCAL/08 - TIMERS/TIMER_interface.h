/*
 * TIMER_interface.h
 *
 *  Created on: Oct 13, 2022
 *      Author: Hosam
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#include "TIMER_private.h"
#include "TIMER_config.h"

#define	TIM_NOT_USED	(0xFFFFFFFF)

typedef enum
{
	TIM_1	= (u8)1,
	TIM_2,
	TIM_3,
	TIM_4,
	TIM_5,
	TIM_9,
	TIM_10,
	TIM_11
}TIM_x;

typedef enum
{
	UP_COUNTER	= (u8)0,
	DOWN_COUNTER
}TIM_DIRECTION;

typedef enum
{
	FROZEN	= (u8)0,
	SET_CHANNEL,
	CLR_CHANNEL,
	TOGGLE,
	FORCE_INACTIVE_LVL,
	FORCE_ACTIVE_LVL,
	PWM1,
	PWM2
}OC_MODE;

typedef enum
{
	ACTIVE_HIGH	= (u8)0,
	ACTIVE_LOw
}OC_POLARITY;

typedef enum
{
	DELAY	= (u8)0,
	OC,
}TIM_MODE;

typedef enum
{
	CHANNEL1	= (u8)0,
	CHANNEL2,
	CHANNEL3,
	CHANNEL4
}TIM_CHANNEL;

typedef struct
{
	TIM_x					enuTIM_x;
	TIM_DIRECTION			enumTimDirection;
	u16						u16Prescaler;
	u32						u32AutoReloadValue;
	TIM_MODE				enumMode;
	u32						u32SignalFreq;
	OC_POLARITY				enumOCPolarity;
}TIM_CONFIG;

TIM_CONFIG GLOB_ptrStrTIM[NUM_OF_TIM_USED];

void TIM_vidInit(TIM_CONFIG *Copy_ptrStrTIM);
void TIM_vidDelayus(TIM_x Copy_enuTIM_x, u16 Copy_u16us);
void TIM_vidDelayms(TIM_x Copy_enuTIM_x, u16 Copy_u16ms);
void TIM_vidDelaySec(TIM_x Copy_enuTIM_x, u16 Copy_u16Sec);
void TIM_vidOCToggleEnable(TIM_CONFIG Copy_strTIMx, TIM_CHANNEL Copy_enumChannel, u32 Copy_u32SignalFreq);
void TIM_vidOCToggleDisable(TIM_CONFIG Copy_strTIMx, TIM_CHANNEL Copy_enumChannel);




#endif /* 02__MCAL_08___TIMERS_TIMER_INTERFACE_H_ */
