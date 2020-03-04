/*
 * dht11.cpp
 *
 *  Created on: 10 фев. 2019 г.
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

/*******************************************************************************
*  Includes
*******************************************************************************/
#include "dht11.hpp"

namespace app {
/*******************************************************************************
*  Defines
*******************************************************************************/
#define TIM_OC	htim2
#define TIM_IC	htim1

#define CHECK_TIMING(timing, value)							\
		(value > (timing - timing * dht11_limit / 100)) &&	\
		(value < (timing + timing * dht11_limit / 100))

}
/*******************************************************************************
*  Constants and variables
*******************************************************************************/

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

namespace app{

static DHT11 dht11;
constexpr static uint8_t dht11_limit = 10;

/*******************************************************************************
*  Enums
*******************************************************************************/
typedef enum : uint32_t{
	DHT11_START = 165,
	DHT11_ONE = 125,
	DHT11_ZERO = 75,
}DHT11_Timings;
/*******************************************************************************
*  Typedefs
*******************************************************************************/

/*******************************************************************************
*  Local functions declarations
*******************************************************************************/
extern "C" void dht11_start(void);
/*******************************************************************************
*  Class methods
*******************************************************************************/

void DHT11::start(void){

	HAL_GPIO_DeInit(TIM1_CH1_DHT11_GPIO_Port, TIM1_CH1_DHT11_Pin);

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = TIM1_CH1_DHT11_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(TIM1_CH1_DHT11_GPIO_Port, &GPIO_InitStruct);
	HAL_GPIO_WritePin(TIM1_CH1_DHT11_GPIO_Port, TIM1_CH1_DHT11_Pin, GPIO_PIN_RESET);

	HAL_TIM_OC_Start_IT(&TIM_OC, TIM_CHANNEL_1);
}

uint8_t DHT11::humidity (void){
	return hum;
}

void  DHT11::convertion (void){
	hum = 0;
	uint_fast16_t pos = 2;

	for (int_fast16_t i = 7; i >= 0 ; i--, pos++){

		if (CHECK_TIMING(DHT11_ONE, frame[pos])){
			hum |= (1 << i);
		}
	}
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*******************************************************************************
*  Local functions definitions
*******************************************************************************/

void timer2_pwm_isr(void) {

	HAL_GPIO_DeInit(TIM1_CH1_DHT11_GPIO_Port, TIM1_CH1_DHT11_Pin);

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = TIM1_CH1_DHT11_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
	HAL_GPIO_Init(TIM1_CH1_DHT11_GPIO_Port, &GPIO_InitStruct);

	HAL_TIM_IC_Start_DMA(&TIM_IC, TIM_CHANNEL_1, (uint32_t*)dht11.frame.data(), 43);
}

void timer1_ic_isr(void){
	dht11.convertion();
}
/*******************************************************************************
*  Public functions definitions
*******************************************************************************/

DHT11& dht11_get(void){
	return dht11;
}

void dht11_start(void){
	dht11.start();
}

} // End of namespace 'app'

