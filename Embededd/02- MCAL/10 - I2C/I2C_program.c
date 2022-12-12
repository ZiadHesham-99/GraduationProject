/*
 * I2C_program.c
 *
 *  Created on: Nov 2, 2022
 *      Author: Hosam
 */

#include "../../01- LIB/01- TYPES/STD_TYPES.h"
#include "../../01- LIB/02- BIT_MATH/BIT_MATH.h"

//#include "STD_TYPES.h"
//#include "BIT_MATH.h"

#include "I2C_private.h"
#include "I2C_config.h"
#include "I2C_interface.h"

static u32  I2C_u32CRRHanlder(I2C_DUTY_CYCLE Copy_enuDutyCycle, u32 Copy_u32FreqDesired);
static void I2C_vidSendSlaveAddress(I2C_x Copy_enuI2C_x, u8 Copy_u16Address, I2C_MASTER Copy_enuMasterState);
static void I2C_vidAddressHandler(I2C_x Copy_enuI2C_x, I2C_ADD_MODE AddMode, u16 Add1, I2C_DUAL_ADD DualMode, u8 Add2);
static void I2C_vidWriteMemoryHandler(I2C_x Copy_enuI2C_x, u8 Copy_u8SlaveAddress, u16 Copy_u16MemAddress, I2C_MEM_SIZE Copy_enuMemSize);
static void I2C_vidReadMemoryHandler(I2C_x Copy_enuI2C_x, u8 Copy_u8SlaveAddress, u16 Copy_u16MemAddress, I2C_MEM_SIZE Copy_enuMemSize);


void I2C_vidInit(void)
{
	u8 	LOC_u8Counter;
	u32	LOC_u32CRRValue;
	u32 LOC_u32TRISEValue;
	I2C_CONFIG LOC_strI2C;
	for(LOC_u8Counter = 0; LOC_u8Counter < NUM_OF_USED_I2C; LOC_u8Counter++)
	{
		LOC_strI2C 							= GLOB_ptrStrI2C[LOC_u8Counter];
		switch(LOC_strI2C.I2C_x)
		{
		case I2C_1 :
		{
			I2C1_R->CR1.BIT.SWRST		= 1;
			I2C1_R->CR1.BIT.PE		= 0;
			I2C1_R->CR1.BIT.SWRST		= 0;
			I2C1_R->CR1.BIT.NOSTRETCH = 0;
			I2C1_R->CR1.BIT.SMBUS		= 0;

			I2C1_R->CR2.BIT.FREQ		= I2C_APB1_FREQ_IN_MHz;

			I2C_vidAddressHandler(I2C_1 , LOC_strI2C.enuAddressingMode, LOC_strI2C.u16SlaveAddress1, LOC_strI2C.enuDualAddress, LOC_strI2C.u8SlaveAddress2);

			I2C1_R->CCR.BIT.F_S		= LOC_strI2C.enuI2CMode;

			if(LOC_strI2C.enuI2CMode == STANDARD_MODE_I2C)
			{
				if(LOC_strI2C.enuI2CFreq > _100KHz)
				{
					LOC_strI2C.enuI2CFreq = _100KHz;
				}
				LOC_u32CRRValue = I2C_u32CRRHanlder(2 ,LOC_strI2C.enuI2CFreq);
				if(LOC_u32CRRValue < 4)
				{
					LOC_u32CRRValue = 4;
				}
				I2C1_R->CCR.BIT.CCR	= LOC_u32CRRValue;
			}
			else if(LOC_strI2C.enuI2CMode == FAST_MODE_I2C)
			{
				I2C1_R->CCR.BIT.DUTY	= LOC_strI2C.enuDutyCycle;
				if(LOC_strI2C.enuI2CFreq > _400KHz)
				{
					LOC_strI2C.enuI2CFreq = _400KHz;
				}
				LOC_u32CRRValue = I2C_u32CRRHanlder(LOC_strI2C.enuDutyCycle,LOC_strI2C.enuI2CFreq);
				if(LOC_u32CRRValue < 1)
				{
					LOC_u32CRRValue = 1;
				}
				I2C1_R->CCR.BIT.CCR	= LOC_u32CRRValue /*0x140*/;
			}
			else{}
			I2C_TRISE_CALC(LOC_strI2C.enuI2CFreq,LOC_u32TRISEValue);
			I2C1_R->TRISE.BIT.TRISE	= LOC_u32TRISEValue /*0x21*/;
		}
		break;
		case I2C_2 :
		{
			I2C2_R->CR1.BIT.SWRST		= 1;
			I2C2_R->CR1.BIT.PE			= 0;
			I2C2_R->CR1.BIT.SWRST		= 0;
			I2C2_R->CR1.BIT.NOSTRETCH 	= 0;
			I2C2_R->CR1.BIT.SMBUS		= 0;

			I2C2_R->CR2.BIT.FREQ		= I2C_APB1_FREQ_IN_MHz;

			I2C_vidAddressHandler(I2C_2 , LOC_strI2C.enuAddressingMode, LOC_strI2C.u16SlaveAddress1, LOC_strI2C.enuDualAddress, LOC_strI2C.u8SlaveAddress2);

			I2C2_R->CCR.BIT.F_S		= LOC_strI2C.enuI2CMode;

			if(LOC_strI2C.enuI2CMode == STANDARD_MODE_I2C)
			{
				if(LOC_strI2C.enuI2CFreq > _100KHz)
				{
					LOC_strI2C.enuI2CFreq = _100KHz;
				}
				LOC_u32CRRValue = I2C_u32CRRHanlder(2 ,LOC_strI2C.enuI2CFreq);
				if(LOC_u32CRRValue < 4)
				{
					LOC_u32CRRValue = 4;
				}
				I2C2_R->CCR.BIT.CCR	= LOC_u32CRRValue;
			}
			else if(LOC_strI2C.enuI2CMode == FAST_MODE_I2C)
			{
				I2C2_R->CCR.BIT.DUTY	= LOC_strI2C.enuDutyCycle;
				if(LOC_strI2C.enuI2CFreq > _400KHz)
				{
					LOC_strI2C.enuI2CFreq = _400KHz;
				}
				LOC_u32CRRValue = I2C_u32CRRHanlder(LOC_strI2C.enuDutyCycle,LOC_strI2C.enuI2CFreq);
				if(LOC_u32CRRValue < 1)
				{
					LOC_u32CRRValue = 1;
				}
				I2C2_R->CCR.BIT.CCR	= LOC_u32CRRValue;
			}
			else{}
			I2C_TRISE_CALC(LOC_strI2C.enuI2CFreq,LOC_u32TRISEValue);
			I2C2_R->TRISE.BIT.TRISE	= LOC_u32TRISEValue;
		}
		break;
		case I2C_3 :
		{
			I2C3_R->CR1.BIT.SWRST		= 1;
			I2C3_R->CR1.BIT.PE			= 0;
			I2C3_R->CR1.BIT.SWRST		= 0;
			I2C3_R->CR1.BIT.NOSTRETCH	= 0;
			I2C3_R->CR1.BIT.SMBUS		= 0;

			I2C3_R->CR2.BIT.FREQ		= I2C_APB1_FREQ_IN_MHz;

			I2C_vidAddressHandler(I2C_1 , LOC_strI2C.enuAddressingMode, LOC_strI2C.u16SlaveAddress1, LOC_strI2C.enuDualAddress, LOC_strI2C.u8SlaveAddress2);

			I2C3_R->CCR.BIT.F_S		= LOC_strI2C.enuI2CMode;

			if(LOC_strI2C.enuI2CMode == STANDARD_MODE_I2C)
			{
				if(LOC_strI2C.enuI2CFreq > _100KHz)
				{
					LOC_strI2C.enuI2CFreq = _100KHz;
				}
				LOC_u32CRRValue = I2C_u32CRRHanlder(2 ,LOC_strI2C.enuI2CFreq);
				if(LOC_u32CRRValue < 4)
				{
					LOC_u32CRRValue = 4;
				}
				I2C3_R->CCR.BIT.CCR	= LOC_u32CRRValue;
			}
			else if(LOC_strI2C.enuI2CMode == FAST_MODE_I2C)
			{
				I2C3_R->CCR.BIT.DUTY	= LOC_strI2C.enuDutyCycle;
				if(LOC_strI2C.enuI2CFreq > _400KHz)
				{
					LOC_strI2C.enuI2CFreq = _400KHz;
				}
				LOC_u32CRRValue = I2C_u32CRRHanlder(LOC_strI2C.enuDutyCycle,LOC_strI2C.enuI2CFreq);
				if(LOC_u32CRRValue < 1)
				{
					LOC_u32CRRValue = 1;
				}
				I2C3_R->CCR.BIT.CCR	= LOC_u32CRRValue;
			}
			else{}
			I2C_TRISE_CALC(LOC_strI2C.enuI2CFreq,LOC_u32TRISEValue);
			I2C3_R->TRISE.BIT.TRISE	= LOC_u32TRISEValue;
		}
		break;
		default :
			break;
		}//end of switch
	}//end of loop
}

