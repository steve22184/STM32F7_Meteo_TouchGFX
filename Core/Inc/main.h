/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Button_Pin GPIO_PIN_13
#define Button_GPIO_Port GPIOC
#define I2C_SDA_Pin GPIO_PIN_0
#define I2C_SDA_GPIO_Port GPIOF
#define I2C_SCL_Pin GPIO_PIN_1
#define I2C_SCL_GPIO_Port GPIOF
#define LCD_RST_Pin GPIO_PIN_10
#define LCD_RST_GPIO_Port GPIOF
#define SPI2_MOSI_Pin GPIO_PIN_3
#define SPI2_MOSI_GPIO_Port GPIOC
#define TIM3_CH1_IR_Pin GPIO_PIN_6
#define TIM3_CH1_IR_GPIO_Port GPIOA
#define Green_Pin GPIO_PIN_0
#define Green_GPIO_Port GPIOB
#define TIM1_CH1_DHT11_Pin GPIO_PIN_9
#define TIM1_CH1_DHT11_GPIO_Port GPIOE
#define Red_Pin GPIO_PIN_14
#define Red_GPIO_Port GPIOB
#define TS_CS_Pin GPIO_PIN_2
#define TS_CS_GPIO_Port GPIOG
#define LCD_RS_Pin GPIO_PIN_0
#define LCD_RS_GPIO_Port GPIOD
#define LCD_CS_Pin GPIO_PIN_1
#define LCD_CS_GPIO_Port GPIOD
#define SPI2_SCK_Pin GPIO_PIN_3
#define SPI2_SCK_GPIO_Port GPIOD
#define Blue_Pin GPIO_PIN_7
#define Blue_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
