/*
 * Delay.c
 *
 *  Created on: Mar 5, 2023
 *      Author: Hosam
 */


#include "LIB/STD_TYPES.h"

#include "MCAL/TIMER_interface.h"

#include "SERVICES/Delay.h"

void Delay_us(u16 Copy_u16us)
{
	TIM_vidDelayus(TIM_10, Copy_u16us);
}
void Delay_ms(u16 Copy_u16ms)
{
	TIM_vidDelayms(TIM_11, Copy_u16ms);
}
void Delay_seconds(u16 Copy_u16seconds)
{
	TIM_vidDelaySec(TIM_11, Copy_u16seconds);
}
