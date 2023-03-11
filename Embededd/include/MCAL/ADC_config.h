/*
 * ADC_config.h
 *
 *  Created on: Oct 23, 2022
 *      Author: Hosam
 */

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

#include "MCAL/ADC_interface.h"

/*
 * Select Channel Number from :
 * 	CHANNEL0_ADC
 *	CHANNEL1_ADC
 *	CHANNEL2_ADC
 *	CHANNEL3_ADC
 *	CHANNEL4_ADC
 *	CHANNEL5_ADC
 *	CHANNEL6_ADC
 *	CHANNEL7_ADC
 *	CHANNEL8_ADC
 *	CHANNEL9_ADC
 *	CHANNEL10_ADC
 *	CHANNEL11_ADC
 *	CHANNEL12_ADC
 *	CHANNEL13_ADC
 *	CHANNEL14_ADC
 *	CHANNEL15_ADC
 *	CHANNEL16_ADC
 *	CHANNEL17_ADC
 *	CHANNEL18_ADC
 */
#define	CHANNEL_NUMBER_ADC		CHANNEL0_ADC


/*
 * Select ADC Resolution from :
 * 	_12_BITS_ADC
 * 	_10_BITS_ADC
 * 	_8_BITS_ADC
 * 	_6_BITS_ADC
 */
#define RESOLUTION_ADC			_12_BITS_ADC


/*
 * Select ADC Alignment from :
 * 	RIGHT_ALIGNMENT
 * 	LEFT_ALIGNMENT
 */
#define ALIGN_ADC				RIGHT_ALIGNMENT


/*
 * Select ADC Prescaler from :
 * 	_2_PRESCALER
 * 	_4_PRESCALER
 * 	_6_PRESCALER
 * 	_8_PRESCALER
 */
#define PRESCALER_ADC			_2_PRESCALER


/*
 * Select ADC Sample Time from :
 * 	_3_CYCLES
 * 	_15_CYCLES,
 * 	_28_CYCLES,
 * 	_56_CYCLES,
 * 	_84_CYCLES,
 * 	_112_CYCLES,
 * 	_114_CYCLES,
 * 	_480_CYCLES,
 */
#define SAMPLE_TIME_ADC			_15_CYCLES



#endif
