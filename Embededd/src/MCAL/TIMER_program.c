/*
 * TIMER_program.c
 *
 *  Created on: Oct 13, 2022
 *      Author: Hosam
 */

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/TIMER_interface.h"
#include "MCAL/TIMER_config.h"
#include "MCAL/TIMER_private.h"


/*
 * switch(LOC_strTemp.enuTIM_x)
		{
		case TIM_1 :
		{

		}
		break;
		case TIM_2 :
		{

		}
		break;
		case TIM_3 :
		{

		}
		break;
		case TIM_4 :
		{

		}
		break;
		case TIM_5 :
		{

		}
		break;
		case TIM_9 :
		{

		}
		break;
		case TIM_10 :
		{

		}
		break;
		case TIM_11 :
		{

		}
		break;
		default :
			break;
		}// end of switch
 */

/*
 * switch(Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			break;
		case TIM_CHANNEL2:
			break;
		case TIM_CHANNEL3:
			break;
		case TIM_CHANNEL4:
			break;
		}
 */

void TIM_vidInit(void)
{
	u8 LOC_u8Counter;
	TIM_CONFIG LOC_strTemp;
	for (LOC_u8Counter = 0; LOC_u8Counter < NUM_OF_TIM_USED; LOC_u8Counter++)
	{
		LOC_strTemp = GLOB_aStrTIM[LOC_u8Counter];
		switch (LOC_strTemp.enmTIM_x)
		{
		case TIM_1:
		{
			TIM1_R->PSC.BIT.PSC = LOC_strTemp.u16Prescaler;
			TIM1_R->CR1.BIT.DIR = LOC_strTemp.enmTimDirection;

			if (TIM_INPUT_OUTPUT == LOC_strTemp.enmMode)
			{
				u8 LOC_u8Counter2;
				TIM_CHANNEL_CONFIG LOC_strChannelConfigTemp;
				for (LOC_u8Counter2 = 0; LOC_u8Counter2 < NUM_OF_CHANNELS_USED_TIM1; LOC_u8Counter2++)
				{
					LOC_strChannelConfigTemp = LOC_strTemp.aStrChannelConfig[LOC_u8Counter2];
					switch (LOC_strChannelConfigTemp.enmTimChannel)
					{
					case TIM_CHANNEL1:
						TIM1_R->CCER.BIT.CC1E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM1_R->CCMR1.BIT_OCM.CC1S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM1_R->CCMR1.BIT_OCM.OC1M = 0b110;
							TIM1_R->CCER.BIT.CC1P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM1_R->CCMR1.BIT_OCM.OC1PE = TRUE;
						}
						else
						{
							TIM1_R->CCMR1.BIT_ICM.CC1S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM1_R->CCMR1.BIT_ICM.IC1PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM1_R->CCMR1.BIT_ICM.IC1F = LOC_strChannelConfigTemp.enmICFilter;
							TIM1_R->CCER.BIT.CC1P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM1_R->CCER.BIT.CC1NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					case TIM_CHANNEL2:
						TIM1_R->CCER.BIT.CC2E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM1_R->CCMR1.BIT_OCM.CC2S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM1_R->CCMR1.BIT_OCM.OC2M = 0b110;
							TIM1_R->CCER.BIT.CC2P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM1_R->CCMR1.BIT_OCM.OC2PE = TRUE;
						}
						else
						{
							TIM1_R->CCMR1.BIT_ICM.CC2S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM1_R->CCMR1.BIT_ICM.IC2PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM1_R->CCMR1.BIT_ICM.IC2F = LOC_strChannelConfigTemp.enmICFilter;
							TIM1_R->CCER.BIT.CC2P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM1_R->CCER.BIT.CC2NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					case TIM_CHANNEL3:
						TIM1_R->CCER.BIT.CC3E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM1_R->CCMR2.BIT_OCM.CC3S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM1_R->CCMR2.BIT_OCM.OC3M = 0b110;
							TIM1_R->CCER.BIT.CC3P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM1_R->CCMR2.BIT_OCM.OC3PE = TRUE;
						}
						else
						{
							TIM1_R->CCMR2.BIT_ICM.CC3S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM1_R->CCMR2.BIT_ICM.IC3PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM1_R->CCMR2.BIT_ICM.IC3F = LOC_strChannelConfigTemp.enmICFilter;
							TIM1_R->CCER.BIT.CC3P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM1_R->CCER.BIT.CC3NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					case TIM_CHANNEL4:
						TIM1_R->CCER.BIT.CC4E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM1_R->CCMR2.BIT_OCM.CC4S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM1_R->CCMR2.BIT_OCM.OC4M = 0b110;
							TIM1_R->CCER.BIT.CC4P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM1_R->CCMR2.BIT_OCM.OC4PE = TRUE;
						}
						else
						{
							TIM1_R->CCMR2.BIT_ICM.CC4S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM1_R->CCMR2.BIT_ICM.IC4PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM1_R->CCMR2.BIT_ICM.IC4F = LOC_strChannelConfigTemp.enmICFilter;
							TIM1_R->CCER.BIT.CC4P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM1_R->CCER.BIT.CC4NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					}
				}
			}
			else
			{
			}
		}
		break;
		case TIM_2:
		{
			TIM2_R->PSC.BIT.PSC = LOC_strTemp.u16Prescaler;
			TIM2_R->CR1.BIT.DIR = LOC_strTemp.enmTimDirection;

			if (TIM_INPUT_OUTPUT == LOC_strTemp.enmMode)
			{
				u8 LOC_u8Counter2;
				TIM_CHANNEL_CONFIG LOC_strChannelConfigTemp;
				for (LOC_u8Counter2 = 0; LOC_u8Counter2 < NUM_OF_CHANNELS_USED_TIM2; LOC_u8Counter2++)
				{
					LOC_strChannelConfigTemp = LOC_strTemp.aStrChannelConfig[LOC_u8Counter2];
					switch (LOC_strChannelConfigTemp.enmTimChannel)
					{
					case TIM_CHANNEL1:
						TIM2_R->CCER.BIT.CC1E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM2_R->CCMR1.BIT_OCM.CC1S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM2_R->CCMR1.BIT_OCM.OC1M = 0b110;
							TIM2_R->CCER.BIT.CC1P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM2_R->CCMR1.BIT_OCM.OC1PE = TRUE;
						}
						else
						{
							TIM2_R->CCMR1.BIT_ICM.CC1S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM2_R->CCMR1.BIT_ICM.IC1PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM2_R->CCMR1.BIT_ICM.IC1F = LOC_strChannelConfigTemp.enmICFilter;
							TIM2_R->CCER.BIT.CC1P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM2_R->CCER.BIT.CC1NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					case TIM_CHANNEL2:
						TIM2_R->CCER.BIT.CC2E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM2_R->CCMR1.BIT_OCM.CC2S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM2_R->CCMR1.BIT_OCM.OC2M = 0b110;
							TIM2_R->CCER.BIT.CC2P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM2_R->CCMR1.BIT_OCM.OC2PE = TRUE;
						}
						else
						{
							TIM2_R->CCMR1.BIT_ICM.CC2S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM2_R->CCMR1.BIT_ICM.IC2PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM2_R->CCMR1.BIT_ICM.IC2F = LOC_strChannelConfigTemp.enmICFilter;
							TIM2_R->CCER.BIT.CC2P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM2_R->CCER.BIT.CC2NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					case TIM_CHANNEL3:
						TIM2_R->CCER.BIT.CC3E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM2_R->CCMR2.BIT_OCM.CC3S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM2_R->CCMR2.BIT_OCM.OC3M = 0b110;
							TIM2_R->CCER.BIT.CC3P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM2_R->CCMR2.BIT_OCM.OC3PE = TRUE;
						}
						else
						{
							TIM2_R->CCMR2.BIT_ICM.CC3S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM2_R->CCMR2.BIT_ICM.IC3PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM2_R->CCMR2.BIT_ICM.IC3F = LOC_strChannelConfigTemp.enmICFilter;
							TIM2_R->CCER.BIT.CC3P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM2_R->CCER.BIT.CC3NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					case TIM_CHANNEL4:
						TIM2_R->CCER.BIT.CC4E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM2_R->CCMR2.BIT_OCM.CC4S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM2_R->CCMR2.BIT_OCM.OC4M = 0b110;
							TIM2_R->CCER.BIT.CC4P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM2_R->CCMR2.BIT_OCM.OC4PE = TRUE;
						}
						else
						{
							TIM2_R->CCMR2.BIT_ICM.CC4S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM2_R->CCMR2.BIT_ICM.IC4PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM2_R->CCMR2.BIT_ICM.IC4F = LOC_strChannelConfigTemp.enmICFilter;
							TIM2_R->CCER.BIT.CC4P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM2_R->CCER.BIT.CC4NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					}
				}
			}
			else
			{
			}
		}
		break;
		case TIM_3:
		{
			TIM3_R->PSC.BIT.PSC = LOC_strTemp.u16Prescaler;
			TIM3_R->CR1.BIT.DIR = LOC_strTemp.enmTimDirection;

			if (TIM_INPUT_OUTPUT == LOC_strTemp.enmMode)
			{
				u8 LOC_u8Counter2;
				TIM_CHANNEL_CONFIG LOC_strChannelConfigTemp;
				for (LOC_u8Counter2 = 0; LOC_u8Counter2 < NUM_OF_CHANNELS_USED_TIM3; LOC_u8Counter2++)
				{
					LOC_strChannelConfigTemp = LOC_strTemp.aStrChannelConfig[LOC_u8Counter2];
					switch (LOC_strChannelConfigTemp.enmTimChannel)
					{
					case TIM_CHANNEL1:
						TIM3_R->CCER.BIT.CC1E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM3_R->CCMR1.BIT_OCM.CC1S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM3_R->CCMR1.BIT_OCM.OC1M = 0b110;
							TIM3_R->CCER.BIT.CC1P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM3_R->CCMR1.BIT_OCM.OC1PE = TRUE;
						}
						else
						{
							TIM3_R->CCMR1.BIT_ICM.CC1S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM3_R->CCMR1.BIT_ICM.IC1PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM3_R->CCMR1.BIT_ICM.IC1F = LOC_strChannelConfigTemp.enmICFilter;
							TIM3_R->CCER.BIT.CC1P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM3_R->CCER.BIT.CC1NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					case TIM_CHANNEL2:
						TIM3_R->CCER.BIT.CC2E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM3_R->CCMR1.BIT_OCM.CC2S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM3_R->CCMR1.BIT_OCM.OC2M = 0b110;
							TIM3_R->CCER.BIT.CC2P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM3_R->CCMR1.BIT_OCM.OC2PE = TRUE;
						}
						else
						{
							TIM3_R->CCMR1.BIT_ICM.CC2S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM3_R->CCMR1.BIT_ICM.IC2PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM3_R->CCMR1.BIT_ICM.IC2F = LOC_strChannelConfigTemp.enmICFilter;
							TIM3_R->CCER.BIT.CC2P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM3_R->CCER.BIT.CC2NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					case TIM_CHANNEL3:
						TIM3_R->CCER.BIT.CC3E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM3_R->CCMR2.BIT_OCM.CC3S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM3_R->CCMR2.BIT_OCM.OC3M = 0b110;
							TIM3_R->CCER.BIT.CC3P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM3_R->CCMR2.BIT_OCM.OC3PE = TRUE;
						}
						else
						{
							TIM3_R->CCMR2.BIT_ICM.CC3S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM3_R->CCMR2.BIT_ICM.IC3PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM3_R->CCMR2.BIT_ICM.IC3F = LOC_strChannelConfigTemp.enmICFilter;
							TIM3_R->CCER.BIT.CC3P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM3_R->CCER.BIT.CC3NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					case TIM_CHANNEL4:
						TIM3_R->CCER.BIT.CC4E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM3_R->CCMR2.BIT_OCM.CC4S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM3_R->CCMR2.BIT_OCM.OC4M = 0b110;
							TIM3_R->CCER.BIT.CC4P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM3_R->CCMR2.BIT_OCM.OC4PE = TRUE;
						}
						else
						{
							TIM3_R->CCMR2.BIT_ICM.CC4S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM3_R->CCMR2.BIT_ICM.IC4PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM3_R->CCMR2.BIT_ICM.IC4F = LOC_strChannelConfigTemp.enmICFilter;
							TIM3_R->CCER.BIT.CC4P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM3_R->CCER.BIT.CC4NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					}
				}
			}
			else
			{
			}
		}
		break;
		case TIM_4:
		{
			TIM4_R->PSC.BIT.PSC = LOC_strTemp.u16Prescaler;
			TIM4_R->CR1.BIT.DIR = LOC_strTemp.enmTimDirection;

			if (TIM_INPUT_OUTPUT == LOC_strTemp.enmMode)
			{
				u8 LOC_u8Counter2;
				TIM_CHANNEL_CONFIG LOC_strChannelConfigTemp;
				for (LOC_u8Counter2 = 0; LOC_u8Counter2 < NUM_OF_CHANNELS_USED_TIM4; LOC_u8Counter2++)
				{
					LOC_strChannelConfigTemp = LOC_strTemp.aStrChannelConfig[LOC_u8Counter2];
					switch (LOC_strChannelConfigTemp.enmTimChannel)
					{
					case TIM_CHANNEL1:
						TIM4_R->CCER.BIT.CC1E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM4_R->CCMR1.BIT_OCM.CC1S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM4_R->CCMR1.BIT_OCM.OC1M = 0b110;
							TIM4_R->CCER.BIT.CC1P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM4_R->CCMR1.BIT_OCM.OC1PE = TRUE;
						}
						else
						{
							TIM4_R->CCMR1.BIT_ICM.CC1S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM4_R->CCMR1.BIT_ICM.IC1PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM4_R->CCMR1.BIT_ICM.IC1F = LOC_strChannelConfigTemp.enmICFilter;
							TIM4_R->CCER.BIT.CC1P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM4_R->CCER.BIT.CC1NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					case TIM_CHANNEL2:
						TIM4_R->CCER.BIT.CC2E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM4_R->CCMR1.BIT_OCM.CC2S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM4_R->CCMR1.BIT_OCM.OC2M = 0b110;
							TIM4_R->CCER.BIT.CC2P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM4_R->CCMR1.BIT_OCM.OC2PE = TRUE;
						}
						else
						{
							TIM4_R->CCMR1.BIT_ICM.CC2S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM4_R->CCMR1.BIT_ICM.IC2PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM4_R->CCMR1.BIT_ICM.IC2F = LOC_strChannelConfigTemp.enmICFilter;
							TIM4_R->CCER.BIT.CC2P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM4_R->CCER.BIT.CC2NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					case TIM_CHANNEL3:
						TIM4_R->CCER.BIT.CC3E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM4_R->CCMR2.BIT_OCM.CC3S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM4_R->CCMR2.BIT_OCM.OC3M = 0b110;
							TIM4_R->CCER.BIT.CC3P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM4_R->CCMR2.BIT_OCM.OC3PE = TRUE;
						}
						else
						{
							TIM4_R->CCMR2.BIT_ICM.CC3S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM4_R->CCMR2.BIT_ICM.IC3PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM4_R->CCMR2.BIT_ICM.IC3F = LOC_strChannelConfigTemp.enmICFilter;
							TIM4_R->CCER.BIT.CC3P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM4_R->CCER.BIT.CC3NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					case TIM_CHANNEL4:
						TIM4_R->CCER.BIT.CC4E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM4_R->CCMR2.BIT_OCM.CC4S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM4_R->CCMR2.BIT_OCM.OC4M = 0b110;
							TIM4_R->CCER.BIT.CC4P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM4_R->CCMR2.BIT_OCM.OC4PE = TRUE;
						}
						else
						{
							TIM4_R->CCMR2.BIT_ICM.CC4S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM4_R->CCMR2.BIT_ICM.IC4PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM4_R->CCMR2.BIT_ICM.IC4F = LOC_strChannelConfigTemp.enmICFilter;
							TIM4_R->CCER.BIT.CC4P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM4_R->CCER.BIT.CC4NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					}
				}
			}
			else
			{
			}
		}
		break;
		case TIM_5:
		{
			TIM5_R->PSC.BIT.PSC = LOC_strTemp.u16Prescaler;
			TIM5_R->CR1.BIT.DIR = LOC_strTemp.enmTimDirection;

			if (TIM_INPUT_OUTPUT == LOC_strTemp.enmMode)
			{
				u8 LOC_u8Counter2;
				TIM_CHANNEL_CONFIG LOC_strChannelConfigTemp;
				for (LOC_u8Counter2 = 0; LOC_u8Counter2 < NUM_OF_CHANNELS_USED_TIM5; LOC_u8Counter2++)
				{
					LOC_strChannelConfigTemp = LOC_strTemp.aStrChannelConfig[LOC_u8Counter2];
					switch (LOC_strChannelConfigTemp.enmTimChannel)
					{
					case TIM_CHANNEL1:
						TIM5_R->CCER.BIT.CC1E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM5_R->CCMR1.BIT_OCM.CC1S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM5_R->CCMR1.BIT_OCM.OC1M = 0b110;
							TIM5_R->CCER.BIT.CC1P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM5_R->CCMR1.BIT_OCM.OC1PE = TRUE;
						}
						else
						{
							TIM5_R->CCMR1.BIT_ICM.CC1S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM5_R->CCMR1.BIT_ICM.IC1PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM5_R->CCMR1.BIT_ICM.IC1F = LOC_strChannelConfigTemp.enmICFilter;
							TIM5_R->CCER.BIT.CC1P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM5_R->CCER.BIT.CC1NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					case TIM_CHANNEL2:
						TIM5_R->CCER.BIT.CC2E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM5_R->CCMR1.BIT_OCM.CC2S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM5_R->CCMR1.BIT_OCM.OC2M = 0b110;
							TIM5_R->CCER.BIT.CC2P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM5_R->CCMR1.BIT_OCM.OC2PE = TRUE;
						}
						else
						{
							TIM5_R->CCMR1.BIT_ICM.CC2S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM5_R->CCMR1.BIT_ICM.IC2PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM5_R->CCMR1.BIT_ICM.IC2F = LOC_strChannelConfigTemp.enmICFilter;
							TIM5_R->CCER.BIT.CC2P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM5_R->CCER.BIT.CC2NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					case TIM_CHANNEL3:
						TIM5_R->CCER.BIT.CC3E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM5_R->CCMR2.BIT_OCM.CC3S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM5_R->CCMR2.BIT_OCM.OC3M = 0b110;
							TIM5_R->CCER.BIT.CC3P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM5_R->CCMR2.BIT_OCM.OC3PE = TRUE;
						}
						else
						{
							TIM5_R->CCMR2.BIT_ICM.CC3S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM5_R->CCMR2.BIT_ICM.IC3PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM5_R->CCMR2.BIT_ICM.IC3F = LOC_strChannelConfigTemp.enmICFilter;
							TIM5_R->CCER.BIT.CC3P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM5_R->CCER.BIT.CC3NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					case TIM_CHANNEL4:
						TIM5_R->CCER.BIT.CC4E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM5_R->CCMR2.BIT_OCM.CC4S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM5_R->CCMR2.BIT_OCM.OC4M = 0b110;
							TIM5_R->CCER.BIT.CC4P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM5_R->CCMR2.BIT_OCM.OC4PE = TRUE;
						}
						else
						{
							TIM5_R->CCMR2.BIT_ICM.CC4S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM5_R->CCMR2.BIT_ICM.IC4PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM5_R->CCMR2.BIT_ICM.IC4F = LOC_strChannelConfigTemp.enmICFilter;
							TIM5_R->CCER.BIT.CC4P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM5_R->CCER.BIT.CC4NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					}
				}
			}
			else
			{
			}
		}
		break;
		case TIM_9:
		{
			TIM9_R->PSC.BIT.PSC = LOC_strTemp.u16Prescaler;
			TIM9_R->CR1.BIT.DIR = LOC_strTemp.enmTimDirection;

			if (TIM_INPUT_OUTPUT == LOC_strTemp.enmMode)
			{
				u8 LOC_u8Counter2;
				TIM_CHANNEL_CONFIG LOC_strChannelConfigTemp;
				for (LOC_u8Counter2 = 0; LOC_u8Counter2 < NUM_OF_CHANNELS_USED_TIM9; LOC_u8Counter2++)
				{
					LOC_strChannelConfigTemp = LOC_strTemp.aStrChannelConfig[LOC_u8Counter2];
					switch (LOC_strChannelConfigTemp.enmTimChannel)
					{
					case TIM_CHANNEL1:
						TIM9_R->CCER.BIT.CC1E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM9_R->CCMR1.BIT_OCM.CC1S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM9_R->CCMR1.BIT_OCM.OC1M = 0b110;
							TIM9_R->CCER.BIT.CC1P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM9_R->CCMR1.BIT_OCM.OC1PE = TRUE;
						}
						else
						{
							TIM9_R->CCMR1.BIT_ICM.CC1S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM9_R->CCMR1.BIT_ICM.IC1PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM9_R->CCMR1.BIT_ICM.IC1F = LOC_strChannelConfigTemp.enmICFilter;
							TIM9_R->CCER.BIT.CC1P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM9_R->CCER.BIT.CC1NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					case TIM_CHANNEL2:
						TIM9_R->CCER.BIT.CC2E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM9_R->CCMR1.BIT_OCM.CC2S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM9_R->CCMR1.BIT_OCM.OC2M = 0b110;
							TIM9_R->CCER.BIT.CC2P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM9_R->CCMR1.BIT_OCM.OC2PE = TRUE;
						}
						else
						{
							TIM9_R->CCMR1.BIT_ICM.CC2S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM9_R->CCMR1.BIT_ICM.IC2PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM9_R->CCMR1.BIT_ICM.IC2F = LOC_strChannelConfigTemp.enmICFilter;
							TIM9_R->CCER.BIT.CC2P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM9_R->CCER.BIT.CC2NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					}
				}
			}
			else
			{
			}
		}
		break;
		case TIM_10:
		{
			TIM10_R->PSC.BIT.PSC = LOC_strTemp.u16Prescaler;
			TIM10_R->CR1.BIT.DIR = LOC_strTemp.enmTimDirection;

			if (TIM_INPUT_OUTPUT == LOC_strTemp.enmMode)
			{
				TIM_CHANNEL_CONFIG LOC_strChannelConfigTemp;
				if(TRUE == NUM_OF_CHANNELS_USED_TIM11)
				{
					LOC_strChannelConfigTemp = LOC_strTemp.aStrChannelConfig[0];
					switch (LOC_strChannelConfigTemp.enmTimChannel)
					{
					case TIM_CHANNEL1:
						TIM10_R->CCER.BIT.CC1E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM10_R->CCMR1.BIT_OCM.CC1S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM10_R->CCMR1.BIT_OCM.OC1M = 0b110;
							TIM10_R->CCER.BIT.CC1P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM10_R->CCMR1.BIT_OCM.OC1PE = TRUE;
						}
						else
						{
							TIM10_R->CCMR1.BIT_ICM.CC1S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM10_R->CCMR1.BIT_ICM.IC1PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM10_R->CCMR1.BIT_ICM.IC1F = LOC_strChannelConfigTemp.enmICFilter;
							TIM10_R->CCER.BIT.CC1P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM10_R->CCER.BIT.CC1NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					}
				}
			}
			else
			{
			}
		}
		break;
		case TIM_11:
		{
			TIM11_R->PSC.BIT.PSC = LOC_strTemp.u16Prescaler;
			TIM11_R->CR1.BIT.DIR = LOC_strTemp.enmTimDirection;

			if (TIM_INPUT_OUTPUT == LOC_strTemp.enmMode)
			{
				TIM_CHANNEL_CONFIG LOC_strChannelConfigTemp;
				if(TRUE == NUM_OF_CHANNELS_USED_TIM11)
				{
					LOC_strChannelConfigTemp = LOC_strTemp.aStrChannelConfig[0];
					switch (LOC_strChannelConfigTemp.enmTimChannel)
					{
					case TIM_CHANNEL1:
						TIM11_R->CCER.BIT.CC1E = FALSE;
						if (PWM_CHANNEL == LOC_strChannelConfigTemp.enmChannelMode)
						{
							TIM11_R->CCMR1.BIT_OCM.CC1S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM11_R->CCMR1.BIT_OCM.OC1M = 0b110;
							TIM11_R->CCER.BIT.CC1P = LOC_strChannelConfigTemp.enmPWMPolarity;
							TIM11_R->CCMR1.BIT_OCM.OC1PE = TRUE;
						}
						else
						{
							TIM11_R->CCMR1.BIT_ICM.CC1S = LOC_strChannelConfigTemp.enmChannelMode;
							TIM11_R->CCMR1.BIT_ICM.IC1PSC = LOC_strChannelConfigTemp.enmICPrescaler;
							TIM11_R->CCMR1.BIT_ICM.IC1F = LOC_strChannelConfigTemp.enmICFilter;
							TIM11_R->CCER.BIT.CC1P = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 0);
							TIM11_R->CCER.BIT.CC1NP = GET_BIT(LOC_strChannelConfigTemp.enmICPolarity, 1);
						}
						break;
					}
				}
			}
			else
			{
			}
		}
		break;
		default:
			break;
		} // end of switch
	}
}

