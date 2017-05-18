/* Private include -----------------------------------------------------------*/
#include "task_supervisor.h"

/* Private functions ---------------------------------------------------------*/
uint16_t SYS_TASK_DEADLINE = 0;
uint32_t START_CNT = 0;
uint32_t STOP_CNT = 0;



void System_SetTaskDeadline(System_TaskSupervisor* instance, uint16_t dl_time)
{
  SYS_TASK_DEADLINE = dl_time;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

uint16_t System_GetTaskDeadline(System_TaskSupervisor* instance)
{
  return instance->task_deadline;
}

float System_GetTaskEXETime()
{
  return  ((float)1/(SystemCoreClock/1000) * System_GetElapseTime());
}

void System_StartCounter()
{
  START_CNT = System_GetCounter();
}

void System_StopCounter()
{
  STOP_CNT = System_GetCounter();
}
  
uint32_t System_GetElapseTime(System_TaskSupervisor* instance)
{
  return (START_CNT >= STOP_CNT) ? (START_CNT - STOP_CNT) : (STOP_CNT - START_CNT);
}