void I2C_vidMasterTX(I2C_x Copy_enuI2C_x, u8 Copy_u8SlaveAddress, u8 * Copy_u8PtrBffr, u8 Copy_u8Size)
{
	u8 	LOC_u8Counter;

	switch(Copy_enuI2C_x)
	{
	case I2C_1 :
	{
		I2C1_R->CR1.BIT.PE 		= 1;
		I2C1_R->CR1.BIT.POS		= 0;
		I2C1_R->CR1.BIT.ACK		= 1;
		I2C1_R->CR1.BIT.START 	= 1;
		while(I2C1_R->SR1.BIT.SB == 0);

		I2C_vidSendSlaveAddress(I2C_1, Copy_u8SlaveAddress, I2C_MASTER_TRANS);

		for(LOC_u8Counter = 0; LOC_u8Counter < Copy_u8Size; LOC_u8Counter++)
		{
			while(I2C1_R->SR1.BIT.TxE == 0);
			I2C1_R->DR.BIT.DR = Copy_u8PtrBffr[LOC_u8Counter];
		}
		while(I2C1_R->SR1.BIT.BTF == 0);

		I2C1_R->CR1.BIT.STOP = 1;

		I2C1_R->CR1.BIT.PE = 0;
	}
	break;
	case I2C_2 :
	{
		I2C2_R->CR1.BIT.PE 		= 1;
		I2C2_R->CR1.BIT.POS		= 0;
		I2C2_R->CR1.BIT.ACK		= 1;
		I2C2_R->CR1.BIT.START 	= 1;
		while(I2C2_R->SR1.BIT.SB == 0);

		I2C_vidSendSlaveAddress(I2C_2, Copy_u8SlaveAddress, I2C_MASTER_TRANS);

		for(LOC_u8Counter = 0; LOC_u8Counter < Copy_u8Size; LOC_u8Counter++)
		{
			while(I2C2_R->SR1.BIT.TxE == 0);
			I2C2_R->DR.BIT.DR = Copy_u8PtrBffr[LOC_u8Counter];
		}
		while(I2C2_R->SR1.BIT.BTF == 0);

		I2C2_R->CR1.BIT.STOP = 1;
		I2C2_R->CR1.BIT.PE = 0;
	}
	break;
	case I2C_3 :
	{
		I2C3_R->CR1.BIT.PE 		= 1;
		I2C3_R->CR1.BIT.POS		= 0;
		I2C3_R->CR1.BIT.ACK		= 1;
		I2C3_R->CR1.BIT.START 	= 1;
		while(I2C3_R->SR1.BIT.SB == 0);

		I2C_vidSendSlaveAddress(I2C_3, Copy_u8SlaveAddress, I2C_MASTER_TRANS);

		for(LOC_u8Counter = 0; LOC_u8Counter < Copy_u8Size; LOC_u8Counter++)
		{
			while(I2C3_R->SR1.BIT.TxE == 0);
			I2C3_R->DR.BIT.DR = Copy_u8PtrBffr[LOC_u8Counter];
		}
		while(I2C3_R->SR1.BIT.BTF == 0);

		I2C3_R->CR1.BIT.STOP = 1;

		I2C3_R->CR1.BIT.PE = 0;
	}
	break;
	default :
		break;
	}
}

