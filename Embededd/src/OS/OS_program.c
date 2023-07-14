/*
 * OS_program.c
 *
 *  Created on: Jul 14, 2023
 *      Author: Hosam
 */

#include "LIB/STD_TYPES.h"

#include "MCAL/SYSTICK_interface.h"

#include "APP/DataAcquisition.h"
#include "APP/RobotMotion.h"

#include "OS/OS_config.h"
#include "OS/OS_interface.h"

static tenuOperatingSystemState LOC_enuOSState;

static u8 LOC_u8Periodicity[OS_NUM_OF_TASKS] = {0};


static tstrTask GLOB_astrTasks[OS_NUM_OF_TASKS] =
{
		[0] = {.enuTaskState = TASK_READY, .u8Periodicity = 2, .pTaskFunction = DAQ_vidCollectData},
		[1] = {.enuTaskState = TASK_READY, .u8Periodicity = 2, .pTaskFunction = RMO_vidMotionHandler},
};

void OS_vidInit(void)
{
	u8 u8Counter;
	u32 u32SysTickTicks = 0;

	LOC_enuOSState = OS_INIT;

	u32SysTickTicks = 2000 * OS_TICK_MILLISECOND;

	for(u8Counter = 0; u8Counter < OS_NUM_OF_TASKS; u8Counter++)
	{
		LOC_u8Periodicity[u8Counter] = GLOB_astrTasks[u8Counter].u8Periodicity;
	}
	LOC_u8Periodicity[0]--;

	SYSTICK_vidStartAsync(u32SysTickTicks, OS_vidSystickISR);
}

void OS_vidScheduler(void)
{
	u8 u8Counter;
	switch(LOC_enuOSState)
	{
	case OS_INIT:

		LOC_enuOSState = OS_WAITING;

		for(u8Counter = 0; u8Counter < OS_NUM_OF_TASKS; u8Counter++)
		{
			GLOB_astrTasks[u8Counter].enuTaskState = TASK_RUNNING;
			GLOB_astrTasks[u8Counter].pTaskFunction();
			GLOB_astrTasks[u8Counter].enuTaskState = TASK_READY;
		}
		u8Counter = 0;

		break;

	case OS_EXECUTING:

		LOC_enuOSState = OS_WAITING;

		for(u8Counter = 0; u8Counter < OS_NUM_OF_TASKS; u8Counter++)
		{
			if( (1 == LOC_u8Periodicity[u8Counter])
					&&
				(TASK_READY == GLOB_astrTasks[u8Counter].enuTaskState))
			{
				GLOB_astrTasks[u8Counter].enuTaskState = TASK_RUNNING;
				GLOB_astrTasks[u8Counter].pTaskFunction();
				GLOB_astrTasks[u8Counter].enuTaskState = TASK_READY;

				LOC_u8Periodicity[u8Counter] = GLOB_astrTasks[u8Counter].u8Periodicity + 1;
			}
		}

		for(u8Counter = 0; u8Counter < OS_NUM_OF_TASKS; u8Counter++)
		{
			LOC_u8Periodicity[u8Counter]--;
		}

		break;

	case OS_WAITING:

		LOC_enuOSState = OS_WAITING;

		break;
	}
}

void OS_vidSystickISR(void)
{
	LOC_enuOSState = OS_EXECUTING;
}
