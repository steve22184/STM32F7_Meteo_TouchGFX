/*
 * timer_dwt.h
 *
 *  Created on: 12 авг. 2019 г.
 *      Author: Home
 */

#ifndef TIMER_DWT_H_
#define TIMER_DWT_H_

#ifdef __cplusplus
extern "C" {
#endif


/****************** Includes *********************************************************************************/
#pragma once
#include "stm32f7xx_hal.h"
#include <stdbool.h>


/****************** Defines **********************************************************************************/

#define delayUS_ASM(us) 	do { \
				asm volatile ("MOV R0,%[loops]\n \
					      1: \n \
					      SUB R0, #1\n \
					      CMP R0, #0\n \
					      BNE 1b \t" \
					      : : [loops] "r" (16*us) : "memory" \
				); \
				  } while(0)
/****************** Define interface function ****************************************************************/

/****************** Struct declaration ***********************************************************************/


/****************** Variables ********************************************************************************/


/****************** Init function declaration ****************************************************************/
  void DWT_Init(void);

/****************** Public function declaration **************************************************************/
  void DWT_Delay_ns(uint32_t ns); // nanoseconds. 1 == 100ns
  void DWT_Delay_us(uint32_t us);
  void DWT_Delay_ms(uint32_t ms);

  uint32_t SetMainTimerMs (const uint32_t AddTimeMS);
  bool MainTimerIsExpiredMs (const uint32_t Timer);
  uint32_t MainTimerRemainingMs(const uint32_t Timer);

  uint32_t SetMainTimerUs (const uint32_t AddTimeUS);
  bool MainTimerIsExpiredUs (const uint32_t Timer);
  uint32_t MainTimerRemainingUs(const uint32_t Timer);

#ifdef __cplusplus
}
#endif


#endif /* TIMER_DWT_H_ */