void I2C_vidMasterRX(I2C_x Copy_enuI2C_x, u8 Copy_u8SlaveAddress, u8 * Copy_u8PtrBffr, u8 Copy_u8Size)
{
	u8 	LOC_u8Counter 	= 0;
	s8 	LOC_s8Size		= (s8)(Copy_u8Size-1);
	u32 LOC_u32Temp		= 0;

	switch(Copy_enuI2C_x)
	{
	case I2C_1 :
	{
		I2C1_R->CR1.BIT.PE 		= 1;
		I2C1_R->CR1.BIT.POS		= 0;
		I2C1_R->CR1.BIT.ACK		= 1;
		I2C1_R->CR1.BIT.START 	= 1;
		while(I2C1_R->SR1.BIT.SB == 0);
		I2C_vidSendSlaveAddress(I2C_1, Copy_u8SlaveAddress, I2C_MASTER_RECEIVE);
		while(LOC_s8Size >= 0)
		{
			if(LOC_s8Size <= 2)
			{
				switch(LOC_s8Size)
				{
				case 0 :
				{
					LOC_s8Size--;
					/* Clear ACK */
					I2C1_R->CR1.BIT.ACK = 0;
					/* Generate STOP */
					I2C1_R->CR1.BIT.STOP = 1;
					/* Clear ADDR */
					LOC_u32Temp = I2C1_R->SR1.REGISTER;
					LOC_u32Temp = I2C1_R->SR2.REGISTER;
					/* Read DR */
					while(I2C1_R->SR1.BIT.RxNE == 0);
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C1_R->DR.BIT.DR;
				}
				break;
				case 1 :
				{
					/* Clear ACK */
					I2C1_R->CR1.BIT.ACK = 0;

					/* Set POS */
					I2C1_R->CR1.BIT.POS = 1;

					/* Clear ADDR */
					LOC_u32Temp = I2C1_R->SR1.REGISTER;
					LOC_u32Temp = I2C1_R->SR2.REGISTER;

					/* Wait BTF */
					while(I2C1_R->SR1.BIT.BTF == 0);

					/* Generate STOP */
					I2C1_R->CR1.BIT.STOP = 1;

					/* Read Data */
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C1_R->DR.BIT.DR;
					LOC_s8Size--;
					while(I2C1_R->SR1.BIT.RxNE == 0);
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C1_R->DR.BIT.DR;
					LOC_s8Size--;
				}
				break;
				default :
				{
					/* Set ACK */
					I2C1_R->CR1.BIT.ACK = 1;

					/* Clear ADDR */
					LOC_u32Temp = I2C1_R->SR1.REGISTER;
					LOC_u32Temp = I2C1_R->SR2.REGISTER;

					/* Wait BTF */
					while(I2C1_R->SR1.BIT.BTF == 0);

					/* Clear ACK */
					I2C1_R->CR1.BIT.ACK = 0;

					/* Read Data */
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C1_R->DR.BIT.DR;
					LOC_s8Size--;

					/* Wait BTF */
					while(I2C1_R->SR1.BIT.BTF == 0);

					/* Generate STOP */
					I2C1_R->CR1.BIT.STOP = 1;

					/* Read Data */
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C1_R->DR.BIT.DR;
					LOC_s8Size--;
					while(I2C1_R->SR1.BIT.RxNE == 0);
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C1_R->DR.BIT.DR;
					LOC_s8Size--;
				}
				break;
				}//end of switch
			}
			else
			{
				/* Read DR */
				while(I2C1_R->SR1.BIT.RxNE == 0);
				Copy_u8PtrBffr[LOC_u8Counter++] = I2C1_R->DR.BIT.DR;
				LOC_s8Size--;
				if(I2C1_R->SR1.BIT.BTF == 1)
				{
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C1_R->DR.BIT.DR;
					LOC_s8Size--;
				}
			}
		}
		I2C1_R->CR1.BIT.PE 	= 0;
	}
	break;
	case I2C_2 :
	{
		I2C2_R->CR1.BIT.PE 	= 1;
		I2C2_R->CR1.BIT.POS	= 0;
		I2C2_R->CR1.BIT.ACK		= 1;
		I2C2_R->CR1.BIT.START 	= 1;
		while(I2C2_R->SR1.BIT.SB == 0);
		I2C_vidSendSlaveAddress(I2C_2, Copy_u8SlaveAddress, I2C_MASTER_RECEIVE);
		while(LOC_s8Size >= 0)
		{
			if(LOC_s8Size <= 2)
			{
				switch(LOC_s8Size)
				{
				case 0 :
				{
					LOC_s8Size--;
					/* Clear ACK */
					I2C2_R->CR1.BIT.ACK = 0;
					/* Generate STOP */
					I2C2_R->CR1.BIT.STOP = 1;
					/* Clear ADDR */
					LOC_u32Temp = I2C2_R->SR1.REGISTER;
					LOC_u32Temp = I2C2_R->SR2.REGISTER;
					/* Read DR */
					while(I2C2_R->SR1.BIT.RxNE == 0);
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C2_R->DR.BIT.DR;
				}
				break;
				case 1 :
				{
					/* Clear ACK */
					I2C2_R->CR1.BIT.ACK = 0;

					/* Set POS */
					I2C2_R->CR1.BIT.POS = 1;

					/* Clear ADDR */
					LOC_u32Temp = I2C2_R->SR1.REGISTER;
					LOC_u32Temp = I2C2_R->SR2.REGISTER;

					/* Wait BTF */
					while(I2C2_R->SR1.BIT.BTF == 0);

					/* Generate STOP */
					I2C2_R->CR1.BIT.STOP = 1;

					/* Read Data */
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C2_R->DR.BIT.DR;
					LOC_s8Size--;
					while(I2C2_R->SR1.BIT.RxNE == 0);
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C2_R->DR.BIT.DR;
					LOC_s8Size--;
				}
				break;
				default :
				{
					/* Set ACK */
					I2C1_R->CR1.BIT.ACK = 1;

					/* Clear ADDR */
					LOC_u32Temp = I2C1_R->SR1.REGISTER;
					LOC_u32Temp = I2C1_R->SR2.REGISTER;

					/* Wait BTF */
					while(I2C2_R->SR1.BIT.BTF == 0);

					/* Clear ACK */
					I2C2_R->CR1.BIT.ACK = 0;

					/* Read Data */
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C2_R->DR.BIT.DR;
					LOC_s8Size--;

					/* Wait BTF */
					while(I2C2_R->SR1.BIT.BTF == 0);

					/* Generate STOP */
					I2C2_R->CR1.BIT.STOP = 1;

					/* Read Data */
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C2_R->DR.BIT.DR;
					LOC_s8Size--;
					while(I2C2_R->SR1.BIT.RxNE == 0);
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C2_R->DR.BIT.DR;
					LOC_s8Size--;
				}
				break;
				}//end of switch
			}
			else
			{
				/* Read DR */
				while(I2C2_R->SR1.BIT.RxNE == 0);
				Copy_u8PtrBffr[LOC_u8Counter++] = I2C2_R->DR.BIT.DR;
				LOC_s8Size--;
				if(I2C2_R->SR1.BIT.BTF == 1)
				{
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C2_R->DR.BIT.DR;
					LOC_s8Size--;
				}
			}
		}
		I2C2_R->CR1.BIT.PE 	= 0;
	}
	break;
	case I2C_3 :
	{
		I2C3_R->CR1.BIT.PE 	= 1;
		I2C3_R->CR1.BIT.POS	= 0;
		I2C3_R->CR1.BIT.ACK		= 1;
		I2C3_R->CR1.BIT.START 	= 1;
		while(I2C3_R->SR1.BIT.SB == 0);
		I2C_vidSendSlaveAddress(I2C_3, Copy_u8SlaveAddress, I2C_MASTER_RECEIVE);
		while(LOC_s8Size >= 0)
		{
			if(LOC_s8Size <= 2)
			{
				switch(LOC_s8Size)
				{
				case 0 :
				{
					LOC_s8Size--;
					/* Clear ACK */
					I2C3_R->CR1.BIT.ACK = 0;
					/* Generate STOP */
					I2C3_R->CR1.BIT.STOP = 1;
					/* Clear ADDR */
					LOC_u32Temp = I2C3_R->SR1.REGISTER;
					LOC_u32Temp = I2C3_R->SR2.REGISTER;
					/* Read DR */
					while(I2C3_R->SR1.BIT.RxNE == 0);
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C3_R->DR.BIT.DR;
				}
				break;
				case 1 :
				{
					/* Clear ACK */
					I2C3_R->CR1.BIT.ACK = 0;

					/* Set POS */
					I2C3_R->CR1.BIT.POS = 1;

					/* Clear ADDR */
					LOC_u32Temp = I2C3_R->SR1.REGISTER;
					LOC_u32Temp = I2C3_R->SR2.REGISTER;

					/* Wait BTF */
					while(I2C3_R->SR1.BIT.BTF == 0);

					/* Generate STOP */
					I2C3_R->CR1.BIT.STOP = 1;

					/* Read Data */
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C3_R->DR.BIT.DR;
					LOC_s8Size--;
					while(I2C3_R->SR1.BIT.RxNE == 0);
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C3_R->DR.BIT.DR;
					LOC_s8Size--;
				}
				break;
				default :
				{
					/* Set ACK */
					I2C1_R->CR1.BIT.ACK = 1;

					/* Clear ADDR */
					LOC_u32Temp = I2C1_R->SR1.REGISTER;
					LOC_u32Temp = I2C1_R->SR2.REGISTER;

					/* Wait BTF */
					while(I2C3_R->SR1.BIT.BTF == 0);

					/* Clear ACK */
					I2C3_R->CR1.BIT.ACK = 0;

					/* Read Data */
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C3_R->DR.BIT.DR;
					LOC_s8Size--;

					/* Wait BTF */
					while(I2C3_R->SR1.BIT.BTF == 0);

					/* Generate STOP */
					I2C3_R->CR1.BIT.STOP = 1;

					/* Read Data */
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C3_R->DR.BIT.DR;
					LOC_s8Size--;
					while(I2C3_R->SR1.BIT.RxNE == 0);
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C3_R->DR.BIT.DR;
					LOC_s8Size--;
				}
				break;
				}//end of switch
			}
			else
			{
				/* Read DR */
				while(I2C3_R->SR1.BIT.RxNE == 0);
				Copy_u8PtrBffr[LOC_u8Counter++] = I2C3_R->DR.BIT.DR;
				LOC_s8Size--;
				if(I2C3_R->SR1.BIT.BTF == 1)
				{
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C3_R->DR.BIT.DR;
					LOC_s8Size--;
				}
			}
		}
		I2C3_R->CR1.BIT.PE 	= 0;
	}
	break;
	default :
		break;
	}
}

