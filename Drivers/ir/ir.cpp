/*
 * ir.cpp
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
#include "ir.hpp"

namespace app {
/*******************************************************************************
*  Defines
*******************************************************************************/
#define TIM_IR	htim3

#define CHECK_TIMING(timing, value)						\
		(value > (timing - timing * ir_limit / 100)) &&	\
		(value < (timing + timing * ir_limit / 100))

#define RESET_FRAME()	\
		ir.shift = 0;	\
		ir.frame = 0;
}
/*******************************************************************************
*  Constants and variables
*******************************************************************************/

TIM_HandleTypeDef htim3;

namespace app{

constexpr static uint8_t ir_limit = 5;
static IR ir;

/*******************************************************************************
*  Enums
*******************************************************************************/
typedef enum : uint32_t{
	IR_START 	= 13500,
	IR_END 		= 40450,
	IR_REPEAT 	= 11300,
	IR_ONE 		= 2245,
	IR_ZERO 	= 1135,
}NEC_Timings;
/*******************************************************************************
*  Typedefs
*******************************************************************************/

/*******************************************************************************
*  Local functions declarations
*******************************************************************************/
extern "C" void ir_init(void);
/*******************************************************************************
*  Class methods
*******************************************************************************/
void IR::init (void){
	HAL_TIM_IC_Start_IT(&TIM_IR, TIM_CHANNEL_1);
}

uint8_t IR::command(void){
	uint8_t tcmd = cmd;
	cmd = 0xFF;
	return tcmd;
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*******************************************************************************
*  Local functions definitions
*******************************************************************************/
void timer3_ic_isr(void){

	uint32_t period = HAL_TIM_ReadCapturedValue(&TIM_IR, TIM_CHANNEL_1);

	if ( CHECK_TIMING(IR_START, period) ){

		RESET_FRAME();

	} else if (CHECK_TIMING(IR_ONE, period)){

		ir.frame |= ( 1 << ir.shift);
		++ir.shift;

	} else if (CHECK_TIMING(IR_ZERO, period)){

		++ir.shift;

	} else if (CHECK_TIMING(IR_END, period)){

		ir.cmd = ( (ir.shift == 32) ? static_cast<uint8_t>(ir.frame >> 16) : 0xFF);
		RESET_FRAME();
	}
}

void ir_init(void){
	ir.init();
}
/*******************************************************************************
*  Public functions definitions
*******************************************************************************/
IR& ir_get (void){
	return ir;
}

} // End of namespace 'app'
