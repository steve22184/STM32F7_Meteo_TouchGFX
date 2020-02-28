/*
 * timer_dwt.c
 *
 *  Created on: 12 авг. 2019 г.
 *      Author: Home
 */

#include "timer_dwt.h"

/****************** User Defines *****************************************************************************/
//#define

/****************** Program Defines **************************************************************************/

/****************** Struct ***********************************************************************************/

/****************** Variables ********************************************************************************/
static uint32_t freq_us;
static uint32_t freq_ns;
/****************** Local function declaration ***************************************************************/


/****************** Local function definition*****************************************************************/


/****************** Public function definition*************************************************************/

void DWT_Init(void)
{
  if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk)) {
      CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
      DWT->LAR = 0xC5ACCE55;
      DWT->CYCCNT = 0;
      DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  }
      SystemCoreClockUpdate();

      freq_us = SystemCoreClock / 1000000;
      freq_ns = SystemCoreClock / 10000000; // 1 == 100ns
}

#pragma GCC push_options
#pragma GCC optimize ("O3")

void DWT_Delay_ns(uint32_t ns) // nanoseconds. 1 == 100ns
{
  uint32_t startTick = DWT->CYCCNT;
  uint32_t delayTicks = ns * freq_ns;

  while (DWT->CYCCNT - startTick < delayTicks);
}

void DWT_Delay_us(uint32_t us) // microseconds
{
  uint32_t startTick = DWT->CYCCNT;
  uint32_t delayTicks = us * freq_us;

  while (DWT->CYCCNT - startTick < delayTicks);
}

void DWT_Delay_ms(uint32_t ms) // milliseconds
{
  uint32_t startTick = DWT->CYCCNT;
  uint32_t delayTicks = ms * (SystemCoreClock / 1000);

  while (DWT->CYCCNT - startTick < delayTicks);
}
#pragma GCC pop_options

/*-----------------------------------------------------------------------------------------------------------*/
uint32_t SetMainTimerMs (const uint32_t AddTimeMS)
{
  return DWT->CYCCNT + AddTimeMS * (SystemCoreClock / 1000);
}

/*-----------------------------------------------------------------------------------------------------------*/
uint32_t SetMainTimerUs (const uint32_t AddTimeUS)
{
  return DWT->CYCCNT + AddTimeUS * freq_us;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool MainTimerIsExpiredMs (const uint32_t Timer)
{
  return ((DWT->CYCCNT - Timer) < (1UL << 31));
}

/*-----------------------------------------------------------------------------------------------------------*/
bool MainTimerIsExpiredUs (const uint32_t Timer)
{
  return ((DWT->CYCCNT - Timer) < (1UL << 31));
}
/*-----------------------------------------------------------------------------------------------------------*/
uint32_t MainTimerRemainingMs(const uint32_t Timer)
{
  if ((DWT->CYCCNT - Timer) > (1UL << 31))
    {
      return (Timer - DWT->CYCCNT);
    }
  else
    {
      return 0;
    }
}
/*-----------------------------------------------------------------------------------------------------------*/

uint32_t MainTimerRemainingUs(const uint32_t Timer)
{
  if ((DWT->CYCCNT - Timer) > (1UL << 31))
    {
      return (Timer - DWT->CYCCNT);
    }
  else
    {
      return 0;
    }
}
/*-----------------------------------------------------------------------------------------------------------*/
