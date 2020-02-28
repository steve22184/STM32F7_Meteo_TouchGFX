/*
 * rtc_sampler.cpp
 *
 *  Created on: 26 февр. 2020 г.
 *      Author: ALSCode
 */

#include "main.h"
#include <tuple>

extern void rtc_set (uint8_t h, uint8_t m, uint8_t s);
extern std::tuple<uint8_t, uint8_t, uint8_t> rtc_get (void);

RTC_HandleTypeDef hrtc;


void rtc_set (uint8_t h, uint8_t m, uint8_t s){
	RTC_TimeTypeDef time;

	time.Hours = h;
	time.Minutes = m;
	time.Seconds = s;

	HAL_RTC_SetTime(&hrtc, &time, FORMAT_BIN);

}

std::tuple<uint8_t, uint8_t, uint8_t> rtc_get (void){
	RTC_DateTypeDef sDate;
	RTC_TimeTypeDef sTime;

	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);

	return std::make_tuple(sTime.Hours, sTime.Minutes, sTime.Seconds);
}
