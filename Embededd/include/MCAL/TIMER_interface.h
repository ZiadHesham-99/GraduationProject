/*
 * TIMER_interface.h
 *
 *  Created on: Oct 13, 2022
 *      Author: Hosam
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/TIMER_config.h"
#include "MCAL/TIMER_private.h"

#define	TIM_NOT_USED	(u32)(0xFFFFFFFF)

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

/*typedef enum
{
	FROZEN	= (u8)0,
	SET_CHANNEL,
	CLR_CHANNEL,
	TOGGLE,
	FORCE_INACTIVE_LVL,
	FORCE_ACTIVE_LVL,
	PWM1,
	PWM2
}OC_MODE;*/

typedef enum
{
	PWM_ACTIVE_HIGH	= (u8)0,
	PWM_ACTIVE_LOW
}PWM_POLARITY;

typedef enum
{
	PWM_0_PERCENTAGE 	= 0,
	PWM_3_PERCENTAGE 	= 3,
	PWM_5_PERCENTAGE 	= 5,
	PWM_6_PERCENTAGE 	= 6,
	PWM_8_PERCENTAGE 	= 8,
	PWM_10_PERCENTAGE 	= 10,
	PWM_12_PERCENTAGE 	= 12,
	PWM_13_PERCENTAGE 	= 13,
	PWM_20_PERCENTAGE 	= 20,
	PWM_25_PERCENTAGE 	= 25,
	PWM_30_PERCENTAGE 	= 30,
	PWM_40_PERCENTAGE 	= 40,
	PWM_50_PERCENTAGE 	= 50,
	PWM_60_PERCENTAGE 	= 60,
	PWM_70_PERCENTAGE 	= 70,
	PWM_75_PERCENTAGE 	= 75,
	PWM_80_PERCENTAGE 	= 80,
	PWM_90_PERCENTAGE 	= 90,
	PWM_100_PERCENTAGE 	= 100,
}PWM_DUTY_CYCLE_PER;

typedef enum
{
	IC_NO_PRESCALER = (u8)0,
	IC_CAPTURE_EVERY_2_EVENTS,
	IC_CAPTURE_EVERY_4_EVENTS,
	IC_CAPTURE_EVERY_8_EVENTS
}IC_PRESCALER;

typedef enum
{
	IC_RAISING_EDGE = (u8)0,
	IC_FALLING_EDGE,
	IC_BOTH_EDGES = (u8)3
}IC_POLARITY;

typedef enum
{
	PWM_CHANNEL = (u8)0,
	IC_DIRECT_MODE_TI1,
	IC_INDIRECT_MODE_TI2,
	IC_TRC_MODE
}CHANNEL_MODE;

typedef enum
{
	IC_NO_FILTER = (u8)0,
	IC_F_CK_INT_N2,
	IC_F_CK_INT_N4,
	IC_F_CK_INT_N8,
	IC_F_DTS_2_N6,
    IC_F_DTS_2_N8,
    IC_F_DTS_4_N6,
	IC_F_DTS_4_N8,
	IC_F_DTS_8_N6,
	IC_F_DTS_8_N8,
	IC_F_DTS_16_N5,
	IC_F_DTS_16_N6,
	IC_F_DTS_16_N8,
	IC_F_DTS_32_N5,
	IC_F_DTS_32_N6,
	IC_F_DTS_32_N8,
}IC_FILTER;

typedef enum
{
	TIM_CHANNEL1	= (u8)1,
	TIM_CHANNEL2,
	TIM_CHANNEL3,
	TIM_CHANNEL4
}TIM_CHANNEL;

typedef enum
{
	TIM_DELAY	= (u8)0,
	TIM_INPUT_OUTPUT
}TIM_MODE;

typedef struct
{
	TIM_CHANNEL		enmTimChannel;
	CHANNEL_MODE	enmChannelMode;
	IC_POLARITY		enmICPolarity;
	IC_PRESCALER	enmICPrescaler;
	IC_FILTER		enmICFilter;
	PWM_POLARITY	enmPWMPolarity;
}TIM_CHANNEL_CONFIG;

typedef struct
{
	TIM_x				enmTIM_x;
	TIM_DIRECTION		enmTimDirection;
	TIM_MODE			enmMode;
	u16					u16Prescaler;
	TIM_CHANNEL_CONFIG	aStrChannelConfig[4];
}TIM_CONFIG;

TIM_CONFIG GLOB_aStrTIM[NUM_OF_TIM_USED];

void TIM_vidInit(void);

void TIM_vidICStart(TIM_x Copy_enmTIM_x, TIM_CHANNEL Copy_enmChannel);
void TIM_vidICStop(TIM_x Copy_enmTIM_x, TIM_CHANNEL Copy_enmChannel);
u32 TIM_u32ICGetCapturedValue(TIM_x Copy_enmTIM_x, TIM_CHANNEL Copy_enmChannel);

u32 TIM_u32GetPlusesCapturedDelayus(TIM_x Copy_enmTIM_x, TIM_CHANNEL Copy_enmChannel, u16 Copy_u16us);
u32 TIM_u32GetPlusesCapturedDelayms(TIM_x Copy_enmTIM_x, TIM_CHANNEL Copy_enmChannel, u16 Copy_u16ms);
u32 TIM_u32GetPlusesCapturedDelaySec(TIM_x Copy_enmTIM_x, TIM_CHANNEL Copy_enmChannel, u16 Copy_u16Sec);

void TIM_vidPWMStart(TIM_x Copy_enmTIM_x, TIM_CHANNEL Copy_enmChannel, f32 Copy_f32SignalFreqInHz, PWM_DUTY_CYCLE_PER Copy_enmDutyCyclePer);
void TIM_vidPWMStop(TIM_x Copy_enmTIM_x, TIM_CHANNEL Copy_enmChannel);

void TIM_vidDelayus(TIM_x Copy_enuTIM_x, u16 Copy_u16us);
void TIM_vidDelayms(TIM_x Copy_enuTIM_x, u16 Copy_u16ms);
void TIM_vidDelaySec(TIM_x Copy_enuTIM_x, u16 Copy_u16Sec);


#endif /* 02__MCAL_08___TIMERS_TIMER_INTERFACE_H_ */