void I2C_vidSlaveTX(I2C_x Copy_enuI2C_x, u8 * Copy_u8PtrBffr, u8 Copy_u8Size)
{
	u8  LOC_u8Counter 	= 0;
	s8 	LOC_s8Size		= (s8)(Copy_u8Size-1);
	u32 LOC_u32Temp		= 0;

	switch(Copy_enuI2C_x)
	{
	case I2C_1 :
	{
		I2C1_R->CR1.BIT.PE 	= 1;
		I2C1_R->CR1.BIT.POS	= 0;
		I2C1_R->CR1.BIT.ACK	= 1;

		/* Wait ADDR */
		while(I2C1_R->SR1.BIT.ADDR == 0);

		/* Clear ADDR */
		LOC_u32Temp = I2C1_R->SR1.REGISTER;
		LOC_u32Temp = I2C1_R->SR2.REGISTER;

		while(LOC_s8Size >= 0)
		{
			/* Wait TxE */
			while(I2C1_R->SR1.BIT.TxE == 0);

			/* Send Data */
			I2C1_R->DR.BIT.DR = Copy_u8PtrBffr[LOC_u8Counter++];
			LOC_s8Size--;

			if(I2C1_R->SR1.BIT.BTF == 1)
			{
				I2C1_R->DR.BIT.DR = Copy_u8PtrBffr[LOC_u8Counter++];
				LOC_s8Size--;
			}
		}

		/* Wait ACK FLAG */
		while(I2C1_R->SR1.BIT.AF == 0);
		I2C1_R->SR1.BIT.AF = 0;

		/* Disable ACK */
		I2C1_R->CR1.BIT.ACK	= 0;

		I2C1_R->CR1.BIT.PE	= 0;
	}
	break;
	case I2C_2 :
	{
		I2C2_R->CR1.BIT.PE 	= 1;
		I2C2_R->CR1.BIT.POS	= 0;
		I2C2_R->CR1.BIT.ACK	= 1;

		/* Wait ADDR */
		while(I2C2_R->SR1.BIT.ADDR == 0);

		/* Clear ADDR */
		LOC_u32Temp = I2C2_R->SR1.REGISTER;
		LOC_u32Temp = I2C2_R->SR2.REGISTER;

		while(LOC_s8Size >= 0)
		{
			/* Wait TxE */
			while(I2C2_R->SR1.BIT.TxE == 0);

			/* Send Data */
			I2C2_R->DR.BIT.DR = Copy_u8PtrBffr[LOC_u8Counter++];
			LOC_s8Size--;

			if(I2C2_R->SR1.BIT.BTF == 1)
			{
				I2C2_R->DR.BIT.DR = Copy_u8PtrBffr[LOC_u8Counter++];
				LOC_s8Size--;
			}
		}

		/* Wait ACK FLAG */
		while(I2C2_R->SR1.BIT.AF == 0);
		I2C2_R->SR1.BIT.AF = 0;

		/* Disable ACK */
		I2C2_R->CR1.BIT.ACK	= 0;

		I2C2_R->CR1.BIT.PE	= 0;
	}
	break;
	case I2C_3 :
	{
		I2C3_R->CR1.BIT.PE 	= 1;
		I2C3_R->CR1.BIT.POS	= 0;
		I2C3_R->CR1.BIT.ACK	= 1;

		/* Wait ADDR */
		while(I2C3_R->SR1.BIT.ADDR == 0);

		/* Clear ADDR */
		LOC_u32Temp = I2C3_R->SR1.REGISTER;
		LOC_u32Temp = I2C3_R->SR2.REGISTER;

		while(LOC_s8Size >= 0)
		{
			/* Wait TxE */
			while(I2C3_R->SR1.BIT.TxE == 0);

			/* Send Data */
			I2C3_R->DR.BIT.DR = Copy_u8PtrBffr[LOC_u8Counter++];
			LOC_s8Size--;

			if(I2C3_R->SR1.BIT.BTF == 1)
			{
				I2C3_R->DR.BIT.DR = Copy_u8PtrBffr[LOC_u8Counter++];
				LOC_s8Size--;
			}
		}

		/* Wait ACK FLAG */
		while(I2C3_R->SR1.BIT.AF == 0);
		I2C3_R->SR1.BIT.AF = 0;

		/* Disable ACK */
		I2C3_R->CR1.BIT.ACK	= 0;

		I2C3_R->CR1.BIT.PE	= 0;
	}
	break;
	default :
		break;
	}
}

void I2C_vidSlaveRX(I2C_x Copy_enuI2C_x, u8 * Copy_u8PtrBffr, u8 Copy_u8Size)
{
	u8  LOC_u8Counter 	= 0;
	s8 	LOC_s8Size		= (s8)(Copy_u8Size-1);
	u32 LOC_u32Temp		= 0;

	switch(Copy_enuI2C_x)
	{
	case I2C_1 :
	{
		I2C1_R->CR1.BIT.PE 	= 1;
		I2C1_R->CR1.BIT.POS	= 0;
		I2C1_R->CR1.BIT.ACK	= 1;

		/* Wait ADDR */
		while(I2C1_R->SR1.BIT.ADDR == 0);

		/* Clear ADDR */
		LOC_u32Temp = I2C1_R->SR1.REGISTER;
		LOC_u32Temp = I2C1_R->SR2.REGISTER;

		while(LOC_s8Size >= 0)
		{
			/* Wait RxNE */
			while(I2C1_R->SR1.BIT.RxNE == 0);

			/* Read Data */
			Copy_u8PtrBffr[LOC_u8Counter++] = I2C1_R->DR.BIT.DR;
			LOC_s8Size--;

			if(I2C1_R->SR1.BIT.BTF == 1)
			{
				Copy_u8PtrBffr[LOC_u8Counter++] = I2C1_R->DR.BIT.DR;
				LOC_s8Size--;
			}
		}

		/* Wait STOP Flag */
		while(I2C1_R->SR1.BIT.STOPF == 0);
		LOC_u32Temp = I2C1_R->SR1.REGISTER;
		I2C1_R->CR1.BIT.PE	= 1;

		/* Disable ACK */
		I2C1_R->CR1.BIT.ACK	= 0;

		I2C1_R->CR1.BIT.PE	= 0;
	}
	break;
	case I2C_2 :
	{
		I2C2_R->CR1.BIT.PE 	= 1;
		I2C2_R->CR1.BIT.POS	= 0;
		I2C2_R->CR1.BIT.ACK	= 1;

		/* Wait ADDR */
		while(I2C2_R->SR1.BIT.ADDR == 0);

		/* Clear ADDR */
		LOC_u32Temp = I2C2_R->SR1.REGISTER;
		LOC_u32Temp = I2C2_R->SR2.REGISTER;

		while(LOC_s8Size >= 0)
		{
			/* Wait RxNE */
			while(I2C2_R->SR1.BIT.RxNE == 0);

			/* Read Data */
			Copy_u8PtrBffr[LOC_u8Counter++] = I2C2_R->DR.BIT.DR;
			LOC_s8Size--;

			if(I2C2_R->SR1.BIT.BTF == 1)
			{
				Copy_u8PtrBffr[LOC_u8Counter++] = I2C2_R->DR.BIT.DR;
				LOC_s8Size--;
			}
		}

		/* Wait STOP Flag */
		while(I2C2_R->SR1.BIT.STOPF == 0);
		LOC_u32Temp = I2C2_R->SR1.REGISTER;
		I2C2_R->CR1.BIT.PE	= 1;

		/* Disable ACK */
		I2C2_R->CR1.BIT.ACK	= 0;

		I2C2_R->CR1.BIT.PE	= 0;
	}
	break;
	case I2C_3 :
	{
		I2C3_R->CR1.BIT.PE 	= 1;
		I2C3_R->CR1.BIT.POS	= 0;
		I2C3_R->CR1.BIT.ACK	= 1;

		/* Wait ADDR */
		while(I2C3_R->SR1.BIT.ADDR == 0);

		/* Clear ADDR */
		LOC_u32Temp = I2C3_R->SR1.REGISTER;
		LOC_u32Temp = I2C3_R->SR2.REGISTER;

		while(LOC_s8Size >= 0)
		{
			/* Wait RxNE */
			while(I2C3_R->SR1.BIT.RxNE == 0);

			/* Read Data */
			Copy_u8PtrBffr[LOC_u8Counter++] = I2C3_R->DR.BIT.DR;
			LOC_s8Size--;

			if(I2C3_R->SR1.BIT.BTF == 1)
			{
				Copy_u8PtrBffr[LOC_u8Counter++] = I2C3_R->DR.BIT.DR;
				LOC_s8Size--;
			}
		}

		/* Wait STOP Flag */
		while(I2C3_R->SR1.BIT.STOPF == 0);
		LOC_u32Temp = I2C3_R->SR1.REGISTER;
		I2C3_R->CR1.BIT.PE	= 1;

		/* Disable ACK */
		I2C3_R->CR1.BIT.ACK	= 0;

		I2C3_R->CR1.BIT.PE	= 0;
	}
	break;
	default :
		break;
	}
}

