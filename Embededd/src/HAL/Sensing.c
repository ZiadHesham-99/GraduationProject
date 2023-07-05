/*
 *  Sensing.c
 *
 *  Created on: Dec 16, 2022
 *      Author: Hosam
 */

#include "HAL/Sensing.h"

static u8 GLOB_u8GasPercentage;

static u16 LOC_u16TemperatureDegree;

static f32 GLOB_f32GyroX;
static f32 GLOB_f32GyroY;
static f32 GLOB_f32GyroZ;
static f32 GLOB_f32AccelX;
static f32 GLOB_f32AccelY;
static f32 GLOB_f32AccelZ;
static tstrADCConfig	LOC_strADCConfigMQ7;
static tstrADCConfig	LOC_strADCConfigLM35;
static u32	LOC_u32LeftMotorRPM;
static u32	LOC_u32RightMotorRPM;

void SEN_vidInit(void)
{
	GLOB_u8GasPercentage		= 0;
	LOC_u16TemperatureDegree 	= 0;
	GLOB_f32AccelX				= 0;
	GLOB_f32AccelY				= 0;
	GLOB_f32AccelZ				= 0;
	GLOB_f32GyroX				= 0;
	GLOB_f32GyroY				= 0;
	GLOB_f32GyroZ				= 0;
	LOC_u32LeftMotorRPM			= 0;
	LOC_u32RightMotorRPM		= 0;

	LOC_strADCConfigMQ7.enmAlignment = RIGHT_ALIGNMENT;
	LOC_strADCConfigMQ7.enmChannelNum	= CHANNEL0_ADC;
	LOC_strADCConfigMQ7.enmPrescaler	= _2_PRESCALER;
	LOC_strADCConfigMQ7.enmResolution	= _12_BITS_ADC;
	LOC_strADCConfigMQ7.enmSampleTime  = _15_CYCLES;

	LOC_strADCConfigLM35.enmAlignment 	= RIGHT_ALIGNMENT;
	LOC_strADCConfigLM35.enmChannelNum  = CHANNEL1_ADC;
	LOC_strADCConfigLM35.enmPrescaler	= _4_PRESCALER;
	LOC_strADCConfigLM35.enmResolution  = _12_BITS_ADC;
	LOC_strADCConfigLM35.enmSampleTime  = _480_CYCLES;

	TIM_vidICStart(TIM_3, TIM_CHANNEL1);
	TIM_vidICStart(TIM_3, TIM_CHANNEL2);

	SEN_vidMPU6050Init();
}

void SEN_vidUpdateSensorsData(void)
{

	ADC_vidInit(LOC_strADCConfigMQ7);
	GLOB_u8GasPercentage = ((u8)(ADC_u16GetADCValue(CHANNEL0_ADC)/41));

	ADC_vidInit(LOC_strADCConfigLM35);
	LOC_u16TemperatureDegree = ADC_u16GetADCValue(CHANNEL1_ADC);

	SEN_vidReadAccel();
	SEN_vidReadGyro();
}

void SEN_vidUpdateEncoders(void)
{
	u32 u32PlusesLeft = 0;
	u32 u32PlusesRight = 0;

	u32PlusesLeft = TIM_u32GetPlusesCapturedDelayms(TIM_3, TIM_CHANNEL1, 10);
	u32PlusesRight = TIM_u32GetPlusesCapturedDelayms(TIM_3, TIM_CHANNEL2, 10);

	LOC_u32LeftMotorRPM = (u32PlusesLeft * 30 * 100)/531;
	LOC_u32RightMotorRPM = (u32PlusesRight * 30 * 100)/531;;
}

u32 SEN_u8GetLeftMotorRPM(void)
{
	return (u8)LOC_u32LeftMotorRPM;
}

u32 SEN_u8GetRightMotorRPM(void)
{
	return (u8)LOC_u32RightMotorRPM;
}

u8 SEN_u8GetGasPercentage(void)
{ 
	return GLOB_u8GasPercentage;
}

u16 SEN_u16GetTemperature(void)
{
	return LOC_u16TemperatureDegree;
}

void SEN_vidGetGyroAccel(f32 * buffer)
{
	buffer[0] = GLOB_f32AccelX;
	buffer[1] = GLOB_f32AccelY;
	buffer[2] = GLOB_f32AccelZ;
	buffer[3] = GLOB_f32GyroX;
	buffer[4] = GLOB_f32GyroY;
	buffer[5] = GLOB_f32GyroZ;

}

PIN_VALUE SEN_enmGetPushButton(void)
{
	Delay_us(50);
	return GPIO_u8GetPinValue(PORT_A, PIN10);
}

