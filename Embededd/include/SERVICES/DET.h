/*
 * DET.h
 *
 *  Created on: Aug 24, 2022
 *      Author: Hosam
 */

#ifndef DET_H
#define DET_H

#include "LIB/STD_TYPES.h"

typedef enum{
	RCC_MODULE_ID = (u8)0,
	GPIO_MODULE_ID,
	SYSTICK_MODULE_ID
}DET_MODULE_ID;

void DET_voidReportError(DET_MODULE_ID Copy_enumModuleID, u8 Copy_u8ErrorID, u8 Copy_u8FunctionID);

#endif /* 04__SERVICES_01__DET_DET_H_ */