void I2C_vidMemWrite(I2C_x Copy_enuI2C_x, u8 Copy_u8SlaveAddress, u16 Copy_u16MemAddress, I2C_MEM_SIZE Copy_enuMemSize, u8 * Copy_u8PtrBffr, u8 Copy_u8Size)
{
	u8 	LOC_u8Counter;
	switch(Copy_enuI2C_x)
	{
	case I2C_1:
	{
		I2C_vidWriteMemoryHandler(I2C_1, Copy_u8SlaveAddress, Copy_u16MemAddress, Copy_enuMemSize);
		for(LOC_u8Counter = 0; LOC_u8Counter < Copy_u8Size; LOC_u8Counter++)
		{
			while(I2C1_R->SR1.BIT.TxE == 0);
			I2C1_R->DR.BIT.DR = Copy_u8PtrBffr[LOC_u8Counter];
		}
		while(I2C1_R->SR1.BIT.BTF == 0);

		I2C1_R->CR1.BIT.STOP = 1;

		I2C1_R->CR1.BIT.PE = 0;
	}
	break;
	case I2C_2:
	{
		I2C_vidWriteMemoryHandler(I2C_2, Copy_u8SlaveAddress, Copy_u16MemAddress, Copy_enuMemSize);
		for(LOC_u8Counter = 0; LOC_u8Counter < Copy_u8Size; LOC_u8Counter++)
		{
			while(I2C2_R->SR1.BIT.TxE == 0);
			I2C2_R->DR.BIT.DR = Copy_u8PtrBffr[LOC_u8Counter];
		}
		while(I2C2_R->SR1.BIT.BTF == 0);

		I2C2_R->CR1.BIT.STOP = 1;

		I2C2_R->CR1.BIT.PE = 0;
	}
	break;
	case I2C_3:
	{
		I2C_vidWriteMemoryHandler(I2C_3, Copy_u8SlaveAddress, Copy_u16MemAddress, Copy_enuMemSize);
		for(LOC_u8Counter = 0; LOC_u8Counter < Copy_u8Size; LOC_u8Counter++)
		{
			while(I2C3_R->SR1.BIT.TxE == 0);
			I2C3_R->DR.BIT.DR = Copy_u8PtrBffr[LOC_u8Counter];
		}
		while(I2C3_R->SR1.BIT.BTF == 0);

		I2C3_R->CR1.BIT.STOP = 1;

		I2C3_R->CR1.BIT.PE = 0;
	}
	break;
	default :
		break;
	}
}

