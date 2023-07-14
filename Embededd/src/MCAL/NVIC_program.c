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

void NVIC_vidGroupSubPriority(void)
{
	AIRCR_REG = NVIC_GROUP_SUB_PRIORITY_MODE;
}

void NVIC_vidSetPrioritySoftware(STM_PERIPHERAL Copy_enuPeripheralName, u8 Copy_u8Priority)
{
	NVIC_R->IPR[Copy_enuPeripheralName] = (Copy_u8Priority<<4) & 0xFF;
}

void NVIC_vidEnableInterrupt(STM_PERIPHERAL Copy_enuPeripheralName)
{
	NVIC_R->ISER[Copy_enuPeripheralName >> 5] = 1 << ( Copy_enuPeripheralName & 0x1F);
}

void NVIC_vidDisableInterrupt(STM_PERIPHERAL Copy_enuPeripheralName)
{
	NVIC_R->ICER[Copy_enuPeripheralName>>5] = 1 << (Copy_enuPeripheralName&0x1F);
}

void NVIC_voidSetPendingFlag(STM_PERIPHERAL Copy_enuPeripheralName)
{
	NVIC_R->ISPR[Copy_enuPeripheralName>>5] = 1 << (Copy_enuPeripheralName&0x1F);
}

void NVIC_vidClearPendingFlag(STM_PERIPHERAL Copy_enuPeripheralName)
{
	NVIC_R->ICPR[Copy_enuPeripheralName>>5] = 1 << (Copy_enuPeripheralName&0x1F);
}

u8	 NVIC_u8GetActiveFlag(STM_PERIPHERAL Copy_enuPeripheralName)
{
	return GET_BIT(NVIC_R->IABR[Copy_enuPeripheralName>>5],(Copy_enuPeripheralName&0x1F));
}
