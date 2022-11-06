/*
 * ADC_program.c
 *
 *  Created on: Oct 23, 2022
 *      Author: Hosam
 */

#include "../../01- LIB/03- ERROR_STATUS/ERROR_STATUS.h"
#include "../../01- LIB/01- TYPES/STD_TYPES.h"
#include "../../01- LIB/02- BIT_MATH/BIT_MATH.h"

//#include "STD_TYPES.h"
//#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

u16 GLOB_u16ADCData;

void ADC_vidStartConversion(CHANNEL_CONFIG Copy_strChannelConfig)
{
	u8 LOC_u8ChannelNum;
	LOC_u8ChannelNum		= (u8)Copy_strChannelConfig.enumChannelNumber;
	ADC_R->CR1.BIT.RES 		= Copy_strChannelConfig.enumResolution;
	ADC_R->CR2.BIT.ALIGN	= Copy_strChannelConfig.enumAlignment;
	ADC_R->SQR1.BIT.L 		= 0;
	ADC_R->SQR1.BIT.SQ16	= LOC_u8ChannelNum;
	ADC_CCR_R->BIT.ADCPRE	= Copy_strChannelConfig.enumPrescaler;
	switch(GET_BIT(Copy_strChannelConfig.enumChannelNumber,15))
	{
	case 1:
	{
		LOC_u8ChannelNum -= 10;
		LOC_u8ChannelNum *= 3;
		ADC_R->SMPR1.REGISTER = (Copy_strChannelConfig.enumSampleTime << LOC_u8ChannelNum);
	}
	break;
	case 0:
	{
		LOC_u8ChannelNum *= 3;
		ADC_R->SMPR2.REGISTER = (Copy_strChannelConfig.enumSampleTime << LOC_u8ChannelNum);
	}
	break;
	}// END OF SWITCH

	ADC_R->CR2.BIT.ADON 	= 1;
	ADC_R->CR2.BIT.SWSTART	= 1;
	while(ADC_R->SR.BIT.EOC == 0);
	GLOB_u16ADCData = ADC_R->DR.BIT.DATA;
	ADC_R->CR2.BIT.ADON 	= 0;
	ADC_R->CR2.BIT.SWSTART	= 0;
}

void ADC_vidGetValue(CHANNEL_CONFIG Copy_strChannelConfig, u16* Copy_u16DataBuffer)
{
	ADC_vidHandleData(Copy_strChannelConfig);
	* Copy_u16DataBuffer = GLOB_u16ADCData;
}

static void ADC_vidHandleData(CHANNEL_CONFIG Copy_strChannelConfig)
{
	switch(Copy_strChannelConfig.enumAlignment)
	{
	case LEFT_ALIGNMENT :
	{
		switch(Copy_strChannelConfig.enumResolution)
		{
		case _12_BITS_ADC :	GLOB_u16ADCData = (GLOB_u16ADCData >> 4);	break;
		case _10_BITS_ADC : GLOB_u16ADCData = (GLOB_u16ADCData >> 6);   break;
		case _8_BITS_ADC  : GLOB_u16ADCData = (GLOB_u16ADCData >> 8);   break;
		case _6_BITS_ADC  : GLOB_u16ADCData = (GLOB_u16ADCData >> 10);  break;
		}
	}
	break;
	default :
		break;
	}
}


