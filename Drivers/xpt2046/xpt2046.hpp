/*
 * xpt2046.h
 *
 *  Created on: 10 фев. 2020 г.
 *      Author: ALScode
 * All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef XPT2046_H_
#define XPT2046_H_


/*******************************************************************************
*  Includes
*******************************************************************************/
#pragma once
#include <array>
#include <algorithm>
#include <numeric>

#include "lldrv.hpp"
#include "timer_dwt.h"

namespace app {
/*******************************************************************************
*  Defines
*******************************************************************************/

/*******************************************************************************
*  Constants and variables
*******************************************************************************/

/*******************************************************************************
*  Enums
*******************************************************************************/
typedef enum{
	TFT_W = 480,
	TFT_H = 320,
} TFT_Size;

typedef enum{
	GET_TOUCH_X = 0b10010010,
	GET_TOUCH_Y = 0b11010010,
	GET_TOUCH_Z1 = 0b10110010,
	GET_TOUCH_Z2 = 0b11000010,
	GET_TOUCH_TEMP = 0b10000110,
	MAX_ADC_TOUCH =	4095,
	JITTER_PRESS =	250,
	JITTER_CUT = 3,
	JITTER = 12,
	OFFSET_POINT = 25,
	POINT1_X = OFFSET_POINT,
	POINT1_Y = OFFSET_POINT,
	POINT2_X = TFT_W - OFFSET_POINT,
	POINT2_Y = OFFSET_POINT,
	POINT3_X = TFT_W - OFFSET_POINT,
	POINT3_Y = TFT_H - OFFSET_POINT,
	POINT4_X = OFFSET_POINT,
	POINT4_Y = TFT_H - OFFSET_POINT,
}ILI_Touch_Parameters;

/*******************************************************************************
*  Typedefs
*******************************************************************************/
typedef struct{
	uint32_t adc_x;
	uint32_t adc_y;
	uint8_t touch_detect;
}ILI_ADC_TypeDef;

typedef struct{
	uint32_t kx;
	uint32_t ky;
	uint32_t offset_x;
	uint32_t offset_y;
}ILI_Calibr_TypeDef;


/*******************************************************************************
*  Struct / Classes
*******************************************************************************/
class TouchSelect{
public:
	TouchSelect();
	~TouchSelect();
};

template <class Communicate>
class XPT2046{
public:
	XPT2046(){
		calibr.kx = 77;
		calibr.ky = 117;
		calibr.offset_x = 20;
		calibr.offset_y = 12;
	}
	XPT2046 &operator=(const XPT2046&)=delete;

	uint8_t scan_adc (void);
	ILI_ADC_TypeDef get_raw_xy (void);
	ILI_Calibr_TypeDef& get_calibr (void);
	uint8_t get_touch_xy(int32_t& x, int32_t& y); //return 1 - touch, 2 - no touch
	void init (void);

private:
	uint32_t conversion (uint8_t command);
	ILI_ADC_TypeDef get_convertion(void);

	std::array<uint32_t, JITTER> array_x;
	std::array<uint32_t, JITTER> array_y;
	ILI_Calibr_TypeDef calibr;

};
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*******************************************************************************
*  Template class methods
*******************************************************************************/

template<class Communicate>
ILI_Calibr_TypeDef& XPT2046<Communicate>::get_calibr (void){
	return calibr;
}

template<class Communicate>
uint8_t XPT2046<Communicate>::scan_adc (void){
	ILI_ADC_TypeDef result;

	for (uint_fast8_t i = 0; i != JITTER; ++i){

		result  = get_convertion();

		if ( result.touch_detect ){
			array_x[i] = result.adc_x;
			array_y[i] = result.adc_y;
		} else {
			return 0;
		}
	}
	return 1;
}

template<class Communicate>
ILI_ADC_TypeDef XPT2046<Communicate>::get_raw_xy (void){
	uint32_t adc_x = 0, adc_y = 0;

	std::sort(array_x.begin(), array_x.end());
	std::sort(array_y.begin(), array_y.end());

	adc_x = std::accumulate(array_x.begin() + JITTER_CUT, array_x.begin() + JITTER_CUT*3, 0) / 6;
	adc_y = std::accumulate(array_y.begin() + JITTER_CUT, array_y.begin() + JITTER_CUT*3, 0) / 6;

	return {adc_x, adc_y, 1};
}

template<class Communicate>
uint8_t XPT2046<Communicate>::get_touch_xy(int32_t& x, int32_t& y){ //return 1 - touch, 2 - no touch
	ILI_ADC_TypeDef raw;

	if ( !scan_adc() ){
		return 0;
	}

	raw = get_raw_xy();

	x = static_cast<int32_t>( (raw.adc_x * 10) / get_calibr().kx - get_calibr().offset_x );
	y = static_cast<int32_t>( (raw.adc_y * 10) / get_calibr().ky - get_calibr().offset_y );

	if ( (x >= TFT_W) || (y >= TFT_H) ){
		return 0;
	}
	return 1;
}

template<class Communicate>
void XPT2046<Communicate>::init (void){
	conversion(GET_TOUCH_X); // dummy conversion
}
template<class Communicate>
uint32_t XPT2046<Communicate>::conversion (uint8_t command){
	Communicate::template set_prescaler<>(SPI_BAUDRATEPRESCALER_64); // 1.6 Mbit/sec
	TouchSelect ts;
	Communicate::template send8b<>(command);

	DWT_Delay_us(100);

	uint16_t adc = 0;
	Communicate::receive16b(&adc, 0x01);
	adc  = (adc & 0x7FF8) >> 3;

	return adc;
}

template<class Communicate>
ILI_ADC_TypeDef XPT2046<Communicate>::get_convertion(void){
	uint32_t press = MAX_ADC_TOUCH - conversion(GET_TOUCH_Z2);
	press += conversion(GET_TOUCH_Z1);
	press /= 2;

	if (press > JITTER_PRESS) {
		//		adc_x = MAX_ADC_TOUCH - conversion(GET_TOUCH_X);
		//		adc_y = MAX_ADC_TOUCH - conversion(GET_TOUCH_Y); // Отражение координат
		return { ( MAX_ADC_TOUCH - conversion(GET_TOUCH_X) ), conversion(GET_TOUCH_Y), 1};
	}
	return {0, 0, 0};
}

/*******************************************************************************
*  Public functions declarations
*******************************************************************************/
XPT2046<spi>& touch(void);

} // End of ... namespace


#endif /* XPT2046_H_ */
