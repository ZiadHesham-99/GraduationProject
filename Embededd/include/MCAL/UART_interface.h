/*
 * UART_interface.h
 *
 *  Created on: Sep 24, 2022
 *      Author: ziad
 */

#ifndef MCAL_07_UART_UART_INTERFACE_H_
#define MCAL_07_UART_UART_INTERFACE_H_

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/UART_config.h"
#include "MCAL/UART_private.h"

void UART_vidInit(void);
void UART_vidTransmitChar(u8 Copy_u8Data);
void UART_vidTransmitString(u8 * Copy_u8PtrData);
u8   UART_u8Receive(u32 Copy_u32MaxTimeToWait);

#endif /* 02_MCAL_07_UART_UART_INTERFACE_H_ */
