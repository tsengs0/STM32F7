#ifndef __TASK_SUPERVISOR_H__
#define __TASK_SUPERVISOR_H__

/* Private Include ------------------------------------------------------------*/
#include "stm32f7xx_ll_tim.h"
#include "stm32f7xx_ll_bus.h"
#include "stm32f7xx.h"

#include "cmsis_os.h"

/* Private definition --------------------------------------------------------*/
#define MAX_SYS_TASK                            10

/* Private Typedef -----------------------------------------------------------*/
typedef struct
{
  uint32_t task_timestamp;
  uint16_t task_exe_time;
  uint16_t task_curr_con;
  uint16_t task_opf;
  uint16_t task_prv_opf;
  uint16_t task_deadline;
  uint8_t isDeadlineMiss;
  uint8_t prevDeadlineMiss;
  uint8_t swing_cnt;
  uint8_t isOptimize;
  TaskHandle_t task_tcb;
}System_TaskSupervisor;

/* Prototpye ------------------------------------------------------------------*/
uint16_t System_GetTaskEXETime(System_TaskSupervisor*);
void System_StartCounter(System_TaskSupervisor*);
uint32_t System_GetElapseTime(System_TaskSupervisor*);


/* Inline Function ------------------------------------------------------------*/
__STATIC_INLINE void System_SuperviosrInit() 
{
  /* Enable Cycle Counter for DVFS*/
   CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
   DWT->LAR = 0xC5ACCE55; 
   DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
   DWT->CYCCNT = 0;
}

__STATIC_INLINE uint32_t System_GetCounter()
{
  return DWT->CYCCNT;
}

__STATIC_INLINE uint8_t System_isCounterENA()
{
  return (uint8_t)0x0 | DWT->CTRL;
}

/** Public Function */
BaseType_t System_TaskCreate(TaskFunction_t, char* const ,const uint16_t ,void * const ,UBaseType_t ,System_TaskSupervisor* ,uint16_t, uint8_t );
#endif