void TIM_vidICStart(TIM_x Copy_enmTIM_x, TIM_CHANNEL Copy_enmChannel)
{
	switch (Copy_enmTIM_x)
	{
	case TIM_1:
	{
		TIM1_R->ARR.BIT.ARR = 0xFFFF;
		TIM1_R->CR1.BIT.CEN = FALSE;
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM1_R->CCER.BIT.CC1E = 1;
			break;
		case TIM_CHANNEL2:
			TIM1_R->CCER.BIT.CC2E = 1;
			break;
		case TIM_CHANNEL3:
			TIM1_R->CCER.BIT.CC3E = 1;
			break;
		case TIM_CHANNEL4:
			TIM1_R->CCER.BIT.CC4E = 1;
			break;
		}
		if (FALSE == TIM1_R->CR1.BIT.CEN)
		{
			TIM1_R->CR1.BIT.CEN = TRUE;
		}
	}
	break;
	case TIM_2:
	{
		TIM2_R->ARR.REGISTER = 0xFFFFFFFF;
		TIM2_R->CR1.BIT.CEN = FALSE;

		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM2_R->CCER.BIT.CC1E = 1;
			break;
		case TIM_CHANNEL2:
			TIM2_R->CCER.BIT.CC2E = 1;
			break;
		case TIM_CHANNEL3:
			TIM2_R->CCER.BIT.CC3E = 1;
			break;
		case TIM_CHANNEL4:
			TIM2_R->CCER.BIT.CC4E = 1;
			break;
		}
		if (FALSE == TIM2_R->CR1.BIT.CEN)
		{
			TIM2_R->CR1.BIT.CEN = TRUE;
		}
	}
	break;
	case TIM_3:
	{
		TIM3_R->ARR.BIT.ARR = 0xFFFF;
		TIM3_R->CR1.BIT.CEN = FALSE;

		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM3_R->CCER.BIT.CC1E = 1;
			break;
		case TIM_CHANNEL2:
			TIM3_R->CCER.BIT.CC2E = 1;
			break;
		case TIM_CHANNEL3:
			TIM3_R->CCER.BIT.CC3E = 1;
			break;
		case TIM_CHANNEL4:
			TIM3_R->CCER.BIT.CC4E = 1;
			break;
		}
		if (FALSE == TIM3_R->CR1.BIT.CEN)
		{
			TIM3_R->CR1.BIT.CEN = TRUE;
		}
	}
	break;
	case TIM_4:
	{
		TIM4_R->ARR.BIT.ARR = 0xFFFF;
		TIM4_R->CR1.BIT.CEN = FALSE;

		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM4_R->CCER.BIT.CC1E = 1;
			break;
		case TIM_CHANNEL2:
			TIM4_R->CCER.BIT.CC2E = 1;
			break;
		case TIM_CHANNEL3:
			TIM4_R->CCER.BIT.CC3E = 1;
			break;
		case TIM_CHANNEL4:
			TIM4_R->CCER.BIT.CC4E = 1;
			break;
		}
		if (FALSE == TIM4_R->CR1.BIT.CEN)
		{
			TIM4_R->CR1.BIT.CEN = TRUE;
		}
	}
	break;
	case TIM_5:
	{
		TIM5_R->ARR.REGISTER = 0xFFFFFFFF;
		TIM5_R->CR1.BIT.CEN = FALSE;

		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM5_R->CCER.BIT.CC1E = 1;
			break;
		case TIM_CHANNEL2:
			TIM5_R->CCER.BIT.CC2E = 1;
			break;
		case TIM_CHANNEL3:
			TIM5_R->CCER.BIT.CC3E = 1;
			break;
		case TIM_CHANNEL4:
			TIM5_R->CCER.BIT.CC4E = 1;
			break;
		}
		if (FALSE == TIM5_R->CR1.BIT.CEN)
		{
			TIM5_R->CR1.BIT.CEN = TRUE;
		}
	}
	break;
	case TIM_9:
	{
		TIM9_R->ARR.BIT.ARR = 0xFFFF;
		TIM9_R->CR1.BIT.CEN = FALSE;
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM9_R->CCER.BIT.CC1E = 1;
			break;
		case TIM_CHANNEL2:
			TIM9_R->CCER.BIT.CC2E = 1;
			break;
		}
		if (FALSE == TIM9_R->CR1.BIT.CEN)
		{
			TIM9_R->CR1.BIT.CEN = TRUE;
		}
	}
	break;
	case TIM_10:
	{
		TIM10_R->ARR.BIT.ARR = 0xFFFF;
		TIM10_R->CR1.BIT.CEN = FALSE;
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM10_R->CCER.BIT.CC1E = 1;
			break;
		}
		if (FALSE == TIM10_R->CR1.BIT.CEN)
		{
			TIM10_R->CR1.BIT.CEN = TRUE;
		}
	}
	break;
	case TIM_11:
	{
		TIM11_R->ARR.BIT.ARR = 0xFFFF;
		TIM11_R->CR1.BIT.CEN = FALSE;

		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM11_R->CCER.BIT.CC1E = 1;
			break;
		}

		if (FALSE == TIM11_R->CR1.BIT.CEN)
		{
			TIM11_R->CR1.BIT.CEN = TRUE;
		}
	}
	break;
	default:
		break;
	} // end of switch
}

