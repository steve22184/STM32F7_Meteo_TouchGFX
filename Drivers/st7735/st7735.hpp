/*
 * st7735.h
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

#ifndef ST7735_H_
#define ST7735_H_


/*******************************************************************************
*  Includes
*******************************************************************************/
#pragma once
#include "stdint.h"
#include "stm32f7xx.h"
#include "lldrv.hpp"


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
ST7735_LCD_PIXEL_WIDTH = 128,
ST7735_LCD_PIXEL_HEIGHT = 160,
ST7735_LCD_PIXEL_NUMBER = (ST7735_LCD_PIXEL_WIDTH *
							ST7735_LCD_PIXEL_HEIGHT),
} Display_Size;

typedef enum{
  LCD_REG_0   = UINT8_C(0x00), /* No Operation: NOP */
  LCD_REG_1   = UINT8_C(0x01), /* Software reset: SWRESET */
  LCD_REG_4   = UINT8_C(0x04), /* Read Display ID: RDDID */
  LCD_REG_9   = UINT8_C(0x09), /* Read Display Statu: RDDST */
  LCD_REG_10  = UINT8_C(0x0A), /* Read Display Power: RDDPM */
  LCD_REG_11  = UINT8_C(0x0B), /* Read Display: RDDMADCTL */
  LCD_REG_12  = UINT8_C(0x0C), /* Read Display Pixel: RDDCOLMOD */
  LCD_REG_13  = UINT8_C(0x0D), /* Read Display Image: RDDIM */
  LCD_REG_14  = UINT8_C(0x0E), /* Read Display Signal: RDDSM */
  LCD_REG_16  = UINT8_C(0x10), /* Sleep in & booster off: SLPIN */
  LCD_REG_17  = UINT8_C(0x11), /* Sleep out & booster on: SLPOUT */
  LCD_REG_18  = UINT8_C(0x12), /* Partial mode on: PTLON */
  LCD_REG_19  = UINT8_C(0x13), /* Partial off (Normal): NORON */
  LCD_REG_32  = UINT8_C(0x20), /* Display inversion off: INVOFF */
  LCD_REG_33  = UINT8_C(0x21), /* Display inversion on: INVON */
  LCD_REG_38  = UINT8_C(0x26), /* Gamma curve select: GAMSET */
  LCD_REG_40  = UINT8_C(0x28), /* Display off: DISPOFF */
  LCD_REG_41  = UINT8_C(0x29), /* Display on: DISPON */
  LCD_REG_42  = UINT8_C(0x2A), /* Column address set: CASET */
  LCD_REG_43  = UINT8_C(0x2B), /* Row address set: RASET */
  LCD_REG_44  = UINT8_C(0x2C), /* Memory write: RAMWR */
  LCD_REG_45  = UINT8_C(0x2D), /* LUT for 4k,65k,262k color: RGBSET */
  LCD_REG_46  = UINT8_C(0x2E), /* Memory read: RAMRD*/
  LCD_REG_48  = UINT8_C(0x30), /* Partial start/end address set: PTLAR */
  LCD_REG_52  = UINT8_C(0x34), /* Tearing effect line off: TEOFF */
  LCD_REG_53  = UINT8_C(0x35), /* Tearing effect mode set & on: TEON */
  LCD_REG_54  = UINT8_C(0x36), /* Memory data access control: MADCTL */
  LCD_REG_56  = UINT8_C(0x38), /* Idle mode off: IDMOFF */
  LCD_REG_57  = UINT8_C(0x39), /* Idle mode on: IDMON */
  LCD_REG_58  = UINT8_C(0x3A), /* Interface pixel format: COLMOD */
  LCD_REG_177 = UINT8_C(0xB1), /* In normal mode (Full colors): FRMCTR1 */
  LCD_REG_178 = UINT8_C(0xB2), /* In Idle mode (8-colors): FRMCTR2 */
  LCD_REG_179 = UINT8_C(0xB3), /* In partial mode + Full colors: FRMCTR3 */
  LCD_REG_180 = UINT8_C(0xB4), /* Display inversion control: INVCTR */
  LCD_REG_192 = UINT8_C(0xC0), /* Power control setting: PWCTR1 */
  LCD_REG_193 = UINT8_C(0xC1), /* Power control setting: PWCTR2 */
  LCD_REG_194 = UINT8_C(0xC2), /* In normal mode (Full colors): PWCTR3 */
  LCD_REG_195 = UINT8_C(0xC3), /* In Idle mode (8-colors): PWCTR4 */
  LCD_REG_196 = UINT8_C(0xC4), /* In partial mode + Full colors: PWCTR5 */
  LCD_REG_197 = UINT8_C(0xC5), /* VCOM control 1: VMCTR1 */
  LCD_REG_199 = UINT8_C(0xC7), /* Set VCOM offset control: VMOFCTR */
  LCD_REG_209 = UINT8_C(0xD1), /* Set LCM version code: WRID2 */
  LCD_REG_210 = UINT8_C(0xD2), /* Customer Project code: WRID3 */
  LCD_REG_217 = UINT8_C(0xD9), /* NVM control status: NVCTR1 */
  LCD_REG_218 = UINT8_C(0xDA), /* Read ID1: RDID1 */
  LCD_REG_219 = UINT8_C(0xDB), /* Read ID2: RDID2 */
  LCD_REG_220 = UINT8_C(0xDC), /* Read ID3: RDID3 */
  LCD_REG_222 = UINT8_C(0xDE), /* NVM Read Command: NVCTR2 */
  LCD_REG_223 = UINT8_C(0xDF), /* NVM Write Command: NVCTR3 */
  LCD_REG_224 = UINT8_C(0xE0), /* Set Gamma adjustment (+ polarity): GAMCTRP1 */
  LCD_REG_225 = UINT8_C(0xE1),  /* Set Gamma adjustment (- polarity): GAMCTRN1 */
} ST7735_Registers;


