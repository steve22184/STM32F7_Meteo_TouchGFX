/*
 * assert_spi.h
 *
 *  Created on: 30 окт. 2019 г.
 *      Author: Home
 */

#ifndef MY_UTILS_H_
#define MY_UTILS_H_

#ifdef __cplusplus
 extern "C" {
#endif

#pragma once
#include "stdio.h"
#include "stm32f7xx_hal.h"
#include "timer_dwt.h"

#ifdef  USE_FULL_ASSERT
/**
  * @brief  The assert_spi macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
#define my_assert(expr)	if (expr) { (void)0U; } else {		\
				my_assert_failed((uint8_t *)__FILE__); \
				while(1){;}				\
				}

/* Exported functions ------------------------------------------------------- */
void my_assert_failed(uint8_t* file);

#else
#define my_assert(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */


//#define u8(val)			((uint8_t)val)
//#define u16(val)		((uint16_t)val)
//#define u32(val)		((uint32_t)val)
//#define cchar(val)		((char)val)

void print_itm (const char* str);
uint32_t TimeStamp (void);
void TimeStampReport (const char* func, uint32_t tStart, uint32_t tEnd);

void FillStackHeap (void);

unsigned CheckStackSize (void);
unsigned CheckHeapSize (void);

#ifdef __cplusplus
}
#endif

#endif /* MY_UTILS_H_ */