void TIM_vidICStop(TIM_x Copy_enmTIM_x, TIM_CHANNEL Copy_enmChannel)
{
	switch (Copy_enmTIM_x)
	{
	case TIM_1:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM1_R->CCER.BIT.CC1E = 0;
			break;
		case TIM_CHANNEL2:
			TIM1_R->CCER.BIT.CC2E = 0;
			break;
		case TIM_CHANNEL3:
			TIM1_R->CCER.BIT.CC3E = 0;
			break;
		case TIM_CHANNEL4:
			TIM1_R->CCER.BIT.CC4E = 0;
			break;
		}
	}
	break;
	case TIM_2:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM2_R->CCER.BIT.CC1E = 0;
			break;
		case TIM_CHANNEL2:
			TIM2_R->CCER.BIT.CC2E = 0;
			break;
		case TIM_CHANNEL3:
			TIM2_R->CCER.BIT.CC3E = 0;
			break;
		case TIM_CHANNEL4:
			TIM2_R->CCER.BIT.CC4E = 0;
			break;
		}
	}
	break;
	case TIM_3:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM3_R->CCER.BIT.CC1E = 0;
			break;
		case TIM_CHANNEL2:
			TIM3_R->CCER.BIT.CC2E = 0;
			break;
		case TIM_CHANNEL3:
			TIM3_R->CCER.BIT.CC3E = 0;
			break;
		case TIM_CHANNEL4:
			TIM3_R->CCER.BIT.CC4E = 0;
			break;
		}
	}
	break;
	case TIM_4:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM4_R->CCER.BIT.CC1E = 0;
			break;
		case TIM_CHANNEL2:
			TIM4_R->CCER.BIT.CC2E = 0;
			break;
		case TIM_CHANNEL3:
			TIM4_R->CCER.BIT.CC3E = 0;
			break;
		case TIM_CHANNEL4:
			TIM4_R->CCER.BIT.CC4E = 0;
			break;
		}
	}
	break;
	case TIM_5:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM5_R->CCER.BIT.CC1E = 0;
			break;
		case TIM_CHANNEL2:
			TIM5_R->CCER.BIT.CC2E = 0;
			break;
		case TIM_CHANNEL3:
			TIM5_R->CCER.BIT.CC3E = 0;
			break;
		case TIM_CHANNEL4:
			TIM5_R->CCER.BIT.CC4E = 0;
			break;
		}
	}
	break;
	case TIM_9:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM9_R->CCER.BIT.CC1E = 0;
			break;
		case TIM_CHANNEL2:
			TIM9_R->CCER.BIT.CC2E = 0;
			break;
		}
	}
	break;
	case TIM_10:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM10_R->CCER.BIT.CC1E = 0;
			break;
		}
	}
	break;
	case TIM_11:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM11_R->CCER.BIT.CC1E = 0;
			break;
		}
	}
	break;
	default:
		break;
	} // end of switch
}

