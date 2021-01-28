#ifndef SCHEDULER_H
#define	SCHEDULER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

/** @brief struct contains all task related variables.  */
typedef struct
{
	uint8_t priority; ///> NOT USED YET, Task priority. 
	time_t period_us; ///> Period after which task is called
	timeout_t time; ///> time structure
	uint32_t timeSpent; ///> total time spend in given task
	void (*run)(void); ///> pointer to function which runs task
	bool (*checkRdy)(void); ///> pointer to function which check is task is ready to call
}task_t;

/** @brief  structure which contains data required for scheduler operation*/
typedef struct
{
	task_t* taskPtr; // pointer to task array
	uint8_t numberOfTasks; ///> Defines number of tasks
	void (*update)(); // pointer to scheduler update function
}scheduler_t;

/**
 * @brief Function initialises tasks
 * 
 * @param[in] task: Pointer to task array.
 * @param[in] runTaskFcn: pointer to the main task function. Each function has 
 * individual main function. 
 * @param[in] checkTaskRdy: pointer to function which checks the state of the 
 * given task
 * 
 * @param[in] priority: Priority value of given task. 
 * @param[in] period: Period value. The value after which task will be called 
 * 
 * @return Function doesn't have return 
 */
void taskInit(task_t* task, void (*runTaskFcn)(), bool (*checkTaskRdy)(), 
		const uint8_t priority, const time_t period);

/**
 * @brief Function checking all tasks and looking for one available to call
 * 
 * Function checks when the task has been called last time. If the value is 
 * bigger than predefined period task will be called again. 
 * 
 * That approach is giving a big flexibility on defining tasks with different
 * periods or functionality.
 * 
 * @param[in] task: Pointer to task array.
 * 
 * @return Function doesn't have return 
 */
void schedulerUpdate(scheduler_t* sched);

/**
 * @brief Function used to initialise task
 * 
 * During task initialisation we have an option to add function which can 
 * check if the task is ready to be called. In result the task might be called
 * more often than specified in task period. 
 * 
 * This function can be used in case when function is called only by timer 
 * timeout
 * 
 * @return Function always returns false
 */
bool taskAlwaysNotRdy(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SCHEDULER_H */

