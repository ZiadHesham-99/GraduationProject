/*
 * I2C_interface.h
 *
 *  Created on: Oct 5, 2022
 *      Author: Hosam
 */

#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/I2C_private.h"
#include "MCAL/I2C_config.h"

#define	I2C_NOT_USED	0xFFFF

typedef enum
{
	I2C_1 = (u8)0,
	I2C_2,
	I2C_3
}I2C_x;

typedef enum
{
	STANDARD_MODE_I2C = (u8)0,
	FAST_MODE_I2C
}I2C_MODE;

typedef enum
{
	_7BITS_I2C = (u8)0,
	_10BITS_I2C
}I2C_ADD_MODE;

typedef enum
{
	DISABLE_I2C_DUAL_ADD = (u8)0,
	ENABLE_I2C_DUAL_ADD
}I2C_DUAL_ADD;

typedef enum
{
	FM_MODE_DUTY_1_2 = (u8)0,
	FM_MODE_DUTY_16_9,
	STANDARD_MODE_DUTY
}I2C_DUTY_CYCLE;

typedef enum
{
	_25KHz 	= 25000,
	_50KHz 	= 50000,
	_75KHz 	= 75000,
	_100KHz = 100000,
	_150KHz = 150000,
	_200KHz = 200000,
	_250KHz = 250000,
	_300KHz = 300000,
	_350KHz = 350000,
	_400KHz = 400000
}I2C_FREQ;

typedef struct
{
	I2C_x				I2C_x;
	I2C_ADD_MODE		enuAddressingMode;
	I2C_DUAL_ADD		enuDualAddress;
	I2C_MODE			enuI2CMode;
	I2C_DUTY_CYCLE		enuDutyCycle;
	I2C_FREQ			enuI2CFreq;
	u16					u16SlaveAddress1;
	u8					u8SlaveAddress2;
}I2C_CONFIG;

typedef enum
{
	_8BITS_I2C_MEM = (u8)0,
	_16BITS_I2C_MEM
}I2C_MEM_SIZE;

I2C_CONFIG	GLOB_ptrStrI2C[NUM_OF_USED_I2C];

void I2C_vidInit(void);
void I2C_vidMasterTX(I2C_x Copy_enuI2C_x, u8 Copy_u8SlaveAddress, u8 * Copy_u8PtrBffr, u8 Copy_u8Size);
void I2C_vidMasterRX(I2C_x Copy_enuI2C_x, u8 Copy_u8SlaveAddress, u8 * Copy_u8PtrBffr, u8 Copy_u8Size);
void I2C_vidSlaveTX(I2C_x Copy_enuI2C_x, u8 * Copy_u8PtrBffr, u8 Copy_u8Size);
void I2C_vidSlaveRX(I2C_x Copy_enuI2C_x, u8 * Copy_u8PtrBffr, u8 Copy_u8Size);
void I2C_vidMemWrite(I2C_x Copy_enuI2C_x, u8 Copy_u8SlaveAddress, u16 Copy_u16MemAddress, I2C_MEM_SIZE Copy_enuMemSize, u8 * Copy_u8PtrBffr, u8 Copy_u8Size);
void I2C_vidMemRead(I2C_x Copy_enuI2C_x, u8 Copy_u8SlaveAddress, u16 Copy_u16MemAddress, I2C_MEM_SIZE Copy_enuMemSize, u8 * Copy_u8PtrBffr, u8 Copy_u8Size);

#endif
