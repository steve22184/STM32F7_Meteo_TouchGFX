/*
 * ow.hpp
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

#ifndef OW_HPP_
#define OW_HPP_


/*******************************************************************************
*  Includes
*******************************************************************************/
#pragma once
#include <vector>
#include <algorithm>
#include "main.h"
#include "custom_alloc.hpp"
#include "lldrv.hpp"

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
typedef enum : uint8_t {
	RST = 0xF0,
	PRL = 0x10,
	PRH = 0x90,
	TR0 = 0xFF,
	RR0 = 0xFE, // or less
	TR1 = 0xFF,
	RR1 = 0xFF,
	TW0 = 0x00,
	RW0 = 0x00,
	TW1 = 0xFF,
	RW1 = 0xFF,
}OW_Params;

typedef enum : uint32_t{
	B9600 = 9600,
	B115200 = 115200,
}USARTx_Params;
/*******************************************************************************
*  Typedefs
*******************************************************************************/

/*******************************************************************************
*  Local functions declarations
*******************************************************************************/
uint8_t prepare_byte (uint8_t byte);
/*******************************************************************************
*  Struct / Classes
*******************************************************************************/

template <class Communicate>
class OW{
public:

	static uint8_t start (void); // 1 - presence detect; 0 - presence not detect
	static uint8_t write_byte (uint8_t byte);
	static uint8_t read_byte (void);

private:
	static inline uint8_t send_bit (uint8_t bit);
	static inline uint8_t read_bit (void);
};
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*******************************************************************************
*  Template class methods
*******************************************************************************/

template <class Communicate>
uint8_t OW<Communicate>::start (void){ // 1 - presence detect; 0 - presence not detect
	uint8_t tbit  = RST;

	Communicate::template mode<>(B9600);

	Communicate::template send_receive8b<>(&tbit, &tbit, 1);

	Communicate::template mode<>(B115200);

	return ( (tbit >= PRL) && (tbit <= PRH)) ? 1 : 0;
}

template <class Communicate>
uint8_t OW<Communicate>::send_bit (uint8_t bit){
	uint8_t tbit  = bit;

	tbit = tbit ? TW1 : TW0;                        /* Convert to 0 or 1 */

	Communicate::template send_receive8b<>(&tbit, &tbit, 1);

	return (tbit == RR1) ? 1 : 0;
}

template <class Communicate>
uint8_t OW<Communicate>::read_bit (void){
	return send_bit(1);
}

template <class Communicate>
uint8_t OW<Communicate>::write_byte (uint8_t byte){
	uint8_t res = 0;

	CustomAllocator<uint8_t>ca( allocator());
	std::vector<uint8_t, alloc_type8> buf(8, 0, ca);

	std::for_each(buf.begin(), buf.end(), [byte](uint8_t& b){ b = prepare_byte(byte); });

	Communicate::template send_receive8b<>(buf.data(), buf.data(), 8);

	for (uint_fast8_t i = 0; i != 8; ++i){
		if (buf[i] == RR1){
			res |= (1 << i);
		}
	}
	return res;
}

template <class Communicate>
uint8_t OW<Communicate>::read_byte (void){
	return write_byte(TW1);
}
/*******************************************************************************
*  Public functions declarations
*******************************************************************************/


} // End of ... namespace

#endif /* OW_HPP_ */
