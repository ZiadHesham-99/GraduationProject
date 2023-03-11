/*
 * OS_interface.h
 *
 *  Created on: Sep 17, 2022
 *      Author: Hosam
 */

#ifndef OS_INTERFACE_H_
#define OS_INTERFACE_H_

typedef enum{
	DORMANT,
	READY,
	RUNNING,
	WAITING,
	SUSPEND
}TASK_STATE;

typedef struct{
	void (*ptr)(void);
	u8 	Priority;
	u8	Task_ID;
	u32 Periodicity;
	u32 First_Delay;
	TASK_STATE State;
}TASK;

void OS_voidTerminateTask(u16 Copy_u16TaskID);
void OS_voidSuspendTask(u16 Copy_u16TaskID);
void OS_voidResumeTask(u16 Copy_u16TaskID);
void OS_voidCreateTask(TASK Copy_structTask);


#endif
