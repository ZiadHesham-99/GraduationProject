/*
 * SYSTICK_private.h
 *
 *  Created on: Aug 23, 2022
 *      Author: Hosam
 */
#ifndef	SYSTIC_PRIVATE_H
#define	SYSTIC_PRIVATE_H

#include "MCAL/SYSTICK_interface.h"

typedef struct{
	union{
		u32 REGISTER;
		struct{
			u32 ENABLE:1;
			u32 TICKINT:1;
			u32 CLKSRC:1;
			u32 RESERVED_0:13;
			u32 COUNTFLAG:1;
			u32 RESERVED_1:15;
		}BIT;
	}CTRL;

	union{
		u32 REGISTER;
		struct{
			u32 RELOAD:24;
			u32 RESERVED_0:8;
		}BIT;
	}LOAD;

	union{
		u32 REGISTER;
		struct{
			u32 CURRENT:24;
			u32 RESERVED_0:8;
		}BIT;
	}VAL;

	union{
		u32 REGISTER;
		struct{
			u32 TENMS:24;
			u32 RESERVED_0:6;
			u32 SKEW:1;
			u32 NOREF:1;
		}BIT;
	}CALIB;

}SYSTICK_REGISTERS;

#define	SYSTICK_BASE_ADDRESS	(0xE000E010)
#define SYSTICK_R				((volatile SYSTICK_REGISTERS*)SYSTICK_BASE_ADDRESS)

#endif
