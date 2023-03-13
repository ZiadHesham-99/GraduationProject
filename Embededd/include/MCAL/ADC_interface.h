/*
 * ADC_interface.h
 *
 *  Created on: Oct 23, 2022
 *      Author: Hosam
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/ADC_private.h"
#include "MCAL/ADC_config.h"

typedef enum
{
	CHANNEL0_ADC 	= (u16)0x0000,
	CHANNEL1_ADC,
	CHANNEL2_ADC,
	CHANNEL3_ADC,
	CHANNEL4_ADC,
	CHANNEL5_ADC,
	CHANNEL6_ADC,
	CHANNEL7_ADC,
	CHANNEL8_ADC,
	CHANNEL9_ADC,
	CHANNEL10_ADC	= (u16)0x800A,
	CHANNEL11_ADC,
	CHANNEL12_ADC,
	CHANNEL13_ADC,
	CHANNEL14_ADC,
	CHANNEL15_ADC,
	CHANNEL16_ADC,
	CHANNEL17_ADC,
	CHANNEL18_ADC
}tenmChannelNumADC;

typedef enum
{
	_12_BITS_ADC	= (u8)0,
	_10_BITS_ADC,
	_8_BITS_ADC,
	_6_BITS_ADC,
}tenmResolutionADC;

typedef enum
{
	RIGHT_ALIGNMENT	= (u8)0,
	LEFT_ALIGNMENT
}tenmAlignmentTypeADC;

typedef enum
{
	_3_CYCLES	= (u32)0,
    _15_CYCLES,
    _28_CYCLES,
    _56_CYCLES,
    _84_CYCLES,
    _112_CYCLES,
    _114_CYCLES,
    _480_CYCLES,
}tenmSampleTimeADC;

typedef enum
{
	_2_PRESCALER	= (u8)0,
	_4_PRESCALER,
	_6_PRESCALER,
	_8_PRESCALER,
}tenmPrescalerADC;


typedef struct
{
	tenmChannelNumADC 		enmChannelNum;
	tenmResolutionADC		enmResolution;
	tenmAlignmentTypeADC	enmAlignment;
	tenmSampleTimeADC		enmSampleTime;	
	tenmPrescalerADC		enmPrescaler;
}tstrADCConfig;

void ADC_vidInit(tstrADCConfig Copy_strConfig);
u16 ADC_u16GetADCValue(tenmChannelNumADC Copy_enmChannel);

static void ADC_vidHandleData(tenmAlignmentTypeADC Copy_enmAlignment, u16 * Copy_pu16Buffer, tenmResolutionADC Copy_enmResolution);


#endif
