/*
 * TIMER_config.c
 *
 *  Created on: Nov 5, 2022
 *      Author: Hosam
 */

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/TIMER_interface.h"
#include "MCAL/TIMER_config.h"
#include "MCAL/TIMER_private.h"

TIM_CONFIG GLOB_aStrTIM[NUM_OF_TIM_USED] =
{
		[0] =
		{
				.enmTIM_x				= TIM_10,
				.enmMode				= TIM_DELAY,
				.enmTimDirection		= UP_COUNTER,
				.u16Prescaler			= 0,
		},
		[1] =
		{
				.enmTIM_x				= TIM_11,
				.enmMode				= TIM_DELAY,
				.enmTimDirection		= UP_COUNTER,
				.u16Prescaler			= 999,
		},
		[2] =
		{
				.enmTIM_x				= TIM_2,
				.enmMode				= TIM_INPUT_OUTPUT,
				.enmTimDirection		= UP_COUNTER,
				.u16Prescaler			= 0,
				.aStrChannelConfig[0] 	=
				{
						.enmTimChannel	= TIM_CHANNEL3,
						.enmChannelMode	= PWM_CHANNEL,
						.enmICPolarity	= TIM_NOT_USED,
						.enmICPrescaler	= TIM_NOT_USED,
						.enmICFilter	= TIM_NOT_USED,
						.enmPWMPolarity = PWM_ACTIVE_HIGH
				},
				.aStrChannelConfig[1] 	=
				{
						.enmTimChannel	= TIM_CHANNEL4,
						.enmChannelMode	= PWM_CHANNEL,
						.enmICPolarity	= TIM_NOT_USED,
						.enmICPrescaler	= TIM_NOT_USED,
						.enmICFilter	= TIM_NOT_USED,
						.enmPWMPolarity = PWM_ACTIVE_HIGH
				},
		},
		[3] =
		{
				.enmTIM_x				= TIM_3,
				.enmMode				= TIM_INPUT_OUTPUT,
				.enmTimDirection		= UP_COUNTER,
				.u16Prescaler			= 0,
				.aStrChannelConfig[0] 	=
				{
						.enmTimChannel	= TIM_CHANNEL1,
						.enmChannelMode	= IC_DIRECT_MODE_TI1,
						.enmICPolarity	= IC_RAISING_EDGE,
						.enmICPrescaler	= IC_NO_PRESCALER,
						.enmICFilter	= IC_NO_FILTER,
						.enmPWMPolarity = TIM_NOT_USED
				},
				.aStrChannelConfig[1] 	=
				{
						.enmTimChannel	= TIM_CHANNEL2,
						.enmChannelMode	= IC_DIRECT_MODE_TI1,
						.enmICPolarity	= IC_RAISING_EDGE,
						.enmICPrescaler	= IC_NO_PRESCALER,
						.enmICFilter	= IC_NO_FILTER,
						.enmPWMPolarity = TIM_NOT_USED
				},
		},
};