u32 TIM_u32ICGetCapturedValue(TIM_x Copy_enmTIM_x, TIM_CHANNEL Copy_enmChannel)
{
	u32 LOC_u32CapturedValue = 0;
	switch (Copy_enmTIM_x)
	{
	case TIM_1:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			while (FALSE == TIM1_R->SR.BIT.CC1IF);
			while (TRUE == TIM1_R->SR.BIT.CC1OF);
			LOC_u32CapturedValue = (u32)(TIM1_R->CCR1.BIT.CCR1);
			TIM1_R->SR.BIT.CC1IF = FALSE;
			TIM1_R->SR.BIT.CC1OF = FALSE;
			break;

		case TIM_CHANNEL2:
			while (FALSE == TIM1_R->SR.BIT.CC2IF);
			while (TRUE == TIM1_R->SR.BIT.CC2OF);
			LOC_u32CapturedValue = (u32)(TIM1_R->CCR2.BIT.CCR2);
			TIM1_R->SR.BIT.CC2IF = FALSE;
			TIM1_R->SR.BIT.CC2OF = FALSE;
			break;

		case TIM_CHANNEL3:
			while (FALSE == TIM1_R->SR.BIT.CC3IF);
			while (TRUE == TIM1_R->SR.BIT.CC3OF);
			LOC_u32CapturedValue = (u32)(TIM1_R->CCR3.BIT.CCR3);
			TIM1_R->SR.BIT.CC3IF = FALSE;
			TIM1_R->SR.BIT.CC3OF = FALSE;
			break;

		case TIM_CHANNEL4:
			while (FALSE == TIM1_R->SR.BIT.CC4IF);
			while (TRUE == TIM1_R->SR.BIT.CC4OF);
			LOC_u32CapturedValue = (u32)(TIM1_R->CCR4.BIT.CCR4);
			TIM1_R->SR.BIT.CC4IF = FALSE;
			TIM1_R->SR.BIT.CC4OF = FALSE;
			break;
		}
	}
	break;
	case TIM_2:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			while (FALSE == TIM2_R->SR.BIT.CC1IF);
			while (TRUE == TIM2_R->SR.BIT.CC1OF);
			LOC_u32CapturedValue = (u32)(TIM2_R->CCR1.REGISTER);
			TIM2_R->SR.BIT.CC1IF = FALSE;
			TIM2_R->SR.BIT.CC1OF = FALSE;
			break;

		case TIM_CHANNEL2:
			while (FALSE == TIM2_R->SR.BIT.CC2IF);
			while (TRUE == TIM2_R->SR.BIT.CC2OF);
			LOC_u32CapturedValue = (u32)(TIM2_R->CCR2.REGISTER);
			TIM2_R->SR.BIT.CC2IF = FALSE;
			TIM2_R->SR.BIT.CC2OF = FALSE;
			break;

		case TIM_CHANNEL3:
			while (FALSE == TIM2_R->SR.BIT.CC3IF);
			while (TRUE == TIM2_R->SR.BIT.CC3OF);
			LOC_u32CapturedValue = (u32)(TIM2_R->CCR3.REGISTER);
			TIM2_R->SR.BIT.CC3IF = FALSE;
			TIM2_R->SR.BIT.CC3OF = FALSE;
			break;

		case TIM_CHANNEL4:
			while (FALSE == TIM2_R->SR.BIT.CC4IF);
			while (TRUE == TIM2_R->SR.BIT.CC4OF);
			LOC_u32CapturedValue = (u32)(TIM2_R->CCR4.REGISTER);
			TIM2_R->SR.BIT.CC4IF = FALSE;
			TIM2_R->SR.BIT.CC4OF = FALSE;
			break;
		}
	}
	break;
	case TIM_3:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			while (FALSE == TIM3_R->SR.BIT.CC1IF);
			//while (TRUE == TIM3_R->SR.BIT.CC1OF);
			LOC_u32CapturedValue = (u32)(TIM3_R->CCR1.BIT.CCR1);
			TIM3_R->SR.BIT.CC1IF = FALSE;
			TIM3_R->SR.BIT.CC1OF = FALSE;
			break;

		case TIM_CHANNEL2:
			while (FALSE == TIM3_R->SR.BIT.CC2IF);
			//while (TRUE == TIM3_R->SR.BIT.CC2OF);
			LOC_u32CapturedValue = (u32)(TIM3_R->CCR2.BIT.CCR2);
			TIM3_R->SR.BIT.CC2IF = FALSE;
			TIM3_R->SR.BIT.CC2OF = FALSE;
			break;

		case TIM_CHANNEL3:
			while (FALSE == TIM3_R->SR.BIT.CC3IF);
			//while (TRUE == TIM3_R->SR.BIT.CC3OF);
			LOC_u32CapturedValue = (u32)(TIM3_R->CCR3.BIT.CCR3);
			TIM3_R->SR.BIT.CC3IF = FALSE;
			TIM3_R->SR.BIT.CC3OF = FALSE;
			break;

		case TIM_CHANNEL4:
			while (FALSE == TIM3_R->SR.BIT.CC4IF);
			//while (TRUE == TIM3_R->SR.BIT.CC4OF);
			LOC_u32CapturedValue = (u32)(TIM3_R->CCR4.BIT.CCR4);
			TIM3_R->SR.BIT.CC4IF = FALSE;
			TIM3_R->SR.BIT.CC4OF = FALSE;
			break;
		}
	}
	break;
	case TIM_4:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			while (FALSE == TIM4_R->SR.BIT.CC1IF);
			//while (TRUE == TIM4_R->SR.BIT.CC1OF);
			LOC_u32CapturedValue = (u32)(TIM4_R->CCR1.BIT.CCR1);
			TIM4_R->SR.BIT.CC1IF = FALSE;
			TIM4_R->SR.BIT.CC1OF = FALSE;
			break;

		case TIM_CHANNEL2:
			while (FALSE == TIM4_R->SR.BIT.CC2IF);
			//while (TRUE == TIM4_R->SR.BIT.CC2OF);
			LOC_u32CapturedValue = (u32)(TIM4_R->CCR2.BIT.CCR2);
			TIM4_R->SR.BIT.CC2IF = FALSE;
			TIM4_R->SR.BIT.CC2OF = FALSE;
			break;

		case TIM_CHANNEL3:
			while (FALSE == TIM4_R->SR.BIT.CC3IF);
			//while (TRUE == TIM4_R->SR.BIT.CC3OF);
			LOC_u32CapturedValue = (u32)(TIM4_R->CCR3.BIT.CCR3);
			TIM4_R->SR.BIT.CC3IF = FALSE;
			TIM4_R->SR.BIT.CC3OF = FALSE;
			break;

		case TIM_CHANNEL4:
			while (FALSE == TIM4_R->SR.BIT.CC4IF);
			//while (TRUE == TIM4_R->SR.BIT.CC4OF);
			LOC_u32CapturedValue = (u32)(TIM4_R->CCR4.BIT.CCR4);
			TIM4_R->SR.BIT.CC4IF = FALSE;
			TIM4_R->SR.BIT.CC4OF = FALSE;
			break;
		}
	}
	break;
	case TIM_5:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			while (FALSE == TIM5_R->SR.BIT.CC1IF);
			//while (TRUE == TIM5_R->SR.BIT.CC1OF);
			LOC_u32CapturedValue = (u32)(TIM5_R->CCR1.REGISTER);
			TIM5_R->SR.BIT.CC1IF = FALSE;
			TIM5_R->SR.BIT.CC1OF = FALSE;
			break;

		case TIM_CHANNEL2:
			while (FALSE == TIM5_R->SR.BIT.CC2IF);
			//while (TRUE == TIM5_R->SR.BIT.CC2OF);
			LOC_u32CapturedValue = (u32)(TIM5_R->CCR2.REGISTER);
			TIM5_R->SR.BIT.CC2IF = FALSE;
			TIM5_R->SR.BIT.CC2OF = FALSE;
			break;

		case TIM_CHANNEL3:
			while (FALSE == TIM5_R->SR.BIT.CC3IF);
			//while (TRUE == TIM5_R->SR.BIT.CC3OF);
			LOC_u32CapturedValue = (u32)(TIM5_R->CCR3.REGISTER);
			TIM5_R->SR.BIT.CC3IF = FALSE;
			TIM5_R->SR.BIT.CC3OF = FALSE;
			break;

		case TIM_CHANNEL4:
			while (FALSE == TIM5_R->SR.BIT.CC4IF);
			while (TRUE == TIM5_R->SR.BIT.CC4OF);
			LOC_u32CapturedValue = (u32)(TIM5_R->CCR4.REGISTER);
			TIM5_R->SR.BIT.CC4IF = FALSE;
			TIM5_R->SR.BIT.CC4OF = FALSE;
			break;
		}
	}
	break;
	case TIM_9:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			while (FALSE == TIM9_R->SR.BIT.CC1IF);
			while (TRUE == TIM9_R->SR.BIT.CC1OF);
			LOC_u32CapturedValue = (u32)(TIM9_R->CCR1.BIT.CCR1);
			TIM9_R->SR.BIT.CC1IF = FALSE;
			TIM9_R->SR.BIT.CC1OF = FALSE;
			break;

		case TIM_CHANNEL2:
			while (FALSE == TIM9_R->SR.BIT.CC2IF);
			while (TRUE == TIM9_R->SR.BIT.CC2OF);
			LOC_u32CapturedValue = (u32)(TIM9_R->CCR2.BIT.CCR2);
			TIM9_R->SR.BIT.CC2IF = FALSE;
			TIM9_R->SR.BIT.CC2OF = FALSE;
			break;
		}
	}
	break;
	case TIM_10:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			while (FALSE == TIM10_R->SR.BIT.CC1IF);
			while (TRUE == TIM10_R->SR.BIT.CC1OF);
			LOC_u32CapturedValue = (u32)(TIM10_R->CCR1.BIT.CCR1);
			TIM10_R->SR.BIT.CC1IF = FALSE;
			TIM10_R->SR.BIT.CC1OF = FALSE;
			break;
		}
	}
	break;
	case TIM_11:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			while (FALSE == TIM11_R->SR.BIT.CC1IF);
			while (TRUE == TIM11_R->SR.BIT.CC1OF);
			LOC_u32CapturedValue = (u32)(TIM11_R->CCR1.BIT.CCR1);
			TIM11_R->SR.BIT.CC1IF = FALSE;
			TIM11_R->SR.BIT.CC1OF = FALSE;
			break;
		}
	}
	break;
	default:
		break;
	} // end of switch
	return LOC_u32CapturedValue;
}

