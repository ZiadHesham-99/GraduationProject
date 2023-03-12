/*
 * I2C_program.c
 *
 *  Created on: Oct 5, 2022
 *      Author: Hosam
 */

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/I2C_interface.h"
#include "MCAL/I2C_private.h"
#include "MCAL/I2C_config.h"

static u32 I2C_u32CRRHanlder(I2C_DUTY_CYCLE Copy_enuDutyCycle, u32 Copy_u32FreqDesired);
static void I2C_vidAddressHandler(I2C_x Copy_enuI2C_x, I2C_ADD_MODE AddMode, u16 Add1, I2C_DUAL_ADD DualMode, u8 Add2);
static void I2C_vidSendSlaveAddress(I2C_x Copy_enuI2C_x, u8 Copy_u8Address, I2C_MASTER Copy_enuMasterState);

void I2C_vidInit(void)
{
	u8 LOC_u8Counter;
	u32 LOC_u32CRRValue;
	u32 LOC_u32TRISEValue;

	I2C_CONFIG LOC_strI2C;

	for (LOC_u8Counter = 0; LOC_u8Counter < NUM_OF_USED_I2C; LOC_u8Counter++)
	{
		LOC_strI2C = GLOB_ptrStrI2C[LOC_u8Counter];
		switch (LOC_strI2C.I2C_x)
		{
		case I2C_1:
		{
			I2C_ENABLE(I2C1_R, FALSE);
			I2C_SOFTWARE_RESET(I2C1_R);
			I2C1_R->CR1.BIT.NOSTRETCH = 0;
			I2C1_R->CR1.BIT.SMBUS = 0;

			I2C1_R->CR2.BIT.FREQ = I2C_APB1_FREQ_IN_MHz;
			I2C_TRISE_CALC(LOC_strI2C.enuI2CFreq, LOC_u32TRISEValue);
			I2C1_R->TRISE.BIT.TRISE = LOC_u32TRISEValue;

			I2C1_R->CCR.BIT.F_S = LOC_strI2C.enuI2CMode;

			if (LOC_strI2C.enuI2CMode == STANDARD_MODE_I2C)
			{
				if (LOC_strI2C.enuI2CFreq > _100KHz)
				{
					LOC_strI2C.enuI2CFreq = _100KHz;
				}
				else
				{
				}

				LOC_u32CRRValue = I2C_u32CRRHanlder(STANDARD_MODE_DUTY, LOC_strI2C.enuI2CFreq);

				if (LOC_u32CRRValue < 4)
				{
					LOC_u32CRRValue = 4;
				}
				else
				{
				}

				I2C1_R->CCR.BIT.CCR = LOC_u32CRRValue;
			}
			else if (LOC_strI2C.enuI2CMode == FAST_MODE_I2C)
			{
				I2C1_R->CCR.BIT.DUTY = LOC_strI2C.enuDutyCycle;
				if (LOC_strI2C.enuI2CFreq > _400KHz)
				{
					LOC_strI2C.enuI2CFreq = _400KHz;
				}
				else
				{
				}

				LOC_u32CRRValue = I2C_u32CRRHanlder(LOC_strI2C.enuDutyCycle, LOC_strI2C.enuI2CFreq);

				if (LOC_u32CRRValue < 1)
				{
					LOC_u32CRRValue = 1;
				}
				else
				{
				}
				I2C1_R->CCR.BIT.CCR = LOC_u32CRRValue;
			}
			else
			{
			}

			I2C_vidAddressHandler(I2C_1, LOC_strI2C.enuAddressingMode, LOC_strI2C.u16SlaveAddress1, LOC_strI2C.enuDualAddress, LOC_strI2C.u8SlaveAddress2);
			I2C_ENABLE(I2C1_R, TRUE);
		}
		break;
		case I2C_2:
		{
			I2C_ENABLE(I2C2_R, FALSE);
			I2C_SOFTWARE_RESET(I2C2_R);
			I2C2_R->CR1.BIT.NOSTRETCH = 0;
			I2C2_R->CR1.BIT.SMBUS = 0;

			I2C2_R->CR2.BIT.FREQ = I2C_APB1_FREQ_IN_MHz;
			I2C_TRISE_CALC(LOC_strI2C.enuI2CFreq, LOC_u32TRISEValue);
			I2C2_R->TRISE.BIT.TRISE = LOC_u32TRISEValue;

			I2C2_R->CCR.BIT.F_S = LOC_strI2C.enuI2CMode;

			if (LOC_strI2C.enuI2CMode == STANDARD_MODE_I2C)
			{
				if (LOC_strI2C.enuI2CFreq > _100KHz)
				{
					LOC_strI2C.enuI2CFreq = _100KHz;
				}
				else
				{
				}

				LOC_u32CRRValue = I2C_u32CRRHanlder(STANDARD_MODE_DUTY, LOC_strI2C.enuI2CFreq);

				if (LOC_u32CRRValue < 4)
				{
					LOC_u32CRRValue = 4;
				}
				else
				{
				}

				I2C2_R->CCR.BIT.CCR = LOC_u32CRRValue;
			}
			else if (LOC_strI2C.enuI2CMode == FAST_MODE_I2C)
			{
				I2C2_R->CCR.BIT.DUTY = LOC_strI2C.enuDutyCycle;
				if (LOC_strI2C.enuI2CFreq > _400KHz)
				{
					LOC_strI2C.enuI2CFreq = _400KHz;
				}
				else
				{
				}

				LOC_u32CRRValue = I2C_u32CRRHanlder(LOC_strI2C.enuDutyCycle, LOC_strI2C.enuI2CFreq);

				if (LOC_u32CRRValue < 1)
				{
					LOC_u32CRRValue = 1;
				}
				else
				{
				}
				I2C2_R->CCR.BIT.CCR = LOC_u32CRRValue;
			}
			else
			{
			}

			I2C_vidAddressHandler(I2C_2, LOC_strI2C.enuAddressingMode, LOC_strI2C.u16SlaveAddress1, LOC_strI2C.enuDualAddress, LOC_strI2C.u8SlaveAddress2);
			I2C_ENABLE(I2C2_R, TRUE);
		}
		break;
		case I2C_3:
		{
			I2C_ENABLE(I2C3_R, FALSE);
			I2C_SOFTWARE_RESET(I2C3_R);
			I2C3_R->CR1.BIT.NOSTRETCH = 0;
			I2C3_R->CR1.BIT.SMBUS = 0;

			I2C3_R->CR2.BIT.FREQ = I2C_APB1_FREQ_IN_MHz;
			I2C_TRISE_CALC(LOC_strI2C.enuI2CFreq, LOC_u32TRISEValue);
			I2C3_R->TRISE.BIT.TRISE = LOC_u32TRISEValue;

			I2C3_R->CCR.BIT.F_S = LOC_strI2C.enuI2CMode;

			if (LOC_strI2C.enuI2CMode == STANDARD_MODE_I2C)
			{
				if (LOC_strI2C.enuI2CFreq > _100KHz)
				{
					LOC_strI2C.enuI2CFreq = _100KHz;
				}
				else
				{
				}

				LOC_u32CRRValue = I2C_u32CRRHanlder(STANDARD_MODE_DUTY, LOC_strI2C.enuI2CFreq);

				if (LOC_u32CRRValue < 4)
				{
					LOC_u32CRRValue = 4;
				}
				else
				{
				}

				I2C3_R->CCR.BIT.CCR = LOC_u32CRRValue;
			}
			else if (LOC_strI2C.enuI2CMode == FAST_MODE_I2C)
			{
				I2C3_R->CCR.BIT.DUTY = LOC_strI2C.enuDutyCycle;
				if (LOC_strI2C.enuI2CFreq > _400KHz)
				{
					LOC_strI2C.enuI2CFreq = _400KHz;
				}
				else
				{
				}

				LOC_u32CRRValue = I2C_u32CRRHanlder(LOC_strI2C.enuDutyCycle, LOC_strI2C.enuI2CFreq);

				if (LOC_u32CRRValue < 1)
				{
					LOC_u32CRRValue = 1;
				}
				else
				{
				}
				I2C3_R->CCR.BIT.CCR = LOC_u32CRRValue;
			}
			else
			{
			}

			I2C_vidAddressHandler(I2C_3, LOC_strI2C.enuAddressingMode, LOC_strI2C.u16SlaveAddress1, LOC_strI2C.enuDualAddress, LOC_strI2C.u8SlaveAddress2);
			I2C_ENABLE(I2C3_R, TRUE);
		}
		break;
		default:
			break;
		} // end of switch
	}	  // end of loop
}