void I2C_vidMemRead(I2C_x Copy_enuI2C_x, u8 Copy_u8SlaveAddress, u16 Copy_u16MemAddress, I2C_MEM_SIZE Copy_enuMemSize, u8 * Copy_u8PtrBffr, u8 Copy_u8Size)
{
	u8 	LOC_u8Counter 	= 0;
	s8 	LOC_s8Size		= (s8)(Copy_u8Size-1);
	u32 LOC_u32Temp		= 0;
	switch(Copy_enuI2C_x)
	{
	case I2C_1 :
	{
		I2C_vidReadMemoryHandler(I2C_1, Copy_u8SlaveAddress, Copy_u16MemAddress, Copy_enuMemSize);

		while(LOC_s8Size >= 0)
		{
			if(LOC_s8Size <= 2)
			{
				switch(LOC_s8Size)
				{
				case 0 :
				{
					LOC_s8Size--;
					/* Clear ACK */
					I2C1_R->CR1.BIT.ACK = 0;
					/* Generate STOP */
					I2C1_R->CR1.BIT.STOP = 1;
					/* Clear ADDR */
					LOC_u32Temp = I2C1_R->SR1.REGISTER;
					LOC_u32Temp = I2C1_R->SR2.REGISTER;
					/* Read DR */
					while(I2C1_R->SR1.BIT.RxNE == 0);
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C1_R->DR.BIT.DR;
				}
				break;
				case 1 :
				{
					/* Clear ACK */
					I2C1_R->CR1.BIT.ACK = 0;

					/* Set POS */
					I2C1_R->CR1.BIT.POS = 1;

					/* Clear ADDR */
					LOC_u32Temp = I2C1_R->SR1.REGISTER;
					LOC_u32Temp = I2C1_R->SR2.REGISTER;

					/* Wait BTF */
					while(I2C1_R->SR1.BIT.BTF == 0);

					/* Generate STOP */
					I2C1_R->CR1.BIT.STOP = 1;

					/* Read Data */
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C1_R->DR.BIT.DR;
					LOC_s8Size--;
					while(I2C1_R->SR1.BIT.RxNE == 0);
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C1_R->DR.BIT.DR;
					LOC_s8Size--;
				}
				break;
				default :
				{

					/* Clear ADDR */
					LOC_u32Temp = I2C1_R->SR1.REGISTER;
					LOC_u32Temp = I2C1_R->SR2.REGISTER;

					/* Set POS */
					I2C1_R->CR1.BIT.POS = 1;

					/* Wait BTF */
					while(I2C1_R->SR1.BIT.BTF == 0);

					/* Clear ACK */
					I2C1_R->CR1.BIT.ACK = 0;

					/* Read Data */
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C1_R->DR.BIT.DR;
					LOC_s8Size--;

					/* Wait BTF */
					while(I2C1_R->SR1.BIT.BTF == 0);

					/* Generate STOP */
					I2C1_R->CR1.BIT.STOP = 1;

					/* Read Data */
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C1_R->DR.BIT.DR;
					LOC_s8Size--;

					while(I2C1_R->SR1.BIT.RxNE == 0);
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C1_R->DR.BIT.DR;
					LOC_s8Size--;
				}
				break;
				}//end of switch
			}
			else
			{
				/* Read DR */
				while(I2C1_R->SR1.BIT.RxNE == 0);
				Copy_u8PtrBffr[LOC_u8Counter++] = I2C1_R->DR.BIT.DR;
				LOC_s8Size--;

				if(I2C1_R->SR1.BIT.BTF == 1)
				{
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C1_R->DR.BIT.DR;
					LOC_s8Size--;
				}
			}
		}
		I2C1_R->CR1.BIT.PE 	= 0;
	}
	break;
	case I2C_2 :
	{
		I2C_vidReadMemoryHandler(I2C_2, Copy_u8SlaveAddress, Copy_u16MemAddress, Copy_enuMemSize);

		while(LOC_s8Size >= 0)
		{
			if(LOC_s8Size <= 2)
			{
				switch(LOC_s8Size)
				{
				case 0 :
				{
					LOC_s8Size--;
					/* Clear ACK */
					I2C2_R->CR1.BIT.ACK = 0;
					/* Generate STOP */
					I2C2_R->CR1.BIT.STOP = 1;
					/* Clear ADDR */
					LOC_u32Temp = I2C2_R->SR1.REGISTER;
					LOC_u32Temp = I2C2_R->SR2.REGISTER;
					/* Read DR */
					while(I2C2_R->SR1.BIT.RxNE == 0);
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C2_R->DR.BIT.DR;
				}
				break;
				case 1 :
				{
					/* Clear ACK */
					I2C2_R->CR1.BIT.ACK = 0;

					/* Set POS */
					I2C2_R->CR1.BIT.POS = 1;

					/* Clear ADDR */
					LOC_u32Temp = I2C2_R->SR1.REGISTER;
					LOC_u32Temp = I2C2_R->SR2.REGISTER;

					/* Wait BTF */
					while(I2C2_R->SR1.BIT.BTF == 0);

					/* Generate STOP */
					I2C2_R->CR1.BIT.STOP = 1;

					/* Read Data */
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C2_R->DR.BIT.DR;
					LOC_s8Size--;
					while(I2C2_R->SR1.BIT.RxNE == 0);
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C2_R->DR.BIT.DR;
					LOC_s8Size--;
				}
				break;
				default :
				{
					/* Clear ADDR */
					LOC_u32Temp = I2C1_R->SR1.REGISTER;
					LOC_u32Temp = I2C1_R->SR2.REGISTER;

					/* Set POS */
					I2C2_R->CR1.BIT.POS = 1;

					/* Wait BTF */
					while(I2C2_R->SR1.BIT.BTF == 0);

					/* Clear ACK */
					I2C2_R->CR1.BIT.ACK = 0;

					/* Read Data */
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C2_R->DR.BIT.DR;
					LOC_s8Size--;

					/* Wait BTF */
					while(I2C2_R->SR1.BIT.BTF == 0);

					/* Generate STOP */
					I2C2_R->CR1.BIT.STOP = 1;

					/* Read Data */
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C2_R->DR.BIT.DR;
					LOC_s8Size--;
					while(I2C2_R->SR1.BIT.RxNE == 0);
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C2_R->DR.BIT.DR;
					LOC_s8Size--;
				}
				break;
				}//end of switch
			}
			else
			{
				/* Read DR */
				while(I2C2_R->SR1.BIT.RxNE == 0);
				Copy_u8PtrBffr[LOC_u8Counter++] = I2C2_R->DR.BIT.DR;
				LOC_s8Size--;
				if(I2C2_R->SR1.BIT.BTF == 1)
				{
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C2_R->DR.BIT.DR;
					LOC_s8Size--;
				}
			}
		}
		I2C2_R->CR1.BIT.PE 	= 0;
	}
	break;
	case I2C_3 :
	{
		I2C_vidReadMemoryHandler(I2C_3, Copy_u8SlaveAddress, Copy_u16MemAddress, Copy_enuMemSize);

		while(LOC_s8Size >= 0)
		{
			if(LOC_s8Size <= 2)
			{
				switch(LOC_s8Size)
				{
				case 0 :
				{
					LOC_s8Size--;
					/* Clear ACK */
					I2C3_R->CR1.BIT.ACK = 0;
					/* Generate STOP */
					I2C3_R->CR1.BIT.STOP = 1;
					/* Clear ADDR */
					LOC_u32Temp = I2C3_R->SR1.REGISTER;
					LOC_u32Temp = I2C3_R->SR2.REGISTER;
					/* Read DR */
					while(I2C3_R->SR1.BIT.RxNE == 0);
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C3_R->DR.BIT.DR;
				}
				break;
				case 1 :
				{
					/* Clear ACK */
					I2C3_R->CR1.BIT.ACK = 0;

					/* Set POS */
					I2C3_R->CR1.BIT.POS = 1;

					/* Clear ADDR */
					LOC_u32Temp = I2C3_R->SR1.REGISTER;
					LOC_u32Temp = I2C3_R->SR2.REGISTER;

					/* Wait BTF */
					while(I2C3_R->SR1.BIT.BTF == 0);

					/* Generate STOP */
					I2C3_R->CR1.BIT.STOP = 1;

					/* Read Data */
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C3_R->DR.BIT.DR;
					LOC_s8Size--;
					while(I2C3_R->SR1.BIT.RxNE == 0);
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C3_R->DR.BIT.DR;
					LOC_s8Size--;
				}
				break;
				default :
				{
					/* Clear ADDR */
					LOC_u32Temp = I2C1_R->SR1.REGISTER;
					LOC_u32Temp = I2C1_R->SR2.REGISTER;

					/* Set POS */
					I2C3_R->CR1.BIT.POS = 1;

					/* Wait BTF */
					while(I2C3_R->SR1.BIT.BTF == 0);

					/* Clear ACK */
					I2C3_R->CR1.BIT.ACK = 0;

					/* Read Data */
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C3_R->DR.BIT.DR;
					LOC_s8Size--;

					/* Wait BTF */
					while(I2C3_R->SR1.BIT.BTF == 0);

					/* Generate STOP */
					I2C3_R->CR1.BIT.STOP = 1;

					/* Read Data */
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C3_R->DR.BIT.DR;
					LOC_s8Size--;
					while(I2C3_R->SR1.BIT.RxNE == 0);
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C3_R->DR.BIT.DR;
					LOC_s8Size--;
				}
				break;
				}//end of switch
			}
			else
			{
				/* Read DR */
				while(I2C3_R->SR1.BIT.RxNE == 0);
				Copy_u8PtrBffr[LOC_u8Counter++] = I2C3_R->DR.BIT.DR;
				LOC_s8Size--;
				if(I2C3_R->SR1.BIT.BTF == 1)
				{
					Copy_u8PtrBffr[LOC_u8Counter++] = I2C3_R->DR.BIT.DR;
					LOC_s8Size--;
				}
			}
		}
		I2C3_R->CR1.BIT.PE 	= 0;
	}
	break;
	default :
		break;
	}
}