void TIM_vidDelayus(TIM_x Copy_enmTIM_x, u16 Copy_u16us)
{
	u16 LOC_u16Counter;
	u16 LOC_u16PSC;
	u32 LOC_u32ARR;
	f64 LOC_f64TIMxCLK;

	for (LOC_u16Counter = 0; LOC_u16Counter < NUM_OF_TIM_USED; LOC_u16Counter++)
	{
		if (Copy_enmTIM_x == GLOB_aStrTIM[LOC_u16Counter].enmTIM_x)
		{
			LOC_u16PSC = GLOB_aStrTIM[LOC_u16Counter].u16Prescaler;
			LOC_u16PSC++;
			break;
		}
	}
	LOC_f64TIMxCLK = ((f64)TIM_CLK_IN_MHZ) / ((f64)LOC_u16PSC);
	LOC_u32ARR = (u32)(LOC_f64TIMxCLK);
	switch (Copy_enmTIM_x)
	{
	case TIM_1:
	{
		TIM1_R->CNT.REGISTER = 0;

		TIM1_R->ARR.BIT.ARR = LOC_u32ARR;
		TIM1_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while (TIM1_R->SR.BIT.UIF == 0)
				;
			TIM1_R->SR.BIT.UIF = 0;
		}
		TIM1_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_2:
	{
		TIM2_R->CNT.REGISTER = 0;

		TIM2_R->ARR.REGISTER = LOC_u32ARR;
		TIM2_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while (TIM2_R->SR.BIT.UIF == 0)
				;
			TIM2_R->SR.BIT.UIF = 0;
		}
		TIM2_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_3:
	{
		TIM3_R->CNT.REGISTER = 0;

		TIM3_R->ARR.BIT.ARR = LOC_u32ARR;
		TIM3_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while (TIM3_R->SR.BIT.UIF == 0)
				;
			TIM3_R->SR.BIT.UIF = 0;
		}
		TIM3_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_4:
	{
		TIM4_R->CNT.REGISTER = 0;

		TIM4_R->ARR.BIT.ARR = LOC_u32ARR;
		TIM4_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while (TIM4_R->SR.BIT.UIF == 0)
				;
			TIM4_R->SR.BIT.UIF = 0;
		}
		TIM4_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_5:
	{
		TIM5_R->CNT.REGISTER = 0;

		TIM5_R->ARR.REGISTER = LOC_u32ARR;
		TIM5_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while (TIM5_R->SR.BIT.UIF == 0)
				;
			TIM5_R->SR.BIT.UIF = 0;
		}
		TIM5_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_9:
	{
		TIM9_R->CNT.REGISTER = 0;

		TIM9_R->ARR.BIT.ARR = LOC_u32ARR;
		TIM9_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while (TIM9_R->SR.BIT.UIF == 0)
				;
			TIM9_R->SR.BIT.UIF = 0;
		}
		TIM9_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_10:
	{
		TIM10_R->CNT.REGISTER = 0;

		TIM10_R->ARR.BIT.ARR = LOC_u32ARR;
		TIM10_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while (TIM10_R->SR.BIT.UIF == 0)
				;
			TIM10_R->SR.BIT.UIF = 0;
		}
		TIM10_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_11:
	{
		TIM11_R->CNT.REGISTER = 0;

		TIM11_R->ARR.BIT.ARR = LOC_u32ARR;
		TIM11_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while (TIM11_R->SR.BIT.UIF == 0)
				;
			TIM11_R->SR.BIT.UIF = 0;
		}
		TIM11_R->CR1.BIT.CEN = 0;
	}
	break;
	default:
		break;
	} // end of switch
}