void I2C_vidMasterTX(I2C_x Copy_enuI2C_x, u8 Copy_u8SlaveAddress, u8 *Copy_u8PtrBffr, u8 Copy_u8Size)
{
	u8 LOC_u8Counter = 0;

	switch (Copy_enuI2C_x)
	{
	case I2C_1:
	{
		I2C_WAIT_BUSY(I2C1_R);

		if (I2C1_R->CR1.BIT.PE == FALSE)
		{
			I2C_ENABLE(I2C1_R, TRUE);
		}
		else
		{
		}

		I2C_POS_ENABLE(I2C1_R, FALSE);
		I2C_ACK_ENABLE(I2C1_R, TRUE);
		I2C_GENERATE_START(I2C1_R);
		I2C_vidSendSlaveAddress(I2C_1, Copy_u8SlaveAddress, I2C_MASTER_TRANS);

		while (0 != Copy_u8Size)
		{
			I2C_WAIT_TXE(I2C1_R);
			I2C_WRITE_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
			LOC_u8Counter++;
			Copy_u8Size--;

			if ((TRUE == I2C_GET_BTF(I2C1_R)) && (0 != Copy_u8Size))
			{
				I2C_WRITE_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
				LOC_u8Counter++;
				Copy_u8Size--;
			}
			else
			{
			}
			I2C_WAIT_BTF(I2C1_R);
		}
		I2C_GENERATE_STOP(I2C1_R);
		//I2C_ENABLE(I2C1_R, FALSE);
	}
	break;
	case I2C_2:
	{
		if (I2C2_R->CR1.BIT.PE == FALSE)
		{
			I2C_ENABLE(I2C2_R, TRUE);
		}
		else
		{
		}

		I2C_POS_ENABLE(I2C2_R, FALSE);
		I2C_ACK_ENABLE(I2C2_R, TRUE);
		I2C_GENERATE_START(I2C2_R);
		I2C_vidSendSlaveAddress(I2C_2, Copy_u8SlaveAddress, I2C_MASTER_TRANS);

		while (0 != Copy_u8Size)
		{
			I2C_WAIT_TXE(I2C2_R);
			I2C_WRITE_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
			LOC_u8Counter++;
			Copy_u8Size--;

			if ((TRUE == I2C_GET_BTF(I2C2_R)) && (0 != Copy_u8Size))
			{
				I2C_WRITE_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
				LOC_u8Counter++;
				Copy_u8Size--;
			}
			else
			{
			}
			I2C_WAIT_BTF(I2C2_R);
		}
		I2C_GENERATE_STOP(I2C2_R);
		//I2C_ENABLE(I2C2_R, FALSE);
	}
	break;
	case I2C_3:
	{
		if (I2C3_R->CR1.BIT.PE == FALSE)
		{
			I2C_ENABLE(I2C3_R, TRUE);
		}
		else
		{
		}

		I2C_POS_ENABLE(I2C3_R, FALSE);
		I2C_ACK_ENABLE(I2C3_R, TRUE);
		I2C_GENERATE_START(I2C3_R);
		I2C_vidSendSlaveAddress(I2C_3, Copy_u8SlaveAddress, I2C_MASTER_TRANS);

		while (0 != Copy_u8Size)
		{
			I2C_WAIT_TXE(I2C3_R);
			I2C_WRITE_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
			LOC_u8Counter++;
			Copy_u8Size--;

			if ((TRUE == I2C_GET_BTF(I2C3_R)) && (0 != Copy_u8Size))
			{
				I2C_WRITE_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
				LOC_u8Counter++;
				Copy_u8Size--;
			}
			else
			{
			}
			I2C_WAIT_BTF(I2C3_R);
		}
		I2C_GENERATE_STOP(I2C3_R);
		//I2C_ENABLE(I2C3_R, FALSE);
	}
	break;
	default:
		break;
	}
}

