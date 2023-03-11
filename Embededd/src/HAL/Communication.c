/*
 * Communication.c
 *
 *  Created on: March 1, 2022
 *      Author: Hosam
 */
#include<math.h>

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "HAL/Communication.h"

void vidToString(s16 Copy_s16Num, u8 Copy_u8DigitsNum, u8 * Copy_pu8Bffr)
{

    u8  u8Counter;
    u16 u16Temp = 0;
    BOOL bFirstTime = TRUE;

    u16Temp = (u16)(pow(10.0, ((f64)(Copy_u8DigitsNum-1))));

    if(Copy_s16Num > 0)
    {
        Copy_pu8Bffr[0] = '+';
    }
    else
    {
        Copy_pu8Bffr[0] = '-';
        Copy_s16Num *=(-1);
    }
    for(u8Counter = 1; u8Counter <= Copy_u8DigitsNum; u8Counter++)
    {
        if(TRUE == bFirstTime)
        {
            Copy_pu8Bffr[u8Counter] = (Copy_s16Num/u16Temp)+(0x30);
            bFirstTime = FALSE;
        }
        else
        {
            Copy_pu8Bffr[u8Counter] = ((Copy_s16Num%u16Temp)/(u16Temp/10))+(0x30);
            u16Temp /= 10;
        }
    }
}

s16  s16ToInteger(u8 * Copy_pu8Bffr, u8 Copy_u8DigitsNum)
{
    s8  s8Counter = 0;
    s16 s16Temp = 0;
    s16 s16Number = 0;
    s16 s16Tens = 10;

    BOOL bFirstTime = TRUE;

    for(s8Counter = (Copy_u8DigitsNum-1); s8Counter > 0; s8Counter--)
    {
        if(TRUE == bFirstTime)
        {
            s16Number = (s16)((Copy_pu8Bffr[s8Counter])-(0x30));
            bFirstTime = FALSE;
        }
        else
        {
            s16Temp = (((Copy_pu8Bffr[s8Counter])-(0x30))*s16Tens);
            s16Number += s16Temp;
            s16Tens *=10;
        }
    }
    if(Copy_pu8Bffr[0] == '-')
    { 
        s16Number *= (-1);
    }
    return s16Number;
}

