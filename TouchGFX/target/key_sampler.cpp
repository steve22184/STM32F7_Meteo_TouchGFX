/*
 * key_sampler.c
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

/*******************************************************************************
*  Includes
*******************************************************************************/
#include "key_sampler.hpp"

#include <touchgfx/HAL/Buttons.hpp>
#include "main.h"

/*******************************************************************************
*  Defines
*******************************************************************************/

using namespace touchgfx;

/*******************************************************************************
*  Constants and variables
*******************************************************************************/

/*******************************************************************************
*  Typedef
*******************************************************************************/

/*******************************************************************************
*  Class methods
*******************************************************************************/

void KeySampler::init(){
  //Initialise gpio for buttons here

  //ALSCode: initializations made in gpio.c
}

bool KeySampler::sample(uint8_t& key){
//   unsigned int buttons = ...; //sample GPIO
   bool result = false;
   static uint8_t state, count;
   //Return true if button 1 was pressed, save 1 to key argument
   //Return true if button 2 was pressed, save 2 to key argument
   if ( (HAL_GPIO_ReadPin(Button_GPIO_Port, Button_Pin) == GPIO_PIN_SET) && (count++ > 7)){
	   count = 0;
	   result = true;

	   switch (state){
	   case 0:
		   key = 0;
		   break;
	   case 1:
		   key = 1;
		   break;
	   case 2:
		   key = 2;
		   break;
	   default:
		   break;
	   }

	   if (++state == 3){
		   state = 0;
	   }
   }
   return result;
}

/*******************************************************************************
*  Local functions definitions
*******************************************************************************/


/*******************************************************************************
*  Public functions definitions
*******************************************************************************/


// End of namespace

