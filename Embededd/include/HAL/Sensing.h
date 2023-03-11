/*
 *  Sensing.h
 *
 *  Created on: Dec 16, 2022
 *      Author: Hosam
 */
#ifndef	SENSING_H
#define	SENSING_H

#include "LIB/STD_TYPES.h"
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
	GAS_SENSOR = (u8)0,
	TEMPERATURE_SENSOR
}SENSOR_TYPE;

typedef enum
{
	TEMP_SEN_ERROR = (u8)0,
	TEMP_SEN_OK
}TEMPERATURE_SENSOR_RESPONSE;

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
u8	 SEN_u8GetGasPercentage(void);
void SEN_vidGetGyroAccel(f32 * buffer);

static void SEN_vidStartDHT(void);
static u8 SEN_u8ReadTemperature(void);
static TEMPERATURE_SENSOR_RESPONSE SEN_vidCheckDHTResponse(void);

static void SEN_vidMPU6050Init(void);
static void SEN_vidReadAccel(void);
static void SEN_vidReadGyro(void);

#endif	
