/*
 * TIMER_program.c
 *
 *  Created on: Oct 13, 2022
 *      Author: Hosam
 */
#include "../../01- LIB/03- ERROR_STATUS/ERROR_STATUS.h"
#include "../../01- LIB/01- TYPES/STD_TYPES.h"
#include "../../01- LIB/02- BIT_MATH/BIT_MATH.h"

//#include "STD_TYPES.h"
//#include "BIT_MATH.h"

#include "TIMER_interface.h"
#include "TIMER_config.h"
#include "TIMER_private.h"

//static u32 GLOB_u32CRRx;

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

void TIM_vidInit(TIM_CONFIG *Copy_ptrStrTIM)
{
	u8 LOC_u8Counter;
	TIM_CONFIG LOC_strTemp;
	for(LOC_u8Counter = 0; LOC_u8Counter < NUM_OF_TIM_USED; LOC_u8Counter++)
	{
		LOC_strTemp 						= Copy_ptrStrTIM[LOC_u8Counter];
		switch(LOC_strTemp.enuTIM_x)
		{
		case TIM_1 :
		{
			TIM1_R->PSC.BIT.PSC = LOC_strTemp.u16Prescaler;
			TIM1_R->CR1.BIT.DIR = LOC_strTemp.enumTimDirection;
		}
		break;
		case TIM_2 :
		{
			TIM2_R->PSC.BIT.PSC = LOC_strTemp.u16Prescaler;
			TIM2_R->CR1.BIT.DIR = LOC_strTemp.enumTimDirection;
		}
		break;
		case TIM_3 :
		{
			TIM3_R->PSC.BIT.PSC = LOC_strTemp.u16Prescaler;
			TIM3_R->CR1.BIT.DIR = LOC_strTemp.enumTimDirection;
		}
		break;
		case TIM_4 :
		{
			TIM4_R->PSC.BIT.PSC = LOC_strTemp.u16Prescaler;
			TIM4_R->CR1.BIT.DIR = LOC_strTemp.enumTimDirection;
		}
		break;
		case TIM_5 :
		{
			TIM5_R->PSC.BIT.PSC = LOC_strTemp.u16Prescaler;
			TIM5_R->CR1.BIT.DIR = LOC_strTemp.enumTimDirection;
		}
		break;
		case TIM_9 :
		{
			TIM9_R->PSC.BIT.PSC = LOC_strTemp.u16Prescaler;
			TIM9_R->CR1.BIT.DIR = LOC_strTemp.enumTimDirection;
		}
		break;
		case TIM_10 :
		{
			TIM10_R->PSC.BIT.PSC = LOC_strTemp.u16Prescaler;
			TIM10_R->CR1.BIT.DIR = LOC_strTemp.enumTimDirection;
		}
		break;
		case TIM_11 :
		{
			TIM11_R->PSC.BIT.PSC = LOC_strTemp.u16Prescaler;
			TIM11_R->CR1.BIT.DIR = LOC_strTemp.enumTimDirection;
		}
		break;
		default :
			break;
		}// end of switch
	}
}

