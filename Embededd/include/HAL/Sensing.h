/*
 *  Sensing.h
 *
 *  Created on: Dec 16, 2022
 *      Author: Hosam
 */
#ifndef	SENSING_H
#define	SENSING_H

#include "LIB/STD_TYPES.h"

#include "SERVICES/Delay.h"

#include "MCAL/ADC_interface.h"
#include "MCAL/GPIO_interface.h"
#include "MCAL/TIMER_interface.h"
#include "MCAL/I2C_interface.h"


#define	TEMPERATURE_PORT			PORT_A
#define	TEMPERATURE_PIN				PIN1

#define	MPU6050_ADDRESS_AD0_GND		(0xD0)
#define	MPU6050_ADDRESS_AD0_HIGH	(0xD2)
#define	MPU6050_ADDRESS_7_BITS		(0x68)

typedef enum
{
	SMPLRT_DIV		= 0x19,
	GYRO_CONFIG		= 0x1B,
	ACCEL_CONFIG	= 0x1C,
	ACCEL_XOUT_H	= 0x3B,
	TEMP_OUT_H		= 0x41,
	GYRO_XOUT_H		= 0x43,
	PWR_MGMT_1		= 0x6B,
	WHO_AM_I		= 0x75,
}MPU_REGISTERS;

void SEN_vidInit(void);
void SEN_vidUpdateSensorsData(void);
void SEN_vidUpdateEncoders(void);

u32 SEN_u8GetLeftMotorRPM(void);
u32 SEN_u8GetRightMotorRPM(void);
u8	 SEN_u8GetGasPercentage(void);
u16 SEN_u16GetTemperature(void);
void SEN_vidGetGyroAccel(f32 * buffer);
PIN_VALUE SEN_enmGetPushButton(void);

static void SEN_vidMPU6050Init(void);
static void SEN_vidReadAccel(void);
static void SEN_vidReadGyro(void);

#endif	
