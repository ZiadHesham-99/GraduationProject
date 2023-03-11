/*
 * NVIC_program.c
 *
 *  Created on: Sep 7, 2022
 *      Author: Hosam
 */


#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/NVIC_config.h"
#include "MCAL/NVIC_interface.h"
#include "MCAL/NVIC_private.h"

void NVIC_voidGroupSubPriority(void){
	AIRCR_REG = NVIC_GROUP_SUB_PRIORITY_MODE;
}

void NVIC_voidSetPrioritySoftware(STM_PERIPHERAL Copy_enumPeripheralName, u8 Copy_u8Priority){
	NVIC_R->IPR[Copy_enumPeripheralName] = (Copy_u8Priority<<4) & 0xFF;
}

void NVIC_voidEnableInterrupt(STM_PERIPHERAL Copy_enumPeripheralName){
	NVIC_R->ISER[Copy_enumPeripheralName>>5] = 1 << (Copy_enumPeripheralName&0x1F);
}

void NVIC_voidDisableInterrupt(STM_PERIPHERAL Copy_enumPeripheralName){
	NVIC_R->ICER[Copy_enumPeripheralName>>5] = 1 << (Copy_enumPeripheralName&0x1F);
}

void NVIC_voidSetPendingFlag(STM_PERIPHERAL Copy_enumPeripheralName){
	NVIC_R->ISPR[Copy_enumPeripheralName>>5] = 1 << (Copy_enumPeripheralName&0x1F);
}

void NVIC_voidClearPendingFlag(STM_PERIPHERAL Copy_enumPeripheralName){
	NVIC_R->ICPR[Copy_enumPeripheralName>>5] = 1 << (Copy_enumPeripheralName&0x1F);
}

u8	 NVIC_u8GetActiveFlag(STM_PERIPHERAL Copy_enumPeripheralName){
	return GET_BIT(NVIC_R->IABR[Copy_enumPeripheralName>>5],(Copy_enumPeripheralName&0x1F));
}
