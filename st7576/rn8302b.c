/****************SPI ���ö˿�ģ��**********************************/
#include "rn8302b.h"
#include "spi.h"
 
 
/*****************SPI д���ֽ�**************************/
void Write_SPI_OneByte(uint8_t TxData)
{
	uint8_t Rxdata;
	HAL_SPI_TransmitReceive(&hspi2,&TxData,&Rxdata,1, 1000);
	return ;
}
/*****************SPI �����ֽ�**************************/
uint8_t Read_SPI_OneByte(void)
{
	uint8_t Rxdata;
	uint8_t TxData=0;
	HAL_SPI_TransmitReceive(&hspi2,&TxData,&Rxdata,1, 1000);
	return Rxdata;
}
/************************* READ_RN8302*************************************************/
uint32_t READ_SPI(uint16_t Address,uint8_t Data_len)
{
	uint8_t i, DTemp,CheckSumR;
	uint32_t drData;
 
	SPI_CS_LOW();    // ����SPI����
 
	DTemp = (uint8_t)(Address&0x00FF);//ADDR[7:0]
	CheckSumR = DTemp;
	Write_SPI_OneByte(DTemp);
	DTemp = (((uint8_t)(Address >> 4)) & 0xf0) ;//CMD=R/W+AD[10:8]+BL[1:0]+2��h0(MSB+LSB)
	CheckSumR += DTemp;
	Write_SPI_OneByte(DTemp);
 
	HAL_Delay(5);
	drData = 0x00000000;//Read 24bit
 
	for(i=0;i<Data_len;i++)//�ȷ����ֽڣ��󷢵��ֽ�
	{
		DTemp = Read_SPI_OneByte();
		drData = drData<<8;
		drData += DTemp;
		CheckSumR += DTemp;
	}
 
	CheckSumR = ~CheckSumR;//У����㷨�� ADDR+CMD+DATA ���ֽ����ȡ����
 
	if (CheckSumR != Read_SPI_OneByte())//�Ƚ�У���
	{
		drData = 0xFFFFFFFF;
	}
 
	SPI_CS_HIGH();	  //�ر�SPI����
	HAL_Delay(2);
	return drData;
}
/**************************Write RN8302******************************/
void Write_SPI(uint16_t Address, uint32_t dwData,uint8_t Date_len)
{
	uint8_t i,CheckSumR, DTemp;
 
	SPI_CS_LOW();	 //����SPI����
 
	DTemp = (uint8_t)(Address&0x00FF);//
	CheckSumR = DTemp;
	Write_SPI_OneByte(DTemp);//д��ַ
	DTemp = (((uint8_t)(Address >> 4)) & 0xf0)+0x80 ;
	CheckSumR += DTemp;
	Write_SPI_OneByte(DTemp);//д����
 
 
	for (i =0 ;i < Date_len;i++)//�ȷ����ֽڣ��󷢵��ֽ�
	{
		DTemp = (uint8_t)(dwData>>(Date_len-1-i)*8);
		Write_SPI_OneByte(DTemp);//д����
		CheckSumR += DTemp;
	}
 
	CheckSumR = ~CheckSumR;//У����㷨�� ADDR+CMD+DATA ���ֽ����ȡ����
 
	Write_SPI_OneByte(CheckSumR);//д����
 
	SPI_CS_HIGH();	    //��������
	HAL_Delay(2);
}
 
void ReadAmmeterData(void)
{
	uint32_t temp = 0;
 
	temp = READ_SPI(DeviceID_CMD,DeviceID_BYTE);//оƬID//supposed to be 0x00830200(hex)
	printf("Device_ID=%x(hex)\r\n",(int)temp);
	if(temp != 0x00830200) //��ID
	{
		printf("===================== \r\n");
		printf("Device_ID!=0x00830200 \r\n");
		printf("===================== \r\n");
		return;
	}
 
	temp = READ_SPI(SYSSR_CMD,SYSSR_BYTE);//ϵͳ״̬
	printf("SYSSR=%x(hex)\r\n",(int)temp);
	HAL_Delay(1000);
	
	temp = READ_SPI(UC_CMD,UC_BYTE);//��ȡ��ѹ��Чֵ
	printf(" UC �Ĵ�����Чֵ=%8X\r\n",(int)temp);
	printf(" UC ���Ŵ���Чֵ=%8.2f\r\n",(float)(temp/167772));
	printf(" UC �˿ڴ���Чֵ=%8.2f\r\n",(float)(temp/167772*1.76));
}