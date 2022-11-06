/*
 * DMA_private.h
 *
 *  Created on: Sep 16, 2022
 *      Author: Hosam
 */

#ifndef DMA_PRIVATE_H_
#define DMA_PRIVATE_H_

typedef struct{
	u32 SCR;
	u32	SNDTR;
	u32	S0PAR;
	u32 SM0AR;
	u32 SM1AR;
	u32 SFCR;
}STREAM_t;

typedef struct{
	u32	LISR;
	u32 HISR;
	u32 LIFCR;
	u32	HIFCR;
	STREAM_t STREAM[8];
}DMA_REGISTERS;

#define DMA1_BASE_ADDRESS	(0x40026000)
#define DMA1_R				((volatile DMA_REGSITERS*)DMA1_BASE_ADDRESS)

#endif
