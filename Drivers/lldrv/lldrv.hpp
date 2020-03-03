/*
 * lldrv.hpp
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

#ifndef LLDRV_H_
#define LLDRV_H_


/*******************************************************************************
*  Includes
*******************************************************************************/
#pragma once
#include "main.h"

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

/*******************************************************************************
*  Typedefs
*******************************************************************************/

/*******************************************************************************
*  Struct / Classes
*******************************************************************************/
template <class Bus>
class Communicate{
public:
	Communicate(){}
	~Communicate(){}
	Communicate(const Communicate&) = delete;
	const Communicate& operator= (const Communicate&) = delete;

	template<class Periph = Bus, typename ...params>
	static void mode (params... parameters){
		Periph:: mode(parameters...);
	}

	template<class Periph = Bus, typename ...params>
	static void send8b (params... parameters){
		Periph::send8b(parameters...);
	}
	template<class Periph = Bus, typename ...params>
	static void send16b (params... parameters){
		Periph::send16b(parameters...);
	}
	template<class Periph = Bus, typename ...params>
	static void receive8b (params... parameters){
		Periph::receive8b(parameters...);
	}
	template<class Periph = Bus, typename ...params>
	static void receive16b (params... parameters){
		Periph::receive16b(parameters...);
	}

	template<class Periph = Bus, typename ...params>
	static void send_receive8b (params... parameters){
		Periph::send_receive8b(parameters...);
	}
};
/*----------------------------------------------------------------------------*/

class Spi {
public:
	static void mode (uint32_t prescaler);
	static void send8b (uint8_t value);
	static void send8b (uint8_t* data, uint16_t size);
	static void send16b (uint16_t value);
	static void send16b (uint16_t* data, uint16_t size);
	static void recieve8b (uint8_t* data, uint16_t size);
	static void receive16b (uint16_t* data, uint16_t size);
};

/*----------------------------------------------------------------------------*/
class IIC {
public:
	static void send8b (uint8_t* data, uint16_t size, uint16_t address);
	static void receive8b (uint8_t* data, uint16_t size, uint16_t address);
};

/*----------------------------------------------------------------------------*/

class Uart {
public:
	static void mode (uint32_t baud);
	static void send_receive8b (uint8_t* tdata, uint8_t* rdata, uint16_t size);
};
/*----------------------------------------------------------------------------*/
typedef Communicate<Spi> spi;
typedef Communicate<IIC> iic;
typedef Communicate<Uart> uart;
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*******************************************************************************
*  Template class methods
*******************************************************************************/


/*******************************************************************************
*  Public functions declarations
*******************************************************************************/


} // End of ... namespace


#endif /* LLDRV_H_ */
