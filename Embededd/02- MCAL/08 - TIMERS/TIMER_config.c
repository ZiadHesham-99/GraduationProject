/*
 * TIMER_config.c
 *
 *  Created on: Nov 5, 2022
 *      Author: Hosam
 */

#include "TIMER_interface.h"
#include "TIMER_config.h"
#include "TIMER_private.h"

TIM_CONFIG GLOB_ptrStrTIM[NUM_OF_TIM_USED] =
{
		[0] =
		{
				.enuTIM_x			= TIM_2,
				.enumTimDirection	= UP_COUNTER,
				.u16Prescaler		= 1000,
				.u32AutoReloadValue	= ~(TIM_NOT_USED),
				.enumMode			= DELAY,
				.u32SignalFreq		= ~(TIM_NOT_USED),
				.enumOCPolarity		= ACTIVE_HIGH
		},
};