static u32  I2C_u32CRRHanlder(I2C_DUTY_CYCLE Copy_enuDutyCycle, u32 Copy_u32FreqDesired)
{
	u32 LOC_u32CRRValue;
	f64 LOC_f64Tp = 1.0/((f64)(I2C_APB1_FREQ_IN_MHz*1000000));
	f64 LOC_f64T  = 1.0/((f64)Copy_u32FreqDesired);
	switch(Copy_enuDutyCycle)
	{
	case FM_MODE_DUTY_1_2 :
	{
		LOC_f64Tp 		= (3.0*LOC_f64Tp);
		LOC_u32CRRValue = (u32)(LOC_f64T/LOC_f64Tp);
		break;
	}
	case FM_MODE_DUTY_16_9 :
	{
		LOC_f64Tp 		= (25.0*LOC_f64Tp);
		LOC_u32CRRValue = (u32)(LOC_f64T/LOC_f64Tp);
		break;
	}
	default :
	{
		LOC_f64Tp 		= (2.0*LOC_f64Tp);
		LOC_u32CRRValue = (u32)(LOC_f64T/LOC_f64Tp);
		break;
	}
	}//end of switch
	return LOC_u32CRRValue;
}

static void I2C_vidAddressHandler(I2C_x Copy_enuI2C_x, I2C_ADD_MODE AddMode, u16 Add1, I2C_DUAL_ADD DualMode, u8 Add2)
{
	Add1					&= (0x03FF);
	switch(Copy_enuI2C_x)
	{
	case I2C_1 :
	{
		I2C1_R->OAR1.REGISTER	&= (0xFFFFFC00);
		I2C1_R->OAR1.BIT.ADDMODE = AddMode;
		switch(AddMode)
		{
		case _7BITS_I2C :
		{
			Add1 = (Add1<<1);
			I2C1_R->OAR1.REGISTER |= Add1;
		}
		break;
		case _10BITS_I2C :
		{
			I2C1_R->OAR1.REGISTER	|= (u32)Add1;
		}
		break;
		default : break;
		}//end of switch

		I2C1_R->OAR2.BIT.ENDUAL 		= DualMode;
		I2C1_R->OAR2.BIT.ADD2_7_1	= (u32)Add2;
	}
	break;
	case I2C_2 :
	{
		I2C2_R->OAR1.REGISTER	&= (0xFFFFFC00);
		I2C2_R->OAR1.BIT.ADDMODE = AddMode;
		switch(AddMode)
		{
		case _7BITS_I2C :
		{
			Add1 = (Add1<<1);
			I2C2_R->OAR1.REGISTER |= Add1;
		}
		break;
		case _10BITS_I2C :
		{
			I2C2_R->OAR1.REGISTER	|= (u32)Add1;
		}
		break;
		default : break;
		}//end of switch

		I2C2_R->OAR2.BIT.ENDUAL 		= DualMode;
		I2C2_R->OAR2.BIT.ADD2_7_1	= (u32)Add2;
	}
	break;
	case I2C_3 :
	{
		I2C3_R->OAR1.REGISTER	&= (0xFFFFFC00);
		I2C3_R->OAR1.BIT.ADDMODE = AddMode;
		switch(AddMode)
		{
		case _7BITS_I2C :
		{
			Add1 = (Add1<<1);
			I2C3_R->OAR1.REGISTER |= Add1;
		}
		break;
		case _10BITS_I2C :
		{
			I2C3_R->OAR1.REGISTER	|= (u32)Add1;
		}
		break;
		default : break;
		}//end of switch

		I2C3_R->OAR2.BIT.ENDUAL 		= DualMode;
		I2C3_R->OAR2.BIT.ADD2_7_1	= (u32)Add2;
	}
	break;
	default :
		break;
	}
}

static void I2C_vidSendSlaveAddress(I2C_x Copy_enuI2C_x, u8 Copy_u8Address, I2C_MASTER Copy_enuMasterState)
{
	u32 LOC_u32Temp		= 0;
	switch(Copy_enuI2C_x)
	{
	case I2C_1 :
	{
		switch(Copy_enuMasterState)
		{
		case I2C_MASTER_TRANS 	:
			I2C1_R->DR.BIT.DR = I2C_WRITE(Copy_u8Address);
//			while(I2C1_R->SR1.BIT.ADDR == 0);
			LOC_u32Temp = I2C1_R->SR1.REGISTER;
			LOC_u32Temp = I2C1_R->SR2.REGISTER;
			break;
		case I2C_MASTER_RECEIVE :
			I2C1_R->DR.BIT.DR = I2C_READ(Copy_u8Address);
			while(I2C1_R->SR1.BIT.ADDR == 0);
			break;
		default:
			break;
		}

	}
	break;
	case I2C_2 :
	{
		switch(Copy_enuMasterState)
		{
		case I2C_MASTER_TRANS 	:
			I2C2_R->DR.BIT.DR = I2C_WRITE(Copy_u8Address);
			while(I2C2_R->SR1.BIT.ADDR == 0);
			LOC_u32Temp = I2C2_R->SR1.REGISTER;
			LOC_u32Temp = I2C2_R->SR2.REGISTER;
			break;
		case I2C_MASTER_RECEIVE :
			I2C2_R->DR.BIT.DR = I2C_READ(Copy_u8Address);
			while(I2C2_R->SR1.BIT.ADDR == 0);
			break;
		default:
			break;
		}

	}
	break;
	case I2C_3 :
	{
		switch(Copy_enuMasterState)
		{
		case I2C_MASTER_TRANS 	:
			I2C3_R->DR.BIT.DR = I2C_WRITE(Copy_u8Address);
			while(I2C3_R->SR1.BIT.ADDR == 0);
			LOC_u32Temp = I2C3_R->SR1.REGISTER;
			LOC_u32Temp = I2C3_R->SR2.REGISTER;
			break;
		case I2C_MASTER_RECEIVE :
			I2C3_R->DR.BIT.DR = I2C_READ(Copy_u8Address);
			while(I2C3_R->SR1.BIT.ADDR == 0);
			break;
		default:
			break;
		}

	}
	break;
	default :
		break;
	}


}