void TIM_vidDelayus(TIM_x Copy_enuTIM_x, u16 Copy_u16us)
{
	u16 LOC_u16Counter;
	u16 LOC_u16PSC;
	u32 LOC_u32ARR ;
	f64 LOC_f64TIMxCLK;
	for(LOC_u16Counter = 0; LOC_u16Counter < NUM_OF_TIM_USED; LOC_u16Counter++)
	{
		if(Copy_enuTIM_x == GLOB_ptrStrTIM[LOC_u16Counter].enuTIM_x)
		{
			LOC_u16PSC		= GLOB_ptrStrTIM[LOC_u16Counter].u16Prescaler;
		}
	}
	if(LOC_u16PSC == 0)
	{
		LOC_u16PSC = 1;
	}
	LOC_f64TIMxCLK	= ((f64)TIM_CLK_IN_MHZ) / ((f64)LOC_u16PSC);
	LOC_u32ARR 		= (u32)(LOC_f64TIMxCLK);
	switch(Copy_enuTIM_x)
	{
	case TIM_1 :
	{
		TIM1_R->ARR.BIT.ARR	= LOC_u32ARR;
		TIM1_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while(TIM1_R->SR.BIT.UIF == 0);
			TIM1_R->SR.BIT.UIF 	= 0;
		}
		TIM1_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_2 :
	{
		TIM2_R->ARR.REGISTER	= LOC_u32ARR;
		TIM2_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while(TIM2_R->SR.BIT.UIF == 0);
			TIM2_R->SR.BIT.UIF 	= 0;
		}
		TIM2_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_3 :
	{
		TIM3_R->ARR.BIT.ARR		= LOC_u32ARR;
		TIM3_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while(TIM3_R->SR.BIT.UIF == 0);
			TIM3_R->SR.BIT.UIF 	= 0;
		}
		TIM3_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_4 :
	{
		TIM4_R->ARR.BIT.ARR		= LOC_u32ARR;
		TIM4_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while(TIM4_R->SR.BIT.UIF == 0);
			TIM4_R->SR.BIT.UIF 	= 0;
		}
		TIM4_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_5 :
	{
		TIM5_R->ARR.REGISTER	= LOC_u32ARR;
		TIM5_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while(TIM5_R->SR.BIT.UIF == 0);
			TIM5_R->SR.BIT.UIF 	= 0;
		}
		TIM5_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_9 :
	{
		TIM9_R->ARR.BIT.ARR		= LOC_u32ARR;
		TIM9_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while(TIM9_R->SR.BIT.UIF == 0);
			TIM9_R->SR.BIT.UIF 	= 0;
		}
		TIM9_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_10 :
	{
		TIM10_R->ARR.BIT.ARR		= LOC_u32ARR;
		TIM10_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while(TIM10_R->SR.BIT.UIF == 0);
			TIM10_R->SR.BIT.UIF 	= 0;
		}
		TIM10_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_11 :
	{
		TIM11_R->ARR.BIT.ARR		= LOC_u32ARR;
		TIM11_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16us; LOC_u16Counter++)
		{
			while(TIM11_R->SR.BIT.UIF == 0);
			TIM11_R->SR.BIT.UIF 	= 0;
		}
		TIM11_R->CR1.BIT.CEN		= 0;
	}
	break;
	default :
		break;
	}// end of switch
}

void TIM_vidDelayms(TIM_x Copy_enuTIM_x, u16 Copy_u16ms)
{
	u16 LOC_u16Counter;
	u16 LOC_u16PSC;
	u32 LOC_u32ARR ;
	f64 LOC_f64TIMxCLK;

	for(LOC_u16Counter = 0; LOC_u16Counter < NUM_OF_TIM_USED; LOC_u16Counter++)
	{
		if(Copy_enuTIM_x == GLOB_ptrStrTIM[LOC_u16Counter].enuTIM_x)
		{
			LOC_u16PSC		= GLOB_ptrStrTIM[LOC_u16Counter].u16Prescaler;
		}
	}
	if(LOC_u16PSC == 0)
	{
		LOC_u16PSC = 1;
	}
	LOC_f64TIMxCLK	= ((f64)TIM_CLK_IN_MHZ) / ((f64)LOC_u16PSC);
	LOC_u32ARR 		= (u32)(LOC_f64TIMxCLK*1000);

	switch(Copy_enuTIM_x)
	{
	case TIM_1 :
	{
		TIM1_R->ARR.REGISTER	= LOC_u32ARR;
		TIM1_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while(TIM1_R->SR.BIT.UIF == 0);
			TIM1_R->SR.BIT.UIF 	= 0;
		}
		TIM1_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_2 :
	{
		TIM2_R->ARR.REGISTER	= LOC_u32ARR;
		TIM2_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while(TIM2_R->SR.BIT.UIF == 0);
			TIM2_R->SR.BIT.UIF 	= 0;
		}
		TIM2_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_3 :
	{
		TIM3_R->ARR.REGISTER	= LOC_u32ARR;
		TIM3_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while(TIM3_R->SR.BIT.UIF == 0);
			TIM3_R->SR.BIT.UIF 	= 0;
		}
		TIM3_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_4 :
	{
		TIM4_R->ARR.REGISTER	= LOC_u32ARR;
		TIM4_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while(TIM4_R->SR.BIT.UIF == 0);
			TIM4_R->SR.BIT.UIF 	= 0;
		}
		TIM4_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_5 :
	{
		TIM5_R->ARR.REGISTER	= LOC_u32ARR;
		TIM5_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while(TIM5_R->SR.BIT.UIF == 0);
			TIM5_R->SR.BIT.UIF 	= 0;
		}
		TIM5_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_9 :
	{
		TIM9_R->ARR.REGISTER	= LOC_u32ARR;
		TIM9_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while(TIM9_R->SR.BIT.UIF == 0);
			TIM9_R->SR.BIT.UIF 	= 0;
		}
		TIM9_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_10 :
	{
		TIM10_R->ARR.REGISTER	= LOC_u32ARR;
		TIM10_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while(TIM10_R->SR.BIT.UIF == 0);
			TIM10_R->SR.BIT.UIF 	= 0;
		}
		TIM10_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_11 :
	{
		TIM11_R->ARR.REGISTER	= LOC_u32ARR;
		TIM11_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16ms; LOC_u16Counter++)
		{
			while(TIM11_R->SR.BIT.UIF == 0);
			TIM11_R->SR.BIT.UIF 	= 0;
		}
		TIM11_R->CR1.BIT.CEN		= 0;
	}
	break;
	default :
		break;
	}// end of switch
}