void TIM_vidDelayms(TIM_x Copy_enmTIM_x, u16 Copy_u16ms)
{
	u16 LOC_u16Counter;
	u16 LOC_u16PSC;
	u32 LOC_u32ARR;
	f64 LOC_f64TIMxCLK;

	for (LOC_u16Counter = 0; LOC_u16Counter < NUM_OF_TIM_USED; LOC_u16Counter++)
	{
		if (Copy_enmTIM_x == GLOB_aStrTIM[LOC_u16Counter].enmTIM_x)
		{
			LOC_u16PSC = GLOB_aStrTIM[LOC_u16Counter].u16Prescaler;
			LOC_u16PSC++;
			break;
		}
	}

	LOC_f64TIMxCLK = ((f64)TIM_CLK_IN_MHZ) / ((f64)LOC_u16PSC);
	LOC_u32ARR = (u32)(LOC_f64TIMxCLK * 1000);

	switch (Copy_enmTIM_x)
	{
	case TIM_1:
	{
		TIM1_R->CNT.REGISTER = 0;

		TIM1_R->ARR.REGISTER = LOC_u32ARR;
		TIM1_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while (TIM1_R->SR.BIT.UIF == 0)
				;
			TIM1_R->SR.BIT.UIF = 0;
		}
		TIM1_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_2:
	{
		TIM2_R->CNT.REGISTER = 0;

		TIM2_R->ARR.REGISTER = LOC_u32ARR;
		TIM2_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while (TIM2_R->SR.BIT.UIF == 0)
				;
			TIM2_R->SR.BIT.UIF = 0;
		}
		TIM2_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_3:
	{
		TIM3_R->CNT.REGISTER = 0;

		TIM3_R->ARR.REGISTER = LOC_u32ARR;
		TIM3_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while (TIM3_R->SR.BIT.UIF == 0)
				;
			TIM3_R->SR.BIT.UIF = 0;
		}
		TIM3_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_4:
	{
		TIM4_R->CNT.REGISTER = 0;

		TIM4_R->ARR.REGISTER = LOC_u32ARR;
		TIM4_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while (TIM4_R->SR.BIT.UIF == 0)
				;
			TIM4_R->SR.BIT.UIF = 0;
		}
		TIM4_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_5:
	{
		TIM5_R->CNT.REGISTER = 0;

		TIM5_R->ARR.REGISTER = LOC_u32ARR;
		TIM5_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while (TIM5_R->SR.BIT.UIF == 0)
				;
			TIM5_R->SR.BIT.UIF = 0;
		}
		TIM5_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_9:
	{
		TIM9_R->CNT.REGISTER = 0;

		TIM9_R->ARR.REGISTER = LOC_u32ARR;
		TIM9_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while (TIM9_R->SR.BIT.UIF == 0)
				;
			TIM9_R->SR.BIT.UIF = 0;
		}
		TIM9_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_10:
	{
		TIM10_R->CNT.REGISTER = 0;

		TIM10_R->ARR.REGISTER = LOC_u32ARR;
		TIM10_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while (TIM10_R->SR.BIT.UIF == 0);
			TIM10_R->SR.BIT.UIF = 0;
		}
		TIM10_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_11:
	{
		TIM11_R->CNT.REGISTER = 0;

		TIM11_R->ARR.REGISTER = LOC_u32ARR;
		TIM11_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while (TIM11_R->SR.BIT.UIF == 0);
			TIM11_R->SR.BIT.UIF = 0;
		}
		TIM11_R->CR1.BIT.CEN = 0;
	}
	break;
	default:
		break;
	} // end of switch
}

void TIM_vidDelaySec(TIM_x Copy_enmTIM_x, u16 Copy_u16Sec)
{
	u16 LOC_u16Counter;
	u16 LOC_u16PSC;
	u32 LOC_u32ARR;
	f64 LOC_f64TIMxCLK;
	for (LOC_u16Counter = 0; LOC_u16Counter < NUM_OF_TIM_USED; LOC_u16Counter++)
	{
		if (Copy_enmTIM_x == GLOB_aStrTIM[LOC_u16Counter].enmTIM_x)
		{
			LOC_u16PSC = GLOB_aStrTIM[LOC_u16Counter].u16Prescaler;
			LOC_u16PSC++;
			break;
		}
	}

	LOC_f64TIMxCLK = ((f64)TIM_CLK_IN_MHZ) / ((f64)LOC_u16PSC);
	LOC_u32ARR = (u32)(LOC_f64TIMxCLK * 1000000);
	switch (Copy_enmTIM_x)
	{
	case TIM_1:
	{
		TIM1_R->CNT.REGISTER = 0;

		TIM1_R->ARR.REGISTER = LOC_u32ARR;
		TIM1_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while (TIM1_R->SR.BIT.UIF == 0)
				;
			TIM1_R->SR.BIT.UIF = 0;
		}
		TIM1_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_2:
	{
		TIM2_R->CNT.REGISTER = 0;

		TIM2_R->ARR.REGISTER = LOC_u32ARR;
		TIM2_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while (TIM2_R->SR.BIT.UIF == 0)
				;
			TIM2_R->SR.BIT.UIF = 0;
		}
		TIM2_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_3:
	{
		TIM3_R->CNT.REGISTER = 0;

		TIM3_R->ARR.BIT.ARR = LOC_u32ARR;
		// TIM3_R->ARR.REGISTER	= LOC_u32ARR;
		TIM3_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while (TIM3_R->SR.BIT.UIF == 0)
				;
			TIM3_R->SR.BIT.UIF = 0;
		}
		TIM3_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_4:
	{
		TIM4_R->CNT.REGISTER = 0;

		TIM4_R->ARR.REGISTER = LOC_u32ARR;
		TIM4_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while (TIM4_R->SR.BIT.UIF == 0)
				;
			TIM4_R->SR.BIT.UIF = 0;
		}
		TIM4_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_5:
	{
		TIM5_R->CNT.REGISTER = 0;

		TIM5_R->ARR.REGISTER = LOC_u32ARR;
		TIM5_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while (TIM5_R->SR.BIT.UIF == 0)
				;
			TIM5_R->SR.BIT.UIF = 0;
		}
		TIM5_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_9:
	{
		TIM9_R->CNT.REGISTER = 0;

		TIM9_R->ARR.REGISTER = LOC_u32ARR;
		TIM9_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while (TIM9_R->SR.BIT.UIF == 0)
				;
			TIM9_R->SR.BIT.UIF = 0;
		}
		TIM9_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_10:
	{
		TIM10_R->CNT.REGISTER = 0;

		TIM10_R->ARR.REGISTER = LOC_u32ARR;
		TIM10_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while (TIM10_R->SR.BIT.UIF == 0)
				;
			TIM10_R->SR.BIT.UIF = 0;
		}
		TIM10_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_11:
	{
		TIM11_R->CNT.REGISTER = 0;

		TIM11_R->ARR.REGISTER = LOC_u32ARR;
		TIM11_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while (TIM11_R->SR.BIT.UIF == 0);
			TIM11_R->SR.BIT.UIF = 0;
		}
		TIM11_R->CR1.BIT.CEN = 0;
	}
	break;
	default:
		break;
	} // end of switch
}

