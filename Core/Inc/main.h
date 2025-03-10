/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ERR_LD_Pin GPIO_PIN_14
#define ERR_LD_GPIO_Port GPIOC
#define PULSE_LD_Pin GPIO_PIN_15
#define PULSE_LD_GPIO_Port GPIOC
#define ETHERNET_STA_Pin GPIO_PIN_1
#define ETHERNET_STA_GPIO_Port GPIOA
#define ETHERNET_TX_Pin GPIO_PIN_2
#define ETHERNET_TX_GPIO_Port GPIOA
#define ETHERNET_RX_Pin GPIO_PIN_3
#define ETHERNET_RX_GPIO_Port GPIOA
#define LDZ_CS_Pin GPIO_PIN_4
#define LDZ_CS_GPIO_Port GPIOA
#define LDZ_SCK_Pin GPIO_PIN_5
#define LDZ_SCK_GPIO_Port GPIOA
#define LDZ_SDA_Pin GPIO_PIN_6
#define LDZ_SDA_GPIO_Port GPIOA
#define LDZ_DC_Pin GPIO_PIN_7
#define LDZ_DC_GPIO_Port GPIOA
#define LDZ_RE_Pin GPIO_PIN_0
#define LDZ_RE_GPIO_Port GPIOB
#define K4_Pin GPIO_PIN_1
#define K4_GPIO_Port GPIOB
#define K1_Pin GPIO_PIN_2
#define K1_GPIO_Port GPIOB
#define K2_Pin GPIO_PIN_10
#define K2_GPIO_Port GPIOB
#define K3_Pin GPIO_PIN_11
#define K3_GPIO_Port GPIOB
#define Rn_input_Pin GPIO_PIN_8
#define Rn_input_GPIO_Port GPIOA
#define RS485_TX_Pin GPIO_PIN_9
#define RS485_TX_GPIO_Port GPIOA
#define RS485_RX_Pin GPIO_PIN_10
#define RS485_RX_GPIO_Port GPIOA
#define LX_LIGHT_PWM_Pin GPIO_PIN_11
#define LX_LIGHT_PWM_GPIO_Port GPIOA
#define RS485_EN_Pin GPIO_PIN_12
#define RS485_EN_GPIO_Port GPIOA
#define BUZZER_Pin GPIO_PIN_15
#define BUZZER_GPIO_Port GPIOA
#define CF1_Pin GPIO_PIN_3
#define CF1_GPIO_Port GPIOB
#define CF2_Pin GPIO_PIN_4
#define CF2_GPIO_Port GPIOB
#define CF3_Pin GPIO_PIN_5
#define CF3_GPIO_Port GPIOB
#define CF4_Pin GPIO_PIN_6
#define CF4_GPIO_Port GPIOB
#define CF5_Pin GPIO_PIN_7
#define CF5_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