static void I2C_vidWriteMemoryHandler(I2C_x Copy_enuI2C_x, u8 Copy_u8SlaveAddress, u16 Copy_u16MemAddress, I2C_MEM_SIZE Copy_enuMemSize)
{
	switch(Copy_enuI2C_x)
	{
	case I2C_1:
	{
		I2C1_R->CR1.BIT.PE 		= 1;
		I2C1_R->CR1.BIT.POS		= 0;

		/* Generate START */
		I2C1_R->CR1.BIT.START	= 1;
		while(I2C1_R->SR1.BIT.SB == 0);

		I2C_vidSendSlaveAddress(I2C_1, Copy_u8SlaveAddress, I2C_MASTER_TRANS);
		/* Wait TxE */
		while(I2C1_R->SR1.BIT.TxE == 0);

		if(Copy_enuMemSize == _8BITS_I2C_MEM)
		{
			I2C1_R->DR.BIT.DR = ((u8)Copy_u16MemAddress);
		}
		else if(Copy_enuMemSize == _16BITS_I2C_MEM)
		{
			/* Send MSB */
			I2C1_R->DR.BIT.DR = ((u8)(Copy_u16MemAddress>>8));

			/* Wait TxE */
			while(I2C1_R->SR1.BIT.TxE == 0);

			/* Send LSB */
			I2C1_R->DR.BIT.DR = ((u8)Copy_u16MemAddress);
		}
		else
		{
		}
	}
	break;
	case I2C_2:
	{
		I2C2_R->CR1.BIT.PE 		= 1;
		I2C2_R->CR1.BIT.POS		= 0;

		/* Generate START */
		I2C2_R->CR1.BIT.START	= 1;
		while(I2C2_R->SR1.BIT.SB == 0);

		I2C_vidSendSlaveAddress(I2C_2, Copy_u8SlaveAddress, I2C_MASTER_TRANS);
		/* Wait TxE */
		while(I2C2_R->SR1.BIT.TxE == 0);

		if(Copy_enuMemSize == _8BITS_I2C_MEM)
		{
			I2C2_R->DR.BIT.DR = ((u8)Copy_u16MemAddress);
		}
		else if(Copy_enuMemSize == _16BITS_I2C_MEM)
		{
			/* Send MSB */
			I2C2_R->DR.BIT.DR = ((u8)(Copy_u16MemAddress>>8));

			/* Wait TxE */
			while(I2C2_R->SR1.BIT.TxE == 0);

			/* Send LSB */
			I2C2_R->DR.BIT.DR = ((u8)Copy_u16MemAddress);
		}
		else
		{
		}
	}
	break;
	case I2C_3:
	{
		I2C3_R->CR1.BIT.PE 		= 1;
		I2C3_R->CR1.BIT.POS		= 0;

		/* Generate START */
		I2C3_R->CR1.BIT.START	= 1;
		while(I2C3_R->SR1.BIT.SB == 0);

		I2C_vidSendSlaveAddress(I2C_3, Copy_u8SlaveAddress, I2C_MASTER_TRANS);
		/* Wait TxE */
		while(I2C3_R->SR1.BIT.TxE == 0);

		if(Copy_enuMemSize == _8BITS_I2C_MEM)
		{
			I2C3_R->DR.BIT.DR = ((u8)Copy_u16MemAddress);
		}
		else if(Copy_enuMemSize == _16BITS_I2C_MEM)
		{
			/* Send MSB */
			I2C3_R->DR.BIT.DR = ((u8)(Copy_u16MemAddress>>8));

			/* Wait TxE */
			while(I2C3_R->SR1.BIT.TxE == 0);

			/* Send LSB */
			I2C3_R->DR.BIT.DR = ((u8)Copy_u16MemAddress);
		}
		else
		{
		}
	}
	break;
	default :
		break;
	}
}

static void I2C_vidReadMemoryHandler(I2C_x Copy_enuI2C_x, u8 Copy_u8SlaveAddress, u16 Copy_u16MemAddress, I2C_MEM_SIZE Copy_enuMemSize)
{

	switch(Copy_enuI2C_x)
	{
	case I2C_1 :
	{
		I2C1_R->CR1.BIT.PE 		= 1;
		I2C1_R->CR1.BIT.POS		= 0;

		/* Enable ACK */
		I2C1_R->CR1.BIT.ACK		= 1;

		/* Generate START */
		I2C1_R->CR1.BIT.START	= 1;
		while(I2C1_R->SR1.BIT.SB == 0);

		I2C_vidSendSlaveAddress(I2C_1, Copy_u8SlaveAddress, I2C_MASTER_TRANS);

		/* Wait TxE */
		while(I2C1_R->SR1.BIT.TxE == 0);

		if(Copy_enuMemSize == _8BITS_I2C_MEM)
		{
			I2C1_R->DR.BIT.DR = ((u8)Copy_u16MemAddress);
		}
		else if(Copy_enuMemSize == _16BITS_I2C_MEM)
		{
			/* Send MSB */
			I2C1_R->DR.BIT.DR = ((u8)(Copy_u16MemAddress>>8));

			/* Wait TxE */
			while(I2C1_R->SR1.BIT.TxE == 0);

			/* Send LSB */
			I2C1_R->DR.BIT.DR = ((u8)Copy_u16MemAddress);
		}
		else
		{
		}
		/* Wait TxE */
		while(I2C1_R->SR1.BIT.TxE == 0);

		/* Generate START */
		I2C1_R->CR1.BIT.START	= 1;
		while(I2C1_R->SR1.BIT.SB == 0);

		I2C_vidSendSlaveAddress(I2C_1, Copy_u8SlaveAddress, I2C_MASTER_RECEIVE);
	}
	break;
	case I2C_2 :
	{
		I2C2_R->CR1.BIT.PE 		= 1;
		I2C2_R->CR1.BIT.POS		= 0;

		/* Enable ACK */
		I2C2_R->CR1.BIT.ACK		= 1;

		/* Generate START */
		I2C2_R->CR1.BIT.START	= 1;
		while(I2C2_R->SR1.BIT.SB == 0);

		I2C_vidSendSlaveAddress(I2C_2, Copy_u8SlaveAddress, I2C_MASTER_TRANS);

		/* Wait TxE */
		while(I2C2_R->SR1.BIT.TxE == 0);

		if(Copy_enuMemSize == _8BITS_I2C_MEM)
		{
			I2C2_R->DR.BIT.DR = ((u8)Copy_u16MemAddress);
		}
		else if(Copy_enuMemSize == _16BITS_I2C_MEM)
		{
			/* Send MSB */
			I2C2_R->DR.BIT.DR = ((u8)(Copy_u16MemAddress>>8));

			/* Wait TxE */
			while(I2C2_R->SR1.BIT.TxE == 0);

			/* Send LSB */
			I2C2_R->DR.BIT.DR = ((u8)Copy_u16MemAddress);
		}
		else
		{
		}
		/* Wait TxE */
		while(I2C2_R->SR1.BIT.TxE == 0);

		/* Generate START */
		I2C2_R->CR1.BIT.START	= 1;
		while(I2C2_R->SR1.BIT.SB == 0);

		I2C_vidSendSlaveAddress(I2C_2, Copy_u8SlaveAddress, I2C_MASTER_RECEIVE);
	}
	break;
	case I2C_3 :
	{
		I2C3_R->CR1.BIT.PE 		= 1;
		I2C3_R->CR1.BIT.POS		= 0;

		/* Enable ACK */
		I2C3_R->CR1.BIT.ACK		= 1;

		/* Generate START */
		I2C3_R->CR1.BIT.START	= 1;
		while(I2C3_R->SR1.BIT.SB == 0);

		I2C_vidSendSlaveAddress(I2C_3, Copy_u8SlaveAddress, I2C_MASTER_TRANS);

		/* Wait TxE */
		while(I2C3_R->SR1.BIT.TxE == 0);

		if(Copy_enuMemSize == _8BITS_I2C_MEM)
		{
			I2C3_R->DR.BIT.DR = ((u8)Copy_u16MemAddress);
		}
		else if(Copy_enuMemSize == _16BITS_I2C_MEM)
		{
			/* Send MSB */
			I2C3_R->DR.BIT.DR = ((u8)(Copy_u16MemAddress>>8));

			/* Wait TxE */
			while(I2C3_R->SR1.BIT.TxE == 0);

			/* Send LSB */
			I2C3_R->DR.BIT.DR = ((u8)Copy_u16MemAddress);
		}
		else
		{
		}
		/* Wait TxE */
		while(I2C3_R->SR1.BIT.TxE == 0);

		/* Generate START */
		I2C3_R->CR1.BIT.START	= 1;
		while(I2C3_R->SR1.BIT.SB == 0);

		I2C_vidSendSlaveAddress(I2C_3, Copy_u8SlaveAddress, I2C_MASTER_RECEIVE);
	}
	break;
	default :
		break;
	}
}
