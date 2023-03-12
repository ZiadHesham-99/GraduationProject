/*
 * Communication.c
 *
 *  Created on: March 1, 2022
 *      Author: Hosam
 */
#include<math.h>

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/I2C_interface.h"
#include "MCAL/UART_interface.h"

#include "HAL/Communication.h"

void COM_vidSendToRaspBerryPi(tstrRaspberryPiMsg Copy_strMsg)
{

	/*
	 ************************************************************************************************
                                    SENDING TO RASPBERRY PI FRAME
	 ************************************************************************************************
                        !!SEND@MPU@G@+XXX@+XXX@+XXX@A@+XXXX@+XXXX@+XXXX@CO@+XX%@T@+XX@!!

                                            64 BYTES
	 ************************************************************************************************
	 */


	u8 au8RaspberryPiMsg[64] = {0};
	u8 au8String[]="!!SEND@MPU@G@";
	u8 u8Counter;
	for(u8Counter = 0; u8Counter < 13; u8Counter++)
	{
		au8RaspberryPiMsg[u8Counter] =  au8String[u8Counter];
	}
	u8Counter = 13;
	vidToString(((s32)(Copy_strMsg.s8GyroX)), 3, (au8RaspberryPiMsg+u8Counter));
	au8RaspberryPiMsg[17] = '@';
	u8Counter = 18;
	vidToString(((s32)(Copy_strMsg.s8GyroY)), 3, (au8RaspberryPiMsg+u8Counter));
	au8RaspberryPiMsg[22] = '@';
	u8Counter = 23;
	vidToString(((s32)(Copy_strMsg.s8GyroZ)), 3, (au8RaspberryPiMsg+u8Counter));
	au8RaspberryPiMsg[27] = '@';
	au8RaspberryPiMsg[28] = 'A';
	au8RaspberryPiMsg[29] = '@';
	u8Counter = 30;
	vidToString(((s32)(Copy_strMsg.s16AccelX)), 4, (au8RaspberryPiMsg+u8Counter));
	au8RaspberryPiMsg[35] = '@';
	u8Counter = 36;
	vidToString(((s32)(Copy_strMsg.s16AccelY)), 4, (au8RaspberryPiMsg+u8Counter));
	au8RaspberryPiMsg[41] = '@';
	u8Counter = 42;
	vidToString(((s32)(Copy_strMsg.s16AccelZ)), 4, (au8RaspberryPiMsg+u8Counter));
	au8RaspberryPiMsg[47] = '@';
	au8RaspberryPiMsg[48] = 'C';
	au8RaspberryPiMsg[49] = 'O';
	au8RaspberryPiMsg[50] = '@';
	u8Counter = 51;
	vidToString(((s32)(Copy_strMsg.u8GasPercentage)), 2, (au8RaspberryPiMsg+u8Counter));
	au8RaspberryPiMsg[54] = '%';
	au8RaspberryPiMsg[55] = '@';
	au8RaspberryPiMsg[56] = 'T';
	au8RaspberryPiMsg[57] = '@';
	u8Counter = 58;
	vidToString(((s32)(Copy_strMsg.u8Temperatue)), 2, (au8RaspberryPiMsg+u8Counter));
	au8RaspberryPiMsg[61] = '@';
	au8RaspberryPiMsg[62] = '!';
	au8RaspberryPiMsg[63] = '!';

	/*for(u8Counter = 0; u8Counter < 58; u8Counter++)
    {
        UART_vidTransmitChar(au8RaspberryPiMsg[u8Counter]);
    }

    UART_vidTransmitChar('\n');
    UART_vidTransmitChar('\n');
    UART_vidTransmitChar('\n');*/
	I2C_vidSlaveTX(I2C_2, au8RaspberryPiMsg, 64);
}

static void vidToString(s32 Copy_s32Num, u8 Copy_u8DigitsNum, u8 * Copy_pu8Bffr)
{

	u8  u8Counter;
	u32 u32Temp = 0;
	BOOL bFirstTime = TRUE;

	u32Temp = (u16)(pow(10.0, ((f64)(Copy_u8DigitsNum-1))));

	if(Copy_s32Num > 0)
	{
		Copy_pu8Bffr[0] = '+';
	}
	else
	{
		Copy_pu8Bffr[0] = '-';
		Copy_s32Num *=(-1);
	}
	for(u8Counter = 1; u8Counter <= Copy_u8DigitsNum; u8Counter++)
	{
		if(TRUE == bFirstTime)
		{
			Copy_pu8Bffr[u8Counter] = (Copy_s32Num/u32Temp)+(0x30);
			bFirstTime = FALSE;
		}
		else
		{
			Copy_pu8Bffr[u8Counter] = ((Copy_s32Num%u32Temp)/(u32Temp/10))+(0x30);
			u32Temp /= 10;
		}
	}
}

static s32  s32ToInteger(u8 * Copy_pu8Bffr, u8 Copy_u8DigitsNum)
{
	s8  s8Counter = 0;
	s32 s32Temp = 0;
	s32 s32Number = 0;
	s32 s32Tens = 10;

	BOOL bFirstTime = TRUE;

	for(s8Counter = (Copy_u8DigitsNum-1); s8Counter > 0; s8Counter--)
	{
		if(TRUE == bFirstTime)
		{
			s32Number = (s16)((Copy_pu8Bffr[s8Counter])-(0x30));
			bFirstTime = FALSE;
		}
		else
		{
			s32Temp = (((Copy_pu8Bffr[s8Counter])-(0x30))*s32Tens);
			s32Number += s32Temp;
			s32Tens *=10;
		}
	}
	if(Copy_pu8Bffr[0] == '-')
	{
		s32Number *= (-1);
	}
	return s32Number;
}

