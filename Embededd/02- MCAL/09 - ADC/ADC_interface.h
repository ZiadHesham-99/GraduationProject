/*
 * ADC_interface.h
 *
 *  Created on: Oct 23, 2022
 *      Author: Hosam
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

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
}ADC_CHANNEL_NUM;

typedef enum
{
	_12_BITS_ADC	= (u8)0,
	_10_BITS_ADC,
	_8_BITS_ADC,
	_6_BITS_ADC,
}ADC_RES;

typedef enum
{
	RIGHT_ALIGNMENT	= (u8)0,
	LEFT_ALIGNMENT
}ADC_ALIGN;

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
}ADC_SAMP_TIME;

typedef enum
{
	_2_PRESCALER	= (u8)0,
	_4_PRESCALER,
	_6_PRESCALER,
	_8_PRESCALER,
}ADC_PRE;

typedef struct
{
	ADC_CHANNEL_NUM		enumChannelNumber;
	ADC_RES				enumResolution;
	ADC_ALIGN			enumAlignment;
	ADC_SAMP_TIME		enumSampleTime;
	ADC_PRE				enumPrescaler;
}CHANNEL_CONFIG;

void ADC_vidStartConversion(CHANNEL_CONFIG Copy_strChannelConfig);
void ADC_vidGetValue(CHANNEL_CONFIG Copy_strChannelConfig, u16* Copy_u16DataBuffer);


#endif
