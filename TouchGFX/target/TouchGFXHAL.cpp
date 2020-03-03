/**
  ******************************************************************************
  * File Name          : TouchGFXHAL.cpp
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
#include <TouchGFXHAL.hpp>

/* USER CODE BEGIN TouchGFXHAL.cpp */

#include "stm32f7xx.h"
#include "key_sampler.hpp"
//#include "st7735.hpp"
#include "ili9486.hpp"
#include "xpt2046.hpp"

using namespace touchgfx;

// Block Allocator for Partial Framebuffer strategy
touchgfx::ManyBlockAllocator<38400, /* block size */
                   2, /* number of blocks */
                   2  /* bytes per pixel */
                   > blockAllocator;

namespace touchgfx {
void startNewTransfer(void);
}
void transmitFrameBufferBlock(uint8_t* pixels, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
uint8_t isTransmittingData();

void calibration (void);

static volatile bool readyForTransfer = false;

KeySampler btnCtrl;

void TouchGFXHAL::initialize()
{
    // Calling parent implementation of initialize().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.
    // Please note, HAL::initialize() must be called to initialize the framework.

    TouchGFXGeneratedHAL::initialize();

    // Partial framebuffers strategy
    setFrameBufferAllocator(&blockAllocator);
    setFrameRefreshStrategy(HAL::REFRESH_STRATEGY_PARTIAL_FRAMEBUFFER);

    TouchGFXGeneratedHAL::lockDMAToFrontPorch(false);

    TouchGFXGeneratedHAL::setButtonController(&btnCtrl);
//    HAL::getButtonController()->init();
    HAL::setTouchSampleRate(30);

//    app::ST7735<app::Spi>::init();
    app::ILI9486<app::spi>::init(1);
    calibration();
}

/**
 * Gets the frame buffer address used by the TFT controller.
 *
 * @return The address of the frame buffer currently being displayed on the TFT.
 */
uint16_t* TouchGFXHAL::getTFTFrameBuffer() const
{
    // Calling parent implementation of getTFTFrameBuffer().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    return TouchGFXGeneratedHAL::getTFTFrameBuffer();
}

/**
 * Sets the frame buffer address used by the TFT controller.
 *
 * @param [in] address New frame buffer address.
 */
void TouchGFXHAL::setTFTFrameBuffer(uint16_t* address)
{
    // Calling parent implementation of setTFTFrameBuffer(uint16_t* address).
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::setTFTFrameBuffer(address);
}

/**
 * This function is called whenever the framework has performed a partial draw.
 *
 * @param rect The area of the screen that has been drawn, expressed in absolute coordinates.
 *
 * @see flushFrameBuffer().
 */
void TouchGFXHAL::flushFrameBuffer(const touchgfx::Rect& rect)
{
    // Calling parent implementation of flushFrameBuffer(const touchgfx::Rect& rect).
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.
    // Please note, HAL::flushFrameBuffer(const touchgfx::Rect& rect) must
    // be called to notify the touchgfx framework that flush has been performed.

    TouchGFXGeneratedHAL::flushFrameBuffer(rect);

//    using namespace app;
//    ST7735<Spi>::set_frame(rect.x, rect.y, rect.width, rect.height);
//    ST7735<Spi>::flush_from_buffer(TouchGFXGeneratedHAL::buffer0,
//    								static_cast<uint16_t>(rect.width * rect.height));

    frameBufferAllocator->markBlockReadyForTransfer();
        if (!isTransmittingData())
        {
            touchgfx::Rect r;
            const uint8_t* pixels = frameBufferAllocator->getBlockForTransfer(r);
            transmitFrameBufferBlock((uint8_t*)pixels, r.x, r.y, r.width, r.height);
        }

        touchgfx::startNewTransfer();



    // If the framebuffer is placed in Write Through cached memory (e.g. SRAM) then we need
    // to flush the Dcache to make sure framebuffer is correct in RAM. That's done
    // using SCB_CleanInvalidateDCache().

    // SCB_CleanInvalidateDCache();
}

/**
 * Configures the interrupts relevant for TouchGFX. This primarily entails setting
 * the interrupt priorities for the DMA and LCD interrupts.
 */
void TouchGFXHAL::configureInterrupts()
{
    // Calling parent implementation of configureInterrupts().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::configureInterrupts();
}

/**
 * Used for enabling interrupts set in configureInterrupts()
 */
void TouchGFXHAL::enableInterrupts()
{
    // Calling parent implementation of enableInterrupts().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::enableInterrupts();
}

/**
 * Used for disabling interrupts set in configureInterrupts()
 */
void TouchGFXHAL::disableInterrupts()
{
    // Calling parent implementation of disableInterrupts().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::disableInterrupts();
}

/**
 * Configure the LCD controller to fire interrupts at VSYNC. Called automatically
 * once TouchGFX initialization has completed.
 */
void TouchGFXHAL::enableLCDControllerInterrupt()
{
    // Calling parent implementation of enableLCDControllerInterrupt().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::enableLCDControllerInterrupt();
}


void TouchGFXHAL::endFrame(){
	TouchGFXGeneratedHAL::endFrame();
	while(isTransmittingData())
	    { }
}

/* ******************************************************
 * Functions required by Partial Frame Buffer Strategy
 * ******************************************************
 *
 *  *  uint8_t isTransmittingData() must return whether or not data is currently being transmitted, over e.g. SPI.
 *  *  void transmitFrameBufferBlock(uint8_t* pixels, uint16_t x, uint16_t y, uint16_t w, uint16_t h) will be called
 *       when the framework wants to send a block. The user must then transfer
 *       the data represented by the arguments.
 *
 *  A user must call touchgfx::startNewTransfer(); once transmitFrameBufferBlock() has succesfully sent a block.
 *  E.g. if using DMA to transfer the block, this could be called in the "Transfer Completed" interrupt handler.
 *
 */
namespace touchgfx
{
/**
 * This functinon is called by FrameBufferAllocator if no block is
 * available.
 */
void FrameBufferAllocatorWaitOnTransfer()
{
  while(!readyForTransfer);
}

/**
 * Called by FrameBufferAllocator when a block is drawn and
 * therefore ready for transfer. The LCD driver should use this
 * method to start a transfer.
 */
void FrameBufferAllocatorSignalBlockDrawn()
{
    readyForTransfer = false;
    return;
}

// A user must call touchgfx::startNewTransfer(); once transmitFrameBufferBlock() has succesfully sent a block.
void startNewTransfer()
{
    FrameBufferAllocator* fba = HAL::getInstance()->getFrameBufferAllocator();
    fba->freeBlockAfterTransfer();
    readyForTransfer = true;

    if (fba->hasBlockReadyForTransfer())
    {
        touchgfx::Rect r;
        const uint8_t* pixels = fba->getBlockForTransfer(r);
        transmitFrameBufferBlock((uint8_t*)pixels, r.x, r.y, r.width, r.height);
    }
}
}

void transmitFrameBufferBlock(uint8_t* pixels, uint16_t x, uint16_t y, uint16_t w, uint16_t h){
	app::ILI9486<app::spi>::set_frame(x, y, w, h);
	app::ILI9486<app::spi>::flush_from_buffer ((uint16_t*) pixels, (uint16_t)(w * h));
}
uint8_t isTransmittingData(){
	return false;
}

void calibration (void){
	using namespace app;
	uint16_t LEFT_TOP_1 = 0, RIGHT_TOP_2 = 1, RIGHT_DOWN_3 = 2, LEFT_DOWN_4 = 3;
	uint32_t MeasureFlags = 0;

//	ALLOCATOR(AppAllocator, uint32_t, al);

	CustomAllocator<uint32_t>ca( allocator() );
	std::vector<uint32_t, alloc_type32>pointX(4, ca);
	std::vector<uint32_t, alloc_type32>pointY(4, ca);
	ILI_ADC_TypeDef raw;

	ILI9486<spi>::draw_fill_circle(POINT1_X, POINT1_Y, 5, GREEN);
	ILI9486<spi>::draw_fill_circle(POINT2_X, POINT2_Y, 5, GREEN);
	ILI9486<spi>::draw_fill_circle(POINT3_X, POINT3_Y, 5, GREEN);
	ILI9486<spi>::draw_fill_circle(POINT4_X, POINT4_Y, 5, GREEN);

	while(MeasureFlags != 0x0F)
	{
		while ( !touch().scan_adc() ) { __NOP(); }

		raw = touch().get_raw_xy();

		if( (raw.adc_x < MAX_ADC_TOUCH / 2) && (raw.adc_y < MAX_ADC_TOUCH / 2) ) {
			pointX[LEFT_TOP_1] = raw.adc_x;
			pointY[LEFT_TOP_1] = raw.adc_y;
			MeasureFlags |= (1 << LEFT_TOP_1);
			ILI9486<spi>::draw_fill_circle(POINT1_X, POINT1_Y, 5, RED);
		}
		else if( (raw.adc_x > MAX_ADC_TOUCH / 2) && (raw.adc_y < MAX_ADC_TOUCH / 2) )	{
			pointX[RIGHT_TOP_2] = raw.adc_x;
			pointY[RIGHT_TOP_2] = raw.adc_y;
			MeasureFlags |= (1 << RIGHT_TOP_2);
			ILI9486<spi>::draw_fill_circle(POINT2_X, POINT2_Y, 5, RED);
		}
		else if( (raw.adc_x > MAX_ADC_TOUCH / 2) && (raw.adc_y > MAX_ADC_TOUCH / 2) ) {
			pointX[RIGHT_DOWN_3] = raw.adc_x;
			pointY[RIGHT_DOWN_3] = raw.adc_y;
			MeasureFlags |= (1 << RIGHT_DOWN_3);
			ILI9486<spi>::draw_fill_circle(POINT3_X, POINT3_Y, 5, RED);
		}
		else if( (raw.adc_x < MAX_ADC_TOUCH/2) && (raw.adc_y > MAX_ADC_TOUCH/2) ) {
			pointX[LEFT_DOWN_4] = raw.adc_x;
			pointY[LEFT_DOWN_4] = raw.adc_y;
			MeasureFlags |= (1 << LEFT_DOWN_4);
			ILI9486<spi>::draw_fill_circle(POINT4_X, POINT4_Y, 5, RED);
		}

		while ( touch().scan_adc() ) { __NOP(); }
		//_delay_ms(100);
	}

	pointX[RIGHT_DOWN_3] = (pointX[RIGHT_DOWN_3] + pointX[RIGHT_TOP_2]) / 2;
	pointX[RIGHT_DOWN_3] *= 10;
	pointX[LEFT_TOP_1] = (pointX[LEFT_TOP_1] + pointX[LEFT_DOWN_4]) / 2;
	pointX[LEFT_TOP_1] *= 10;

	pointY[RIGHT_DOWN_3] = (pointY[RIGHT_DOWN_3] + pointY[LEFT_DOWN_4]) / 2;
	pointY[RIGHT_DOWN_3] *= 10;
	pointY[LEFT_TOP_1] = (pointY[LEFT_TOP_1] + pointY[RIGHT_TOP_2]) / 2;
	pointY[LEFT_TOP_1] *= 10;

	touch().get_calibr().kx = (pointX[RIGHT_DOWN_3] - pointX[LEFT_TOP_1]) / (POINT3_X - POINT1_X);
	touch().get_calibr().ky = (pointY[RIGHT_DOWN_3] - pointY[LEFT_TOP_1]) / (POINT3_Y - POINT1_Y);

	touch().get_calibr().offset_x = (pointX[LEFT_TOP_1]) / touch().get_calibr().kx - POINT1_X;
	touch().get_calibr().offset_y = (pointY[LEFT_TOP_1]) / touch().get_calibr().ky - POINT1_Y;
}
/* USER CODE END TouchGFXHAL.cpp */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