u32 TIM_u32GetPlusesCapturedDelayus(TIM_x Copy_enmTIM_x, TIM_CHANNEL Copy_enmChannel, u16 Copy_u16us)
{
	u16 LOC_u16Counter;
	u16 LOC_u16PSC;
	u32 LOC_u32ARR;
	f64 LOC_f64TIMxCLK;

    u32 LOC_u32PlusesCounter = 0;

	for (LOC_u16Counter = 0; LOC_u16Counter < NUM_OF_TIM_USED; LOC_u16Counter++)
	{
		if (Copy_enmTIM_x == GLOB_aStrTIM[LOC_u16Counter].enmTIM_x)
		{
			LOC_u16PSC = GLOB_aStrTIM[LOC_u16Counter].u16Prescaler;
			LOC_u16PSC++;
			break;
		}
	}
	LOC_f64TIMxCLK = ((f64)TIM_CLK_IN_MHZ) / ((f64)LOC_u16PSC);
	LOC_u32ARR = (u32)(LOC_f64TIMxCLK);
	switch (Copy_enmTIM_x)
	{
	case TIM_1:
	{
		TIM1_R->CNT.REGISTER = 0;

		TIM1_R->ARR.BIT.ARR = LOC_u32ARR;
		TIM1_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while (TIM1_R->SR.BIT.UIF == 0)
			{
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM1_R->SR.BIT.UIF = 0;
		}
		TIM1_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_2:
	{
		TIM2_R->CNT.REGISTER = 0;

		TIM2_R->ARR.REGISTER = LOC_u32ARR;
		TIM2_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while (TIM2_R->SR.BIT.UIF == 0)
            {
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM2_R->SR.BIT.UIF = 0;
		}
		TIM2_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_3:
	{
		TIM3_R->CNT.REGISTER = 0;

		TIM3_R->ARR.BIT.ARR = LOC_u32ARR;
		TIM3_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while (TIM3_R->SR.BIT.UIF == 0)
			{
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM3_R->SR.BIT.UIF = 0;
		}
		TIM3_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_4:
	{
		TIM4_R->CNT.REGISTER = 0;

		TIM4_R->ARR.BIT.ARR = LOC_u32ARR;
		TIM4_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while (TIM4_R->SR.BIT.UIF == 0)
			{
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM4_R->SR.BIT.UIF = 0;
		}
		TIM4_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_5:
	{
		TIM5_R->CNT.REGISTER = 0;

		TIM5_R->ARR.REGISTER = LOC_u32ARR;
		TIM5_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while (TIM5_R->SR.BIT.UIF == 0)
			{
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM5_R->SR.BIT.UIF = 0;
		}
		TIM5_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_9:
	{
		TIM9_R->CNT.REGISTER = 0;

		TIM9_R->ARR.BIT.ARR = LOC_u32ARR;
		TIM9_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while (TIM9_R->SR.BIT.UIF == 0)
			{
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM9_R->SR.BIT.UIF = 0;
		}
		TIM9_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_10:
	{
		TIM10_R->CNT.REGISTER = 0;

		TIM10_R->ARR.BIT.ARR = LOC_u32ARR;
		TIM10_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while (TIM10_R->SR.BIT.UIF == 0)
			{
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM10_R->SR.BIT.UIF = 0;
		}
		TIM10_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_11:
	{
		TIM11_R->CNT.REGISTER = 0;

		TIM11_R->ARR.BIT.ARR = LOC_u32ARR;
		TIM11_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while (TIM11_R->SR.BIT.UIF == 0)
			{
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM11_R->SR.BIT.UIF = 0;
		}
		TIM11_R->CR1.BIT.CEN = 0;
	}
	break;
	default:
		break;
	} // end of switch
    return LOC_u32PlusesCounter;
}

u32 TIM_u32GetPlusesCapturedDelayms(TIM_x Copy_enmTIM_x, TIM_CHANNEL Copy_enmChannel, u16 Copy_u16ms)
{
	u16 LOC_u16Counter;
	u16 LOC_u16PSC;
	u32 LOC_u32ARR;
	f64 LOC_f64TIMxCLK;

    u32 LOC_u32PlusesCounter;

	for (LOC_u16Counter = 0; LOC_u16Counter < NUM_OF_TIM_USED; LOC_u16Counter++)
	{
		if (Copy_enmTIM_x == GLOB_aStrTIM[LOC_u16Counter].enmTIM_x)
		{
			LOC_u16PSC = GLOB_aStrTIM[LOC_u16Counter].u16Prescaler;
			LOC_u16PSC++;
			break;
		}
	}

	LOC_f64TIMxCLK = ((f64)TIM_CLK_IN_MHZ) / ((f64)LOC_u16PSC);
	LOC_u32ARR = (u32)(LOC_f64TIMxCLK * 1000);

	switch (Copy_enmTIM_x)
	{
	case TIM_1:
	{
		TIM1_R->CNT.REGISTER = 0;

		TIM1_R->ARR.REGISTER = LOC_u32ARR;
		TIM1_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while (TIM1_R->SR.BIT.UIF == 0)
			{
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM1_R->SR.BIT.UIF = 0;
		}
		TIM1_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_2:
	{
		TIM2_R->CNT.REGISTER = 0;

		TIM2_R->ARR.REGISTER = LOC_u32ARR;
		TIM2_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while (TIM2_R->SR.BIT.UIF == 0)
			{
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM2_R->SR.BIT.UIF = 0;
		}
		TIM2_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_3:
	{
		TIM3_R->CNT.REGISTER = 0;

		TIM3_R->ARR.REGISTER = LOC_u32ARR;
		TIM3_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while (TIM3_R->SR.BIT.UIF == 0)
			{
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM3_R->SR.BIT.UIF = 0;
		}
		TIM3_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_4:
	{
		TIM4_R->CNT.REGISTER = 0;

		TIM4_R->ARR.REGISTER = LOC_u32ARR;
		TIM4_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while (TIM4_R->SR.BIT.UIF == 0)
			{
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM4_R->SR.BIT.UIF = 0;
		}
		TIM4_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_5:
	{
		TIM5_R->CNT.REGISTER = 0;

		TIM5_R->ARR.REGISTER = LOC_u32ARR;
		TIM5_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while (TIM5_R->SR.BIT.UIF == 0)
			{
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM5_R->SR.BIT.UIF = 0;
		}
		TIM5_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_9:
	{
		TIM9_R->CNT.REGISTER = 0;

		TIM9_R->ARR.REGISTER = LOC_u32ARR;
		TIM9_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while (TIM9_R->SR.BIT.UIF == 0)
			{
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM9_R->SR.BIT.UIF = 0;
		}
		TIM9_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_10:
	{
		TIM10_R->CNT.REGISTER = 0;

		TIM10_R->ARR.REGISTER = LOC_u32ARR;
		TIM10_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while (TIM10_R->SR.BIT.UIF == 0)
            {
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM10_R->SR.BIT.UIF = 0;
		}
		TIM10_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_11:
	{
		TIM11_R->CNT.REGISTER = 0;

		TIM11_R->ARR.REGISTER = LOC_u32ARR;
		TIM11_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while (TIM11_R->SR.BIT.UIF == 0)
            {
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM11_R->SR.BIT.UIF = 0;
		}
		TIM11_R->CR1.BIT.CEN = 0;
	}
	break;
	default:
		break;
	} // end of switch
    return LOC_u32PlusesCounter;
}

u32 TIM_u32GetPlusesCapturedDelaySec(TIM_x Copy_enmTIM_x, TIM_CHANNEL Copy_enmChannel, u16 Copy_u16Sec)
{
	u16 LOC_u16Counter;
	u16 LOC_u16PSC;
	u32 LOC_u32ARR;
	f64 LOC_f64TIMxCLK;

    u32 LOC_u32PlusesCounter;

	for (LOC_u16Counter = 0; LOC_u16Counter < NUM_OF_TIM_USED; LOC_u16Counter++)
	{
		if (Copy_enmTIM_x == GLOB_aStrTIM[LOC_u16Counter].enmTIM_x)
		{
			LOC_u16PSC = GLOB_aStrTIM[LOC_u16Counter].u16Prescaler;
			LOC_u16PSC++;
			break;
		}
	}

	LOC_f64TIMxCLK = ((f64)TIM_CLK_IN_MHZ) / ((f64)LOC_u16PSC);
	LOC_u32ARR = (u32)(LOC_f64TIMxCLK * 1000000);
	switch (Copy_enmTIM_x)
	{
	case TIM_1:
	{
		TIM1_R->CNT.REGISTER = 0;

		TIM1_R->ARR.REGISTER = LOC_u32ARR;
		TIM1_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while (TIM1_R->SR.BIT.UIF == 0)
			{
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM1_R->SR.BIT.UIF = 0;
		}
		TIM1_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_2:
	{
		TIM2_R->CNT.REGISTER = 0;

		TIM2_R->ARR.REGISTER = LOC_u32ARR;
		TIM2_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while (TIM2_R->SR.BIT.UIF == 0)
			{
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM2_R->SR.BIT.UIF = 0;
		}
		TIM2_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_3:
	{
		TIM3_R->CNT.REGISTER = 0;

		TIM3_R->ARR.BIT.ARR = LOC_u32ARR;
		// TIM3_R->ARR.REGISTER	= LOC_u32ARR;
		TIM3_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while (TIM3_R->SR.BIT.UIF == 0)
			{
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM3_R->SR.BIT.UIF = 0;
		}
		TIM3_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_4:
	{
		TIM4_R->CNT.REGISTER = 0;

		TIM4_R->ARR.REGISTER = LOC_u32ARR;
		TIM4_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while (TIM4_R->SR.BIT.UIF == 0)
			{
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM4_R->SR.BIT.UIF = 0;
		}
		TIM4_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_5:
	{
		TIM5_R->CNT.REGISTER = 0;

		TIM5_R->ARR.REGISTER = LOC_u32ARR;
		TIM5_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while (TIM5_R->SR.BIT.UIF == 0)
			{
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM5_R->SR.BIT.UIF = 0;
		}
		TIM5_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_9:
	{
		TIM9_R->CNT.REGISTER = 0;

		TIM9_R->ARR.REGISTER = LOC_u32ARR;
		TIM9_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while (TIM9_R->SR.BIT.UIF == 0)
			{
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM9_R->SR.BIT.UIF = 0;
		}
		TIM9_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_10:
	{
		TIM10_R->CNT.REGISTER = 0;

		TIM10_R->ARR.REGISTER = LOC_u32ARR;
		TIM10_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while (TIM10_R->SR.BIT.UIF == 0)
			{
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM10_R->SR.BIT.UIF = 0;
		}
		TIM10_R->CR1.BIT.CEN = 0;
	}
	break;
	case TIM_11:
	{
		TIM11_R->CNT.REGISTER = 0;

		TIM11_R->ARR.REGISTER = LOC_u32ARR;
		TIM11_R->CR1.BIT.CEN = 1;
		for (LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while (TIM11_R->SR.BIT.UIF == 0)
            {
                TIM_u32ICGetCapturedValue(Copy_enmTIM_x, Copy_enmChannel);
                LOC_u32PlusesCounter++;
            }
			TIM11_R->SR.BIT.UIF = 0;
		}
		TIM11_R->CR1.BIT.CEN = 0;
	}
	break;
	default:
		break;
	} // end of switch
    return LOC_u32PlusesCounter;
}

void TIM_vidPWMStart(TIM_x Copy_enmTIM_x, TIM_CHANNEL Copy_enmChannel, f32 Copy_f32SignalFreqInHz, PWM_DUTY_CYCLE_PER Copy_enmDutyCyclePer)
{
	u8 	LOC_u8Counter;
	u32 LOC_u32ArrValue = 0;
	f32 LOC_f32TimerFreq = 0;
	u16 LOC_u16TimerPrescaler = 0;
	u32 LOC_u32CCRxValue = 0;

	for(LOC_u8Counter = 0; LOC_u8Counter < NUM_OF_TIM_USED; LOC_u8Counter++)
	{
		if(Copy_enmTIM_x == GLOB_aStrTIM[LOC_u8Counter].enmTIM_x)
		{
			LOC_u16TimerPrescaler = GLOB_aStrTIM[LOC_u8Counter].u16Prescaler;
			LOC_u16TimerPrescaler++;
			break;
		}
		else{}
	}

	LOC_f32TimerFreq =(((f32)TIM_CLK_IN_MHZ)*(1000000.0/((f32)LOC_u16TimerPrescaler)));
	LOC_u32ArrValue = (u32)(LOC_f32TimerFreq/Copy_f32SignalFreqInHz);
	if(PWM_12_PERCENTAGE == Copy_enmDutyCyclePer)
	{
		LOC_u32CCRxValue = (u32)(((f32)LOC_u32ArrValue)*(((f32)12.5)/100.0));

	}
	else
	{
		LOC_u32CCRxValue = (u32)(((f32)LOC_u32ArrValue)*(((f32)Copy_enmDutyCyclePer)/100.0));
	}

	switch (Copy_enmTIM_x)
	{
	case TIM_1:
	{
		TIM1_R->ARR.BIT.ARR = LOC_u32ArrValue;
		TIM1_R->CR1.BIT.CEN = FALSE;
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM1_R->CCR1.BIT.CCR1 = LOC_u32CCRxValue;
			TIM1_R->CCER.BIT.CC1E = 1;
			break;
		case TIM_CHANNEL2:
			TIM1_R->CCR2.BIT.CCR2 = LOC_u32CCRxValue;
			TIM1_R->CCER.BIT.CC2E = 1;
			break;
		case TIM_CHANNEL3:
			TIM1_R->CCR3.BIT.CCR3 = LOC_u32CCRxValue;
			TIM1_R->CCER.BIT.CC3E = 1;
			break;
		case TIM_CHANNEL4:
			TIM1_R->CCR4.BIT.CCR4 = LOC_u32CCRxValue;
			TIM1_R->CCER.BIT.CC4E = 1;
			break;
		}
		if (FALSE == TIM1_R->CR1.BIT.CEN)
		{
			TIM1_R->CR1.BIT.CEN = TRUE;
		}
	}
	break;
	case TIM_2:
	{
		TIM2_R->ARR.REGISTER = LOC_u32ArrValue;
		TIM2_R->CR1.BIT.CEN = FALSE;

		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM2_R->CCR1.REGISTER = LOC_u32CCRxValue;
			TIM2_R->CCER.BIT.CC1E = 1;
			break;
		case TIM_CHANNEL2:
			TIM2_R->CCR2.REGISTER = LOC_u32CCRxValue;
			TIM2_R->CCER.BIT.CC2E = 1;
			break;
		case TIM_CHANNEL3:
			TIM2_R->CCR3.REGISTER = LOC_u32CCRxValue;
			TIM2_R->CCER.BIT.CC3E = 1;
			break;
		case TIM_CHANNEL4:
			TIM2_R->CCR4.REGISTER = LOC_u32CCRxValue;
			TIM2_R->CCER.BIT.CC4E = 1;
			break;
		}
		if (FALSE == TIM2_R->CR1.BIT.CEN)
		{
			TIM2_R->CR1.BIT.CEN = TRUE;
		}
	}
	break;
	case TIM_3:
	{
		TIM3_R->ARR.BIT.ARR = LOC_u32ArrValue;
		TIM3_R->CR1.BIT.CEN = FALSE;

		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM3_R->CCR1.BIT.CCR1 = LOC_u32CCRxValue;
			TIM3_R->CCER.BIT.CC1E = 1;
			break;
		case TIM_CHANNEL2:
			TIM3_R->CCR2.BIT.CCR2 = LOC_u32CCRxValue;
			TIM3_R->CCER.BIT.CC2E = 1;
			break;
		case TIM_CHANNEL3:
			TIM3_R->CCR3.BIT.CCR3 = LOC_u32CCRxValue;
			TIM3_R->CCER.BIT.CC3E = 1;
			break;
		case TIM_CHANNEL4:
			TIM3_R->CCR4.BIT.CCR4 = LOC_u32CCRxValue;
			TIM3_R->CCER.BIT.CC4E = 1;
			break;
		}
		if (FALSE == TIM3_R->CR1.BIT.CEN)
		{
			TIM3_R->CR1.BIT.CEN = TRUE;
		}
	}
	break;
	case TIM_4:
	{
		TIM4_R->ARR.BIT.ARR = LOC_u32ArrValue;
		TIM4_R->CR1.BIT.CEN = FALSE;

		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM4_R->CCR1.BIT.CCR1 = LOC_u32CCRxValue;
			TIM4_R->CCER.BIT.CC1E = 1;
			break;
		case TIM_CHANNEL2:
			TIM4_R->CCR2.BIT.CCR2 = LOC_u32CCRxValue;
			TIM4_R->CCER.BIT.CC2E = 1;
			break;
		case TIM_CHANNEL3:
			TIM4_R->CCR3.BIT.CCR3 = LOC_u32CCRxValue;
			TIM4_R->CCER.BIT.CC3E = 1;
			break;
		case TIM_CHANNEL4:
			TIM4_R->CCR4.BIT.CCR4 = LOC_u32CCRxValue;
			TIM4_R->CCER.BIT.CC4E = 1;
			break;
		}
		if (FALSE == TIM4_R->CR1.BIT.CEN)
		{
			TIM4_R->CR1.BIT.CEN = TRUE;
		}
	}
	break;
	case TIM_5:
	{
		TIM5_R->ARR.REGISTER = LOC_u32ArrValue;
		TIM5_R->CR1.BIT.CEN = FALSE;

		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM5_R->CCR1.REGISTER = LOC_u32CCRxValue;
			TIM5_R->CCER.BIT.CC1E = 1;
			break;
		case TIM_CHANNEL2:
			TIM5_R->CCR2.REGISTER = LOC_u32CCRxValue;
			TIM5_R->CCER.BIT.CC2E = 1;
			break;
		case TIM_CHANNEL3:
			TIM5_R->CCR3.REGISTER = LOC_u32CCRxValue;
			TIM5_R->CCER.BIT.CC3E = 1;
			break;
		case TIM_CHANNEL4:
			TIM5_R->CCR4.REGISTER = LOC_u32CCRxValue;
			TIM5_R->CCER.BIT.CC4E = 1;
			break;
		}
		if (FALSE == TIM5_R->CR1.BIT.CEN)
		{
			TIM5_R->CR1.BIT.CEN = TRUE;
		}
	}
	break;
	case TIM_9:
	{
		TIM9_R->ARR.BIT.ARR = LOC_u32ArrValue;
		TIM9_R->CR1.BIT.CEN = FALSE;
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM9_R->CCR1.BIT.CCR1 = LOC_u32CCRxValue;
			TIM9_R->CCER.BIT.CC1E = 1;
			break;
		case TIM_CHANNEL2:
			TIM9_R->CCR2.BIT.CCR2 = LOC_u32CCRxValue;
			TIM9_R->CCER.BIT.CC2E = 1;
			break;
		}
		if (FALSE == TIM9_R->CR1.BIT.CEN)
		{
			TIM9_R->CR1.BIT.CEN = TRUE;
		}
	}
	break;
	case TIM_10:
	{
		TIM10_R->ARR.BIT.ARR = LOC_u32ArrValue;
		TIM10_R->CR1.BIT.CEN = FALSE;
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM10_R->CCR1.BIT.CCR1 = LOC_u32CCRxValue;
			TIM10_R->CCER.BIT.CC1E = 1;
			break;
		}
		if (FALSE == TIM10_R->CR1.BIT.CEN)
		{
			TIM10_R->CR1.BIT.CEN = TRUE;
		}
	}
	break;
	case TIM_11:
	{
		TIM11_R->ARR.BIT.ARR = LOC_u32ArrValue;
		TIM11_R->CR1.BIT.CEN = FALSE;

		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM11_R->CCR1.BIT.CCR1 = LOC_u32CCRxValue;
			TIM11_R->CCER.BIT.CC1E = 1;
			break;
		}

		if (FALSE == TIM11_R->CR1.BIT.CEN)
		{
			TIM11_R->CR1.BIT.CEN = TRUE;
		}
	}
	break;
	default:
		break;
	} // end of switch
}

void TIM_vidPWMStop(TIM_x Copy_enmTIM_x, TIM_CHANNEL Copy_enmChannel)
{
	switch (Copy_enmTIM_x)
	{
	case TIM_1:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM1_R->CCER.BIT.CC1E = 0;
			break;
		case TIM_CHANNEL2:
			TIM1_R->CCER.BIT.CC2E = 0;
			break;
		case TIM_CHANNEL3:
			TIM1_R->CCER.BIT.CC3E = 0;
			break;
		case TIM_CHANNEL4:
			TIM1_R->CCER.BIT.CC4E = 0;
			break;
		}
	}
	break;
	case TIM_2:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM2_R->CCER.BIT.CC1E = 0;
			break;
		case TIM_CHANNEL2:
			TIM2_R->CCER.BIT.CC2E = 0;
			break;
		case TIM_CHANNEL3:
			TIM2_R->CCER.BIT.CC3E = 0;
			break;
		case TIM_CHANNEL4:
			TIM2_R->CCER.BIT.CC4E = 0;
			break;
		}
	}
	break;
	case TIM_3:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM3_R->CCER.BIT.CC1E = 0;
			break;
		case TIM_CHANNEL2:
			TIM3_R->CCER.BIT.CC2E = 0;
			break;
		case TIM_CHANNEL3:
			TIM3_R->CCER.BIT.CC3E = 0;
			break;
		case TIM_CHANNEL4:
			TIM3_R->CCER.BIT.CC4E = 0;
			break;
		}
	}
	break;
	case TIM_4:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM4_R->CCER.BIT.CC1E = 0;
			break;
		case TIM_CHANNEL2:
			TIM4_R->CCER.BIT.CC2E = 0;
			break;
		case TIM_CHANNEL3:
			TIM4_R->CCER.BIT.CC3E = 0;
			break;
		case TIM_CHANNEL4:
			TIM4_R->CCER.BIT.CC4E = 0;
			break;
		}
	}
	break;
	case TIM_5:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM5_R->CCER.BIT.CC1E = 0;
			break;
		case TIM_CHANNEL2:
			TIM5_R->CCER.BIT.CC2E = 0;
			break;
		case TIM_CHANNEL3:
			TIM5_R->CCER.BIT.CC3E = 0;
			break;
		case TIM_CHANNEL4:
			TIM5_R->CCER.BIT.CC4E = 0;
			break;
		}
	}
	break;
	case TIM_9:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM9_R->CCER.BIT.CC1E = 0;
			break;
		case TIM_CHANNEL2:
			TIM9_R->CCER.BIT.CC2E = 0;
			break;
		}
	}
	break;
	case TIM_10:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM10_R->CCER.BIT.CC1E = 0;
			break;
		}
	}
	break;
	case TIM_11:
	{
		switch (Copy_enmChannel)
		{
		case TIM_CHANNEL1:
			TIM11_R->CCER.BIT.CC1E = 0;
			break;
		}
	}
	break;
	default:
		break;
	} // end of switch
}
