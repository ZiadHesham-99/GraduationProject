/*********************************
Author	:	Hosam Magdy
Date	:	22 July 2022
Version	:	1.0
*********************************/
#ifndef	RCC_PRIVATE_H
#define	RCC_PRIVATE_H

typedef struct{
    u32 CR;
    u32 PLLCFGR;
    u32 CFGR;
    u32 CIR;
    u32 AHB1RSTR;
    u32 AHB2RSTR;
    u32 RCC_RESERVED_0;
    u32 RCC_RESERVED_1;
    u32 APB1RSTR;
    u32 APB2RSTR;
    u32 RCC_RESERVED_2;
    u32 RCC_RESERVED_3;
    u32 AHB1ENR;
    u32 AHB2ENR;
    u32 RCC_RESERVED_4;
    u32 RCC_RESERVED_5;
    u32 APB1ENR;
    u32 APB2ENR;
    u32 RCC_RESERVED_6;
    u32 RCC_RESERVED_7;
    u32 AHB1LPENR;
    u32 AHB2LPENR;
    u32 RCC_RESERVED_8;
    u32 RCC_RESERVED_9;
    u32 APB1LPENR;
    u32 APB2LPENR;
    u32 RCC_RESERVED_10;
    u32 RCC_RESERVED_11;
    u32 BDCR;
    u32 CSR;
    u32 RCC_RESERVED_12;
    u32 RCC_RESERVED_13;
    u32 SSCGR;
    u32 PLLI2SCFGR;
    u32 RCC_RESERVED_14;
    u32 DCKCFGR;
}RCC_REGISTERS;

#define	    RCC_BASE_ADDRESS    			(0x40023800)
#define	    RCC                 			((RCC_REGISTERS*)RCC_BASE_ADDRESS)

#define		CR_CLR_MSK						(0xFAF2FFFF)
#define		CLK_CONFIG_CLR_MSK				(0xFFFF030C)
#define		PERIPH_ID_CLR_MSK				(0x3F)

typedef enum{
	AHB1=(u8)0,
	AHB2,
	APB1,
	APB2
}BUS_ID;

#endif
