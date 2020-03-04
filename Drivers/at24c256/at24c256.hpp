/*
 * at24c256.hpp
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

#ifndef AT24C256_HPP_
#define AT24C256_HPP_


/*******************************************************************************
*  Includes
*******************************************************************************/
#pragma once
#include <array>
#include "main.h"
#include "lldrv.hpp"

namespace app {
/*******************************************************************************
*  Defines
*******************************************************************************/


/*******************************************************************************
*  Constants and variables
*******************************************************************************/
}


namespace app{
/*******************************************************************************
*  Enums
*******************************************************************************/
typedef enum : uint16_t{
	PAGE_SIZE = 64,
	PAGE_NUMBER = 512,
	CLUSTER_SIZE = 512,
	ENTRY_NUMBER = 5
}Eeeprom_params;
/*******************************************************************************
*  Typedefs
*******************************************************************************/

/*******************************************************************************
*  Public functions declarations
*******************************************************************************/
extern "C" void i2c2_ev_isr(void);

/*******************************************************************************
*  Struct / Classes
*******************************************************************************/
template <class Communicate>
class Eeprom{
public:
	using entries = std::array<uint16_t, ENTRY_NUMBER>;
	using cluster = std::array<uint8_t, CLUSTER_SIZE>;

	Eeprom(const entries& entry_) : flag(0), entry(entry_){}
	~Eeprom(){}
	Eeprom(const Eeprom&) = delete;
	const Eeprom& operator= (const Eeprom&) = delete;

	void read_cluster(void);
	uint8_t* get_data(void);
	uint8_t get_flag (void);
	friend
	void i2c2_ev_isr(void);

private:
	cluster buf;
	volatile uint8_t flag;
	const entries& entry;
};
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*******************************************************************************
*  Template class methods
*******************************************************************************/
template<class Communicate>
void Eeprom<Communicate>::read_cluster(void){
	flag = 0;
	static uint16_t counter;
	Communicate::template receive8b<>(buf.data(), CLUSTER_SIZE, entry[counter]);
	if (++counter == ENTRY_NUMBER ){
		counter = 0;
	}
}
template<class Communicate>
uint8_t* Eeprom<Communicate>::get_data(void){
	flag = 0;
	return buf.data();
}
template<class Communicate>
uint8_t Eeprom<Communicate>::get_flag (void){
	uint8_t tflag = flag;
	flag = 0;
	return tflag;
}

/*******************************************************************************
*  Public functions declarations
*******************************************************************************/

Eeprom<iic>& eeprom (void);

} // End of ... namespace

#endif /* AT24C256_HPP_ */
