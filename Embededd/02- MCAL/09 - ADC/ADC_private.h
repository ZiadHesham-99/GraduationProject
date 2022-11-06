/*
 * ADC_private.h
 *
 *  Created on: Oct 23, 2022
 *      Author: Hosam
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

typedef struct
{
	union
	{
		u32 REGISTER;
		struct
		{
			u32 AWD:1;
			u32 EOC:1;
			u32 JEOC:1;
			u32 JSTRT:1;
			u32 STRT:1;
			u32 OVR:1;
			u32 RESERVED_0:26;
		}BIT;
	}SR;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 AWDCH:5;
			u32 EOCIE:1;
			u32 AWDIE:1;
			u32 JEOCIE:1;
			u32 SCAN:1;
			u32 AWDSGL:1;
			u32 JAUTO:1;
			u32 DISCEN:1;
			u32 JDISCEN:1;
			u32 DISCNUM:3;
			u32 RESERVED_0:6;
			u32 JAWDEN:1;
			u32 AWDEN:1;
			u32 RES:2;
			u32 OVRIE:1;
			u32 RESERVED_1:5;
		}BIT;
	}CR1;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 ADON:1;
			u32 CONT:1;
			u32 RESERVED_0:6;
			u32 DMA:1;
			u32 DDS:1;
			u32 EOCS:1;
			u32 ALIGN:1;
			u32 RESERVED_1:4;
			u32 JEXTSEL:4;
			u32 JEXTEN:2;
			u32 JSWSTART:1;
			u32 RESERVED_2:1;
			u32 EXTSEL:4;
			u32 EXTEN:2;
			u32 SWSTART:1;
			u32 RESERVED_3:1;
		}BIT;
	}CR2;

	union
	{
		u32 REGISTER;
		struct
		{
			u32	SMP10:3;
			u32	SMP11:3;
			u32	SMP12:3;
			u32	SMP13:3;
			u32	SMP14:3;
			u32	SMP15:3;
			u32	SMP16:3;
			u32	SMP17:3;
			u32	SMP18:3;
			u32	RESERVED_0:5;
		}BIT;
	}SMPR1;

	union
	{
		u32 REGISTER;
		struct
		{
			u32	SMP0:3;
			u32	SMP1:3;
			u32	SMP2:3;
			u32	SMP3:3;
			u32	SMP4:3;
			u32	SMP5:3;
			u32	SMP6:3;
			u32	SMP7:3;
			u32	SMP8:3;
			u32	SMP9:3;
			u32	RESERVED_0:2;
		}BIT;
	}SMPR2;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 JOFFSET1:12;
			u32	RESERVED_0:20;
		}BIT;
	}JOFR1;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 JOFFSET2:12;
			u32	RESERVED_0:20;
		}BIT;
	}JOFR2;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 JOFFSET3:12;
			u32	RESERVED_0:20;
		}BIT;
	}JOFR3;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 JOFFSET4:12;
			u32	RESERVED_0:20;
		}BIT;
	}JOFR4;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 HT:12;
			u32	RESERVED_0:20;
		}BIT;
	}HTR;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 LT:12;
			u32	RESERVED_0:20;
		}BIT;
	}LTR;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 SQ13:5;
			u32 SQ14:5;
			u32 SQ15:5;
			u32 SQ16:5;
			u32 L:4;
			u32	RESERVED_0:8;
		}BIT;
	}SQR1;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 SQ7:5;
			u32 SQ8:5;
			u32 SQ9:5;
			u32 SQ10:5;
			u32 SQ11:5;
			u32 SQ12:5;
			u32	RESERVED_0:2;
		}BIT;
	}SQR2;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 SQ1:5;
			u32 SQ2:5;
			u32 SQ3:5;
			u32 SQ4:5;
			u32 SQ5:5;
			u32 SQ6:5;
			u32	RESERVED_0:2;
		}BIT;
	}SQR3;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 JSQ1:5;
			u32 JSQ2:5;
			u32 JSQ3:5;
			u32 JSQ4:5;
			u32 JL:2;
			u32	RESERVED_0:10;
		}BIT;
	}JSQR;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 JDATA:16;
			u32	RESERVED_0:16;
		}BIT;
	}JDR1;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 JDATA:16;
			u32	RESERVED_0:16;
		}BIT;
	}JDR2;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 JDATA:16;
			u32	RESERVED_0:16;
		}BIT;
	}JDR3;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 JDATA:16;
			u32	RESERVED_0:16;
		}BIT;
	}JDR4;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 DATA:16;
			u32	RESERVED_0:16;
		}BIT;
	}DR;
}ADC_REGISTERS;

typedef union
{
	u32 REGISTER;
	struct
	{
		u32	RESERVED_0:16;
		u32	ADCPRE:2;
		u32	RESERVED_1:4;
		u32	VBATE:1;
		u32	TSVREFE:1;
		u32	RESERVED_2:8;
	}BIT;
}ADC_CCR;

#define ADC_BASE_ADDRESS		(0x40012000)
#define ADC_R					((volatile ADC_REGISTERS*)ADC_BASE_ADDRESS)
#define ADC_CCR_R				((volatile ADC_CCR*)(ADC_BASE_ADDRESS+0x300))

static void ADC_vidHandleData(CHANNEL_CONFIG Copy_strChannelConfig);

#endif
