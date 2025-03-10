/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdio.h>
#include <string.h>
#include "st7567.h"
#include "rn8302b.h"
#include "at24c02.h"
#include "modbus.h"

uint8_t size[4]={0x01,0x02,0x03,0x05};
uint8_t err[4]={0x01,0x02,0x03,0x04};
uint8_t size_out[4]={0,0,0,0};

uint8_t KEY_falg=0;

extern uint8_t null[50];
uint8_t Connect_mode[1];

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t pictureData[]={ 

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xC0,0xE0,0xF8,0xFC,0x7E,0x3F,0x7F,0xFE,0xFC,0xF0,0xE0,0x80,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xE0,0xF8,
0xFC,0xFF,0x3F,0x0F,0x03,0x00,0x00,0x00,0x80,0xC0,0xC3,0xC7,0x1F,0x7F,0xFF,0xFC,
0xF0,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xE0,0xF8,0xFC,0xFF,0x7F,0x1F,0x07,
0x01,0x00,0x60,0x70,0x78,0x7C,0x7E,0x7F,0xF7,0xF3,0xF1,0xF0,0x70,0x30,0x01,0x03,
0x0F,0x3F,0xFF,0xFF,0xFC,0xF8,0xE0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xC0,0xE0,0xF8,0xFE,0xFF,0xFF,0x3F,0x0F,0x03,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0x60,0x70,0x38,0x1C,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0x07,0x1F,0x3F,0x7F,0xFF,0xFC,0xF8,0xE0,0x80,0x00,0x00,0x00,
0x30,0x3C,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,
0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,
0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3C,0x30,/*"C:\Users\21360\Desktop\download-imageonline-imageonline.co-9139668.bmp",0*/
};
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
void PVD_config(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI2_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_I2C1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	
	LDZ_Init();
	LDZ_Cfg();
	LDZ_Clear();
	
	HAL_TIM_Base_Start_IT(&htim3);  //������ʱ��TIM3
	Modbus_Init();//������Ϊ�ӻ�ʹ��ʱ��ʼ��
	RS485DIR_RX;//����PB5������RS485ģʽΪ����
	
	
    // ģ���ͼƬ���ݣ�ʵ��Ӧ�������滻Ϊ��ʵ��ͼƬ����
    u8 pageStart = 0;
    u8 pageEnd = 5;
    u8 colStart = 45;
    u8 colEnd = 45+38;

//    LDZ_ShowPictureAnimation(pageStart, pageEnd, colStart, colEnd, pictureData);
	LDZ_ShowCHN32(0, 0,0);LDZ_ShowCHN32(0, 32,1);LDZ_ShowCHN32(0, 64,2);LDZ_ShowCHN32(0, 96,3);

	HAL_AT24C02_read(0x11,Connect_mode, 1);
	HAL_Delay(200);

	uint32_t temp;
	
	Write_SPI(RN8302_WREN , 0xE5,1);//дʹ��

	Write_SPI(RN8302_SOFTRST, 0xFA,0x01);//���������λ�Ĵ���(82H=0xfa)
	
	if(Connect_mode[0]==0x00)
	{LDZ_ShowCHN16(4, 16+16, 59); LDZ_ShowCHN16(4, 32+16, 61);LDZ_ShowCHN16(4, 48+16, 60); LDZ_ShowCHN16(4, 64+16,62);}//��������
	else if(Connect_mode[0]==0x01)
	{LDZ_ShowCHN16(4, 16+16, 59); LDZ_ShowCHN16(4, 32+16, 61);LDZ_ShowCHN16(4, 48+16, 59); LDZ_ShowCHN16(4, 64+16,62);}//��������
	else
	{LDZ_ShowCHN16(4, 16+16, 59); LDZ_ShowCHN16(4, 32+16, 61);LDZ_ShowCHN16(4, 48+16, 60); LDZ_ShowCHN16(4, 64+16,62);}//��������
		
	for(int i=0;i<128;i+=1)//�����ȴ�����оƬ��λ1.5s
		{
			LDZ_ShowASC16(6, i, 12);
			HAL_Delay(10);
		}

		LDZ_Clear();
	Write_SPI(RN8302_WREN , 0xE5,1);//дʹ��

	Write_SPI(RN8302_WMSW , 0xA2,0x01);///*�л�������ģʽ*/
		
	if(Connect_mode[0]==0x00)
		Write_SPI(RN8302_MODSEL, 0x00,0x01);//0x00��ʾ��������
	else if(Connect_mode[0]==0x01)
			Write_SPI(RN8302_MODSEL, 0x33,0x01);//0x00��ʾ��������
	else
		Write_SPI(RN8302_MODSEL, 0x00,0x01);//0x00��ʾ��������
		
	Write_SPI(RN8302_EMUCFG, 0x080000,0x03);/*������Ԫ���ã�������������ģʽ������������ģʽ�������ݵĲ�ͬ����ʽ*/
	
	Write_SPI(RN8302_CFCFG, 0x102207,0x03);/*CF �����������*/

	Write_SPI(RN8302_EMUCON, 0x777777,3);///*ʹ�ܸ��ࣨA/B/C���й�/�޹�/RMS ����/�����й�/�����޹�/�������ڵ��ܼ���*/

	
	Write_SPI(RN8302_WSAVECON ,0x10,1);///*��ղ������ݻ����������������20ms��BUFF�Ż�ʵ�����*/
	HAL_Delay(100);

	Write_SPI(RN8302_HFConst1, 0x0640,0x02);//������HFConst1�Ĵ���
	Write_SPI(RN8302_HFConst2, 0x0640,0x02);//������HFConst2�Ĵ���
	
	Write_SPI(RN8302_WREN , 0xdc,1);//д����

	PVD_config();
  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* ��ʼ��PVD */

void PVD_config()//�������ʼ��
{
	
PWR_PVDTypeDef PvdStruct;
 
    HAL_PWR_EnablePVD();                        /* ʹ��PVD */
 
    PvdStruct.PVDLevel = PWR_PVDLEVEL_7;        /* PVD��ֵ3.1V */
    PvdStruct.Mode = PWR_PVD_MODE_IT_RISING;    /* ������ */
    HAL_PWR_ConfigPVD(&PvdStruct);
 
    HAL_NVIC_SetPriority(PVD_IRQn, 5, 0);       /* ����PVD�ж����ȼ� */
    HAL_NVIC_EnableIRQ(PVD_IRQn);               /* ʹ��PVD�ж� */
}

/* PVD�жϴ��� */


/* �ⲿ�жϴ���ص����� */


/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM2 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//  /* USER CODE BEGIN Callback 0 */

//  /* USER CODE END Callback 0 */
//  if (htim->Instance == TIM2) {
//    HAL_IncTick();
//  }
//  /* USER CODE BEGIN Callback 1 */

//  /* USER CODE END Callback 1 */
//}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
