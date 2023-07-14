/*
 * NVIC_interface.h
 *
 *  Created on: Sep 7, 2022
 *      Author: Hosam
 */

#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/NVIC_config.h"
#include "MCAL/NVIC_private.h"

typedef enum
{
	XXXX = 0xFFFFF8FF,
	XXXY = 0xFFFFFCFF,
	XXYY,
	XYYY,
	YYYY
}GROUP_SUB_PRIORITY_MODE;

typedef enum
{
	SYSTICK_INTR	= (s8)-1,
	WWDG_INTR 		= (u8)0,
	EXTI16_INTR		= (u8)1,
	PVD_INTR		= (u8)1,
	EXTI21_INTR		= (u8)2,
	TAMP_STAMP_INTR	= (u8)2,
	EXTI22_INTR		= (u8)3,
	RTC_WKUP_INTR	= (u8)3,
	FLASH_INTR,
	RCC_INTR,
	EXTI0_INTR,
	EXTI1_INTR,
	EXTI2_INTR,
	EXTI3_INTR,
	EXTI4_INTR,
	DMA1_Stream0_INTR,
	DMA1_Stream1_INTR,
	DMA1_Stream2_INTR,
	DMA1_Stream3_INTR,
	DMA1_Stream4_INTR,
	DMA1_Stream5_INTR,
	DMA1_Stream6_INTR,
	ADC_INTR,
	EXTI9_5_INTR	= (u8)23,
	TIM1_BRK_TIM9_INTR,
	TIM1_UP_TIM10_INTR,
	TIM1_TRG_COM_TIM11_INTR,
	TIM1_CC_INTR,
	TIM2_INTR,
	TIM3_INTR,
	TIM4_INTR,
	I2C1_EV_INTR,
	I2C1_ER_INTR,
	I2C2_EV_INTR,
	I2C2_ER_INTR,
	SPI1_INTR,
	SPI2_INTR,
	USART1_INTR,
	USART2_INTR,
	EXTI15_10_INTR		= (u8)40,
	EXTI17_INTR			= (u8)41,
	RTC_ALARM_INTR		= (u8)41,
	EXTI18_INTR			= (u8)42,
	OTG_FS_WKUP_INTR	= (u8)42,
	DMA1_STREAM7_INTR	= (u8)47,
	SDIO_INTR			= (u8)49,
	TIM5_INTR,
	SPI3_INTR,
	DMA2_Stream0_INTR	= (u8)56,
	DMA2_STREAM1_INTR,
	DMA2_STREAM2_INTR,
	DMA2_STREAM3_INTR,
	DMA2_STREAM4_INTR,
	OTG_FS_INTR			= (u8)67,
	DMA2_STREAM5_INTR,
	DMA2_STREAM6_INTR,
	DMA2_STREAM7_INTR,
	USART6_INTR,
	I2C3_EV_INTR,
	I2C3_ER_INTR,
	FPU_INTR			= (u8)81,
	SPI4_INTR			= (u8)84,
}STM_PERIPHERAL;

void NVIC_vidGroupSubPriority(void);
void NVIC_vidSetPrioritySoftware(STM_PERIPHERAL Copy_enuPeripheralName, u8 Copy_u8Priority);
void NVIC_vidEnableInterrupt(STM_PERIPHERAL Copy_enuPeripheralName);
void NVIC_vidDisableInterrupt(STM_PERIPHERAL Copy_enuPeripheralName);
void NVIC_vidSetPendingFlag(STM_PERIPHERAL Copy_enuPeripheralName);
void NVIC_vidClearPendingFlag(STM_PERIPHERAL Copy_enuPeripheralName);
u8	 NVIC_u8GetActiveFlag(STM_PERIPHERAL Copy_enuPeripheralName);

#endif
