/****************SPI 采用端口模拟**********************************/
#include "rn8302b.h"
#include "spi.h"
 
 
/*****************SPI 写单字节**************************/
void Write_SPI_OneByte(uint8_t TxData)
{
	uint8_t Rxdata;
	HAL_SPI_TransmitReceive(&hspi2,&TxData,&Rxdata,1, 1000);
	return ;
}
/*****************SPI 读单字节**************************/
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
 
	SPI_CS_LOW();    // 开启SPI传输
 
	DTemp = (uint8_t)(Address&0x00FF);//ADDR[7:0]
	CheckSumR = DTemp;
	Write_SPI_OneByte(DTemp);
	DTemp = (((uint8_t)(Address >> 4)) & 0xf0) ;//CMD=R/W+AD[10:8]+BL[1:0]+2’h0(MSB+LSB)
	CheckSumR += DTemp;
	Write_SPI_OneByte(DTemp);
 
	HAL_Delay(5);
	drData = 0x00000000;//Read 24bit
 
	for(i=0;i<Data_len;i++)//先发高字节，后发低字节
	{
		DTemp = Read_SPI_OneByte();
		drData = drData<<8;
		drData += DTemp;
		CheckSumR += DTemp;
	}
 
	CheckSumR = ~CheckSumR;//校验和算法： ADDR+CMD+DATA 单字节求和取反。
 
	if (CheckSumR != Read_SPI_OneByte())//比较校验和
	{
		drData = 0xFFFFFFFF;
	}
 
	SPI_CS_HIGH();	  //关闭SPI传输
	HAL_Delay(2);
	return drData;
}
/**************************Write RN8302******************************/
void Write_SPI(uint16_t Address, uint32_t dwData,uint8_t Date_len)
{
	uint8_t i,CheckSumR, DTemp;
 
	SPI_CS_LOW();	 //开启SPI传输
 
	DTemp = (uint8_t)(Address&0x00FF);//
	CheckSumR = DTemp;
	Write_SPI_OneByte(DTemp);//写地址
	DTemp = (((uint8_t)(Address >> 4)) & 0xf0)+0x80 ;
	CheckSumR += DTemp;
	Write_SPI_OneByte(DTemp);//写命令
 
 
	for (i =0 ;i < Date_len;i++)//先发高字节，后发低字节
	{
		DTemp = (uint8_t)(dwData>>(Date_len-1-i)*8);
		Write_SPI_OneByte(DTemp);//写命令
		CheckSumR += DTemp;
	}
 
	CheckSumR = ~CheckSumR;//校验和算法： ADDR+CMD+DATA 单字节求和取反。
 
	Write_SPI_OneByte(CheckSumR);//写命令
 
	SPI_CS_HIGH();	    //结束传输
	HAL_Delay(2);
}
 
void ReadAmmeterData(void)
{
	uint32_t temp = 0;
 
	temp = READ_SPI(DeviceID_CMD,DeviceID_BYTE);//芯片ID//supposed to be 0x00830200(hex)
	printf("Device_ID=%x(hex)\r\n",(int)temp);
	if(temp != 0x00830200) //读ID
	{
		printf("===================== \r\n");
		printf("Device_ID!=0x00830200 \r\n");
		printf("===================== \r\n");
		return;
	}
 
	temp = READ_SPI(SYSSR_CMD,SYSSR_BYTE);//系统状态
	printf("SYSSR=%x(hex)\r\n",(int)temp);
	HAL_Delay(1000);
	
	temp = READ_SPI(UC_CMD,UC_BYTE);//读取电压有效值
	printf(" UC 寄存器有效值=%8X\r\n",(int)temp);
	printf(" UC 引脚处有效值=%8.2f\r\n",(float)(temp/167772));
	printf(" UC 端口处有效值=%8.2f\r\n",(float)(temp/167772*1.76));
}