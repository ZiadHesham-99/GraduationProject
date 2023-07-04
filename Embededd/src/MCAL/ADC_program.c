/*
 * ADC_program.c
 *
 *  Created on: Oct 23, 2022
 *      Author: Hosam
 */

#include "MCAL/ADC_interface.h"

void ADC_vidInit(tstrADCConfig Copy_strConfig)
{
	u8 LOC_u8ChannelNum;
	//s8 LOC_s8Counter 		= 0;

	LOC_u8ChannelNum		= (u8)(Copy_strConfig.enmChannelNum);

	ADC_R->CR1.BIT.RES 		= Copy_strConfig.enmResolution;
	ADC_R->CR2.BIT.ALIGN	= Copy_strConfig.enmAlignment;
	ADC_CCR_R->BIT.ADCPRE	= Copy_strConfig.enmPrescaler;
	ADC_R->SQR1.BIT.L 		= 0;

	switch(GET_BIT(Copy_strConfig.enmChannelNum,15))
	{
	case 1:
	{
		LOC_u8ChannelNum 		-= 10;
		ADC_R->SQR3.BIT.SQ1		= LOC_u8ChannelNum;
		LOC_u8ChannelNum 		*= 3;
		ADC_R->SMPR1.REGISTER 	= (Copy_strConfig.enmSampleTime << LOC_u8ChannelNum);
	}
	break;
	case 0:
	{
		ADC_R->SQR3.BIT.SQ1		= LOC_u8ChannelNum;
		LOC_u8ChannelNum 		*= 3;
		ADC_R->SMPR2.REGISTER 	= (Copy_strConfig.enmSampleTime << LOC_u8ChannelNum);
	}
	break;
	default : break;
	}// END OF SWITCH

	//Enable ADC
	ADC_R->CR2.BIT.ADON 	= 1;

	/*for(LOC_s8Counter = (3*16); LOC_s8Counter > 0; LOC_s8Counter--)
	{

	}*/
}

u16 ADC_u16GetADCValue(tenmChannelNumADC Copy_enmChannel)
{
	u16 LOC_u16Data;

	ADC_R->DR.REGISTER = 0;

	// Start ADC Conversion
	ADC_R->CR2.BIT.SWSTART = 1;
	while (ADC_R->SR.BIT.STRT == 0);

	// Wait Until Conversion Completed
	while (ADC_R->SR.BIT.EOC == 0);

	ADC_R->CR2.BIT.SWSTART = 0;
	ADC_R->SR.BIT.STRT = 0;
	ADC_R->SR.BIT.EOC = 0;

	// Read ADC Data Register
	LOC_u16Data = (u16)(ADC_R->DR.BIT.DATA);
	switch (Copy_enmChannel)
	{
	case CHANNEL0_ADC:
		ADC_vidHandleData(CHANNEL0_ADC_ALIGN, &LOC_u16Data, CHANNEL0_ADC_RESOL);
		break;
	case CHANNEL1_ADC:
		ADC_vidHandleData(CHANNEL1_ADC_ALIGN, &LOC_u16Data, CHANNEL1_ADC_RESOL);
		break;
	case CHANNEL2_ADC:
		ADC_vidHandleData(CHANNEL2_ADC_ALIGN, &LOC_u16Data, CHANNEL2_ADC_RESOL);
		break;
	case CHANNEL3_ADC:
		ADC_vidHandleData(CHANNEL3_ADC_ALIGN, &LOC_u16Data, CHANNEL3_ADC_RESOL);
		break;
	case CHANNEL4_ADC:
		ADC_vidHandleData(CHANNEL4_ADC_ALIGN, &LOC_u16Data, CHANNEL4_ADC_RESOL);
		break;
	case CHANNEL5_ADC:
		ADC_vidHandleData(CHANNEL5_ADC_ALIGN, &LOC_u16Data, CHANNEL5_ADC_RESOL);
		break;
	case CHANNEL6_ADC:
		ADC_vidHandleData(CHANNEL6_ADC_ALIGN, &LOC_u16Data, CHANNEL6_ADC_RESOL);
		break;
	case CHANNEL7_ADC:
		ADC_vidHandleData(CHANNEL7_ADC_ALIGN, &LOC_u16Data, CHANNEL7_ADC_RESOL);
		break;
	case CHANNEL8_ADC:
		ADC_vidHandleData(CHANNEL8_ADC_ALIGN, &LOC_u16Data, CHANNEL8_ADC_RESOL);
		break;
	case CHANNEL9_ADC:
		ADC_vidHandleData(CHANNEL9_ADC_ALIGN, &LOC_u16Data, CHANNEL9_ADC_RESOL);
		break;
	case CHANNEL10_ADC:
		ADC_vidHandleData(CHANNEL10_ADC_ALIGN, &LOC_u16Data, CHANNEL10_ADC_RESOL);
		break;
	case CHANNEL11_ADC:
		ADC_vidHandleData(CHANNEL11_ADC_ALIGN, &LOC_u16Data, CHANNEL11_ADC_RESOL);
		break;
	case CHANNEL12_ADC:
		ADC_vidHandleData(CHANNEL12_ADC_ALIGN, &LOC_u16Data, CHANNEL12_ADC_RESOL);
		break;
	case CHANNEL13_ADC:
		ADC_vidHandleData(CHANNEL13_ADC_ALIGN, &LOC_u16Data, CHANNEL13_ADC_RESOL);
		break;
	case CHANNEL14_ADC:
		ADC_vidHandleData(CHANNEL14_ADC_ALIGN, &LOC_u16Data, CHANNEL14_ADC_RESOL);
		break;
	case CHANNEL15_ADC:
		ADC_vidHandleData(CHANNEL15_ADC_ALIGN, &LOC_u16Data, CHANNEL15_ADC_RESOL);
		break;
	case CHANNEL16_ADC:
		ADC_vidHandleData(CHANNEL16_ADC_ALIGN, &LOC_u16Data, CHANNEL16_ADC_RESOL);
		break;
	case CHANNEL17_ADC:
		ADC_vidHandleData(CHANNEL17_ADC_ALIGN, &LOC_u16Data, CHANNEL17_ADC_RESOL);
		break;
	case CHANNEL18_ADC:
		ADC_vidHandleData(CHANNEL18_ADC_ALIGN, &LOC_u16Data, CHANNEL18_ADC_RESOL);
		break;
	}
	return LOC_u16Data;
}

static void ADC_vidHandleData(tenmAlignmentTypeADC Copy_enmAlignment, u16 * Copy_pu16Buffer, tenmResolutionADC Copy_enmResolution)
{

	
	if(LEFT_ALIGNMENT == Copy_enmAlignment)
	{
		u16 LOC_u16Buffer = *Copy_pu16Buffer;
		switch(Copy_enmResolution)
		{
		case _12_BITS_ADC :	LOC_u16Buffer = (LOC_u16Buffer >> 4);		break;
		case _10_BITS_ADC : LOC_u16Buffer = (LOC_u16Buffer >> 6);   	break;
		case _8_BITS_ADC  : LOC_u16Buffer = (LOC_u16Buffer >> 8);   	break;
		case _6_BITS_ADC  : LOC_u16Buffer = (LOC_u16Buffer >> 10);  	break;
		}
		*Copy_pu16Buffer = LOC_u16Buffer;
	}
	else
	{
	}
}



