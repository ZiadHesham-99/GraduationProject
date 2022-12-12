/*
 * GPIO_config.c
 *
 *  Created on: Aug 23, 2022
 *      Author: Hosam
 */

#include "GPIO_private.h"
#include "GPIO_interface.h"
#include "GPIO_config.h"

PIN_CONFIG	GLOB_prtStrPins[NUMBER_OF_USED_PINS] = {
		[0] = {.PORT = PORT_A, .PIN=PIN9, .MODE=ALT_FUNC, .TYPE=GPIO_NOT_USED, .SPEED=NORMAL, .PULL_UP_DOWN=GPIO_NOT_USED, .AF=AF_USART1_2},
		[1] = {.PORT = PORT_A, .PIN=PIN10, .MODE=ALT_FUNC, .TYPE=GPIO_NOT_USED, .SPEED=NORMAL, .PULL_UP_DOWN=GPIO_NOT_USED, .AF=AF_USART1_2},
		[2] = {.PORT = PORT_B, .PIN=PIN8, .MODE=ALT_FUNC, .TYPE=GPIO_NOT_USED, .SPEED=NORMAL, .PULL_UP_DOWN=GPIO_NOT_USED, .AF=AF_I2C1_3},
		[3] = {.PORT = PORT_B, .PIN=PIN9, .MODE=ALT_FUNC, .TYPE=GPIO_NOT_USED, .SPEED=NORMAL, .PULL_UP_DOWN=GPIO_NOT_USED, .AF=AF_I2C1_3}

};
