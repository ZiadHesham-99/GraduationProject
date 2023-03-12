/*********************************
AIRCRAuthor	:	Hosam Magdy
Date	:	22 July 2022
Version	:	1.0
 *********************************/

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "SERVICES/DET.h"

#include "MCAL/RCC_interface.h"
#include "MCAL/RCC_private.h"
#include "MCAL/RCC_config.h"


void RCC_voidInit(void){
	RCC->CR 	&= CR_CLR_MSK;
	RCC->CR 	|= (RCC_SYSCLOCK & 0x0FFFFFFF);
	RCC->CFGR	&= CLK_CONFIG_CLR_MSK;
	RCC->CFGR	|= (RCC_SYSCLOCK>>30);
	RCC->CFGR	|= (RCC_SYSCLK_PRESCALER_AHB<<4);
	RCC->CFGR	|= (RCC_AHB_PRESCALER_APB1<<10);
	RCC->CFGR	|= (RCC_AHB_PRESCALER_APB2<<13);
	switch(RCC_SYSCLOCK){
	case HSI							:	while(!GET_BIT(RCC->CR,1 ));	break;
	case HSE_CRYSTAL 					:	while(!GET_BIT(RCC->CR,17));	break;
	case HSE_CRYSTAL_WITH_CLK_SECURITY	:	while(!GET_BIT(RCC->CR,17));	break;
	case HSE_RC 						:	while(!GET_BIT(RCC->CR,17));	break;
	case HSE_RC_WITH_CLK_SECURITY 		:	while(!GET_BIT(RCC->CR,17));	break;
	case PLL 							:	while(!GET_BIT(RCC->CR,25));	break;
	default	:	DET_voidReportError(RCC_MODULE_ID, INVALID_CLK_SRC, RCC_voidInit_ID);
	break;
	}
}

void RCC_voidEnablePeripheralClock(PERIPHERAL_ID Copy_enumPeripheralID){
	BUS_ID Local_enumBusID = (Copy_enumPeripheralID>>6);
	switch(Local_enumBusID){
	case AHB1 :	SET_BIT(RCC->AHB1ENR,(Copy_enumPeripheralID&PERIPH_ID_CLR_MSK));	break;
	case AHB2 :	SET_BIT(RCC->AHB2ENR,(Copy_enumPeripheralID&PERIPH_ID_CLR_MSK));	break;
	case APB1 :	SET_BIT(RCC->APB1ENR,(Copy_enumPeripheralID&PERIPH_ID_CLR_MSK));	break;
	case APB2 :	SET_BIT(RCC->APB2ENR,(Copy_enumPeripheralID&PERIPH_ID_CLR_MSK));	break;
	default	:	DET_voidReportError(RCC_MODULE_ID, INVALID_PERIPHERAL_ID, RCC_voidEnablePeripheralClock_ID);
	break;
	}
}

void RCC_voidDisablePeripheralClock(PERIPHERAL_ID Copy_enumPeripheralID){
	BUS_ID Local_enumBusID = (Copy_enumPeripheralID>>6);
	switch(Local_enumBusID){
	case AHB1 :	CLR_BIT(RCC->AHB1ENR,(Copy_enumPeripheralID&PERIPH_ID_CLR_MSK));	break;
	case AHB2 :	CLR_BIT(RCC->AHB2ENR,(Copy_enumPeripheralID&PERIPH_ID_CLR_MSK));	break;
	case APB1 :	CLR_BIT(RCC->APB1ENR,(Copy_enumPeripheralID&PERIPH_ID_CLR_MSK));	break;
	case APB2 :	CLR_BIT(RCC->APB2ENR,(Copy_enumPeripheralID&PERIPH_ID_CLR_MSK));	break;
	default	:	DET_voidReportError(RCC_MODULE_ID, INVALID_PERIPHERAL_ID, RCC_voidDisablePeripheralClock_ID);
	break;
	}
}
