/*
 * TIMER_private.h
 *
 *  Created on: Oct 13, 2022
 *      Author: Hosam
 */

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#include "MCAL/TIMER_interface.h"

typedef struct
{
	union
	{
		u32 REGISTER;
		struct
		{
			u32 CEN:1;
			u32 UDIS:1;
			u32 URS:1;
			u32 OPM:1;
			u32 DIR:1;
			u32 CMS:2;
			u32 ARPE:1;
			u32 CKD:2;
			u32 RESERVED_0:22;
		}BIT;
	}CR1;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 CCPC:1;
			u32 RESERVED_0:1;
			u32 CCUS:1;
			u32 CCDS:1;
			u32 MMS:3;
			u32 TI1S:1;
			u32 OIS1:1;
			u32 OIS1N:1;
			u32 OIS2:1;
			u32 OIS2N:1;
			u32 OIS3:1;
			u32 OIS3N:1;
			u32 OIS4:1;
			u32 RESERVED_1:17;
		}BIT;
	}CR2;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 SMS:3;
			u32 RESERVED_0:1;
			u32 TS:3;
			u32 MSM:1;
			u32 ETF:4;
			u32 ETPS:2;
			u32 ECE:1;
			u32 ETP:1;
			u32 RESERVED_1:16;
		}BIT;
	}SMCR;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 UIE:1;
			u32 CC1IE:1;
			u32 CC2IE:1;
			u32 CC3IE:1;
			u32 CC4IE:1;
			u32 COMIE:1;
			u32 TIE:1;
			u32 BIE:1;
			u32 UDE:1;
			u32 CC1DE:1;
			u32 CC2DE:1;
			u32 CC3DE:1;
			u32 CC4DE:1;
			u32 COMDE:1;
			u32 TDE:1;
			u32 RESERVED_0:17;
		}BIT;
	}DIER;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 UIF:1;
			u32 CC1IF:1;
			u32 CC2IF:1;
			u32 CC3IF:1;
			u32 CC4IF:1;
			u32 COMIF:1;
			u32 TIF:1;
			u32 BIF:1;
			u32 RESERVED_0:1;
			u32 CC1OF:1;
			u32 CC2OF:1;
			u32 CC3OF:1;
			u32 CC4OF:1;
			u32 RESERVED_2:19;
		}BIT;
	}SR;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 UG:1;
			u32 CC1G:1;
			u32 CC2G:1;
			u32 CC3G:1;
			u32 CC4G:1;
			u32 COMG:1;
			u32 TG:1;
			u32 BG:1;
			u32 RESERVED_0:24;
		}BIT;
	}EGR;

	union
	{
		u32 REGISTER_OCM;
		struct
		{
			u32 CC1S:2;
			u32 OC1FE:1;
			u32 OC1PE:1;
			u32 OC1M:3;
			u32 OC1CE:1;
			u32 CC2S:2;
			u32 OC2FE:1;
			u32 OC2PE:1;
			u32 OC2M:3;
			u32 OC2CE:1;
			u32 RESERVED_0:16;
		}BIT_OCM;

		u32 REGISTER_ICM;
		struct
		{
			u32 CC1S:2;
			u32 IC1PSC:2;
			u32 IC1F:4;
			u32 CC2S:2;
			u32 IC2PSC:2;
			u32 IC2F:4;
			u32 RESERVED_0:16;
		}BIT_ICM;
	}CCMR1;

	union
	{
		u32 REGISTER_OCM;
		struct
		{
			u32 CC3S:2;
			u32 OC3FE:1;
			u32 OC3PE:1;
			u32 OC3M:3;
			u32 OC3CE:1;
			u32 CC4S:2;
			u32 OC4FE:1;
			u32 OC4PE:1;
			u32 OC4M:3;
			u32 OC4CE:1;
			u32 RESERVED_0:16;
		}BIT_OCM;

		u32 REGISTER_ICM;
		struct
		{
			u32 CC3S:2;
			u32 IC3PSC:2;
			u32 IC3F:4;
			u32 CC4S:2;
			u32 IC4PSC:2;
			u32 IC4F:4;
			u32 RESERVED_0:16;
		}BIT_ICM;
	}CCMR2;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 CC1E:1;
			u32 CC1P:1;
			u32 CC1NE:1;
			u32 CC1NP:1;
			u32 CC2E:1;
			u32 CC2P:1;
			u32 CC2NE:1;
			u32 CC2NP:1;
			u32 CC3E:1;
			u32 CC3P:1;
			u32 CC3NE:1;
			u32 CC3NP:1;
			u32 CC4E:1;
			u32 CC4P:1;
			u32 RESERVED_3:1;
			u32 CC4NP:1;
			u32 RESERVED_4:16;
		}BIT;
	}CCER;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 CNT:16;
			u32 CNT_TIM2_TIM5:16;
		}BIT;
	}CNT;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 PSC:16;
			u32 RESERVED_0:16;
		}BIT;
	}PSC;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 ARR:16;
			u32 ARR_TIM2_TIM5:16;
		}BIT;
	}ARR;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 REP:8;
			u32 RESERVED_0:24;
		}BIT;
	}RCR;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 CCR1:16;
			u32 CCR1_TIM2_TIM5:16;
		}BIT;
	}CCR1;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 CCR2:16;
			u32 CCR2_TIM2_TIM5:16;
		}BIT;
	}CCR2;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 CCR3:16;
			u32 CCR3_TIM2_TIM5:16;
		}BIT;
	}CCR3;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 CCR4:16;
			u32 CCR4_TIM2_TIM5:16;
		}BIT;
	}CCR4;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 DT:8;
			u32 LOCK:2;
			u32 OSSI:1;
			u32 OSSR:1;
			u32 BKE:1;
			u32 BKP:1;
			u32 AOE:1;
			u32 MOE:1;
			u32 RESERVED_0:16;
		}BIT;
	}BDTR;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 DBA:5;
			u32 RESERVED_0:3;
			u32 DBL:5;
			u32 RESERVED_1:19;
		}BIT;
	}DCR;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 DMAB:32;
		}BIT;
	}DMAR;
	
	union
	{
		u32 REGISTER;
		struct
		{
			u32 TI1_RMP_TIM11:2;
			u32 RESERVED_0:4;
			u32 TI4_RMP_TIM5:2;
			u32 RESERVED_1:2;
			u32 ITR1_RMP_TIM2:2;
			u32 RESERVED_2:20;
		}BIT;
	}OR;
}TIM_REGISTERS;

