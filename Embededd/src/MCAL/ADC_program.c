/*
 * ADC_program.c
 *
 *  Created on: Oct 23, 2022
 *      Author: Hosam
 */

#include "MCAL/ADC_interface.h"

void ADC_vidInit(void)
{
	u8 LOC_u8ChannelNum;
	//s8 LOC_s8Counter 		= 0;

	LOC_u8ChannelNum		= (u8)(CHANNEL_NUMBER_ADC);

	ADC_R->CR1.BIT.RES 		= RESOLUTION_ADC;
	ADC_R->CR2.BIT.ALIGN	= ALIGN_ADC;
	ADC_CCR_R->BIT.ADCPRE	= PRESCALER_ADC;
	ADC_R->SQR1.BIT.L 		= 0;

	switch(GET_BIT(CHANNEL_NUMBER_ADC,15))
	{
	case 1:
	{
		LOC_u8ChannelNum 		-= 10;
		ADC_R->SQR3.BIT.SQ1		= LOC_u8ChannelNum;
		LOC_u8ChannelNum 		*= 3;
		ADC_R->SMPR1.REGISTER 	= (SAMPLE_TIME_ADC << LOC_u8ChannelNum);
	}
	break;
	case 0:
	{
		ADC_R->SQR3.BIT.SQ1		= LOC_u8ChannelNum;
		LOC_u8ChannelNum 		*= 3;
		ADC_R->SMPR2.REGISTER 	= (SAMPLE_TIME_ADC << LOC_u8ChannelNum);
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

u16 ADC_u16GetADCValue(void)
{
	u16 LOC_u16Data;

	ADC_R->DR.REGISTER = 0;

	//Start ADC Conversion
	ADC_R->CR2.BIT.SWSTART	= 1;
	while(ADC_R->SR.BIT.STRT == 0);

	//Wait Until Conversion Completed
	while(ADC_R->SR.BIT.EOC == 0);

	ADC_R->CR2.BIT.SWSTART	= 0;
	ADC_R->SR.BIT.STRT		= 0;
	ADC_R->SR.BIT.EOC 		= 0;

	//Read ADC Data Register
	LOC_u16Data = (u16)(ADC_R->DR.BIT.DATA);

	ADC_vidHandleData(ALIGN_ADC, &LOC_u16Data);

	return LOC_u16Data;
}

static void ADC_vidHandleData(ADC_ALIGN Copy_enuAlignment, u16 * Copy_ptrU16Buffer)
{
	switch(Copy_enuAlignment)
	{
	case LEFT_ALIGNMENT :
	{
		u16 LOC_u16Buffer = *Copy_ptrU16Buffer;
		switch(Copy_enuAlignment)
		{
		case _12_BITS_ADC :	LOC_u16Buffer = (LOC_u16Buffer >> 4);		break;
		case _10_BITS_ADC : LOC_u16Buffer = (LOC_u16Buffer >> 6);   	break;
		case _8_BITS_ADC  : LOC_u16Buffer = (LOC_u16Buffer >> 8);   	break;
		case _6_BITS_ADC  : LOC_u16Buffer = (LOC_u16Buffer >> 10);  	break;
		}
		*Copy_ptrU16Buffer = LOC_u16Buffer;
	}
	break;
	default :
		break;
	}
}



