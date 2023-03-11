/*
 * GPIO_config.c
 *
 *  Created on: Aug 23, 2022
 *      Author: Hosam
 */

#include "LIB/STD_TYPES.h"

#include "MCAL/GPIO_interface.h"
#include "MCAL/GPIO_config.h"
#include "MCAL/GPIO_private.h"

PIN_CONFIG	GLOB_prtStrPins[NUMBER_OF_USED_PINS] =
{

		[0] = {PORT_B, PIN0, OUTPUT, PUSH_PULL, NORMAL, NO_PULL_UP_DOWN, GPIO_NOT_USED},
		[1] = {PORT_B, PIN6, ALT_FUNC, OPEN_DRAIN, VERY_HIGH, PULL_UP, AF_4},
		[2] = {PORT_B, PIN7, ALT_FUNC, OPEN_DRAIN, VERY_HIGH, PULL_UP, AF_4},
		[3] = {PORT_A, PIN9, ALT_FUNC, PUSH_PULL, NORMAL, NO_PULL_UP_DOWN, AF_7},
		[4] = {PORT_A, PIN10, ALT_FUNC, PUSH_PULL, NORMAL, NO_PULL_UP_DOWN, AF_7},
};
