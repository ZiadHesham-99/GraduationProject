/*
 * SPI_program.c
 *
 *  Created on: Sep 24, 2022
 *      Author: ziad
 */

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include"MCAL/SPI_config.h"
#include"MCAL/SPI_private.h"

#include"MCAL/SPI_interface.h"

void SPI_vidInit(void)
{
	//SPI->CR1.REGISTER = 0x0347;
	/*using undirectional mode */
	SPI->CR1.BIT.BIDIMODE = 0;
	/*this bit has no effect since undirectional mode*/
	SPI->CR1.BIT.BIDIOE =0;
	/*CRC mode is not used*/
	SPI->CR1.BIT.CRCEN =0;
	SPI->CR1.BIT.CRCNEXT =0;
	/*using 8 bit data format*/
	SPI->CR1.BIT.DFF = SPI_DATA_FRAME_FORMAT ;
	/*using full duplex*/
	SPI->CR1.BIT.RXONLY =0;
	/*Slave selction is managed by software */
	SPI->CR1.BIT.SSM = 1;
	/*This bit has no effect since SSM s enabled */
	SPI->CR1.BIT.SSI =1;
	/*MSB first */
	SPI->CR1.BIT.LSBFIRST = 0;
	/*baudrate = f/2 */
	SPI->CR1.BIT.BR = 000;
	/*master mode*/
	SPI->CR1.BIT.MSTR=1;
	/*clock plarity write first*/
	SPI->CR1.BIT.CPOL =1;
	/*clock phase normal high*/
	SPI->CR1.BIT.CPHA = 1;
	/*Enable spi*/
	SPI->CR1.BIT.SPE =1;

}

void SPI_vidSlaveInit(void)
{
	//SPI->CR1.REGISTER = 0x0347;
	/*using undirectional mode */
	SPI->CR1.BIT.BIDIMODE = 0;
	/*this bit has no effect since undirectional mode*/
	SPI->CR1.BIT.BIDIOE =0;
	/*CRC mode is not used*/
	SPI->CR1.BIT.CRCEN =0;
	SPI->CR1.BIT.CRCNEXT =0;
	/*using 8 bit data format*/
	SPI->CR1.BIT.DFF = SPI_DATA_FRAME_FORMAT ;
	/*using full duplex*/
	SPI->CR1.BIT.RXONLY =0;
	/*MSB first */
	SPI->CR1.BIT.LSBFIRST = 0;
	/*Slave mode*/
	SPI->CR1.BIT.MSTR=0;
	/*clock plarity write first*/
	SPI->CR1.BIT.CPOL =1;
	/*clock phase normal high*/
	SPI->CR1.BIT.CPHA = 1;
	/*Enable spi*/
	SPI->CR1.BIT.SPE =1;

}

#if SPI_DATA_FRAME_FORMAT == FRAME_FORMAT_8_BIT
void SPI_vidSendData(u8 Data)
{
	while(SPI->SR.BIT.BSY);
	SPI->DR = Data ;
}

u8 SPI_u8RecieveData(void)
{
	while(SPI->SR.BIT.BSY);
	return SPI->DR ;
}
#else
void SPI_vidSendData(u16 Data){
	while(SPI->SR.BIT.BSY);
	SPI->DR = Data ;
}

u16 SPI_u8RecieveData(void){
	while(SPI->SR.BIT.BSY);
	return SPI->DR ;
}
#endif




