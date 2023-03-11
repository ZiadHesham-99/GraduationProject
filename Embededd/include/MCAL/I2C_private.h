/*
 * I2C_private.h
 *
 *  Created on: Oct 5, 2022
 *      Author: Hosam
 */

#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

#include "MCAL/I2C_interface.h"

typedef struct
{

	union
	{
		u32 REGISTER;
		struct
		{
			u32 PE:1;
			u32 SMBUS:1;
			u32 RESERVED_0:1;
			u32 SMBTYPE:1;
			u32 ENARP:1;
			u32 ENPEC:1;
			u32 ENGC:1;
			u32 NOSTRETCH:1;
			u32 START:1;
			u32 STOP:1;
			u32 ACK:1;
			u32 POS:1;
			u32 PEC:1;
			u32 ALERT:1;
			u32 RESERVED_1:1;
			u32 SWRST:1;
			u32 RESERVED_2:16;
		}BIT;
	}CR1;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 FREQ:6;
			u32 RESERVED_0:2;
			u32 ITERREN:1;
			u32 ITEVTEN:1;
			u32 ITBUFEN:1;
			u32 DMAEN:1;
			u32 LAST:1;
			u32 RESERVED_1:3;
			u32 RESERVED_2:16;
		}BIT;
	}CR2;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 ADD0:1;
			u32 ADD1_7_1:7;
			u32 ADD1_9_8:2;
			u32 RESERVED_0:5;
			u32 ADDMODE:1;
			u32 RESERVED_1:16;
		}BIT;
	}OAR1;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 ENDUAL:1;
			u32 ADD2_7_1:7;
			u32 RESERVED_0:24;
		}BIT;
	}OAR2;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 DR:8;
			u32 RESERVED_0:24;
		}BIT;
	}DR;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 SB:1;
			u32 ADDR:1;
			u32 BTF:1;
			u32 ADD10:1;
			u32 STOPF:1;
			u32 RESERVED_0:1;
			u32 RxNE:1;
			u32 TxE:1;
			u32 BERR:1;
			u32 ARLO:1;
			u32 AF:1;
			u32 OVR:1;
			u32 PECERR:1;
			u32 RESERVED_1:1;
			u32 TIMEOUT:1;
			u32 SMBALERT:1;
			u32 RESERVED_2:16;
		}BIT;
	}SR1;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 MSL:1;
			u32 BUSY:1;
			u32 TRA:1;
			u32 RESERVED_0:1;
			u32 GENCALL:1;
			u32 SMBDEFAULT:1;
			u32 SMBHOST:1;
			u32 DUALF:1;
			u32 PEC:8;
			u32 RESERVED_1:16;
		}BIT;
	}SR2;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 CCR:12;
			u32 RESERVED_0:2;
			u32 DUTY:1;
			u32 F_S:1;
			u32 RESERVED_1:16;
		}BIT;
	}CCR;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 TRISE:6;
			u32 RESERVED_0:26;
		}BIT;
	}TRISE;

	union
	{
		u32 REGISTER;
		struct
		{
			u32 DNF:4;
			u32 ANOFF:1;
			u32 RESERVED_0:27;
		}BIT;
	}FLTR;
}I2Cx_REGISTERS;

#define	I2C1_BASE_ADDRESS		(0x40005400)
#define I2C2_BASE_ADDRESS		(0x40005800)
#define I2C3_BASE_ADDRESS		(0x40005C00)

#define I2C1_R					((volatile I2Cx_REGISTERS*)I2C1_BASE_ADDRESS)
#define I2C2_R              	((volatile I2Cx_REGISTERS*)I2C2_BASE_ADDRESS)
#define I2C3_R              	((volatile I2Cx_REGISTERS*)I2C3_BASE_ADDRESS)


#define	I2C_ENABLE(I2Cn,IS_ENABLE)		I2Cn->CR1.BIT.PE = IS_ENABLE
#define	I2C_POS_ENABLE(I2Cn,IS_ENABLE)	I2Cn->CR1.BIT.POS = IS_ENABLE
#define	I2C_ACK_ENABLE(I2Cn,IS_ENABLE)	I2Cn->CR1.BIT.ACK = IS_ENABLE

#define	I2C_SOFTWARE_RESET(I2Cn)		I2Cn->CR1.BIT.SWRST = 1; 	I2Cn->CR1.BIT.SWRST = 0
#define	I2C_GENERATE_START(I2Cn)		I2Cn->CR1.BIT.START = 1;	while(I2Cn->SR1.BIT.SB == 0)
#define I2C_GENERATE_STOP(I2Cn)			I2Cn->CR1.BIT.STOP = 1

#define	I2C_WAIT_TXE(I2Cn)				while(FALSE == I2Cn->SR1.BIT.TxE)
#define I2C_WAIT_RXNE(I2Cn)				while(FALSE == I2Cn->SR1.BIT.RxNE)
#define I2C_WAIT_BTF(I2Cn)				while(FALSE == I2Cn->SR1.BIT.BTF)
#define	I2C_WAIT_ADDR(I2Cn)				while(FALSE == I2Cn->SR1.BIT.ADDR)
#define	I2C_WAIT_AF(I2Cn)				while(FALSE == I2Cn->SR1.BIT.AF)
#define	I2C_WAIT_STOPF(I2Cn)			while(FALSE == I2Cn->SR1.BIT.STOPF)
#define I2C_WAIT_BUSY(I2Cn)				while(TRUE == I2Cn->SR2.BIT.BUSY)

#define	I2C_GET_BTF(I2Cn)				(I2Cn->SR1.BIT.BTF)

#define	I2C_CLR_ADDR(I2Cn, BUFFER)		BUFFER = I2Cn->SR1.REGISTER;	BUFFER = I2Cn->SR2.REGISTER
#define	I2C_CLR_AF(I2Cn)				I2Cn->SR1.BIT.AF = FALSE
#define	I2C_CLR_STOPF(I2Cn)				I2Cn->CR1.BIT.PE = FALSE

#define	I2C_WRITE_DATA(I2Cn, DATA)		I2Cn->DR.BIT.DR = DATA
#define	I2C_READ_DATA(I2Cn, BUFFER)		BUFFER = ((u8)(I2Cn->DR.BIT.DR))

#define	I2C_WRITE(ADDRESS)				( ((u8)ADDRESS) & (~0x01) )
#define I2C_READ(ADDRESS)				( ((u8)ADDRESS) | (0x01)  )

#define I2C_MEMORY_ADD_MSB(ADDRESS)		((u8) ((((u16)ADDRESS) & 0xFF00) >> 8))
#define I2C_MEMORY_ADD_LSB(ADDRESS)		((u8) (((u16)ADDRESS) & 0x00FF))

#define	I2C_TRISE_CALC(FREQ,X) 			( ((FREQ)<=100000U) ? (X = I2C_APB1_FREQ_IN_MHz+1U) : (X=((I2C_APB1_FREQ_IN_MHz*300U) /1000U) +1U) )



typedef enum
{
	I2C_MASTER_TRANS = (u8)0,
	I2C_MASTER_RECEIVE,
}I2C_MASTER;


#endif
