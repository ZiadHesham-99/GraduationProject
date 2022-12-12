/*
 * NVIC_private.h
 *
 *  Created on: Sep 7, 2022
 *      Author: Hosam
 */

#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_

typedef struct{
	u32 ISER[8];
	u32	RESERVED_0[24];
	u32	ICER[8];
	u32	RESERVED_1[24];
	u32 ISPR[8];
	u32	RESERVED_2[24];
	u32 ICPR[8];
	u32	RESERVED_3[24];
	u32 IABR[8];
	u32	RESERVED_4[56];
	u8 	IPR[84];
}NVIC_REGISTERS;

#define NVIC_BASE_ADDRESS	(0xE000E100)
#define NVIC_R				((volatile NVIC_REGISTERS*)NVIC_BASE_ADDRESS)
#define AIRCR_REG			*((volatile u32*)0xE000ED0C)

#endif