/*******************************************************************************
*  Typedefs
*******************************************************************************/

/*******************************************************************************
*  Struct / Classes
*******************************************************************************/
namespace app {

class WriteData{
public:
	WriteData();
	~WriteData();
};

class WriteReg{
public:
	WriteReg();
	~WriteReg();
};

template <class Communicate>
class ST7735{
public:
	ST7735 &operator=(const ST7735&)=delete;

	static void set_frame (uint16_t x, uint16_t y, uint16_t width, uint16_t height);
	static void flush_from_buffer (uint16_t* buf, uint16_t size);
	static void init (void);

private:
	static void hard_reset (void);
	static inline void write_reg (uint8_t reg);
	static inline void write_data (uint8_t data);
	static inline void send_reg (uint8_t reg, uint8_t val);
	static void set_cursor (uint16_t x, uint16_t y);
	static void fill_screen (uint16_t color);
};
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*******************************************************************************
*  Template class methods
*******************************************************************************/

template<class  Communicate>
void ST7735<Communicate>::hard_reset (void){
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_SET);
	HAL_Delay(130);
}


template<class  Communicate>
void ST7735<Communicate>::write_reg (uint8_t reg){
	WriteReg wr;
	Communicate::send8b(reg);
}

template<class  Communicate>
void ST7735<Communicate>::write_data (uint8_t data){
	WriteData wd;
	Communicate::send8b(data);
}

template<class  Communicate>
void ST7735<Communicate>::send_reg (uint8_t reg, uint8_t data){
	write_reg(reg);
	write_data(data);
}

template<class  Communicate>
void ST7735<Communicate>::set_cursor (uint16_t x, uint16_t y){
	uint8_t data = 0;
	write_reg(LCD_REG_42);
	data = static_cast<uint8_t>(x >> 8);
	write_data(data);
	data = static_cast<uint8_t>(x & 0xFF);
	write_data(data);
	write_reg(LCD_REG_43);
	data = static_cast<uint8_t>(y >> 8);
	write_data(data);
	data = static_cast<uint8_t>(y & 0xFF);
	write_data(data);
	write_reg(LCD_REG_44);
}

template<class  Communicate>
void ST7735<Communicate>::init (void){

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_Delay(40);

	hard_reset();

	write_reg(LCD_REG_1);
	HAL_Delay(130);

	write_reg(LCD_REG_17);

	write_reg(LCD_REG_58);
	write_data( 0x05);
	HAL_Delay(500);

	write_reg(LCD_REG_54);
	write_data(0x40);
	HAL_Delay(10);

	write_reg(LCD_REG_32);
	HAL_Delay(10);

	fill_screen(0x001F);

	write_reg(LCD_REG_41);
}

template<class  Communicate>
void ST7735<Communicate>::set_frame (uint16_t x, uint16_t y,
										uint16_t width, uint16_t height){
	uint8_t data = 0;
	/* Column addr set, 4 args, no delay: XSTART = Xpos, XEND = (Xpos + Width - 1) */
	write_reg(LCD_REG_42);
	data = static_cast<uint8_t>(x >> 8);
	write_data(data);
	data = static_cast<uint8_t>(x & 0xFF);
	write_data(data);
	data = static_cast<uint8_t>( (x + width - 1) >> 8 );
	write_data(data);
	data = static_cast<uint8_t>( (x + width - 1) & 0xFF );
	write_data(data);
	/* Row addr set, 4 args, no delay: YSTART = Ypos, YEND = (Ypos + Height - 1) */
	write_reg(LCD_REG_43);
	data = static_cast<uint8_t>(y >> 8);
	write_data(data);
	data = static_cast<uint8_t>(y & 0xFF);
	write_data(data);
	data = static_cast<uint8_t>( (y + height - 1) >> 8 );
	write_data(data);
	data = static_cast<uint8_t>( (y + height - 1) & 0xFF );
	write_data(data);

	write_reg(LCD_REG_44);
}

template<class  Communicate>
void ST7735<Communicate>::flush_from_buffer (uint16_t* buf, uint16_t size){
	WriteData wd;
	Communicate::send16b(buf, size);
}

template<class  Communicate>
void ST7735<Communicate>::fill_screen (uint16_t color){
	set_frame(0, 0, ST7735_LCD_PIXEL_WIDTH, ST7735_LCD_PIXEL_WIDTH);

	for (uint_fast16_t i = 0; i != ST7735_LCD_PIXEL_NUMBER; ++i){
		write_data( (uint8_t)(color >> 8) );
		write_data( (uint8_t)(color & 0xFF) );
	}
}

/*******************************************************************************
*  Public functions declarations
*******************************************************************************/

} // End of ... namespace

#endif /* ST7735_H_ */
