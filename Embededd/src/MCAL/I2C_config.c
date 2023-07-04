/*
 * I2C_config.c
 *
 *  Created on: Oct 5, 2022
 *      Author: Hosam
 */

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/I2C_private.h"
#include "MCAL/I2C_config.h"
#include "MCAL/I2C_interface.h"

I2C_CONFIG	GLOB_ptrStrI2C[NUM_OF_USED_I2C] = 
{
		[0] = 
		{
				.I2C_x 					= I2C_2,
				.enuAddressingMode		= _7BITS_I2C,
				.enuDualAddress			= DISABLE_I2C_DUAL_ADD,
				.enuI2CMode				= STANDARD_MODE_I2C,
				.enuDutyCycle			= STANDARD_MODE_DUTY,
				.enuI2CFreq				= _100KHz,
				.u16SlaveAddress1		= 0x70,
				.u8SlaveAddress2		= (~I2C_NOT_USED)
		},
		[1] = 
		{
				.I2C_x 					= I2C_1,
				.enuAddressingMode		= _7BITS_I2C,
				.enuDualAddress			= DISABLE_I2C_DUAL_ADD,
				.enuI2CMode				= FAST_MODE_I2C,
				.enuDutyCycle			= FM_MODE_DUTY_1_2,
				.enuI2CFreq				= _400KHz,
				.u16SlaveAddress1		= 0x00,
				.u8SlaveAddress2		= (~I2C_NOT_USED)
		},
};
