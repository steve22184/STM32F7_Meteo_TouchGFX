
/*
 * lldrv.cpp
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
#include "lldrv.hpp"

namespace app {
/*******************************************************************************
*  Defines
*******************************************************************************/
#define HSPI			hspi5
#define IICx			hi2c2
#define UARTx			huart2

#define SET_DATASIZE(datasize)										\
	do {															\
		if (HSPI.Init.DataSize != datasize){						\
			MODIFY_REG(HSPI.Instance->CR2, SPI_CR2_DS, datasize);	\
			HSPI.Init.DataSize = datasize; }						\
		} while (0)
/*******************************************************************************
*  Constants and variables
*******************************************************************************/
}

SPI_HandleTypeDef hspi5;
I2C_HandleTypeDef hi2c2;
UART_HandleTypeDef huart2;

namespace app{

constexpr uint32_t UART_WAIT = UINT32_C(3000);
constexpr uint16_t i2c_start_address = UINT16_C(0x40);
constexpr uint16_t EEPROM_DRIVER = UINT16_C(0xA0);
/*******************************************************************************
*  Enums
*******************************************************************************/

/*******************************************************************************
*  Typedefs
*******************************************************************************/

/*******************************************************************************
*  Local functions declarations
*******************************************************************************/

/*******************************************************************************
*  Class methods
*******************************************************************************/
void Spi::mode (uint32_t prescaler){
	if (HSPI.Init.BaudRatePrescaler != prescaler){
		MODIFY_REG(HSPI.Instance->CR1, SPI_CR1_BR, prescaler);
		HSPI.Init.BaudRatePrescaler = prescaler;
	}
}

void Spi::send8b (uint8_t value){
	SET_DATASIZE(SPI_DATASIZE_8BIT);
	uint8_t temp = value;
	HAL_SPI_Transmit(&HSPI, &temp, 1, 50);
}

void Spi::send8b (uint8_t* data, uint16_t size){
	SET_DATASIZE(SPI_DATASIZE_8BIT);
	HAL_SPI_Transmit(&HSPI, data, size, 10000);
}

void Spi::send16b (uint16_t value){
	SET_DATASIZE(SPI_DATASIZE_16BIT);
	uint16_t temp = value;
	HAL_SPI_Transmit(&HSPI, (uint8_t*)&temp, 1, 50);
}

void Spi::send16b (uint16_t* data, uint16_t size){
	SET_DATASIZE(SPI_DATASIZE_16BIT);
	HAL_SPI_Transmit(&HSPI, (uint8_t*)data, size, 10000);
}

void Spi::recieve8b (uint8_t* data, uint16_t size){
	SET_DATASIZE(SPI_DATASIZE_8BIT);
	HAL_SPI_Receive(&HSPI, data, size, 10000);
}

void Spi::receive16b (uint16_t* data, uint16_t size){
	SET_DATASIZE(SPI_DATASIZE_16BIT);
	HAL_SPI_Receive(&HSPI, (uint8_t*)data, size, 10000);
}

/*----------------------------------------------------------------------------*/
void IIC::send8b (uint8_t* data, uint16_t size, uint16_t address){
	HAL_I2C_Mem_Write_DMA(&IICx, EEPROM_DRIVER, address,
					 I2C_MEMADD_SIZE_16BIT, data, size);
}
void IIC::receive8b (uint8_t* data, uint16_t size, uint16_t address){
	HAL_I2C_Mem_Read_DMA(&IICx, EEPROM_DRIVER, address,
				 I2C_MEMADD_SIZE_16BIT, data, size);
}

/*----------------------------------------------------------------------------*/
void Uart::mode (uint32_t baud){
	HAL_UART_DeInit(&UARTx);
	UARTx.Init.BaudRate = baud;
	HAL_UART_Init(&UARTx);
}

void Uart::send_receive8b (uint8_t* tdata, uint8_t* rdata, uint16_t size){
	uint8_t *tx = tdata;
	uint8_t *rx = rdata;

	SET_BIT(UARTx.Instance->CR1, USART_CR1_UE);

	while (size--) {
		UARTx.Instance->TDR = *tx++;
		while (READ_BIT(UARTx.Instance->ISR, USART_ISR_TXE) != USART_ISR_TXE ){__NOP();}
		while (READ_BIT(UARTx.Instance->ISR, USART_ISR_RXNE) != USART_ISR_RXNE){__NOP();}
		*rx++ = UARTx.Instance->RDR;
	}
	while ( READ_BIT(UARTx.Instance->ISR, USART_ISR_TC) != USART_ISR_TC ){__NOP();}

	CLEAR_BIT(UARTx.Instance->CR1, USART_CR1_UE);
}
/*******************************************************************************
*  Local functions definitions
*******************************************************************************/

/*******************************************************************************
*  Public functions definitions
*******************************************************************************/

} // End of app namespace

