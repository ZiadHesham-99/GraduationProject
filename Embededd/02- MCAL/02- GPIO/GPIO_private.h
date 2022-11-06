/*
 * GPIO_private.h
 *
 *  Created on: Aug 10, 2022
 *      Author: Hosam
 */

#ifndef	GPIO_PRIVATE_H
#define	GPIO_PRIVATE_H

#include "../../01- LIB/01- TYPES/STD_TYPES.h"

typedef struct{
	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDR;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFRL;
	u32 AFRH;
}GPIOx_REGISTERS;

#define GPIOA_BASE_ADDRESS				(0x40020000)
#define GPIOB_BASE_ADDRESS				(0x40020400)
#define GPIOC_BASE_ADDRESS				(0x40020800)
#define GPIOA_R							((GPIOx_REGISTERS*)GPIOA_BASE_ADDRESS)
#define GPIOB_R							((GPIOx_REGISTERS*)GPIOB_BASE_ADDRESS)
#define GPIOC_R							((GPIOx_REGISTERS*)GPIOC_BASE_ADDRESS)
#define CLR_TWO_BITS(VAR,_1st_BITNO)	(VAR) &= ~( ((u32)3) << ((_1st_BITNO)*2) )
#define CLR_FOUR_BITS(VAR,_1st_BITNO)	(VAR) &= ~( ((u32)15) << ((_1st_BITNO)*4) )

#endif
