/*
 * I2C_config.c
 *
 *  Created on: Nov 2, 2022
 *      Author: Hosam
 */

#include "I2C_private.h"
#include "I2C_config.h"
#include "I2C_interface.h"

I2C_CONFIG	GLOB_ptrStrI2C[NUM_OF_USED_I2C] = {
		[0] = {
				.I2C_x 					= I2C_1,
				.enuAddressingMode		= _7BITS_I2C,
				.enuDualAddress			= DISABLE_I2C_DUAL_ADD,
				.enuI2CMode				= FAST_MODE_I2C,
				.enuDutyCycle			= FM_MODE_DUTY_16_9,
				.enuI2CFreq				= _200KHz,
				.u16SlaveAddress1		= 0x01,
				.u8SlaveAddress2		= (u8)(~I2C_NOT_USED)
		},
		[1] = {
				.I2C_x 					= I2C_2,
				.enuAddressingMode		= _7BITS_I2C,
				.enuDualAddress			= DISABLE_I2C_DUAL_ADD,
				.enuI2CMode				= FAST_MODE_I2C,
				.enuDutyCycle			= FM_MODE_DUTY_1_2,
				.enuI2CFreq				= _400KHz,
				.u16SlaveAddress1		= 0x02,
				.u8SlaveAddress2		= (u8)(~I2C_NOT_USED)
		},
};