#define TIM1_BASE_ADDRESS		(0x40010000)
#define TIM2_BASE_ADDRESS       (0x40000000)
#define TIM3_BASE_ADDRESS       (0x40000400)
#define TIM4_BASE_ADDRESS       (0x40000800)
#define TIM5_BASE_ADDRESS       (0x40000C00)
#define TIM9_BASE_ADDRESS       (0x40014000)
#define TIM10_BASE_ADDRESS      (0x40014400)
#define TIM11_BASE_ADDRESS      (0x40014800)

#define TIM1_R					((volatile TIM_REGISTERS*)TIM1_BASE_ADDRESS)
#define TIM2_R                  ((volatile TIM_REGISTERS*)TIM2_BASE_ADDRESS)
#define TIM3_R                  ((volatile TIM_REGISTERS*)TIM3_BASE_ADDRESS)
#define TIM4_R                  ((volatile TIM_REGISTERS*)TIM4_BASE_ADDRESS)
#define TIM5_R                  ((volatile TIM_REGISTERS*)TIM5_BASE_ADDRESS)
#define TIM9_R                  ((volatile TIM_REGISTERS*)TIM9_BASE_ADDRESS)
#define TIM10_R                 ((volatile TIM_REGISTERS*)TIM10_BASE_ADDRESS)
#define TIM11_R                 ((volatile TIM_REGISTERS*)TIM11_BASE_ADDRESS)

#endif
