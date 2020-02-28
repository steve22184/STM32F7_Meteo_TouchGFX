/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "stdio.h"
#include "app_touchgfx.h"
#include "stack_check.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAX_TASKS_MONITOR	15
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern volatile unsigned long ulHighFrequencyTimerTicks;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId MonitorTaskHandle;
osTimerId statTimerHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void print_itm (const char* str);
char CurrentStateConvert (eTaskState state_);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartMonitorTask(void const * argument);
void statTimerCallback(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{
	ulHighFrequencyTimerTicks = 0;
}

__weak unsigned long getRunTimeCounterValue(void)
{
	return ulHighFrequencyTimerTicks;
}
/* USER CODE END 1 */

/* USER CODE BEGIN 4 */
__weak void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
	taskENTER_CRITICAL();
	{
		while (1)
		{
			portNOP();
		}
	}
	taskEXIT_CRITICAL();
}
/* USER CODE END 4 */

/* USER CODE BEGIN 5 */
__weak void vApplicationMallocFailedHook(void)
{
   /* vApplicationMallocFailedHook() will only be called if
   configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
   function that will get called if a call to pvPortMalloc() fails.
   pvPortMalloc() is called internally by the kernel whenever a task, queue,
   timer or semaphore is created. It is also called by various parts of the
   demo application. If heap_1.c or heap_2.c are used, then the size of the
   heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
   FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
   to query the size of free heap space that remains (although it does not
   provide information on how the remaining heap might be fragmented). */
	taskENTER_CRITICAL();
	{
		while (1)
		{
			portNOP();
		}
	}
	taskEXIT_CRITICAL();
}
/* USER CODE END 5 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];
  
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )  
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}                   
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of statTimer */
  osTimerDef(statTimer, statTimerCallback);
  statTimerHandle = osTimerCreate(osTimer(statTimer), osTimerPeriodic, NULL);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  osTimerStart (statTimerHandle, 2000);
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 4096);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of MonitorTask */
  osThreadDef(MonitorTask, StartMonitorTask, osPriorityNormal, 0, 256);
  MonitorTaskHandle = osThreadCreate(osThread(MonitorTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	MX_TouchGFX_Process();
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartMonitorTask */
/**
* @brief Function implementing the MonitorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMonitorTask */
void StartMonitorTask(void const * argument)
{
  /* USER CODE BEGIN StartMonitorTask */
	UNUSED(argument);
	/* Infinite loop */
	UBaseType_t pulTotalRunTime = 0, taskCount = 0;
	/* Infinite loop */
	for(;;)
	{
		ulTaskNotifyTake( pdTRUE,  portMAX_DELAY );

		taskCount = uxTaskGetNumberOfTasks();

		if (taskCount < MAX_TASKS_MONITOR)
		{
			static TaskStatus_t TaskStatusArray[MAX_TASKS_MONITOR];
			static portCHAR taskStr[72];

			taskCount = uxTaskGetSystemState(TaskStatusArray, taskCount, &pulTotalRunTime);

			for (UBaseType_t task = 0; task < taskCount; task++)
			{
				sprintf (taskStr, "%22s: %c, %2lu, %6u, %lu\n%c",
						TaskStatusArray[task].pcTaskName,
						CurrentStateConvert(TaskStatusArray[task].eCurrentState),
						TaskStatusArray[task].uxCurrentPriority,
						TaskStatusArray[task].usStackHighWaterMark,
						TaskStatusArray[task].ulRunTimeCounter,
						'\0');
				print_itm(taskStr);
			}
			sprintf (taskStr, "Current Heap Free Size: %u\n%c", xPortGetFreeHeapSize(), '\0');
			print_itm(taskStr);
			sprintf (taskStr, "Minimal Heap Free Size: %u\n%c", xPortGetMinimumEverFreeHeapSize(), '\0');
			print_itm(taskStr);
			sprintf (taskStr, "Total RunTime:  %lu ms\n%c", pulTotalRunTime, '\0');
			print_itm(taskStr);
			sprintf (taskStr, "System Uptime:  %lu ms\n%c", xTaskGetTickCount() * portTICK_PERIOD_MS, '\0');
			print_itm(taskStr);

			sprintf (taskStr, "Stack used: %u\n%c", CheckStackSize(), '\0');
			print_itm(taskStr);

			sprintf (taskStr, "Heap used: %u\n%c", CheckHeapSize(), '\0');
			print_itm(taskStr);
		}
		else
		{
			print_itm("There are more tasks than MAX_TASKS_MONITOR!\n");
		}

	}
	vTaskDelete(NULL);
  /* USER CODE END StartMonitorTask */
}

/* statTimerCallback function */
void statTimerCallback(void const * argument)
{
  /* USER CODE BEGIN statTimerCallback */
	UNUSED(argument);
	xTaskNotifyGive( MonitorTaskHandle );
  /* USER CODE END statTimerCallback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void print_itm (const char* str){
  for(uint8_t i = 0;
      ( str[i] != '\0') && (str[i] < 256 ); i++){

      ITM_SendChar(str[i]);
  }
}

char CurrentStateConvert (eTaskState state_){
	char result = 'I';
	int state = (int)state_;

	switch (state) {

	case eReady:
		result = 'R';
		break;

	case eBlocked:
		result = 'B';
		break;

	case eSuspended:
		result = 'S';
		break;

	case eDeleted:
		result = 'D';
		break;

	case eRunning:
		result = 'E';
		break;

	default:
		break;
	}
	return result;
}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
