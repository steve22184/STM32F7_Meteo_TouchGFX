/*
 * ds18b20.cpp
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
#include "ds18b20.hpp"
namespace app {
/*******************************************************************************
*  Defines
*******************************************************************************/
//#define PRECISION_9		0X1F
//#define PRECISION_10		0X3F
//#define PRECISION_11		0X5F
#define PRECISION_12		0X7F

#define READ_BYTES(num)												\
	for (uint_fast8_t i = 0; i != num; i++){						\
			buf[i] = static_cast<uint16_t>( OW<uart>::read_byte() );\
		}

/*******************************************************************************
*  Constants and variables
*******************************************************************************/
#ifdef PRECISION_9
static constexpr uint32_t CONVERTION_TIME = UINT32_C(0X5F); // 93.75ms  (t CONV /8)
#endif

#ifdef PRECISION_10
static constexpr uint32_t CONVERTION_TIME = UINT32_C(0XBE); // 187.5ms  (t CONV /4)
#endif

#ifdef PRECISION_11
static constexpr uint32_t CONVERTION_TIME = UINT32_C(0X0177); // 375ms  (t CONV /2)
#endif

#ifdef PRECISION_12
static constexpr uint32_t CONVERTION_TIME = UINT32_C(0X02EE); // 750ms  (t CONV )
#endif

constexpr uint8_t fraction_digits_to_display = 1;

CustomAllocator<uint16_t>ca(allocator());
static std::vector<uint16_t, alloc_type16> buf(12, 0, ca);

/*******************************************************************************
*  Enums
*******************************************************************************/
typedef enum : uint8_t
  {
    SEARCH_ROM 		= 0xF0,
    READ_ROM 		= 0x33,
    MATCH_ROM 		= 0x55,
    SKIP_ROM 		= 0xCC,
    ALARM_SEARCH 	= 0xEC,
	TH 				= 0xCE, // -50C
	TL 				= 0x78, // 120C
  }DS18B20_ROMCommand;

  typedef enum : uint8_t
  {
    CONVERT_T 			= 0x44,
    WRITE_SCRATCHPAD 	= 0x4E,
    READ_SCRATCHPAD 	= 0xBE,
    COPY_SCRATCHPAD 	= 0x48,
    RECALL_E 			= 0xB8,
    READ_POWER_SUPPLY 	= 0xB4,
  }DS18B20_FuncCommand;
/*******************************************************************************
*  Typedefs
*******************************************************************************/

/*******************************************************************************
*  Local functions declarations
*******************************************************************************/
  extern "C" void ds_config(void);
  extern "C" uint16_t* ds_read_id(void);
  extern "C" uint32_t ds_request_temp(void);
  extern "C" uint16_t* ds_read_temp(void);
/*******************************************************************************
*  Class methods
*******************************************************************************/

void DS18B20::config (void){
	OW<uart>::start();
	OW<uart>::write_byte(SKIP_ROM);
	OW<uart>::write_byte(WRITE_SCRATCHPAD);

	OW<uart>::write_byte(TH);
	OW<uart>::write_byte(TL);
	OW<uart>::write_byte(PRECISION_12);

	OW<uart>::start();
	OW<uart>::write_byte(SKIP_ROM);
	OW<uart>::write_byte(COPY_SCRATCHPAD);

}
uint16_t* DS18B20::read_id (void){
	OW<uart>::start();
	OW<uart>::write_byte(READ_ROM);

	READ_BYTES(8);

	std::for_each(buf.begin(), buf.end(), [](uint16_t& val){ val += '0'; });

	return buf.data();
}

uint32_t DS18B20::request_temp(void){
	OW<uart>::start();
	OW<uart>::write_byte(SKIP_ROM);
	OW<uart>::write_byte(CONVERT_T);
	return CONVERTION_TIME;
}

uint16_t* DS18B20::read_temp(void){
	OW<uart>::start();
	OW<uart>::write_byte(SKIP_ROM);
	OW<uart>::write_byte(READ_SCRATCHPAD);

	READ_BYTES(9);

	return buf.data();
}

std::tuple<uint16_t, uint16_t> DS18B20::get_temp(void){
	uint16_t temp = buf[1];
	temp = temp << 0x08;
	temp = temp | buf[0];

	uint16_t mantissa = (temp >> 0x04) & 0x7F;

#ifdef PRECISION_9
	uint16_t fraction = temp & 0x08;
#endif

#ifdef PRECISION_10
	uint16_t fraction = temp & 0x0C;
#endif

#ifdef PRECISION_11
	uint16_t fraction = temp & 0x07;
#endif

#ifdef PRECISION_12
	uint16_t fraction = temp & 0x0F;
#endif

	fraction = static_cast<uint16_t>(fraction / 16.0 * 10);

	return std::make_tuple(mantissa, fraction);
}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*******************************************************************************
*  Local functions definitions
*******************************************************************************/
void ds_config(void){
	DS18B20::config();
}

uint16_t* ds_read_id(void){
	return DS18B20::read_id();
}

uint32_t ds_request_temp(void){
	return DS18B20::request_temp();
}

uint16_t* ds_read_temp(void){
	return DS18B20::read_temp();
}

/*******************************************************************************
*  Public functions definitions
*******************************************************************************/

} // End of app namespace