void I2C_vidMasterRX(I2C_x Copy_enuI2C_x, u8 Copy_u8SlaveAddress, u8 *Copy_u8PtrBffr, u8 Copy_u8Size)
{
	u8 LOC_u8Counter 	= 0;
	volatile u32 LOC_u32Temp 	= 0;
	switch (Copy_enuI2C_x)
	{
	case I2C_1:
	{
		I2C_WAIT_BUSY(I2C1_R);

		if (I2C1_R->CR1.BIT.PE == FALSE)
		{
			I2C_ENABLE(I2C1_R, TRUE);
		}
		else
		{
		}

		I2C_POS_ENABLE(I2C1_R, FALSE);
		I2C_ACK_ENABLE(I2C1_R, TRUE);
		I2C_GENERATE_START(I2C1_R);
		I2C_vidSendSlaveAddress(I2C_1, Copy_u8SlaveAddress, I2C_MASTER_RECEIVE);

		switch (Copy_u8Size)
		{
		case 0:
			I2C_CLR_ADDR(I2C1_R, LOC_u32Temp);
			I2C_GENERATE_STOP(I2C1_R);
			break;
		case 1:
			I2C_ACK_ENABLE(I2C1_R, FALSE);
			I2C_CLR_ADDR(I2C1_R, LOC_u32Temp);
			I2C_GENERATE_STOP(I2C1_R);
			break;
		case 2:
			I2C_ACK_ENABLE(I2C1_R, FALSE);
			I2C_POS_ENABLE(I2C1_R, TRUE);
			I2C_CLR_ADDR(I2C1_R, LOC_u32Temp);
			break;
		default:
			I2C_ACK_ENABLE(I2C1_R, TRUE);
			I2C_CLR_ADDR(I2C1_R, LOC_u32Temp);
			break;
		}

		while (0 != Copy_u8Size)
		{
			if (Copy_u8Size <= 3)
			{

				switch (Copy_u8Size)
				{
				case 1:
				{

					I2C_WAIT_RXNE(I2C1_R);
					I2C_READ_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				break;
				case 2:
				{
					I2C_WAIT_BTF(I2C1_R);
					I2C_GENERATE_STOP(I2C1_R);
					I2C_READ_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
					I2C_READ_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				break;
				default:
				{
					I2C_WAIT_BTF(I2C1_R);
					I2C_ACK_ENABLE(I2C1_R, FALSE);
					I2C_READ_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
					I2C_WAIT_BTF(I2C1_R);
					I2C_GENERATE_STOP(I2C1_R);
					I2C_READ_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
					I2C_READ_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				break;
				} // end of switch
			}
			else
			{
				I2C_WAIT_RXNE(I2C1_R);
				I2C_READ_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
				LOC_u8Counter++;
				Copy_u8Size--;
				if (TRUE == I2C1_R->SR1.BIT.BTF)
				{
					I2C_READ_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				else
				{
				}
			}
		}
		//I2C_ENABLE(I2C1_R, FALSE);
	}
	break;
	case I2C_2:
	{
		I2C_WAIT_BUSY(I2C2_R);

		if (I2C2_R->CR1.BIT.PE == FALSE)
		{
			I2C_ENABLE(I2C2_R, TRUE);
		}
		else
		{
		}

		I2C_POS_ENABLE(I2C2_R, FALSE);
		I2C_ACK_ENABLE(I2C2_R, TRUE);
		I2C_GENERATE_START(I2C2_R);
		I2C_vidSendSlaveAddress(I2C_2, Copy_u8SlaveAddress, I2C_MASTER_RECEIVE);

		switch (Copy_u8Size)
		{
		case 0:
			I2C_CLR_ADDR(I2C2_R, LOC_u32Temp);
			I2C_GENERATE_STOP(I2C2_R);
			break;
		case 1:
			I2C_ACK_ENABLE(I2C2_R, FALSE);
			I2C_CLR_ADDR(I2C2_R, LOC_u32Temp);
			I2C_GENERATE_STOP(I2C2_R);
			break;
		case 2:
			I2C_ACK_ENABLE(I2C2_R, FALSE);
			I2C_POS_ENABLE(I2C2_R, TRUE);
			I2C_CLR_ADDR(I2C2_R, LOC_u32Temp);
			break;
		default:
			I2C_ACK_ENABLE(I2C2_R, TRUE);
			I2C_CLR_ADDR(I2C2_R, LOC_u32Temp);
			break;
		}

		while (0 != Copy_u8Size)
		{
			if (Copy_u8Size <= 3)
			{

				switch (Copy_u8Size)
				{
				case 1:
				{

					I2C_WAIT_RXNE(I2C2_R);
					I2C_READ_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				break;
				case 2:
				{
					I2C_WAIT_BTF(I2C2_R);
					I2C_GENERATE_STOP(I2C2_R);
					I2C_READ_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
					I2C_READ_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				break;
				default:
				{
					I2C_WAIT_BTF(I2C2_R);
					I2C_ACK_ENABLE(I2C2_R, FALSE);
					I2C_READ_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
					I2C_WAIT_BTF(I2C2_R);
					I2C_GENERATE_STOP(I2C2_R);
					I2C_READ_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
					I2C_READ_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				break;
				} // end of switch
			}
			else
			{
				I2C_WAIT_RXNE(I2C2_R);
				I2C_READ_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
				LOC_u8Counter++;
				Copy_u8Size--;
				if (TRUE == I2C2_R->SR1.BIT.BTF)
				{
					I2C_READ_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				else
				{
				}
			}
		}
		//I2C_ENABLE(I2C2_R, FALSE);
	}
	break;
	case I2C_3:
	{
		I2C_WAIT_BUSY(I2C3_R);

		if (I2C3_R->CR1.BIT.PE == FALSE)
		{
			I2C_ENABLE(I2C3_R, TRUE);
		}
		else
		{
		}

		I2C_POS_ENABLE(I2C3_R, FALSE);
		I2C_ACK_ENABLE(I2C3_R, TRUE);
		I2C_GENERATE_START(I2C3_R);
		I2C_vidSendSlaveAddress(I2C_3, Copy_u8SlaveAddress, I2C_MASTER_RECEIVE);

		switch (Copy_u8Size)
		{
		case 0:
			I2C_CLR_ADDR(I2C3_R, LOC_u32Temp);
			I2C_GENERATE_STOP(I2C3_R);
			break;
		case 1:
			I2C_ACK_ENABLE(I2C3_R, FALSE);
			I2C_CLR_ADDR(I2C3_R, LOC_u32Temp);
			I2C_GENERATE_STOP(I2C3_R);
			break;
		case 2:
			I2C_ACK_ENABLE(I2C3_R, FALSE);
			I2C_POS_ENABLE(I2C3_R, TRUE);
			I2C_CLR_ADDR(I2C3_R, LOC_u32Temp);
			break;
		default:
			I2C_ACK_ENABLE(I2C3_R, TRUE);
			I2C_CLR_ADDR(I2C3_R, LOC_u32Temp);
			break;
		}

		while (0 != Copy_u8Size)
		{
			if (Copy_u8Size <= 3)
			{

				switch (Copy_u8Size)
				{
				case 1:
				{

					I2C_WAIT_RXNE(I2C3_R);
					I2C_READ_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				break;
				case 2:
				{
					I2C_WAIT_BTF(I2C3_R);
					I2C_GENERATE_STOP(I2C3_R);
					I2C_READ_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
					I2C_READ_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				break;
				default:
				{
					I2C_WAIT_BTF(I2C3_R);
					I2C_ACK_ENABLE(I2C3_R, FALSE);
					I2C_READ_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
					I2C_WAIT_BTF(I2C3_R);
					I2C_GENERATE_STOP(I2C3_R);
					I2C_READ_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
					I2C_READ_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				break;
				} // end of switch
			}
			else
			{
				I2C_WAIT_RXNE(I2C3_R);
				I2C_READ_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
				LOC_u8Counter++;
				Copy_u8Size--;
				if (TRUE == I2C3_R->SR1.BIT.BTF)
				{
					I2C_READ_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				else
				{
				}
			}
		}
		//I2C_ENABLE(I2C3_R, FALSE);
	}
	break;
	default:
		break;
	}
}

void I2C_vidSlaveTX(I2C_x Copy_enuI2C_x, u8 *Copy_u8PtrBffr, u8 Copy_u8Size)
{
	u8 LOC_u8Counter = 0;
	volatile u32 LOC_u32Temp = 0;

	switch (Copy_enuI2C_x)
	{
	case I2C_1:
	{
		if (I2C1_R->CR1.BIT.PE == FALSE)
		{
			I2C_ENABLE(I2C1_R, TRUE);
		}
		else
		{
		}
		I2C_POS_ENABLE(I2C1_R, FALSE);
		I2C_ACK_ENABLE(I2C1_R, TRUE);
		I2C_WAIT_ADDR(I2C1_R);
		I2C_CLR_ADDR(I2C1_R, LOC_u32Temp);
		if(_10BITS_I2C == I2C1_R->OAR1.BIT.ADDMODE)
		{
			I2C_WAIT_ADDR(I2C1_R);
			I2C_CLR_ADDR(I2C1_R, LOC_u32Temp);
		}
		else{}

		while(0 != Copy_u8Size)
		{
			I2C_WAIT_TXE(I2C1_R);

			I2C_WRITE_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
			Copy_u8Size--;
			LOC_u8Counter++;

			if((TRUE == I2C_GET_BTF(I2C1_R)) && (0 != Copy_u8Size))
			{
				I2C_WRITE_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
				Copy_u8Size--;
				LOC_u8Counter++;
			}
			else{}
		}
		I2C_WAIT_AF(I2C1_R);
		I2C_CLR_AF(I2C1_R);	
		I2C_ACK_ENABLE(I2C1_R, FALSE);
	}
	break;
	case I2C_2:
	{
		if (I2C2_R->CR1.BIT.PE == FALSE)
		{
			I2C_ENABLE(I2C2_R, TRUE);
		}
		else
		{
		}
		I2C_POS_ENABLE(I2C2_R, FALSE);
		I2C_ACK_ENABLE(I2C2_R, TRUE);
		I2C_WAIT_ADDR(I2C2_R);
		I2C_CLR_ADDR(I2C2_R, LOC_u32Temp);
		if(_10BITS_I2C == I2C2_R->OAR1.BIT.ADDMODE)
		{
			I2C_WAIT_ADDR(I2C2_R);
			I2C_CLR_ADDR(I2C2_R, LOC_u32Temp);
		}
		else{}

		while(0 != Copy_u8Size)
		{
			I2C_WAIT_TXE(I2C2_R);

			I2C_WRITE_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
			Copy_u8Size--;
			LOC_u8Counter++;

			if((TRUE == I2C_GET_BTF(I2C2_R)) && (0 != Copy_u8Size))
			{
				I2C_WRITE_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
				Copy_u8Size--;
				LOC_u8Counter++;
			}
			else{}
		}
		I2C_WAIT_AF(I2C2_R);
		I2C_CLR_AF(I2C2_R);	
		I2C_ACK_ENABLE(I2C2_R, FALSE);
	}
	break;
	case I2C_3:
	{
		if (I2C3_R->CR1.BIT.PE == FALSE)
		{
			I2C_ENABLE(I2C3_R, TRUE);
		}
		else
		{
		}
		I2C_POS_ENABLE(I2C3_R, FALSE);
		I2C_ACK_ENABLE(I2C3_R, TRUE);
		I2C_WAIT_ADDR(I2C3_R);
		I2C_CLR_ADDR(I2C3_R, LOC_u32Temp);
		if(_10BITS_I2C == I2C3_R->OAR1.BIT.ADDMODE)
		{
			I2C_WAIT_ADDR(I2C3_R);
			I2C_CLR_ADDR(I2C3_R, LOC_u32Temp);
		}
		else{}

		while(0 != Copy_u8Size)
		{
			I2C_WAIT_TXE(I2C3_R);

			I2C_WRITE_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
			Copy_u8Size--;
			LOC_u8Counter++;

			if((TRUE == I2C_GET_BTF(I2C3_R)) && (0 != Copy_u8Size))
			{
				I2C_WRITE_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
				Copy_u8Size--;
				LOC_u8Counter++;
			}
			else{}
		}
		I2C_WAIT_AF(I2C3_R);
		I2C_CLR_AF(I2C3_R);	
		I2C_ACK_ENABLE(I2C3_R, FALSE);
	}
	break;
	default:
		break;
	}
}

void I2C_vidSlaveRX(I2C_x Copy_enuI2C_x, u8 *Copy_u8PtrBffr, u8 Copy_u8Size)
{
	u8 LOC_u8Counter = 0;
	volatile u32 LOC_u32Temp = 0;

	switch (Copy_enuI2C_x)
	{
	case I2C_1:
	{
		if (I2C1_R->CR1.BIT.PE == FALSE)
		{
			I2C_ENABLE(I2C1_R, TRUE);
		}
		else
		{
		}
		I2C_POS_ENABLE(I2C1_R, FALSE);
		I2C_ACK_ENABLE(I2C1_R, TRUE);
		I2C_WAIT_ADDR(I2C1_R);
		I2C_CLR_ADDR(I2C1_R, LOC_u32Temp);

		while(0 != Copy_u8Size)
		{
			I2C_WAIT_RXNE(I2C1_R);
			I2C_READ_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
			LOC_u8Counter++;
			Copy_u8Size--;

			if((TRUE == I2C_GET_BTF(I2C1_R)) && (0 != Copy_u8Size))
			{
				I2C_READ_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
				LOC_u8Counter++;
				Copy_u8Size--;
			}
			else{}
		}
		I2C_WAIT_STOPF(I2C1_R);
		I2C_CLR_STOPF(I2C1_R);
		I2C_ACK_ENABLE(I2C1_R, FALSE);
	}
	break;
	case I2C_2:
	{
		if (I2C2_R->CR1.BIT.PE == FALSE)
		{
			I2C_ENABLE(I2C2_R, TRUE);
		}
		else
		{
		}
		I2C_POS_ENABLE(I2C2_R, FALSE);
		I2C_ACK_ENABLE(I2C2_R, TRUE);
		I2C_WAIT_ADDR(I2C2_R);
		I2C_CLR_ADDR(I2C2_R, LOC_u32Temp);

		while(0 != Copy_u8Size)
		{
			I2C_WAIT_RXNE(I2C2_R);
			I2C_READ_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
			LOC_u8Counter++;
			Copy_u8Size--;

			if((TRUE == I2C_GET_BTF(I2C2_R)) && (0 != Copy_u8Size))
			{
				I2C_READ_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
				LOC_u8Counter++;
				Copy_u8Size--;
			}
			else{}
		}
		I2C_WAIT_STOPF(I2C2_R);
		I2C_CLR_STOPF(I2C2_R);
		I2C_ACK_ENABLE(I2C2_R, FALSE);
	}
	break;
	case I2C_3:
	{
		if (I2C3_R->CR1.BIT.PE == FALSE)
		{
			I2C_ENABLE(I2C3_R, TRUE);
		}
		else
		{
		}
		I2C_POS_ENABLE(I2C3_R, FALSE);
		I2C_ACK_ENABLE(I2C3_R, TRUE);
		I2C_WAIT_ADDR(I2C3_R);
		I2C_CLR_ADDR(I2C3_R, LOC_u32Temp);

		while(0 != Copy_u8Size)
		{
			I2C_WAIT_RXNE(I2C3_R);
			I2C_READ_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
			LOC_u8Counter++;
			Copy_u8Size--;

			if((TRUE == I2C_GET_BTF(I2C3_R)) && (0 != Copy_u8Size))
			{
				I2C_READ_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
				LOC_u8Counter++;
				Copy_u8Size--;
			}
			else{}
		}
		I2C_WAIT_STOPF(I2C3_R);
		I2C_CLR_STOPF(I2C3_R);
		I2C_ACK_ENABLE(I2C3_R, FALSE);
	}
	break;
	default:
		break;
	}
}

void I2C_vidMemWrite(I2C_x Copy_enuI2C_x, u8 Copy_u8SlaveAddress, u16 Copy_u16MemAddress, I2C_MEM_SIZE Copy_enuMemSize, u8 *Copy_u8PtrBffr, u8 Copy_u8Size)
{
	u8 LOC_u8Counter = 0;
	switch (Copy_enuI2C_x)
	{
	case I2C_1:
	{
		I2C_WAIT_BUSY(I2C1_R);
		if (I2C1_R->CR1.BIT.PE == FALSE)
		{
			I2C_ENABLE(I2C1_R, TRUE);
		}
		else
		{
		}

		I2C_POS_ENABLE(I2C1_R, FALSE);
		I2C_GENERATE_START(I2C1_R);
		I2C_vidSendSlaveAddress(I2C_1, Copy_u8SlaveAddress, I2C_MASTER_TRANS);
		I2C_WAIT_TXE(I2C1_R);

		if (_8BITS_I2C_MEM == Copy_enuMemSize)
		{
			I2C_WRITE_DATA(I2C1_R, I2C_MEMORY_ADD_LSB(Copy_u16MemAddress));
		}
		else if (_16BITS_I2C_MEM == Copy_enuMemSize)
		{
			I2C_WRITE_DATA(I2C1_R, I2C_MEMORY_ADD_MSB(Copy_u16MemAddress));
			I2C_WAIT_TXE(I2C1_R);
			I2C_WRITE_DATA(I2C1_R, I2C_MEMORY_ADD_LSB(Copy_u16MemAddress));
		}
		else
		{
		}

		while (0 != Copy_u8Size)
		{
			I2C_WAIT_TXE(I2C1_R);
			I2C_WRITE_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
			LOC_u8Counter++;
			Copy_u8Size--;

			if ((TRUE == I2C1_R->SR1.BIT.BTF) && (0 != Copy_u8Size))
			{
				I2C_WRITE_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
				LOC_u8Counter++;
				Copy_u8Size--;
			}
			else
			{
			}
		}

		I2C_WAIT_BTF(I2C1_R);
		I2C_GENERATE_STOP(I2C1_R);
		//I2C_ENABLE(I2C1_R, FALSE);
	}
	break;
	case I2C_2:
	{
		I2C_WAIT_BUSY(I2C2_R);
		if (I2C2_R->CR1.BIT.PE == FALSE)
		{
			I2C_ENABLE(I2C2_R, TRUE);
		}
		else
		{
		}

		I2C_POS_ENABLE(I2C2_R, FALSE);
		I2C_GENERATE_START(I2C2_R);
		I2C_vidSendSlaveAddress(I2C_2, Copy_u8SlaveAddress, I2C_MASTER_TRANS);
		I2C_WAIT_TXE(I2C2_R);

		if (_8BITS_I2C_MEM == Copy_enuMemSize)
		{
			I2C_WRITE_DATA(I2C2_R, I2C_MEMORY_ADD_LSB(Copy_u16MemAddress));
		}
		else if (_16BITS_I2C_MEM == Copy_enuMemSize)
		{
			I2C_WRITE_DATA(I2C2_R, I2C_MEMORY_ADD_MSB(Copy_u16MemAddress));
			I2C_WAIT_TXE(I2C2_R);
			I2C_WRITE_DATA(I2C2_R, I2C_MEMORY_ADD_LSB(Copy_u16MemAddress));
		}
		else
		{
		}

		while (0 != Copy_u8Size)
		{
			I2C_WAIT_TXE(I2C2_R);
			I2C_WRITE_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
			LOC_u8Counter++;
			Copy_u8Size--;

			if ((TRUE == I2C2_R->SR1.BIT.BTF) && (0 != Copy_u8Size))
			{
				I2C_WRITE_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
				LOC_u8Counter++;
				Copy_u8Size--;
			}
			else
			{
			}
		}

		I2C_WAIT_BTF(I2C2_R);
		I2C_GENERATE_STOP(I2C2_R);
		//I2C_ENABLE(I2C2_R, FALSE);
	}
	break;
	case I2C_3:
	{
		I2C_WAIT_BUSY(I2C3_R);
		if (I2C3_R->CR1.BIT.PE == FALSE)
		{
			I2C_ENABLE(I2C3_R, TRUE);
		}
		else
		{
		}

		I2C_POS_ENABLE(I2C3_R, FALSE);
		I2C_GENERATE_START(I2C3_R);
		I2C_vidSendSlaveAddress(I2C_3, Copy_u8SlaveAddress, I2C_MASTER_TRANS);
		I2C_WAIT_TXE(I2C3_R);

		if (_8BITS_I2C_MEM == Copy_enuMemSize)
		{
			I2C_WRITE_DATA(I2C3_R, I2C_MEMORY_ADD_LSB(Copy_u16MemAddress));
		}
		else if (_16BITS_I2C_MEM == Copy_enuMemSize)
		{
			I2C_WRITE_DATA(I2C3_R, I2C_MEMORY_ADD_MSB(Copy_u16MemAddress));
			I2C_WAIT_TXE(I2C3_R);
			I2C_WRITE_DATA(I2C3_R, I2C_MEMORY_ADD_LSB(Copy_u16MemAddress));
		}
		else
		{
		}

		while (0 != Copy_u8Size)
		{
			I2C_WAIT_TXE(I2C3_R);
			I2C_WRITE_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
			LOC_u8Counter++;
			Copy_u8Size--;

			if ((TRUE == I2C3_R->SR1.BIT.BTF) && (0 != Copy_u8Size))
			{
				I2C_WRITE_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
				LOC_u8Counter++;
				Copy_u8Size--;
			}
			else
			{
			}
		}

		I2C_WAIT_BTF(I2C3_R);
		I2C_GENERATE_STOP(I2C3_R);
		//I2C_ENABLE(I2C3_R, FALSE);
	}
	break;
	default:
		break;
	}
}

void I2C_vidMemRead(I2C_x Copy_enuI2C_x, u8 Copy_u8SlaveAddress, u16 Copy_u16MemAddress, I2C_MEM_SIZE Copy_enuMemSize, u8 *Copy_u8PtrBffr, u8 Copy_u8Size)
{
	u8 LOC_u8Counter = 0;
	volatile u32 LOC_u32Temp = 0;

	switch (Copy_enuI2C_x)
	{
	case I2C_1:
	{
		I2C_WAIT_BUSY(I2C1_R);
		if (I2C1_R->CR1.BIT.PE == FALSE)
		{
			I2C_ENABLE(I2C1_R, TRUE);
		}
		else
		{
		}

		I2C_POS_ENABLE(I2C1_R, FALSE);
		I2C_ACK_ENABLE(I2C1_R, TRUE);
		I2C_GENERATE_START(I2C1_R);
		I2C_vidSendSlaveAddress(I2C_1, Copy_u8SlaveAddress, I2C_MASTER_TRANS);
		I2C_WAIT_TXE(I2C1_R);

		if (_8BITS_I2C_MEM == Copy_enuMemSize)
		{
			I2C_WRITE_DATA(I2C1_R, I2C_MEMORY_ADD_LSB(Copy_u16MemAddress));
		}
		else if (_16BITS_I2C_MEM == Copy_enuMemSize)
		{
			I2C_WRITE_DATA(I2C1_R, I2C_MEMORY_ADD_MSB(Copy_u16MemAddress));
			I2C_WAIT_TXE(I2C1_R);
			I2C_WRITE_DATA(I2C1_R, I2C_MEMORY_ADD_LSB(Copy_u16MemAddress));
		}
		else
		{
		}

		I2C_WAIT_TXE(I2C1_R);
		I2C_GENERATE_START(I2C1_R);
		I2C_vidSendSlaveAddress(I2C_1, Copy_u8SlaveAddress, I2C_MASTER_RECEIVE);

		switch (Copy_u8Size)
		{
		case 0:
			I2C_CLR_ADDR(I2C1_R, LOC_u32Temp);
			I2C_GENERATE_STOP(I2C1_R);
			break;
		case 1:
			I2C_ACK_ENABLE(I2C1_R, FALSE);
			I2C_CLR_ADDR(I2C1_R, LOC_u32Temp);
			I2C_GENERATE_STOP(I2C1_R);
			break;
		case 2:
			I2C_ACK_ENABLE(I2C1_R, FALSE);
			I2C_POS_ENABLE(I2C1_R, TRUE);
			I2C_CLR_ADDR(I2C1_R, LOC_u32Temp);
			break;
		default:
			// I2C_ACK_ENABLE(I2C1_R, TRUE);
			I2C_CLR_ADDR(I2C1_R, LOC_u32Temp);
			break;
		}

		while (0 != Copy_u8Size)
		{
			if (Copy_u8Size <= 3)
			{
				switch (Copy_u8Size)
				{
				case 1:
				{

					I2C_WAIT_RXNE(I2C1_R);
					I2C_READ_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				break;
				case 2:
				{
					I2C_WAIT_BTF(I2C1_R);
					I2C_GENERATE_STOP(I2C1_R);
					I2C_READ_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
					I2C_READ_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				break;
				default:
				{
					I2C_WAIT_BTF(I2C1_R);
					I2C_ACK_ENABLE(I2C1_R, FALSE);
					I2C_READ_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
					I2C_WAIT_BTF(I2C1_R);
					I2C_GENERATE_STOP(I2C1_R);
					I2C_READ_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
					I2C_READ_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				break;
				} // end of switch
			}
			else
			{
				I2C_WAIT_RXNE(I2C1_R);
				I2C_READ_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
				LOC_u8Counter++;
				Copy_u8Size--;
				if (TRUE == I2C1_R->SR1.BIT.BTF)
				{
					I2C_READ_DATA(I2C1_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				else
				{
				}
			}
		}
		//I2C_ENABLE(I2C1_R, FALSE);
	}
	break;
	case I2C_2:
	{
		//I2C_SOFTWARE_RESET(I2C2_R);
		I2C_WAIT_BUSY(I2C2_R);
		if (I2C2_R->CR1.BIT.PE == FALSE)
		{
			I2C_ENABLE(I2C2_R, TRUE);
		}
		else
		{
		}

		I2C_POS_ENABLE(I2C2_R, FALSE);
		I2C_ACK_ENABLE(I2C2_R, TRUE);
		I2C_GENERATE_START(I2C2_R);
		I2C_vidSendSlaveAddress(I2C_2, Copy_u8SlaveAddress, I2C_MASTER_TRANS);
		I2C_WAIT_TXE(I2C2_R);

		if (_8BITS_I2C_MEM == Copy_enuMemSize)
		{
			I2C_WRITE_DATA(I2C2_R, I2C_MEMORY_ADD_LSB(Copy_u16MemAddress));
		}
		else if (_16BITS_I2C_MEM == Copy_enuMemSize)
		{
			I2C_WRITE_DATA(I2C2_R, I2C_MEMORY_ADD_MSB(Copy_u16MemAddress));
			I2C_WAIT_TXE(I2C2_R);
			I2C_WRITE_DATA(I2C2_R, I2C_MEMORY_ADD_LSB(Copy_u16MemAddress));
		}
		else
		{
		}

		I2C_WAIT_TXE(I2C2_R);
		I2C_GENERATE_START(I2C2_R);
		I2C_vidSendSlaveAddress(I2C_2, Copy_u8SlaveAddress, I2C_MASTER_RECEIVE);

		switch (Copy_u8Size)
		{
		case 0:
			I2C_CLR_ADDR(I2C2_R, LOC_u32Temp);
			I2C_GENERATE_STOP(I2C2_R);
			break;
		case 1:
			I2C_ACK_ENABLE(I2C2_R, FALSE);
			I2C_CLR_ADDR(I2C2_R, LOC_u32Temp);
			I2C_GENERATE_STOP(I2C2_R);
			break;
		case 2:
			I2C_ACK_ENABLE(I2C2_R, FALSE);
			I2C_POS_ENABLE(I2C2_R, TRUE);
			I2C_CLR_ADDR(I2C2_R, LOC_u32Temp);
			break;
		default:
			// I2C_ACK_ENABLE(I2C2_R, TRUE);
			I2C_CLR_ADDR(I2C2_R, LOC_u32Temp);
			break;
		}

		while (0 != Copy_u8Size)
		{
			if (Copy_u8Size <= 3)
			{
				switch (Copy_u8Size)
				{
				case 1:
				{

					I2C_WAIT_RXNE(I2C2_R);
					I2C_READ_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				break;
				case 2:
				{
					I2C_WAIT_BTF(I2C2_R);
					I2C_GENERATE_STOP(I2C2_R);
					I2C_READ_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
					I2C_READ_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				break;
				default:
				{
					I2C_WAIT_BTF(I2C2_R);
					I2C_ACK_ENABLE(I2C2_R, FALSE);
					I2C_READ_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
					I2C_WAIT_BTF(I2C2_R);
					I2C_GENERATE_STOP(I2C2_R);
					I2C_READ_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
					I2C_READ_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				break;
				} // end of switch
			}
			else
			{
				I2C_WAIT_RXNE(I2C2_R);
				I2C_READ_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
				LOC_u8Counter++;
				Copy_u8Size--;
				if (TRUE == I2C2_R->SR1.BIT.BTF)
				{
					I2C_READ_DATA(I2C2_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				else
				{
				}
			}
		}
		//I2C_ENABLE(I2C2_R, FALSE);
	}
	break;
	case I2C_3:
	{
		I2C_WAIT_BUSY(I2C3_R);
		if (I2C2_R->CR1.BIT.PE == FALSE)
		{
			I2C_ENABLE(I2C3_R, TRUE);
		}
		else
		{
		}

		I2C_POS_ENABLE(I2C3_R, FALSE);
		I2C_ACK_ENABLE(I2C3_R, TRUE);
		I2C_GENERATE_START(I2C3_R);
		I2C_vidSendSlaveAddress(I2C_3, Copy_u8SlaveAddress, I2C_MASTER_TRANS);
		I2C_WAIT_TXE(I2C3_R);

		if (_8BITS_I2C_MEM == Copy_enuMemSize)
		{
			I2C_WRITE_DATA(I2C3_R, I2C_MEMORY_ADD_LSB(Copy_u16MemAddress));
		}
		else if (_16BITS_I2C_MEM == Copy_enuMemSize)
		{
			I2C_WRITE_DATA(I2C3_R, I2C_MEMORY_ADD_MSB(Copy_u16MemAddress));
			I2C_WAIT_TXE(I2C3_R);
			I2C_WRITE_DATA(I2C3_R, I2C_MEMORY_ADD_LSB(Copy_u16MemAddress));
		}
		else
		{
		}

		I2C_WAIT_TXE(I2C3_R);
		I2C_GENERATE_START(I2C3_R);
		I2C_vidSendSlaveAddress(I2C_3, Copy_u8SlaveAddress, I2C_MASTER_RECEIVE);

		switch (Copy_u8Size)
		{
		case 0:
			I2C_CLR_ADDR(I2C3_R, LOC_u32Temp);
			I2C_GENERATE_STOP(I2C3_R);
			break;
		case 1:
			I2C_ACK_ENABLE(I2C3_R, FALSE);
			I2C_CLR_ADDR(I2C3_R, LOC_u32Temp);
			I2C_GENERATE_STOP(I2C3_R);
			break;
		case 2:
			I2C_ACK_ENABLE(I2C3_R, FALSE);
			I2C_POS_ENABLE(I2C3_R, TRUE);
			I2C_CLR_ADDR(I2C3_R, LOC_u32Temp);
			break;
		default:
			// I2C_ACK_ENABLE(I2C3_R, TRUE);
			I2C_CLR_ADDR(I2C3_R, LOC_u32Temp);
			break;
		}

		while (0 != Copy_u8Size)
		{
			if (Copy_u8Size <= 3)
			{
				switch (Copy_u8Size)
				{
				case 1:
				{

					I2C_WAIT_RXNE(I2C3_R);
					I2C_READ_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				break;
				case 2:
				{
					I2C_WAIT_BTF(I2C3_R);
					I2C_GENERATE_STOP(I2C3_R);
					I2C_READ_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
					I2C_READ_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				break;
				default:
				{
					I2C_WAIT_BTF(I2C3_R);
					I2C_ACK_ENABLE(I2C3_R, FALSE);
					I2C_READ_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
					I2C_WAIT_BTF(I2C3_R);
					I2C_GENERATE_STOP(I2C3_R);
					I2C_READ_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
					I2C_READ_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				break;
				} // end of switch
			}
			else
			{
				I2C_WAIT_RXNE(I2C3_R);
				I2C_READ_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
				LOC_u8Counter++;
				Copy_u8Size--;
				if (TRUE == I2C3_R->SR1.BIT.BTF)
				{
					I2C_READ_DATA(I2C3_R, Copy_u8PtrBffr[LOC_u8Counter]);
					LOC_u8Counter++;
					Copy_u8Size--;
				}
				else
				{
				}
			}
		}
		//I2C_ENABLE(I2C3_R, FALSE);
	}
	break;
	default:
		break;
	}
}

static u32 I2C_u32CRRHanlder(I2C_DUTY_CYCLE Copy_enuDutyCycle, u32 Copy_u32FreqDesired)
{
	u32 LOC_u32CRRValue = 0;
	// f64 LOC_f64Tp = 1.0/((f64)(I2C_APB1_FREQ_IN_MHz*1000000));
	// f64 LOC_f64T  = 1.0/((f64)Copy_u32FreqDesired);

	switch (Copy_enuDutyCycle)
	{
	case FM_MODE_DUTY_1_2:
	{
		// LOC_f64Tp 		= (3.0*LOC_f64Tp);
		LOC_u32CRRValue = (((I2C_APB1_FREQ_IN_MHz * 1000000) - 1) / (Copy_u32FreqDesired * 3)) + 1;
		break;
	}
	case FM_MODE_DUTY_16_9:
	{
		// LOC_f64Tp 		= (25.0*LOC_f64Tp);
		LOC_u32CRRValue = (((I2C_APB1_FREQ_IN_MHz * 1000000) - 1) / (Copy_u32FreqDesired * 25)) + 1;
		break;
	}
	case STANDARD_MODE_DUTY:
	{
		// LOC_f64Tp 		= (2.0*LOC_f64Tp);
		LOC_u32CRRValue = (((I2C_APB1_FREQ_IN_MHz * 1000000) - 1) / (Copy_u32FreqDesired * 2)) + 1;
		break;
	}
	} // end of switch
	return LOC_u32CRRValue;
}

static void I2C_vidAddressHandler(I2C_x Copy_enuI2C_x, I2C_ADD_MODE AddMode, u16 Add1, I2C_DUAL_ADD DualMode, u8 Add2)
{
	Add1 &= (0x03FF);
	switch (Copy_enuI2C_x)
	{
	case I2C_1:
	{
		I2C1_R->OAR1.REGISTER &= (0xFFFFFC00);
		I2C1_R->OAR1.BIT.ADDMODE = AddMode;
		switch (AddMode)
		{
		case _7BITS_I2C:
		{
			Add1 = (Add1 << 1);
			I2C1_R->OAR1.REGISTER |= Add1;
		}
		break;
		case _10BITS_I2C:
		{
			I2C1_R->OAR1.REGISTER |= (u32)Add1;
		}
		break;
		default:
			break;
		} // end of switch

		I2C1_R->OAR2.BIT.ENDUAL = DualMode;
		I2C1_R->OAR2.BIT.ADD2_7_1 = (u32)Add2;
	}
	break;
	case I2C_2:
	{
		I2C2_R->OAR1.REGISTER &= (0xFFFFFC00);
		I2C2_R->OAR1.BIT.ADDMODE = AddMode;
		switch (AddMode)
		{
		case _7BITS_I2C:
		{
			Add1 = (Add1 << 1);
			I2C2_R->OAR1.REGISTER |= Add1;
		}
		break;
		case _10BITS_I2C:
		{
			I2C2_R->OAR1.REGISTER |= (u32)Add1;
		}
		break;
		default:
			break;
		} // end of switch

		I2C2_R->OAR2.BIT.ENDUAL = DualMode;
		I2C2_R->OAR2.BIT.ADD2_7_1 = (u32)Add2;
	}
	break;
	case I2C_3:
	{
		I2C3_R->OAR1.REGISTER &= (0xFFFFFC00);
		I2C3_R->OAR1.BIT.ADDMODE = AddMode;
		switch (AddMode)
		{
		case _7BITS_I2C:
		{
			Add1 = (Add1 << 1);
			I2C3_R->OAR1.REGISTER |= Add1;
		}
		break;
		case _10BITS_I2C:
		{
			I2C3_R->OAR1.REGISTER |= (u32)Add1;
		}
		break;
		default:
			break;
		} // end of switch

		I2C3_R->OAR2.BIT.ENDUAL = DualMode;
		I2C3_R->OAR2.BIT.ADD2_7_1 = (u32)Add2;
	}
	break;
	default:
		break;
	}
}

static void I2C_vidSendSlaveAddress(I2C_x Copy_enuI2C_x, u8 Copy_u8Address, I2C_MASTER Copy_enuMasterState)
{
	volatile u32 LOC_u32Temp;
	switch (Copy_enuI2C_x)
	{
	case I2C_1:
	{
		switch (Copy_enuMasterState)
		{
		case I2C_MASTER_TRANS:
			I2C_WRITE_DATA(I2C1_R, I2C_WRITE(Copy_u8Address));
			I2C_WAIT_ADDR(I2C1_R);
			I2C_CLR_ADDR(I2C1_R, LOC_u32Temp);
			break;
		case I2C_MASTER_RECEIVE:
			I2C_WRITE_DATA(I2C1_R, I2C_READ(Copy_u8Address));
			I2C_WAIT_ADDR(I2C1_R);
			break;
		default:
			break;
		}
	}
	break;
	case I2C_2:
	{
		switch (Copy_enuMasterState)
		{
		case I2C_MASTER_TRANS:
			I2C_WRITE_DATA(I2C2_R, I2C_WRITE(Copy_u8Address));
			I2C_WAIT_ADDR(I2C2_R);
			I2C_CLR_ADDR(I2C2_R, LOC_u32Temp);
			break;
		case I2C_MASTER_RECEIVE:
			I2C_WRITE_DATA(I2C2_R, I2C_READ(Copy_u8Address));
			I2C_WAIT_ADDR(I2C2_R);
			break;
		default:
			break;
		}
	}
	break;
	case I2C_3:
	{
		switch (Copy_enuMasterState)
		{
		case I2C_MASTER_TRANS:
			I2C_WRITE_DATA(I2C3_R, I2C_WRITE(Copy_u8Address));
			I2C_WAIT_ADDR(I2C3_R);
			I2C_CLR_ADDR(I2C3_R, LOC_u32Temp);
			break;
		case I2C_MASTER_RECEIVE:
			I2C_WRITE_DATA(I2C3_R, I2C_READ(Copy_u8Address));
			I2C_WAIT_ADDR(I2C3_R);
			break;
		default:
			break;
		}
	}
	break;
	default:
		break;
	}
}

