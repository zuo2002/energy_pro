#ifndef _SPI_H_
#define _SPI_H_
 
#include "main.h"
#include "stdio.h"
 
//---------------------- RN8302计量寄存器地址定义---------------------------------------------------//
#define UC_CMD      0x0009//4//C相电压有效值
#define UC_BYTE     4
 
#define SYSSR_CMD   0x018A//系统状态寄存器
#define SYSSR_BYTE  2
 
#define DeviceID_CMD   0x018f//RN8302B Device ID
#define DeviceID_BYTE  3
 
#define SPI_CS_HIGH() 	HAL_GPIO_WritePin( Rn_nss_GPIO_Port, Rn_nss_Pin, GPIO_PIN_SET );
#define SPI_CS_LOW() 	HAL_GPIO_WritePin( Rn_nss_GPIO_Port, Rn_nss_Pin, GPIO_PIN_RESET );
 
void Write_SPI_OneByte(uint8_t TxData);
uint8_t Read_SPI_OneByte(void);
uint32_t READ_SPI(uint16_t Address,uint8_t Data_len);
void Write_SPI(uint16_t Address, uint32_t dwData,uint8_t Date_len);
void ReadAmmeterData(void);
 
#endif