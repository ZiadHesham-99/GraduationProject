/*
 * OS_interface.h
 *
 *  Created on: Jul 14, 2023
 *      Author: Hosam
 */

#ifndef OS_OS_INTERFACE_H_
#define OS_OS_INTERFACE_H_

typedef enum
{
	OS_INIT = (u8)0,
	OS_WAITING,
	OS_EXECUTING
}tenuOperatingSystemState;

typedef enum
{
	TASK_DORMANT = (u8)0,
	TASK_READY,
	TASK_RUNNING,
	TASK_WAITING,
	TASK_SUSPEND
}tenuTaskState;

typedef struct
{
	tenuTaskState 	enuTaskState;
	u8				u8Periodicity;
	void (*pTaskFunction)(void);
}tstrTask;

void OS_vidInit(void);
void OS_vidScheduler(void);

void led1(void);
void led2(void);

void OS_vidSystickISR(void);

#endif /* OS_OS_INTERFACE_H_ */