static void SEN_vidMPU6050Init(void)
{
	u8 LOC_u8Check = 0;
	u8 LOC_u8Data;

	/*
	 * Checking if the sensor is working by reading WHO_AM_I register. 
	 * The sensor should return MPU6050_ADDRESS_7_BITS.
	 */
	I2C_vidMemRead(I2C_1, MPU6050_ADDRESS_AD0_GND, WHO_AM_I, _8BITS_I2C_MEM, &LOC_u8Check, 1);
	if(MPU6050_ADDRESS_7_BITS == LOC_u8Check)
	{
		/*
		 * Waking the sensor up by writing 0x00 to PWR_MGMT_1 Register.
		 */
		LOC_u8Data = 0x00;
		I2C_vidMemWrite(I2C_1, MPU6050_ADDRESS_AD0_GND, PWR_MGMT_1, _8BITS_I2C_MEM, &LOC_u8Data, 1);

		/*
		 * Setting the Data Output Rate or the Sample Rate by writing in SMPLRT_DIV Register.
		 * For 1 KHz Sample Rate, the value should be 0x07.
		 */
		LOC_u8Data = 0x07;
		I2C_vidMemWrite(I2C_1, MPU6050_ADDRESS_AD0_GND, SMPLRT_DIV, _8BITS_I2C_MEM, &LOC_u8Data, 1);

		/*
		 * Configuring the Full Scale Range of the Accel. and the Gyroscope by writing 0x00 to GYRO_CONFIG
		 * and ACCEL_CONFIG Registers.
		 * 
		 * 				FULL SCALE FOR GYROSCOPE IS 		+-250 °/s
		 * 				FULL SCALE FOR ACCELEROMETER IS 	+-2g
		 */
		LOC_u8Data = 0x00;
		I2C_vidMemWrite(I2C_1, MPU6050_ADDRESS_AD0_GND, ACCEL_CONFIG, _8BITS_I2C_MEM, &LOC_u8Data, 1);
		I2C_vidMemWrite(I2C_1, MPU6050_ADDRESS_AD0_GND, GYRO_CONFIG, _8BITS_I2C_MEM, &LOC_u8Data, 1);
	}
	else
	{
	}
}

static void SEN_vidReadAccel(void)
{
	u8 	LOC_u8AccelData[6];
	s16 LOC_s16AccelRawX = 0;
	s16 LOC_s16AccelRawY = 0;
	s16 LOC_s16AccelRawZ = 0;

	I2C_vidMemRead(I2C_1, MPU6050_ADDRESS_AD0_GND, ACCEL_XOUT_H, _8BITS_I2C_MEM, LOC_u8AccelData, 6);

	LOC_s16AccelRawX 	= (s16)((LOC_u8AccelData[0]<<8 ) | LOC_u8AccelData[1]);
	LOC_s16AccelRawY 	= (s16)((LOC_u8AccelData[2]<<8 ) | LOC_u8AccelData[3]);
	LOC_s16AccelRawZ 	= (s16)((LOC_u8AccelData[4]<<8 ) | LOC_u8AccelData[5]);

	GLOB_f32AccelX 		= (f32)(((f32)LOC_s16AccelRawX)/16384.0); 			
	GLOB_f32AccelY		= (f32)(((f32)LOC_s16AccelRawY)/16384.0);
	GLOB_f32AccelZ		= (f32)(((f32)LOC_s16AccelRawZ)/16384.0);	
}

static void SEN_vidReadGyro(void)
{
	u8 	LOC_u8GyroData[6];
	s16 LOC_s16GyroRawX = 0;
	s16 LOC_s16GyroRawY = 0;
	s16 LOC_s16GyroRawZ = 0;

	I2C_vidMemRead(I2C_1, MPU6050_ADDRESS_AD0_GND, GYRO_XOUT_H, _8BITS_I2C_MEM, LOC_u8GyroData, 6);

	LOC_s16GyroRawX = (s16)((LOC_u8GyroData[0]<<8 ) | LOC_u8GyroData[1]);
	LOC_s16GyroRawY = (s16)((LOC_u8GyroData[2]<<8 ) | LOC_u8GyroData[3]);
	LOC_s16GyroRawZ = (s16)((LOC_u8GyroData[4]<<8 ) | LOC_u8GyroData[5]);

	GLOB_f32GyroX 	= (f32)(((f32)LOC_s16GyroRawX)/131.0); 			
	GLOB_f32GyroY	= (f32)(((f32)LOC_s16GyroRawY)/131.0);
	GLOB_f32GyroZ	= (f32)(((f32)LOC_s16GyroRawZ)/131.0); 
}
