/*
 * ili9486.h
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

#ifndef ILI9486_H_
#define ILI9486_H_


/*******************************************************************************
*  Includes
*******************************************************************************/
#pragma once
#include <array>
#include <vector>
#include "lldrv.hpp"
#include <custom_alloc.hpp>

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
	ILI9486_LCD_PIXEL_WIDTH = 480,
	ILI9486_LCD_PIXEL_HEIGHT = 320,
	ILI9486_LCD_PIXEL_NUMBER = (ILI9486_LCD_PIXEL_WIDTH *
			ILI9486_LCD_PIXEL_HEIGHT),
} Display_Size;

typedef enum {
	WHITE      =   UINT16_C(0xFFFF),
	BLACK      =   UINT16_C(0x0000),
	BLUE       =   UINT16_C(0x001F),
	RED        =   UINT16_C(0xF800),
	MAGENTA    =   UINT16_C(0xF81F),
	GREEN      =   UINT16_C(0x07E0),
	CYAN       =   UINT16_C(0x7FFF),
	YELLOW     =   UINT16_C(0xFFE0),
	BROWN	    =	UINT16_C(0xBC40),
	BRRED	    =	UINT16_C(0xFC07),			// brownish red
	GRAY 	    =	UINT16_C(0x8430), 		// gray
	DARKBLUE   = 	UINT16_C(0x01CF), 		// dark blue
	LIGHTBLUE  = 	UINT16_C(0x7D7C), 		// blue
	GRAYBLUE 	=	UINT16_C(0x5458), 	    // gray-blue
	LIGHTGREEN =	UINT16_C(0x841F), 		// light green
	LIGHTGRAY 	=	UINT16_C(0xC618), 	    // light gray
}BasicColors;

