/*********************************
Author	:	Hosam Magdy
Date	:	22 July 2022
Version	:	1.0
*********************************/
#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(VAR,BITNO) (VAR) |=  (1 << (BITNO))
#define CLR_BIT(VAR,BITNO) (VAR) &= ~(1 << (BITNO))
#define TOG_BIT(VAR,BITNO) (VAR) ^=  (1 << (BITNO))
#define GET_BIT(VAR,BITNO) (((VAR) >> (BITNO)) & 1)

#define CLR_TWO_BITS(VAR,_1st_BITNO)	(VAR) &= ~( ((u32)3) << ((_1st_BITNO)*2) )
#define CLR_FOUR_BITS(VAR,_1st_BITNO)	(VAR) &= ~( ((u32)15) << ((_1st_BITNO)*4) )

#endif
