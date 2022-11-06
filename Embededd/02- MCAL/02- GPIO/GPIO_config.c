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
		[0] = {PORTA, PIN0, OUTPUT, PUSH_PULL, NORMAL, GPIO_NOT_USED, GPIO_NOT_USED},
};
