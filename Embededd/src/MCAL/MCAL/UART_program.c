/*
 * UART_program.c
 *
 *  Created on: Sep 24, 2022
 *      Author: ziad
 */
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/UART_config.h"
#include "MCAL/UART_interface.h"
#include "MCAL/UART_private.h"

void UART_vidInit(void)
{
	/*equation to calc BRR from baud rate*/
	volatile f32 LOC_f32Temp 		= 0;
	volatile u16 LOC_u16Mantissa 	= 0;
	volatile u8  LOC_u8Fraction 	= 0;

	LOC_f32Temp 	= ((16000000)/(((float)UART_BAUD_RATE)*16)) ;
	/*mantissa */
	LOC_u16Mantissa = (u16)LOC_f32Temp;
	LOC_f32Temp		-= LOC_u16Mantissa;
	LOC_f32Temp 	*= 16;
	/*approximating fraction to the nearest whole number*/
	if( ( LOC_f32Temp-( (u32) LOC_f32Temp ) )*10 >=5 )
	{
		LOC_f32Temp++;
	}
	/*fraction*/
	LOC_u8Fraction = (u8) LOC_f32Temp ;
	UART->BRR.BIT.DIV_MANTISSA = LOC_u16Mantissa;
	UART->BRR.BIT.DIV_FRACTION = LOC_u8Fraction;
	/*enable Tx */
	UART->CR1.BIT.TE =1;
	/*enable Rx*/
	UART->CR1.BIT.RE =1 ;
	/*enable UART*/
	UART->CR1.BIT.UE = 1;
}

u8 UART_u8Receive(u32 Copy_u32MaxTimeToWait)
{
	u32 LOC_u32Counter =0 ;
	/*poll on data register not empty flag*/
	while(UART->SR.BIT.RXNE==0)
	{
		/*inc counter*/
		LOC_u32Counter++;
		if(LOC_u32Counter==Copy_u32MaxTimeToWait)
		{
			return '#' ;
		}
	}
	/*clear flag by writing zero*/
	UART->SR.BIT.RXNE=0;
	/*return data register when data is ready */
	return UART->DR.BIT.DATA ;
}
void UART_vidTransmitChar(u8 Copy_u8Data)
{
	/*poll on transmission complete flag*/
	while(UART->SR.BIT.TC==0);
	/*clear flag by writing zero*/
	UART->SR.BIT.TC=0;
	/*put data in UART data register*/
	UART->DR.BIT.DATA = Copy_u8Data ;

}
void UART_vidTransmitString(u8 * Copy_u8PtrData)
{
	u32 LOC_u32Counter=0;
	/*loop until null character*/
	while(Copy_u8PtrData[LOC_u32Counter] != '\0')
	{
		UART_vidTransmitChar(Copy_u8PtrData[LOC_u32Counter++]);
	}
}



