/*
 *  Sensing.c
 *
 *  Created on: Dec 16, 2022
 *      Author: Hosam
 */

#include "HAL/Sensing.h"

static u16 GLOB_u16TemperatureDegree;
static u16 GLOB_u16GasVoltage;

static f32 GLOB_f32AccelX;
static f32 GLOB_f32AccelY;
static f32 GLOB_f32AccelZ;
static f32 GLOB_f32GyroX;
static f32 GLOB_f32GyroY;
static f32 GLOB_f32GyroZ;


void SEN_vidInit(void)
{
	GLOB_u16GasVoltage			= 0;
	GLOB_u16TemperatureDegree	= 0;
	GLOB_f32AccelX				= 0;
	GLOB_f32AccelY				= 0;
	GLOB_f32AccelZ				= 0;
	GLOB_f32GyroX				= 0;
	GLOB_f32GyroY				= 0;
	GLOB_f32GyroZ				= 0;

	SEN_vidMPU6050Init();
}

void SEN_vidUpdateSensorsData(void)
{
	u8 LOC_u8Byte1 = 0;
	u8 LOC_u8Byte2 = 0;

	GLOB_u16GasVoltage = ADC_u16GetADCValue();

	SEN_vidReadAccel();
	SEN_vidReadGyro();

	//Sequence to read the temperature sensor.
	//SEN_vidStartDHT();
	//switch(SEN_vidCheckDHTResponse())
	//{
	//case TEMP_SEN_OK:
	//{
	//	SEN_u8ReadTemperature();
	//	SEN_u8ReadTemperature();
	//	LOC_u8Byte1 = SEN_u8ReadTemperature();
	//	LOC_u8Byte2 = SEN_u8ReadTemperature();
	//	GLOB_u16TemperatureDegree =  ((LOC_u8Byte1<<8) | LOC_u8Byte2);
	//	GLOB_u16TemperatureDegree /= 10;
	//}
	//break;
	//case TEMP_SEN_ERROR:
	//	GLOB_u16TemperatureDegree = 0;
	//	break;
	//}
}

u16	 SEN_u16GetGasSensor(void)
{ 
	return GLOB_u16GasVoltage;
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

static void SEN_vidStartDHT(void)
{
	GPIO_vidSetPinDirection(TEMPERATURE_PORT, TEMPERATURE_PIN, OUTPUT);
	GPIO_voidSetPinValue(TEMPERATURE_PORT, TEMPERATURE_PIN, LOW);
	TIM_vidDelayms(TIM_2, 18);
	GPIO_vidSetPinDirection(TEMPERATURE_PORT, TEMPERATURE_PIN, INPUT);
}

static TEMPERATURE_SENSOR_RESPONSE SEN_vidCheckDHTResponse(void)
{
	TEMPERATURE_SENSOR_RESPONSE LOC_enuRespone = TEMP_SEN_ERROR;

	TIM_vidDelayus(TIM_2, 40);

	if(LOW == GPIO_u8GetPinValue(TEMPERATURE_PORT, TEMPERATURE_PIN))
	{
		TIM_vidDelayus(TIM_2, 80);

		if(HIGH == GPIO_u8GetPinValue(TEMPERATURE_PORT, TEMPERATURE_PIN))
		{
			LOC_enuRespone = TEMP_SEN_OK;
		}
		else
		{
			LOC_enuRespone = TEMP_SEN_ERROR;
		}
	}
	else
	{
	}
	while(HIGH == GPIO_u8GetPinValue(TEMPERATURE_PORT, TEMPERATURE_PIN));
	return LOC_enuRespone;
}

static u8 SEN_u8ReadTemperature(void)
{
	u8 LOC_u8Byte 	= 0;
	u8 LOC_u8BitNum	= 0;

	for(; LOC_u8BitNum < 8; LOC_u8BitNum++)
	{
		while(LOW == GPIO_u8GetPinValue(TEMPERATURE_PORT, TEMPERATURE_PIN));

		TIM_vidDelayus(TIM_2, 40);

		if(HIGH == GPIO_u8GetPinValue(TEMPERATURE_PORT, TEMPERATURE_PIN))
		{
			SET_BIT(LOC_u8Byte, LOC_u8BitNum);
		}
		else
		{
			CLR_BIT(LOC_u8Byte, LOC_u8BitNum);
		}
		while(HIGH == GPIO_u8GetPinValue(TEMPERATURE_PORT, TEMPERATURE_PIN));
	}

	return LOC_u8Byte;
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