void TIM_vidDelaySec(TIM_x Copy_enuTIM_x, u16 Copy_u16Sec)
{
	u16 LOC_u16Counter;
	u16 LOC_u16PSC;
	u32 LOC_u32ARR ;
	f64 LOC_f64TIMxCLK;
	for(LOC_u16Counter = 0; LOC_u16Counter < NUM_OF_TIM_USED; LOC_u16Counter++)
	{
		if(Copy_enuTIM_x == GLOB_ptrStrTIM[LOC_u16Counter].enuTIM_x)
		{
			LOC_u16PSC		= GLOB_ptrStrTIM[LOC_u16Counter].u16Prescaler;
		}
	}
	if(LOC_u16PSC == 0)
	{
		LOC_u16PSC = 1;
	}
	LOC_f64TIMxCLK	= ((f64)TIM_CLK_IN_MHZ) / ((f64)LOC_u16PSC);
	LOC_u32ARR 		= (u32)(LOC_f64TIMxCLK*1000000);
	switch(Copy_enuTIM_x)
	{
	case TIM_1 :
	{
		TIM1_R->ARR.REGISTER	= LOC_u32ARR;
		TIM1_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while(TIM1_R->SR.BIT.UIF == 0);
			TIM1_R->SR.BIT.UIF 	= 0;
		}
		TIM1_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_2 :
	{
		TIM2_R->ARR.REGISTER	= LOC_u32ARR;
		TIM2_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while(TIM2_R->SR.BIT.UIF == 0);
			TIM2_R->SR.BIT.UIF 	= 0;
		}
		TIM2_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_3 :
	{
		TIM3_R->ARR.REGISTER	= LOC_u32ARR;
		TIM3_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while(TIM3_R->SR.BIT.UIF == 0);
			TIM3_R->SR.BIT.UIF 	= 0;
		}
		TIM3_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_4 :
	{
		TIM4_R->ARR.REGISTER	= LOC_u32ARR;
		TIM4_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while(TIM4_R->SR.BIT.UIF == 0);
			TIM4_R->SR.BIT.UIF 	= 0;
		}
		TIM4_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_5 :
	{
		TIM5_R->ARR.REGISTER	= LOC_u32ARR;
		TIM5_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while(TIM5_R->SR.BIT.UIF == 0);
			TIM5_R->SR.BIT.UIF 	= 0;
		}
		TIM5_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_9 :
	{
		TIM9_R->ARR.REGISTER	= LOC_u32ARR;
		TIM9_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while(TIM9_R->SR.BIT.UIF == 0);
			TIM9_R->SR.BIT.UIF 	= 0;
		}
		TIM9_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_10 :
	{
		TIM10_R->ARR.REGISTER	= LOC_u32ARR;
		TIM10_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while(TIM10_R->SR.BIT.UIF == 0);
			TIM10_R->SR.BIT.UIF 	= 0;
		}
		TIM10_R->CR1.BIT.CEN		= 0;
	}
	break;
	case TIM_11 :
	{
		TIM11_R->ARR.REGISTER	= LOC_u32ARR;
		TIM11_R->CR1.BIT.CEN		= 1;
		for(LOC_u16Counter = 0; LOC_u16Counter < Copy_u16Sec; LOC_u16Counter++)
		{
			while(TIM11_R->SR.BIT.UIF == 0);
			TIM11_R->SR.BIT.UIF 	= 0;
		}
		TIM11_R->CR1.BIT.CEN		= 0;
	}
	break;
	default :
		break;
	}// end of switch
}

