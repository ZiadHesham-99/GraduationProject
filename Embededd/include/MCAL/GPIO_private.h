/*
 * GPIO_private.h
 *
 *  Created on: Aug 10, 2022
 *      Author: Hosam
 */

#ifndef	GPIO_PRIVATE_H
#define	GPIO_PRIVATE_H

#include "GPIO_interface.h"

typedef struct
{
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
#define GPIOA_R							((volatile GPIOx_REGISTERS*)GPIOA_BASE_ADDRESS)
#define GPIOB_R							((volatile GPIOx_REGISTERS*)GPIOB_BASE_ADDRESS)
#define GPIOC_R							((volatile GPIOx_REGISTERS*)GPIOC_BASE_ADDRESS)

#endif
