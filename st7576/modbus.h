#ifndef MODBUS_H_
#define MODBUS_H_

#include "stm32f1xx_hal.h"//HAL库文件声明
#include "gpio.h"
#include "usart.h"

#define BUFFER_SIZE 600 //最大数据帧
#define RS485DIR_RX HAL_GPIO_WritePin(RS485_EN_GPIO_Port,RS485_EN_Pin,0);//这是开启485发送
#define RS485DIR_TX HAL_GPIO_WritePin(RS485_EN_GPIO_Port,RS485_EN_Pin,1);//这是开启485接受

typedef struct {
	uint8_t myadd;//从机设备地址
	uint8_t timrun;//定时器
	uint8_t slave_add;//主机要匹配的从机地址（本设备作为主机时）
	uint8_t reflag;//接收完成标志位，1：完成 0：未完成
	uint8_t Host_time_flag;//发送数据标志
	uint8_t recount;//接收到的字节数
	unsigned char rcbuf[BUFFER_SIZE];//接受数据帧
	unsigned char sendbuf[BUFFER_SIZE];//发送数据帧
	uint32_t timout;//超时时间 单位：ms
	uint32_t Host_Sendtime;//发送完上一帧后的时间计数 单位：ms
	
	
}MODBUS;
 // Modbus初始化函数
void Modbus_Init(void);
void Modbus_Event(void);
void Modbus_Func3(void);
void Modbus_Func6(void);
void Modbus_Func16(void);
 void Modbus_Send_Byte(  uint8_t ch );
 int Modbus_CRC16(uint8_t buff[],int len);
uint32_t my_htonl(uint32_t value);
void floatToUint16Pair(float f, uint16_t* part1, uint16_t* part2) ;
#endif