/*static void TIM_vidCalcCRRxValue(u32 Copy_u32Freq, u16 Copy_u16Prescaler)
{
	GLOB_u32CRRx = ( (TIM_CLK_IN_MHZ * 1000000) / (Copy_u32Freq * 2 * Copy_u16Prescaler) );
}


void TIM_vidOCToggleEnable(TIM_CONFIG Copy_strTIMx, TIM_CHANNEL Copy_enumChannel, u32 Copy_u32SignalFreq)
{
	TIM_vidCalcCRRxValue(Copy_u32SignalFreq, Copy_strTIMx.u16Prescaler);
	Copy_strTIMx.ptrStrTIMx->ARR.REGISTER			= 0xFFFFFFFF;
	switch(Copy_enumChannel)
	{
	case CHANNEL1:
		Copy_strTIMx.ptrStrTIMx->CCR1.REGISTER 		= GLOB_u32CRRx;
		Copy_strTIMx.ptrStrTIMx->CCMR1.BIT_OCM.CC1S	= 0;
		Copy_strTIMx.ptrStrTIMx->CCMR1.BIT_OCM.OC1M	= TOGGLE;
		Copy_strTIMx.ptrStrTIMx->CCER.BIT.CC1P		= Copy_strTIMx.enumOCPolarity;
		Copy_strTIMx.ptrStrTIMx->DIER.BIT.CC1IE		= 1;
		break;
	case CHANNEL2:
		Copy_strTIMx.ptrStrTIMx->CCR2.REGISTER 		= GLOB_u32CRRx;
		Copy_strTIMx.ptrStrTIMx->CCMR1.BIT_OCM.CC2S	= 0;
		Copy_strTIMx.ptrStrTIMx->CCMR1.BIT_OCM.OC2M	= TOGGLE;
		Copy_strTIMx.ptrStrTIMx->CCER.BIT.CC2P		= Copy_strTIMx.enumOCPolarity;
		Copy_strTIMx.ptrStrTIMx->DIER.BIT.CC2IE		= 1;
		break;
	case CHANNEL3:
		Copy_strTIMx.ptrStrTIMx->CCR3.REGISTER 		= GLOB_u32CRRx;
		Copy_strTIMx.ptrStrTIMx->CCMR2.BIT_OCM.CC3S	= 0;
		Copy_strTIMx.ptrStrTIMx->CCMR2.BIT_OCM.OC3M	= TOGGLE;
		Copy_strTIMx.ptrStrTIMx->CCER.BIT.CC3P		= Copy_strTIMx.enumOCPolarity;
		Copy_strTIMx.ptrStrTIMx->DIER.BIT.CC3IE		= 1;
		break;
	case CHANNEL4:
		Copy_strTIMx.ptrStrTIMx->CCR4.REGISTER 		= GLOB_u32CRRx;
		Copy_strTIMx.ptrStrTIMx->CCMR2.BIT_OCM.CC4S	= 0;
		Copy_strTIMx.ptrStrTIMx->CCMR2.BIT_OCM.OC4M	= TOGGLE;
		Copy_strTIMx.ptrStrTIMx->CCER.BIT.CC4P		= Copy_strTIMx.enumOCPolarity;
		Copy_strTIMx.ptrStrTIMx->DIER.BIT.CC4IE		= 1;
		break;
	}
	Copy_strTIMx.ptrStrTIMx->CR1.BIT.CEN 			= 1;
}

void TIM_vidOCToggleDisable(TIM_CONFIG Copy_strTIMx, TIM_CHANNEL Copy_enumChannel)
{
	Copy_strTIMx.ptrStrTIMx->CR1.BIT.CEN 			= 0;
	switch(Copy_enumChannel)
	{
	case CHANNEL1:
		Copy_strTIMx.ptrStrTIMx->CCMR1.BIT_OCM.OC1M	= FROZEN;
		Copy_strTIMx.ptrStrTIMx->DIER.BIT.CC1IE		= 0;
		break;
	case CHANNEL2:
		Copy_strTIMx.ptrStrTIMx->CCMR1.BIT_OCM.OC2M	= FROZEN;
		Copy_strTIMx.ptrStrTIMx->DIER.BIT.CC2IE		= 1;
		break;
	case CHANNEL3:
		Copy_strTIMx.ptrStrTIMx->CCMR2.BIT_OCM.OC3M	= FROZEN;
		Copy_strTIMx.ptrStrTIMx->DIER.BIT.CC3IE		= 0;
		break;
	case CHANNEL4:
		Copy_strTIMx.ptrStrTIMx->CCMR2.BIT_OCM.OC4M	= FROZEN;
		Copy_strTIMx.ptrStrTIMx->DIER.BIT.CC4IE		= 0;
		break;
	}
}

static void TIM_vidToggleOCHandler(TIM_REGISTERS * Copy_ptrStrTIMx)
{
	static u8 	LOC_u8Counter = 0;
	static u32 	LOC_u32ArrCRRx[4] = {0};
	switch(LOC_u8Counter)
	{
	case 0 :
	{
		if(Copy_ptrStrTIMx->SR.BIT.CC1IF == 1)
		{
			LOC_u32ArrCRRx[0] 				= 	Copy_ptrStrTIMx->CCR1.REGISTER;
			Copy_ptrStrTIMx->CCR1.REGISTER += 	LOC_u32ArrCRRx[0];
		}
		if(Copy_ptrStrTIMx->SR.BIT.CC2IF == 1)
		{
			LOC_u32ArrCRRx[1] 				= 	Copy_ptrStrTIMx->CCR2.REGISTER;
			Copy_ptrStrTIMx->CCR2.REGISTER += 	LOC_u32ArrCRRx[1];
		}
		if(Copy_ptrStrTIMx->SR.BIT.CC3IF == 1)
		{
			LOC_u32ArrCRRx[2] 				= 	Copy_ptrStrTIMx->CCR3.REGISTER;
			Copy_ptrStrTIMx->CCR3.REGISTER += 	LOC_u32ArrCRRx[2];
		}
		if(TIM2_R->SR.BIT.CC4IF == 1)
		{
			LOC_u32ArrCRRx[3] 				= 	Copy_ptrStrTIMx->CCR4.REGISTER;
			Copy_ptrStrTIMx->CCR4.REGISTER 	+= 	LOC_u32ArrCRRx[3];
		}
		LOC_u8Counter++;
	}
	break;

	default:
	{
		if(Copy_ptrStrTIMx->SR.BIT.CC1IF == 1)
		{
			Copy_ptrStrTIMx->CCR1.REGISTER += 	LOC_u32ArrCRRx[0];
		}
		if(Copy_ptrStrTIMx->SR.BIT.CC2IF == 1)
		{
			Copy_ptrStrTIMx->CCR2.REGISTER += 	LOC_u32ArrCRRx[1];
		}
		if(Copy_ptrStrTIMx->SR.BIT.CC3IF == 1)
		{
			Copy_ptrStrTIMx->CCR3.REGISTER += 	LOC_u32ArrCRRx[2];
		}
		if(Copy_ptrStrTIMx->SR.BIT.CC4IF == 1)
		{
			Copy_ptrStrTIMx->CCR4.REGISTER += 	LOC_u32ArrCRRx[3];
		}
	}
	break;

	}//END OF SWITCH

}*/

void TIM2_IRQHandler(void)
{

}
