/***************************************************************************
 *
 *        Description: The main file of the system. At the moment that is a 
 *			working version. Probably, the most of the functions will be relocated
 * 
 ***************************************************************************/

#include "scheduler.h"

#include "timer.h"
#include "types.h"

#include <stdlib.h>

void taskInit(task_t* task, void (*runTask)(), bool (*checkTaskRdy)(), 
		const uint8_t priority, const time_t period)
{
	
	if(task == NULL)
	{
		return; 
	}
	
	if(runTask == NULL)
	{
		return;
	}

	task->priority = priority;
	task->period_us = period;
	task->time.prevEventStartTime = 0; 
	task->run = runTask;
	task->checkRdy = checkTaskRdy;
	task->timeSpent = 0;
}

void schedulerUpdate(scheduler_t* sched)
{
	time_t eventStartTime = 0;
	uint8_t i = 0;
	
	if(sched == NULL) 
	{
		return; 
	}
	
	for(i = 0; i < sched->numberOfTasks; i++)
	{
		if(sched->taskPtr[i].run == NULL)
		{
			continue;
		}
		// with that I can measure how much time I spent inside the function
		eventStartTime = getSysTimer(); 
	
		if((sched->taskPtr[i].checkRdy()) || ((eventStartTime - sched->taskPtr[i].time.prevEventStartTime) > sched->taskPtr[i].period_us))
		{
			sched->taskPtr[i].run();
			sched->taskPtr[i].timeSpent += (getSysTimer() - eventStartTime);
			sched->taskPtr[i].time.prevEventStartTime = eventStartTime;
		}
	}
}

bool taskAlwaysNotRdy(void)
{
	return false;
}
