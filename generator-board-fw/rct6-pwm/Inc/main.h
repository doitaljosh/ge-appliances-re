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
#include "stm32f1xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CH2_TSENSE_Pin GPIO_PIN_1
#define CH2_TSENSE_GPIO_Port GPIOC
#define CH2_ISENSE_Pin GPIO_PIN_3
#define CH2_ISENSE_GPIO_Port GPIOA
#define CH1_ISENSE_Pin GPIO_PIN_6
#define CH1_ISENSE_GPIO_Port GPIOA
#define CH2_LOW_Pin GPIO_PIN_7
#define CH2_LOW_GPIO_Port GPIOA
#define CH1_TSENSE_Pin GPIO_PIN_5
#define CH1_TSENSE_GPIO_Port GPIOC
#define GEA_TXD_Pin GPIO_PIN_10
#define GEA_TXD_GPIO_Port GPIOB
#define GEA_RXD_Pin GPIO_PIN_11
#define GEA_RXD_GPIO_Port GPIOB
#define CH1_LOW_Pin GPIO_PIN_13
#define CH1_LOW_GPIO_Port GPIOB
#define CH1_OE_Pin GPIO_PIN_15
#define CH1_OE_GPIO_Port GPIOB
#define CH2_HIGH_Pin GPIO_PIN_6
#define CH2_HIGH_GPIO_Port GPIOC
#define CH2_OE_Pin GPIO_PIN_9
#define CH2_OE_GPIO_Port GPIOC
#define CH1_HIGH_Pin GPIO_PIN_8
#define CH1_HIGH_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_8
#define LED_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