typedef enum{
	ILI9486_CASET = UINT8_C(0x2A),
	ILI9486_PASET = UINT8_C(0x2B),
	ILI9486_RAMWR = UINT8_C(0x2C),
	ILI9486_RAMRD = UINT8_C(0x2E),
	ILI9486_MADCTL = UINT8_C(0x36),
	MADCTL_MY = UINT8_C(0x80),
	MADCTL_MX = UINT8_C(0x40),
	MADCTL_MV = UINT8_C(0x20),
	MADCTL_ML = UINT8_C(0x10),
	MADCTL_BGR = UINT8_C(0x08),
	MADCTL_MH = UINT8_C(0x04),
}ILI9486_Commands;


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
class ILI9486{
public:
	ILI9486 &operator=(const ILI9486&)=delete;
	static void set_frame (uint16_t x, uint16_t y, uint16_t width, uint16_t height);
	static void draw_rectangle (uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
	static void draw_line (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
							uint16_t size, uint16_t color);
	static void draw_fill_circle (uint16_t x0, uint16_t y0, uint16_t radius, uint16_t color);
	static void flush_from_buffer (uint16_t* buf, uint16_t size);
	static void init (uint32_t rotation);

private:
	static void hard_reset (void);
	static inline void write_command (uint8_t reg);
	static inline void write_data (uint8_t data);
	static void set_rotation (uint32_t rotation);
};
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*******************************************************************************
*  Template class methods
*******************************************************************************/

template<class Communicate>
void ILI9486<Communicate>::set_frame (uint16_t x, uint16_t y,
		uint16_t width, uint16_t height){
	// this controller seems to need separate transactions; reason speed on SPI ?

	write_command(ILI9486_CASET);  // Column addr set
	uint8_t data = static_cast<uint8_t>(x >> 8);
	write_data(data);
	data = static_cast<uint8_t>(x & 0xFF);
	write_data(data); // XSTART
	data = static_cast<uint8_t>((x + width - 1) >> 8);
	write_data(data);
	data = static_cast<uint8_t>((x + width - 1) & 0xFF);
	write_data(data); // XEND

	write_command(ILI9486_PASET);  // Row addr set
	data = static_cast<uint8_t>(y >> 8);
	write_data(data);
	data = static_cast<uint8_t>(y);
	write_data(data); // YSTART
	data = static_cast<uint8_t>((y + height - 1) >> 8);
	write_data(data);
	data = static_cast<uint8_t>((y + height - 1));
	write_data(data); // YSTART

	write_command(ILI9486_RAMWR); // Команда на запись в видеопамять
}

template<class Communicate>
void ILI9486<Communicate>::draw_rectangle (uint16_t x, uint16_t y,
													uint16_t w, uint16_t h, uint16_t color){
	Communicate::template set_prescaler<>(SPI_BAUDRATEPRESCALER_4);

	set_frame(x, y, w, h);

//	ALLOCATOR(AppAllocator, uint16_t, al);
	CustomAllocator<uint16_t>ca( allocator() );

	std::vector<uint16_t, alloc_type16>buf(w, ca);
	std::fill(buf.begin(), buf.end(), color);

	WriteData wd;
	for (uint_fast16_t i = 0; i != h; ++i){
		Communicate::template send16b<>(buf.data(), w);
	}
}

template<class Communicate>
void ILI9486<Communicate>::draw_line (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
		uint16_t size, uint16_t color){
	if (x1 >= ILI9486_LCD_PIXEL_WIDTH)	return;
	if (y1 >= ILI9486_LCD_PIXEL_HEIGHT)	return;
	if (x2 >= ILI9486_LCD_PIXEL_WIDTH)	return;
	if (y2 >= ILI9486_LCD_PIXEL_HEIGHT)	return;

	int deltaX = (x2 <= x1) ? (x1 - x2) : (x2 - x1);
	int deltaY = (y2 <= y1) ? (y1 - y2) : (y2 - y1);
	int signX = (x1 < x2) ? 1 : -1;
	int signY = (y1 < y2) ? 1 : -1;
	int error = deltaX - deltaY;

	while(1)
	{
		draw_rectangle(x1, y1, size, size, color);
		if(x1 == x2 && y1 == y2){
			break;
		}
		int error2 = error*2;

		if(error2 > -deltaY) {
			error -= deltaY;
			x1 = static_cast<uint16_t>(x1 + signX);
		}

		if(error2 < deltaX) {
			error += deltaX;
			y1 = static_cast<uint16_t>(y1 + signY);
		}
	}
}
template<class Communicate>
void ILI9486<Communicate>::draw_fill_circle (uint16_t x0, uint16_t y0, uint16_t radius, uint16_t color){
	int x = -radius, y = 0, err = 2 - 2 * radius, e2 = 0;
	do {
		draw_line(x0 - x, y0 - y, x0 - x, y0 + y, 1, color);
		draw_line(x0 + x, y0 - y, x0 + x, y0 + y, 1, color);
		e2 = err;
		if (e2 <= y)
		{
			++y;
			err += (y * 2 + 1);
			if (-x == y && e2 <= x) {
				e2 = 0;
			}
		}
		if (e2 > x) {
			++x;
			err += (x * 2 + 1);
		}
	} while (x <= 0);
}

template<class Communicate>
void ILI9486<Communicate>::flush_from_buffer (uint16_t* buf, uint16_t size){
	Communicate::template set_prescaler(SPI_BAUDRATEPRESCALER_4);
	WriteData wr;
	Communicate::template send16b<>(buf, size);
}


template<class Communicate>
void ILI9486<Communicate>::init (uint32_t rotation){

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_Delay(40);

	hard_reset();
	write_command(0x3A);
	write_data(0x55);  // use 16 bits per pixel color
	write_command(0x36);
	write_data(0x48);  // MX, BGR == rotation 0
	// PGAMCTRL(Positive Gamma Control)
	write_command(0xE0);
	write_data(0x0F);
	write_data(0x1F);
	write_data(0x1C);
	write_data(0x0C);
	write_data(0x0F);
	write_data(0x08);
	write_data(0x48);
	write_data(0x98);
	write_data(0x37);
	write_data(0x0A);
	write_data(0x13);
	write_data(0x04);
	write_data(0x11);
	write_data(0x0D);
	write_data(0x00);
	// NGAMCTRL(Negative Gamma Control)
	write_command(0xE1);
	write_data(0x0F);
	write_data(0x32);
	write_data(0x2E);
	write_data(0x0B);
	write_data(0x0D);
	write_data(0x05);
	write_data(0x47);
	write_data(0x75);
	write_data(0x37);
	write_data(0x06);
	write_data(0x10);
	write_data(0x03);
	write_data(0x24);
	write_data(0x20);
	write_data(0x00);
	// Digital Gamma Control 1
	write_command(0xE2);
	write_data(0x0F);
	write_data(0x32);
	write_data(0x2E);
	write_data(0x0B);
	write_data(0x0D);
	write_data(0x05);
	write_data(0x47);
	write_data(0x75);
	write_data(0x37);
	write_data(0x06);
	write_data(0x10);
	write_data(0x03);
	write_data(0x24);
	write_data(0x20);
	write_data(0x00);
	write_command(0x11);  // Sleep OUT
	HAL_Delay(150);   // wait some time
	write_command(0x29);  // Display ON
	set_rotation(rotation);
	draw_rectangle(0, 0, ILI9486_LCD_PIXEL_WIDTH, ILI9486_LCD_PIXEL_HEIGHT, BLUE);
}

template<class Communicate>
void ILI9486<Communicate>::hard_reset (void){
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_SET);
	HAL_Delay(130);
}


template<class Communicate>
void ILI9486<Communicate>::write_command (uint8_t reg){
	Communicate::template set_prescaler<>(SPI_BAUDRATEPRESCALER_4);
	WriteReg wr;
	Communicate::template send8b<>(reg);
}

template<class Communicate>
void ILI9486<Communicate>::write_data (uint8_t data){
	Communicate::template set_prescaler<>(SPI_BAUDRATEPRESCALER_4);
	WriteData wd;
	Communicate::template send8b<>(data);
}

template<class Communicate>
void ILI9486<Communicate>::set_rotation (uint32_t rotation){
	write_command(ILI9486_MADCTL);
	switch (rotation & 3)
	{
	case 0:
		write_data(MADCTL_MX | MADCTL_BGR);
		break;
	case 1:
		write_data(MADCTL_MV | MADCTL_BGR);
		break;
	case 2:
		write_data(MADCTL_MY | MADCTL_BGR);
		break;
	case 3:
		write_data(MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
		break;
	}
}

/*******************************************************************************
*  Public functions declarations
*******************************************************************************/

} // End of ... namespace

#endif /* ILI9486_H_ */
