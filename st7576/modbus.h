#ifndef MODBUS_H_
#define MODBUS_H_

#include "stm32f1xx_hal.h"//HAL���ļ�����
#include "gpio.h"
#include "usart.h"

#define BUFFER_SIZE 600 //�������֡
#define RS485DIR_RX HAL_GPIO_WritePin(RS485_EN_GPIO_Port,RS485_EN_Pin,0);//���ǿ���485����
#define RS485DIR_TX HAL_GPIO_WritePin(RS485_EN_GPIO_Port,RS485_EN_Pin,1);//���ǿ���485����

typedef struct {
	uint8_t myadd;//�ӻ��豸��ַ
	uint8_t timrun;//��ʱ��
	uint8_t slave_add;//����Ҫƥ��Ĵӻ���ַ�����豸��Ϊ����ʱ��
	uint8_t reflag;//������ɱ�־λ��1����� 0��δ���
	uint8_t Host_time_flag;//�������ݱ�־
	uint8_t recount;//���յ����ֽ���
	unsigned char rcbuf[BUFFER_SIZE];//��������֡
	unsigned char sendbuf[BUFFER_SIZE];//��������֡
	uint32_t timout;//��ʱʱ�� ��λ��ms
	uint32_t Host_Sendtime;//��������һ֡���ʱ����� ��λ��ms
	
	
}MODBUS;
 // Modbus��ʼ������
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
